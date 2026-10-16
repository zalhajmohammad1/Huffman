# Huffman Encoder & Decoder

A C++ file compression utility that implements the Huffman coding algorithm to shrink and restore text files. The program builds a custom binary tree based on character frequencies to generate variable-length prefix codes, saving storage space for repetitive text data.

## Features

* **Interactive CLI:** A simple menu prompt that lets you choose between compression and decompression modes.
* **Dynamic Huffman Tree Generation:** Counts character frequencies at runtime, builds a priority-queue-backed binary tree, and maps characters to optimized bitstrings.
* **Self-Contained Storage Format:** The compressed file embeds its own frequency mapping table in a custom file header so it can be decompressed on any system without external dependencies.

---

## How It Works

### 1. Compression Pipeline
* **File Reading:** Reads the raw input text file directly into a single string buffer.
* **Frequency Mapping:** Analyzes the text to calculate the exact frequency weight of each character.
* **Tree Building:** 
  1. Spawns leaf nodes for each character and pushes them into a priority queue.
  2. Pops the lowest-weight nodes sequentially to construct internal tree nodes.
  3. Pushes internal nodes back into the queue until a single root Huffman Tree is formed.
* **Code Assignment:** Traverses the tree paths (left/right) to generate unique binary strings for each character, saving them in an `unordered_map`.
* **Serialization:** Writes the translation table as a file header into the destination file, followed immediately by the compressed bitstream data.

### 2. Decompression Pipeline
* **Header Parsing:** Reads the embedded translation metadata from the top of the compressed file into a code map.
* **Tree Reconstruction:** Rebuilds the Huffman Tree from the root downward using the mapped bit sequences to re-establish the leaf nodes.
* **Bitstream Decoding:** Streams the compressed data bit-by-bit, traversing the reconstructed tree to pull original characters and dump them directly into the output text file.

---

## Operational Workflow

When you launch the executable, the program guides you through the following setup steps:

```text
[Main Menu] Choose an option:
 1. Compress a file
 2. Decompress a file

If 'Compress' is selected:
  └─► Enter source file path (e.g., input.txt)
  └─► Enter destination file path for compressed data (e.g., compressed.bin)

If 'Decompress' is selected:
  └─► Enter compressed source file path (e.g., compressed.bin)
  └─► Enter destination file path for original text (e.g., restored.txt)
```

---

## Getting Started

### Compilation
Compile your program files using any standard C++ compiler with C++11 support or newer:

```bash
g++ -std=c++11 main.cpp Huffman.cpp -o huffman_utility
```

### Execution
Run the compiled binary to start using the interface:

```bash
./huffman_utility
```
