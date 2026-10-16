#include <string>
#include <queue>
#include <fstream>
#include <unordered_map>

#include "Node.h"
#include "Storage/Storage.h"

#ifndef HUFFMAN_H
#define HUFFMAN_H

/**
 * @class Huffman
 * @brief represents a program that encodes and decodes data by compressing and decompressing pieces of text to reduce
 * the amount of bits used as much as possible
 */
class Huffman {



private:

    Node* root = nullptr;

    Storage storage;


public:
    /**
     * public method that creates the frequency table as the first step into constructing the huffman tree
     * @param user_input // takes in the string data from the user's desired text file
     * @return returns an unordered map with each letter and how many times it occures
     */
    std::unordered_map<char, int> frequencyTable(std::string user_input);

    /**
     * public method that builds the huffman tree
     * @param freq_table // takes in the returned frequency table which creates the leaf nodes from, which then stores them
     * in a priority queue
     * @return returns the root, the last element left in the priority queue
     */
    Node* buildHuffmanTree(std::unordered_map<char, int> freq_table);

    /**
     * public method that creates the binary codes of 1s and 0s by traversing the already built huffman tree
     * @param root // root of the huffman tree
     * @param output // passed by reference map which stored each character along with its unique binary code
     * @param binary // 1s and 0s are stored in here as the tree is being traversed
     */
    void getBinaryCodes(Node* root, std::unordered_map<char, std::string> &output, std::string binary);

    /**
     * public method that compresses the text file by created unique binary codes and a map with pairs of each binary code
     * and its corresponding letter. Then these pairs are put in a file header using 'storage' and it has the binary string
     * added there as well
     * @param infile // the user's desired source of text to compress
     * @param outfile // the user's desired file to store the compressed data (the binary version of the data)
     */
    void compressData(std::string &infile, std::string &outfile);

    /**
     * public method that decompresses the data compressed from before
     * @param infile // the user's desired source of file with compressed data
     * @param outfile // the user's desired file to store the decompressed data (the english version of the data)
     */
    void decompressData(std::string &infile, std::string &outfile);


};






#endif //HUFFMAN_H
