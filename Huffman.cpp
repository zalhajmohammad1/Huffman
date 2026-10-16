#include "Huffman.h"
#include "Node.h"
#include <sstream>
#include <ostream>
//first step is to build a frequency table of the provided user input

std::unordered_map<char, int> Huffman::frequencyTable(std::string user_input) {

    if (user_input.empty()) {throw std::invalid_argument("Please input a valid text");}


    std::unordered_map<char, int> freq_table;


    for (int i = 0; i < user_input.length(); i++) {

        char curr = user_input[i];

        if (freq_table.count(curr) > 0) freq_table[curr]++;

        else freq_table[curr] = 1;

    }
    return freq_table;
}



Node* Huffman::buildHuffmanTree(std::unordered_map<char, int> freq_table) {
    //create priority queue to put values from the frequency table in
    std::priority_queue<Node*, std::vector<Node*>, compareWeights > pq;

    for (std::pair<const char, int>  curr : freq_table) {

        Node* huffmanNode = new Node (curr.first, curr.second);
        pq.push(huffmanNode);

    }

    if (pq.size() >= 2) {
        while (pq.size() > 1) {
            Node* temp1 = pq.top(); pq.pop();
            Node* temp2 = pq.top(); pq.pop();

            Node* internalNode = new Node ('\0', temp1->weight + temp2->weight, temp1, temp2);
            pq.push(internalNode);
        }

    }
    this->root = pq.top();
   return pq.top();

}




void Huffman::getBinaryCodes(Node* root, std::unordered_map<char, std::string> &output, std::string binary) {


    if (root == nullptr) throw std::invalid_argument("root is null");

    if (root->one == nullptr && root->zero == nullptr) {
        output[root->letter] = binary;
    }

    else  {
        getBinaryCodes(root->zero, output, binary + "0");
        getBinaryCodes(root->one, output, binary + "1");
    }

    return;
}



void Huffman::compressData(std::string &infile, std::string &outfile) {

    std::fstream file(infile);

    std::string line;
    std::string user_input;
    while (std::getline(file, line )) {
        user_input += (line + '\n');
    }
    user_input+='\3';



    std::unordered_map<char, std::string> output;
    std::string binaryCode;


    getBinaryCodes(buildHuffmanTree(frequencyTable(user_input)), output, binaryCode);

    std::string result;

    storage.open(outfile, "write");

    std::string data;
    for (std::pair<const char, std::string> curr : output) {
        data.push_back(curr.first);
        data += '\36' + curr.second + '\36';
    }



    storage.setHeader(data);
    for (char curr : user_input) {

        storage.insert(output[curr]);
    }

    storage.close();

}





void Huffman::decompressData(std::string &infile, std::string &outfile) {
    storage.open(infile, "read");


    std::string line;


    std::unordered_map<char, std::string> output;

    std::string header = storage.getHeader();
    std::stringstream ss(header);
    while(getline(ss, line, '\36')) {

        char curr = line[0];
        getline(ss, line, '\36');
        std::string temp = line;

        output[curr] = temp; //puts the header info in a map


    }

    root  = new Node('\0', 0);

    for (std::pair<const char, std::string> curr : output) {

        Node* temp = root;

        for (char curr2 : curr.second) {
            if (curr2 == '0') {
                if(temp->zero == nullptr) temp->zero = new Node ('\0', 0, nullptr, nullptr);
                temp = temp->zero;
            }
            else {
                if(temp->one == nullptr) temp->one = new Node ('\0', 0, nullptr, nullptr);
                temp = temp->one;
            }

        }

        temp->letter = curr.first;

    }
    std::ofstream file(outfile);
    std::string letters;
    std::string result;
    Node* traverse = root;
    while (storage.extract(result)) {


        for (int i = 0; i < result.length(); i++) {
            if (result[i] == '0') {
                traverse = traverse->zero;
            }
            else {
                traverse = traverse->one;
            }
            if (traverse->letter != '\0') {
                if(traverse->letter == '\3') {
                    file << letters;
                    return;
                }
                 letters += traverse->letter;
                traverse = root;
            }
        }
    }
    file << letters;
    storage.close();
}









