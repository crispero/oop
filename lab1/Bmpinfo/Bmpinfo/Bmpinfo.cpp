#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Bmpinfo.h"

using namespace std;

const int BMP_TYPE_CODE = 0x4D42;
const int EIGHT_BITS_PER_PIXEL = 8;
const string INVALID_ARGUMENTS_COUNT = "Invalid arguments count\nUsage: bmpinfo.exe <input file name>\n";
const string ERROR_OPEN_FILE = "Unable to open file for reading\n";
const string NOT_BMP_FILE = " is not BMP file\n";

bool CollectBpmInfo(ifstream& fin, BITMAPFILEHEADER &fileHeader, BITMAPINFOHEADER &fileInfoHeader)
{
	read(fin, fileHeader.bfType, sizeof(fileHeader.bfType));

	if (fileHeader.bfType != BMP_TYPE_CODE)
	{
		return false;
	} 

	read(fin, fileHeader.bfSize, sizeof(fileHeader.bfSize));
	read(fin, fileHeader.bfReserved1, sizeof(fileHeader.bfReserved1));
	read(fin, fileHeader.bfReserved2, sizeof(fileHeader.bfReserved2));
	read(fin, fileHeader.bfOffBits, sizeof(fileHeader.bfOffBits)); 

	read(fin, fileInfoHeader.biSize, sizeof(fileInfoHeader.biSize));
	read(fin, fileInfoHeader.biWidth, sizeof(fileInfoHeader.biWidth));
	read(fin, fileInfoHeader.biHeight, sizeof(fileInfoHeader.biHeight));
	read(fin, fileInfoHeader.biPlanes, sizeof(fileInfoHeader.biPlanes));
	read(fin, fileInfoHeader.biBitCount, sizeof(fileInfoHeader.biBitCount));
	read(fin, fileInfoHeader.biCompression, sizeof(fileInfoHeader.biCompression));
	read(fin, fileInfoHeader.biSizeImage, sizeof(fileInfoHeader.biSizeImage));
	read(fin, fileInfoHeader.biXPelsPerMeter, sizeof(fileInfoHeader.biXPelsPerMeter));
	read(fin, fileInfoHeader.biYPelsPerMeter, sizeof(fileInfoHeader.biYPelsPerMeter));
	read(fin, fileInfoHeader.biClrUsed, sizeof(fileInfoHeader.biClrUsed));
	read(fin, fileInfoHeader.biClrImportant, sizeof(fileInfoHeader.biClrImportant));

	return true;
}

void PrintBmpInfo(BITMAPINFOHEADER &fileInfoHeader)
{
	cout << "biWidth: " << fileInfoHeader.biWidth << endl;
	cout << "biHeight: " << fileInfoHeader.biHeight << endl;
	cout << "biBitCount: " << fileInfoHeader.biBitCount << endl;
	if (fileInfoHeader.biBitCount <= EIGHT_BITS_PER_PIXEL)
	{
		cout << "biClrUsed: " << fileInfoHeader.biClrUsed << endl;
	}
	cout << "biSizeImage: " << fileInfoHeader.biSizeImage << endl;
}

int main(int argc, char* argv[])
{
	int parametersNumber = argc;

	if (parametersNumber != 2)
	{
		cout << INVALID_ARGUMENTS_COUNT;
		return 1;
	}

	string fileName = argv[1];
	ifstream fin(fileName, ios::binary);

	if (!fin.is_open())
	{
		cout << ERROR_OPEN_FILE;
		return 1;
	}

	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER fileInfoHeader;

	if (!CollectBpmInfo(fin, fileHeader, fileInfoHeader))
	{
		cout << fileName << NOT_BMP_FILE;
		return 1;
	}

	PrintBmpInfo(fileInfoHeader);
	
	return 0;
}
