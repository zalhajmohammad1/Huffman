***How to use the program:***
 
The program starts with a prompt for if the user wants to compress or decompress

a) if user wants to compress, they are asked to chose from which file path they want to compress, then are asked to chose
the file path to store the compressed data in 

b) if the user wants to decompress, they are asked to choose the file source from where to decompress, then are asked for 
the file to store the decompressed data in.


***How the program is implemented:***

*a) compression:*

Text data is processed from the file, then put into a string.

based off the text data, a frequency table is created. The frequency table is then used to create base leaf nodes, with 
the letters and weight, then they are all pushed in a priority queue. 

From there the internal nodes are created from the base
nodes from the priority queue. 

Internal nodes are pushed into the priority queue as well.

The huffman tree is now created. 

After this the huffman tree is traversed left and right to compute the unique binary string for each character.

This is all saved in an unordered map. 

After this table is stored into the storage object's header.

the compressed data is now saved in the user's desired file.


*b) decompression:*

Text data is processed from the file with the compressed data from the header in the storage object.

The data is then stored in a map. (each letter and its unique binary code).

A new huffman tree is built from the root, until it reaches the bottom and builds the leaf nodes with the english letters

We then traverse the tree to grab all the english letters and store them into the user's desired file 
