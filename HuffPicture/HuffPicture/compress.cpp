#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstring>
#include"Huffman.h"
#include"compress.h"

namespace compress {
	const int N = 256, M = 2 * N - 1;

	HTNode pHT[2 * N + 1];
	HuffmanCode pHC[N + 1];

	struct HEAD head;
}
using namespace std;
using namespace compress;

// Read file,save file info,and so on
bool InitHead(const char* infile, HEAD& sHead, HuffmanTree pHT, HuffmanCode pHC[]);

// Show Head data
void ShowHead(HEAD ahead);


// Recoding str to byte
char Str2byte(const char* pBinStr);

// Encoding and compress
char* Encode(const char* pFilename, const HuffmanCode pHC[], char* pBuffer, const int nSize);

// Write the compress data to file
int WriteFile(const char* pFilename, const HEAD sHead, const char* pBuffer, const int nSize);

void showDetial();

int Compress(const char* pFilename)
{
	InitHead(pFilename, head, pHT,pHC);

	createHuffmanTree(pHT, 256);

	HuffmanCoding(pHT, pHC, 256);


	int nSize = 0;

	for (int i = 1; i <= 256; i++)
	{
		nSize += head.weight[i - 1] * strlen(pHC[i].code.bits + pHC[i].code.start);
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;


	char* pBuffer = nullptr;

	pBuffer=Encode(pFilename, pHC, pBuffer, nSize);
	if (!pBuffer)
	{
		return ERROR;
	}

	char compressFile[MAX];
	strcpy(compressFile, pFilename);
	strcat(compressFile, ".huf");

	WriteFile(compressFile, head, pBuffer, nSize);

	//showDetial();

	// Information output start
	cout << head.length << " Byte" << endl;
	cout << "Output compress file:" << compressFile << endl;
	cout << nSize << " Byte" << endl;

	cout << "Compress percentage: " << (double)nSize / (double)head.length * 100 << "%" << endl;

	// Information output end

	if (pBuffer) {
		delete[] pBuffer;
	}
	return SUCCESS;
}

int WriteFile(const char* pFilename, const HEAD sHead, const char* pBuffer, const int nSize)
{
	FILE* out = fopen(pFilename, "wb");
	if (out == NULL) {
		return ERROR;
	}

	fwrite(&sHead, sizeof(HEAD), 1, out);
	fwrite(pBuffer,nSize,1,out);
	fclose(out);
	return SUCCESS;
}

char* Encode(const char* pFilename, const HuffmanCode pHC[], char* pBuffer, const int nSize)
{
	FILE* in;
	in = fopen(pFilename, "rb");

	// Build a cashe area
	pBuffer = new char[nSize+1];
	if (!pBuffer)
	{
		cout << "Failed to build a cashe area" << endl;
		return NULL;
	}
	char cd[SIZE] = { 0 };
	int pos = 0;
	int ch;

	// Scan the file,compress it with the HuffmanCode,save the compress result to cashe
	while ((ch = fgetc(in)) != EOF) {
		strcat(cd,pHC[ch+1].code.bits + pHC[ch+1].code.start);

		while (strlen(cd) >= 8)
		{
			// Cut up 8 char from the left of the cd,and the recode to byte
			pBuffer[pos++] = Str2byte(cd);

			// Move the str 8 char to left
			for (int i = 0; i < SIZE-8; i++)
			{
				cd[i] = cd[i + 8];
			}
		}
	}
	if (strlen(cd) > 0)
	{
		pBuffer[pos++] = Str2byte(cd);
	}

	fclose(in);
	return pBuffer;
}

void showDetial() {
	ShowHead(head);
	ShowHuffmanTree(pHT, 256);
	TestHufTreeN(N * 2 - 1, pHT);
	cout << endl;
	cout << endl << "Huffman code output" << endl;
	TestHufCode(N * 2 - 1, pHT, pHC);
}

bool InitHead(const char* infile, HEAD& sHead, HuffmanTree pHT, HuffmanCode pHC[])
{
	int ch;
	FILE* in;
	in = fopen(infile, "rb");
	if (in == nullptr) {
		return false;
	}

	strcpy(sHead.type, "huf");

	// Scan the file and get the right
	while ((ch = getc(in)) != EOF)
	{
		sHead.weight[ch]++;
		sHead.length++;
	}

	// init the pHT
	for (int i = 0; i < 256; i++)
	{
		pHT[i + 1].weight = sHead.weight[i];
		pHT[i + 1].parent = 0;
		pHT[i + 1].lchild = 0;
		pHT[i + 1].rchild = 0;
		pHC[i + 1].symbol = i + 1;
	}

	fclose(in);
	return true;
}

void ShowHead(HEAD ahead) {
	cout << "The right of each char of Orignal list:" << endl;
	cout << "Byte" << " " << "Weight" << endl;
	for (int i = 0; i < 256; i++)
	{
		if (i == 200) {
			cout << "......" << endl;
		}
		if (i < 6 || i>251) {
			printf("0x%02X %d\n", i, head.weight[i]);
		}
	}
	cout << "File Length = " << head.length << endl;
	cout << endl;
}

char Str2byte(const char* pBinStr)
{
	char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;	// move left 1
		if (pBinStr[i] == '1')
		{
			b = b | 0x01;
		}
	}
	return b;
}
