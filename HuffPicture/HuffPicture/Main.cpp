#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"compress.h"
#include"uncompress.h"

using namespace std;
constexpr auto MAX = 256;

int main() {
	char fileName[MAX];
	char choice[MAX];
	int result;
	cout << "========== Huffman File compress ==========" << endl;
	cout << "Example file name : Pic.bmp" << endl;
	cout << "1.Compress file" << endl;
	cout << "2.Decompress file" << endl;
	cout << "0.Exit" << endl;
	while (true) {
		cout << endl << "Enter your choice:";
		cin >> choice;

		if (choice[0] == '1' || choice[0] == '2') {
			do {
				cout << "Please enter the file name:";
				cin >> fileName;
				FILE* f = fopen(fileName, "rb");
				if (f != nullptr) {
					fclose(f);
					break;
				}
				cout << "Can not open file :" << fileName << endl;
			} while (true);
		}

		switch (choice[0])
		{
		case '1':
			// Compress file
			result=Compress(fileName);
			if (result == 0) {
				cout << "Compress success" << endl;
			}
			else
			{
				cout << "Compress error" << endl;
			}
			break;
		case '2':
			// DeCompress file
			result=DeCompress(fileName);
			if (result == 0) {
				cout << "DeCompress success" << endl;
			}
			else
			{
				cout << "DeCompress error" << endl;
			}
			break;
		case '0':
			cout << "Exit system" << endl;
			return 0;
		default:
			cout << "Wrong choice" << endl;
			break;
		}
	}

	return 0;
}
