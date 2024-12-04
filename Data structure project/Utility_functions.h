#pragma once
#include <iostream>
#include <fstream>
#include "String.h"
void replaceLine(String filename, int l, String replace)
{
	ifstream file(filename.getdata());
	String arr[4];
	char* buffer = new char[1000];
	for (int i = 0;i < 4;i++)
	{
		file.getline(buffer, 1000);
		if (i == l - 1)
		{
			arr[i] = replace;
		}
		else
		{
			arr[i] = buffer;
		}
	}
	file.close();

	ofstream updated_file(filename.getdata());

	for (int i = 0;i < 4;i++)
	{
		updated_file << arr[i] << '\n';
	}
	updated_file.close();
	return;
}

char* getLineFile(String filename, int l)
{
	ifstream file(filename.getdata());
	char* buffer = new char[1000];
	for (int i = 0;i < l;i++)
	{
		file.getline(buffer, 1000);
	}
	return buffer;
}
int stringToInt(String& s) {
	int result = 0;
	int index = 0;

	int length = s.getLength();

	for (int i = index; i < length; i++) {
		result = result * 10 + (s[i] - '0');
	}

	return result;
}

//char* extract(String s, int col, char end)
//{
//	int curr = 1;
//	int count = 0;
//	int length = s.getLength();
//	//*temp = s;
//	int i = 0;
//	for (;length;i++)
//	{
//		if (curr > col)
//		{
//			break;
//		}
//		if (s[i] == end)
//		{
//			curr++;
//			continue;
//		}
//		if (curr == col)
//		{
//			count++;
//
//		}
//
//
//
//
//
//
//	}
//
//	char* result = new char[count + 1];
//	int j = i - count - 1;
//	int k = 0;
//	for (;k < count;j++)
//	{
//		result[k++] = s[j];
//
//	}
//	result[count] = '\0';
//	return result;
//}