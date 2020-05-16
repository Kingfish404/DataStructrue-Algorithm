#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H

constexpr auto ERROR = 1;
constexpr auto SUCCESS = 0;
constexpr auto MAX = 256;
constexpr auto SIZE = 256;

// File head info
struct HEAD
{
	char type[4];				// File type
	int length = 0;				// Orginal file length
	int weight[256+1] = { 0 };	// Right of Number
};

// Huffman tree's node
struct HTNode
{
	int weight;	// right
	int parent; // node's parent
	int lchild;	// left child
	int rchild;	// right child
};

typedef HTNode* HuffmanTree;

// Huffman Code Node
struct codetype
{
	int start;
	char bits[256] = { '0' };
};

// Huffman Code
struct HuffmanCode
{
	unsigned char symbol;
	codetype code;
};

// Create Huffman Tree
int createHuffmanTree(HuffmanTree pHT, int n);

// Find the min x1 and min x2 right node
void Select(HuffmanTree pHT, int nSize, int& x1, int& x2);

//	TestHufTree 
void TestHufTreeN(int root, HuffmanTree pHT);

//	TestHufCode
void TestHufCode(int root, HuffmanTree pHT, HuffmanCode pHC[]);

// Show list of Huffman Tree
void ShowHuffmanTree(HuffmanTree pHT, int n);

// Coding Huffman code
void HuffmanCoding(HuffmanTree pHT, HuffmanCode pHC[], int n);

#endif // !HUFFMAN_H