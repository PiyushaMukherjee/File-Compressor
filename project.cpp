//Project Title : File Compression
//Date : 17/11/23
#include <bits/stdc++.h>
using namespace std;

// Node Structure
struct Node {
    char character;
    int frequency;
    struct Node *left, *right;

    Node(char c, int f) : character(c), frequency(f),left(nullptr),right(nullptr) {}

    // Overloading the < operator for min heap
    bool operator<(const Node &other) const {
        return frequency > other.frequency;
    }
};

// Author : Krish Nariya
// Function to build min-heap with data given
// chr[] - array of unique characters
// freq[] - array of frequencies of unique characters
priority_queue<Node> buildMinHeap(vector<char> &chr, vector<int> &freq) {
    priority_queue<Node> min_Heap;
    for (int i = 0; i < chr.size(); ++i) {
	    Node* node = new Node(chr[i],freq[i]);
	    min_Heap.push(*node);
    }
    return min_Heap;
}

// Function to build huffman tree
Node* buildHuffman(priority_queue<Node> minHeap){
	while(minHeap.size() > 1){
		Node *left = new Node(minHeap.top());
		minHeap.pop();
		Node *right = new Node(minHeap.top());
		minHeap.pop();

		Node* mergedNode = new Node('$', left->frequency+right->frequency);
		mergedNode->left = left;
		mergedNode->right = right;
		minHeap.push(*mergedNode);
	}
	return new Node(minHeap.top());
}
//--------END--------

// Author : Piyusha
// Function to print huffman codes
unordered_map<char,string> huffmanCodes;
unordered_map<char,string> HuffmanCodes(Node* root,string code=""){
	if(root==nullptr){
		return huffmanCodes;
	}
	if(root->character!='$'){
		huffmanCodes[root->character] = code;
	}
	HuffmanCodes(root->left,code+"0");
	HuffmanCodes(root->right,code+"1");
	return huffmanCodes;
}
//--------END-------
// Author : Dave
// Function to substitude the huffman codes(compressor)
void compressor(string f_name,const std::string& outputFileName) {
    // Open the output file for writing
    fstream inp_file;
    inp_file.open(f_name,ios::in);
    
    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file!" << std::endl;
        return;
    }

    // Write the size of the Huffman codes map to the output file
    size_t huffmanCodesSize = huffmanCodes.size();
    outputFile.write(reinterpret_cast<const char*>(&huffmanCodesSize), sizeof(size_t));

    // Write the Huffman codes to the output file
    for (const auto& entry : huffmanCodes) {
        outputFile.put(entry.first);  // Write the character
        outputFile.put(entry.second.length());  // Write the code length
        outputFile << entry.second;  // Write the code
    }

    // Write the separator between Huffman codes and encoded text
    outputFile.put('\n');

    // Write the encoded text to the output file using bit manipulation
    string encodedBits;
    string text;
    while(inp_file){
    	getline(inp_file,text);
    	for (char ch : text) {
        	encodedBits += huffmanCodes.at(ch);
    	}
    }

    // Calculate the padding (number of bits to be added)
    size_t padding = 8 - (encodedBits.length() % 8);
    encodedBits += std::string(padding, '0');  // Pad with zeros

    // Write the size of the encoded text to the output file
    size_t encodedBitsSize = encodedBits.size();
    outputFile.write(reinterpret_cast<const char*>(&encodedBitsSize), sizeof(size_t));

    // Write the encoded text to the output file using bytes
    for (size_t i = 0; i < encodedBitsSize; i += 8) {
        std::bitset<8> bits(encodedBits.substr(i, 8));
        outputFile.put(bits.to_ulong());
    }

    // Close the output file
    outputFile.close();

    std::cout << "File compressed successfully." << std::endl;
}
//--------END---------
// Author : Nivedha
// Function to decompress the text file
// it takes the file to be decompressed as argument
void decompressor(string& inputFileName) {
    // Open the input file for reading
	// ifstream module for input file handling
    std::ifstream inputFile(inputFileName, std::ios::binary);
	//checking existence of file
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file!" << std::endl;
        return;
    }

    // Read the size of the Huffman codes map from the input file
    size_t huffmanCodesSize;
    inputFile.read(reinterpret_cast<char*>(&huffmanCodesSize), sizeof(size_t));

    // Read the Huffman codes from the input file
    std::unordered_map<char, std::string> huffmanCodes;
    for (size_t i = 0; i < huffmanCodesSize; ++i) {
        char character;
        inputFile.get(character);

        char codeLength;
        inputFile.get(codeLength);

        std::string code;
        for (int j = 0; j < codeLength; ++j) {
            code += inputFile.get();
        }

        huffmanCodes[character] = code;
    }

    // Read the separator between Huffman codes and encoded text
    inputFile.get();

    // Read the size of the encoded text from the input file
    size_t encodedBitsSize;
    inputFile.read(reinterpret_cast<char*>(&encodedBitsSize), sizeof(size_t));

    // Read the encoded text from the input file using bytes
    std::string encodedBits;
    char byte;
    while (inputFile.get(byte)) {
        encodedBits += std::bitset<8>(byte).to_string();
    }

    // Truncate to the actual size
    encodedBits.resize(encodedBitsSize);

    // Close the input file
    inputFile.close();

    // Decode the text
    std::string decodedText;
    std::string currentCode;

    for (char bit : encodedBits) {
        currentCode += bit;
        for (const auto& entry : huffmanCodes) {
            if (entry.second == currentCode) {
                decodedText += entry.first;
                currentCode.clear();
                break;
            }
        }
    }
    fstream out_file;
    out_file.open("decompressed.txt",ios::out);
    out_file<<decodedText;
    cout << "File decompressed successfully." <<endl;
}

// --------END--------

// Author : Aakarsh Lohani
// UTILITY FUNCTIONS
// Function to store unique characters in a character array
vector<char> buildChar(unordered_map<char, int> map) {
    vector<char> unique_chars;
    for (auto pair : map) {
        unique_chars.push_back(pair.first);
    }
    return unique_chars;
}

// Function to store frequencies of unique characters in an array
vector<int> buildFreq(unordered_map<char, int> map) {
    vector<int> unique_freq;
    for (auto pair : map) {
        unique_freq.push_back(pair.second);
    }
    return unique_freq;
}

// Function to count unique characters and frequencies
unordered_map<char, int> countChar(string& file_name) {
    unordered_map<char, int> charCount;

    fstream file;
    file.open(file_name, ios::in);

    if (!file) {
        cout << "check file name";
        return charCount;
    }

    while (file) {
        string line;
        getline(file, line);

        
        for (char c : line) {
            if (charCount.find(c) == charCount.end()) {
                charCount[c] = 1;
            } else {
                charCount[c]++;
            }
        }
    }
    return charCount;
}

// --------END--------

// Author : Priyam
// integration of all the functions and debugging
int main() {
    int ch;
    string f_name;
    string file;

    cout << "x-x-x-x-x-x-x-x-x" << endl;
    cout << "|     MENU      |" << endl;
    cout << "x-x-x-x-x-x-x-x-x" << endl;
    cout << "| 1.Compress    |" << endl;
    cout << "| 2.Decompress  |" << endl;
    cout << "x-x-x-x-x-x-x-x-x" << endl;
    cout << "Enter choice :";
    cin >> ch;

    if (ch == 1) {
        cout << "Enter Filename :";
        cin >> f_name;

        // Process1 : count unique characters and their frequencies
        unordered_map<char, int> result = countChar(f_name);

        // Process2 : store unique characters and their frequencies in two separate arrays
        vector<char> uniqueChars = buildChar(result);
        vector<int> uniqueFreq = buildFreq(result);

        // Process3 : sort the above two data with min-heap
       	priority_queue<Node> minHeap = buildMinHeap(uniqueChars,uniqueFreq);
        
        // Process4 : build huffman tree from minHeap
	Node *root = buildHuffman(minHeap);

	// Process5 : generate huffman codes

	unordered_map<char,string> temp = HuffmanCodes(root,"");
	
	for(const auto& it : temp){
		cout<<it.first<<" "<<it.second<<endl;
	}
	
	// Process6 : substitute huffman codes(compressor)
	compressor(f_name,"output.txt");
	
    }
    if(ch == 2){
    	cout<<"Enter filename: ";
    	cin>>file;
    	cout<<"Decompressing the file..."<<endl;
    	// Process7 : decompress
    	decompressor(file);
    }
    return 0;
}