# File_Compressor
A text file compression tool based on Huffman encoding algorithm. The tool enjoys the benefit given by huffman encoding algorithm, i.e, Lossless compression.
We can compress the data upto 30-40% without any loss in the data, saving 60-70% space. This comes very handy in case of cloud sharing. 
# UseCase
Imagine you have to send a 1GB data file, and you only have 500MB of internet data. No need to worry! Huffman encoding algorithm got you covered. After compression the file's size becomes somewhere around 300MB(not guaranteed) which can now be safely sent without any problems.
# About the Algorithm
Huffman coding, an optimal prefix-free binary code, is a renowned data compression technique designed by David A. Huffman in 1952. This ingenious algorithm is based on the principle of assigning shorter codes to frequently occurring symbols in a dataset, resulting in more efficient representation and compression. Huffman encoding achieves this by constructing a binary tree, known as the Huffman tree, where each leaf node corresponds to a symbol and is assigned a binary code based on its frequency in the input data. The algorithm employs a priority queue to efficiently merge nodes with the lowest frequencies until a single root node is formed. The resulting binary codes exhibit the desirable property of being prefix-free, ensuring that no code is a prefix of another. This characteristic simplifies decoding, as it enables unambiguous identification of each symbol in the compressed data.
It finds its unique applications in the real-world. Notably, in file compression algorithms such as ZIP and in network protocols where efficient data transmission is crucial.
# Merits of the tool
## Lossless Compression:
Huffman coding is a lossless compression algorithm, meaning that the decompressed data is identical to the original.
## Widely Used:
Huffman coding is widely adopted and implemented in various applications, including file compression utilities (e.g., ZIP) and network protocols, attesting to its effectiveness.
## Simple and Fast Decoding:
The decoding process in Huffman coding is straightforward and fast. The prefix-free nature of the codes ensures unambiguous decoding, making it efficient for both compression and decompression.
# Demerits of the tool
## Compression Overhead for Small Files:
For very small files or files with limited redundancy, the overhead introduced by the Huffman coding tree might result in a compressed file size that is larger than the original.
## Complexity in Real-Time Applications:
While Huffman coding is generally efficient, its adaptive nature and tree-building process might introduce complexities in real-time applications where encoding and decoding need to be performed quickly.
## Limited Compression Improvement with ASCII Text:
For ASCII text, where each character already requires 8 bits, the potential for compression improvement is limited compared to scenarios where symbol frequencies vary widely.

# Getting Started
## Step1 : 
Clone the repository(make sure git is installed)

        git clone https://github.com/dave1725/File_compressor.git

## Step2 : 
Compile the project source file using g++ or any compiler
Make sure MingW is installed for windows and OSX.
+ For LINUX
For linux install g++.
        
        apt-get install g++
  
Compiling the project.

        g++ project.cpp - o project

Executing the project.

        ./project

+ For Windows
Install MinGW from https://sourceforge.net/projects/mingw/

Compiling the project.

        g++ project.cpp -o project

Executing the project.

        ./project
        
## Step3 : 
Finally! Run the project executable file.

# Members
+ Krish Nariya
+ Aakarsh Lohani
+ Piyusha Mukherjee
+ Nivedha Sriram
+ Priyam Kotnala
+ Dave Meshak

# References
+ https://www.geeksforgeeks.org/text-file-compression-and-decompression-using-huffman-coding/
+ https://codereview.stackexchange.com/questions/195251/compression-decompression-using-huffman-coding-algorithm
+ https://www.programiz.com/dsa/huffman-coding

# License
This project is licensed under MIT license - Kindly refer the LICENSE file for details.


