#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include"Huffman.h"
#include"uncompress.h"

namespace uncompress {
	const int N = 256, M = 2 * N - 1;
	HTNode pHT[2 * N + 1];

	struct HEAD head;
}

using namespace std;
using namespace uncompress;

// read the file and init the head file
int InitHead(const char* pFilename, HEAD& sHead, HuffmanTree pHT);

void ShowReadHead(HEAD ahead);

// Encoding and DeCompress
char* ReEncode(const char* pFilename, const HuffmanTree pHT, char* pBuffer, const int nSize);


// Write the compress data to file
int ReWriteFile(const char* pFilename,const char* pBuffer, const int nSize);

// Byte to char[]
void Byte2Char(char* pBinStr, int pBin);

// deCompress file
int DeCompress(const char* pFilename) {
	InitHead(pFilename, head, pHT);

	//ShowReadHead(head);

	createHuffmanTree(pHT, 256);

	int nSize = head.length;

	char* pBuffer = nullptr;

	char compressFile[MAX];
	char DeCompressFile[MAX] = { "Re" };
	strcpy(compressFile, pFilename);
	int len = strlen(compressFile);
	for (int i = len-4; i < len; i++)
	{
		compressFile[i] = '\0';
	}
	strcat(DeCompressFile, compressFile);
	cout << "DeCompress file:" << DeCompressFile << endl;

	pBuffer = ReEncode(pFilename, pHT, pBuffer, nSize);
	if (!pBuffer)
	{
		return ERROR;
	}

	ReWriteFile(DeCompressFile, pBuffer, nSize);

	return SUCCESS;
}

int ReWriteFile(const char* pFilename,const char* pBuffer, const int nSize)
{
	FILE* out = fopen(pFilename, "wb");
	if (out == NULL) {
		return ERROR;
	}

	fwrite(pBuffer, nSize, 1, out);
	fclose(out);
	return SUCCESS;
	return SUCCESS;
}

char* ReEncode(const char* pFilename, const HuffmanTree pHT, char* pBuffer, const int nSize)
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
	char cd[SIZE*2] = { 0 };
	char mid[SIZE];
	int pos = 0;
	int ch;
	int byte;

	fseek(in, sizeof(HEAD), 0);

	// Scan the file,compress it with the HuffmanCode,save the compress result to cashe
	while ((ch = fgetc(in)) != EOF) {
		Byte2Char(mid, ch);

		strcat(cd, mid);

		while (strlen(cd) >= 256)
		{
			int move = 0,root=256*2-1;

			while (pHT[root].lchild != 0 && pHT[root].rchild != 0)
			{
				if (cd[move] == '1') {
					root = pHT[root].lchild;
				}
				else {
					root = pHT[root].rchild;
				}
				move++;
			}
			byte = root-1;


			// Cut up 8 char from the left of the cd,and the recode to byte
			pBuffer[pos++] = byte;

			// Move the str 8 char to left
			for (int i = 0; i < SIZE*2 - move; i++)
			{
				cd[i] = cd[i + move];
			}
		}
	}
	if (strlen(cd) > 0)
	{
		int move = 0, root = 256 * 2 - 1;

		while (pHT[root].lchild != 0 && pHT[root].rchild != 0)
		{
			if (cd[move] == '1') {
				root = pHT[root].lchild;
			}
			else {
				root = pHT[root].rchild;
			}
			move++;
		}
		byte = root - 1;

		// Cut up 8 char from the left of the cd,and the recode to byte
		pBuffer[pos++] = byte;
	}

	fclose(in);

	return pBuffer;
}

void Byte2Char(char* pBinStr, int pBin)
{
	for (int i = 0; i <8; i++)
	{
		if (pBin % 2 == 1) {
			pBinStr[7 - i] = '1';
		}
		else
		{
			pBinStr[7 - i] = '0';
		}
		pBin = pBin >> 1;	// move right 1
	}
	pBinStr[8] = '\0';
}

int InitHead(const char* pFilename, HEAD& sHead, HuffmanTree pHT)
{
	FILE* in;
	in = fopen(pFilename, "rb");
	if (in == nullptr) {
		return ERROR;
	}
	fread(&head, sizeof(HEAD), 1, in);

	// init the pHT
	for (int i = 0; i < 256; i++)
	{
		pHT[i + 1].weight = sHead.weight[i];
		pHT[i + 1].parent = 0;
		pHT[i + 1].lchild = 0;
		pHT[i + 1].rchild = 0;
	}

	fclose(in);
	return true;
}

void ShowReadHead(HEAD ahead) {
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