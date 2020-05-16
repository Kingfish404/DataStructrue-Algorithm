#include<iostream>
#include<cstdio>
#include"Huffman.h"

using namespace std;

int createHuffmanTree(HuffmanTree pHT, int n)	// n=256
{
	int x1, x2;
	for (int i = n + 1; i <= n * 2 - 1; i++)
	{
		Select(pHT, i - 1, x1, x2);
		pHT[i].lchild = x1;
		pHT[i].rchild = x2;
		pHT[i].weight = pHT[x1].weight + pHT[x2].weight;
		pHT[x1].parent = i;
		pHT[x2].parent = i;
	}

	return 0;
}


void Select(HuffmanTree pHT, int nSize, int& x1, int& x2)
{
	int i;
	long long v1;	// 1st min
	long long v2;	// 2nd min
	v1 = v2 = 0xFFFFFFFFFFF;
	for (i = 1; i <= nSize; i++)
	{
		if (pHT[i].parent == 0) {
			if (pHT[i].weight < v1) {
				v2 = v1;
				v1 = pHT[i].weight;
				x2 = x1;
				x1 = i;
			}
			else if (pHT[i].weight < v2) {
				v2 = pHT[i].weight;
				x2 = i;
			}
		}
	}
}



void HuffmanCoding(HuffmanTree pHT, HuffmanCode pHC[], int n)
{
	for (int i = 1; i <= n; i++)
	{
		pHC[i].code.start = n + 1;
		int s = i, f = pHT[i].parent;
		while (f != 0)
		{
			pHC[i].code.start--;
			if (pHT[f].lchild == s) {
				pHC[i].code.bits[pHC[i].code.start] = '1';
			}
			else
			{
				pHC[i].code.bits[pHC[i].code.start] = '0';
			}
			s = f;
			f = pHT[s].parent;
		}
	}
}


void TestHufTreeN(int root, HuffmanTree pHT)
{
	cout << pHT[root].weight << " ";
	if (pHT[root].lchild != 0)
	{
		TestHufTreeN(pHT[root].lchild, pHT);
	}
	if (pHT[root].rchild != 0)
	{
		TestHufTreeN(pHT[root].rchild, pHT);
	}
}

void TestHufCode(int root, HuffmanTree pHT, HuffmanCode pHC[])
{
	if (pHT[root].lchild == 0 && pHT[root].rchild == 0)
	{
		if (root == 100) {
			cout << "......" << endl;
		}
		if (root < 5 || root>252) {
			printf("0x%02X %s\n", root - 1, pHC[root].code.bits + pHC[root].code.start);
		}
	}
	if (pHT[root].lchild)
	{
		TestHufCode(pHT[root].lchild, pHT,pHC);
	}
	if (pHT[root].rchild)
	{
		TestHufCode(pHT[root].rchild, pHT, pHC);
	}
}

void ShowHuffmanTree(HuffmanTree pHT, int n)
{
	cout << "The info of each of Huffman Tree's node" << endl;
	cout << "Byte    Wegith  Parent Lchild Rchild" << endl;
	for (int i = 1; i <= n * 2 - 1; i++)
	{
		if (i == 100) {
			cout << "......" << endl;
		}
		if (i < 6 || i>n * 2 - 5) {
			printf("pHT[%2d] %6d %5d %5d %5d\n", i, pHT[i].weight, pHT[i].parent, pHT[i].lchild, pHT[i].rchild);
		}
	}
	cout << endl;
}