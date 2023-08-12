#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

/*
Compression format:
First 4 bytes - Number of bits for Huffman tree
Next X bytes - Huffman tree
Next X bytes - Encoded text
*/
void huffmanEncode(std::string fileName) {
    const int ALPHABET_SIZE = 256;

    std::ifstream fin(fileName);

    // Get file contents
    std::ifstream t("file.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string fileContents = buffer.str();

    // Count frequency of each character
    int charCounts[ALPHABET_SIZE];
    std::memset(charCounts, 0, ALPHABET_SIZE * sizeof(int));

    for (char c : fileContents) {
        charCounts[c]++;
    }

    std::sort(charCounts, charCounts + ALPHABET_SIZE);

    // Build huffman tree
}

int main() {


}