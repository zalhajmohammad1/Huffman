#ifndef NODE_H
#define NODE_H
#include <string>

//template<class DataType>

/**
 * @struct Node
 * defines each huffman tree node
 */
struct Node {

public:
    /**
     * public parameterized constructor that constructs the base leave nodes, that are then pushed in the priority queue
     * @param letter // takes in the letter during the process of building the huffman tree from the frequency table
     * @param weight // the amount of times the letter occures from the user's input, can be extracted from the frequency table
     * as well
     */
    Node(char letter, int weight) {
        this->letter = letter;
        this->weight = weight;
        this->zero = nullptr;
        this->one = nullptr;
        this->code = "";

    }


    /**
     * public parameterized constructor that constructs the internal huffman nodes that are as well pushed into the
     * priorty queue
     * @param letter // empty character
     * @param weight // the first 2 nodes' weights added together from the priority queue
     * @param zero // one of the first 2 least nodes in the priority queue that's made child to the internal huffman node
     * @param one // the second least node in the priority queue that's made child to the internal huffman node
     */
    Node(char letter, int weight, Node *zero, Node *one) {
        this->letter = letter;
        this->weight = weight;
        this->zero = zero;
        this->one = one;
        this->code = "";
    }

    char letter;        // letter character to be stored
    Node* zero;
    Node* one;
    int weight;         // count for how many times the character is used in the file
    std::string code;   // binary string code created from the huffman tree
};


#endif //NODE_H


#ifndef COMPARE_WEIGHTS
#define COMPARE_WEIGHTS
/**
 * Class needed for the to compare Nodes in the priority queue
 * @see https://www.geeksforgeeks.org/stl-priority-queue-for-structure-or-class/
 */

//template<class DataType>

/**
 * @struct compareWeights
 * @brief used to organize the nodes in the priority queue in ascending order based off of their weights
 */
struct compareWeights{
    /**
     * overloaded () operator
     * @param lhs // left hand side node
     * @param rhs // right hand side node
     * @return returns true if the lhs node's weight is greater than the rhs node's weight
     */
    bool operator()(Node* const& lhs, Node* const& rhs){
        return lhs->weight > rhs->weight;
    }
};
#endif // COMPARE_WEIGHTS