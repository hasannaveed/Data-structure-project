#pragma once

//Name:Muhammad Hasan Naveed
//Roll no: 23I-0797
//Assignment #2

#include <iostream>
using namespace std;

class String {
	// think about the private data members
	char* s;
	int size;

public:
	// provide definitions of following functions
	String(); // default constructor
	String(const char* str); // initializes the string with constant c-string
	String(const String&); // copy constructor to initialize the string from the existing string
	String(int x); // initializes a string of predefined size
	char* getdata(); //returns the string inside the object
	// Binary Operators // Sub - script Operators
	const char operator[](int i) const; // returns the character at index [x]
	//NOTE: in above [] operator functions if i=negative int value, print ith character from end //of string e.g. in case of “LOOP” if i=-1 OR i=3, it should return ‘P’ similarly i = -4 OR i = 0, //return ‘L’
		// Arithmetic Operators
	String operator+(const String& str); // appends a String at the end of the String
	String operator+(const char& str); // appends a char at the end of the String
	String operator+(const char* str); // appends a String at the end of the String
	String operator-(const String& substr); //removes the substr from the String
	String operator-(const char& str); //removes all occurrences of char from the String
	String operator-(const char* str); //removes the str from the String
	// Assignment Operators
	String& operator=(const String&); // copies one String to another
	String& operator=(char*); // copies one c-string to another
	// Logical Operators
	bool operator==(const String&) const; // returns true if two Strings are equal
	bool operator==(const char*) const; // returns true if the c-string is equal to the String
	// Unary Operators // Boolean Not Operator
	bool operator!(); // returns true if the String is empty
	// Function-Call Operators
	//If something is not found then return -1
	int operator()(char) const; // returns the first index of the character being searched
	int operator()(const String&) const; // returns the first index of the String being searched
	int operator()(const char*) const; // returns the index of the c-string being searched


	// Conversion Operator
	operator int() const; // returns the length of string
	friend ostream& operator<<(ostream& output, const String& str); // outputs the string
	friend istream& operator>>(istream& input, String& str);

	int getLength() {

		int length = 0;
		for (int i = 0; s[i] != '\0'; i++)
		{
			length++;
		}

		return length;
	}


	


	~String(); // destructor
};
ostream& operator<<(ostream& output, const String& str); // outputs the string
istream& operator>>(istream& input, String& str); // inputs the string



String::String()
{
	s = NULL;
	size = 0;
}
String::String(const char* str)
{
	size = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		size++;
	}
	char* s2 = new char[size + 1];
	for (int i = 0; i < size; i++)
	{
		s2[i] = str[i];
	}
	s2[size] = '\0';
	s = s2;

}
String::String(const String& cs)
{
	size = cs.size;
	s = new char[size + 1];
	for (int i = 0; i < size; i++)
	{
		s[i] = cs.s[i];
	}
	s[size] = '\0';
}
String::String(int x)
{
	size = x;
	char* s1 = new char[x];
	for (int i = 0; i < x; i++)
	{
		s1[i] = '\0';
	}
	s = s1;

}
char* String::getdata()
{
	return s;
}


const char String::operator[](int i) const
{
	if (i >= 0)
	{
		const char c = s[i];
		return c;
	}
	else
	{
		const char c = s[i + strlen(s)];
		return c;
	}
}

String String::operator+(const String& str)
{
	int newSize = size;
	for (int i = 0; str[i] != '\0'; i++)
	{
		newSize += 1;
	}
	char* temp = new char[newSize + 1];

	for (int i = 0; i < size; i++)
	{
		temp[i] = s[i];
	}
	for (int i = size; i < newSize; i++)
	{
		temp[i] = str[i - size];
	}
	temp[newSize] = '\0';
	String s1(temp);
	s = s1.s;
	size = newSize;
	delete[]temp;
	return s1;

}

String String::operator+(const char& str)
{
	char* temp = new char[size + 2];
	for (int i = 0; i < size; i++)
	{
		temp[i] = s[i];
	}
	temp[size] = str;
	temp[size + 1] = '\0';
	String s1(temp);
	s = s1.s;
	size = size + 1;
	delete[]temp;
	return s1;
}
String String::operator+(const char* str)
{
	int newSize = size;
	for (int i = 0; str[i] != '\0'; i++)
	{
		newSize += 1;
	}
	char* temp = new char[newSize + 1];

	for (int i = 0; i < size; i++)
	{
		temp[i] = s[i];
	}
	for (int i = size; i < newSize; i++)
	{
		temp[i] = str[i - size];
	}
	temp[newSize] = '\0';

	String s1(temp);
	s = s1.s;
	size = newSize;
	delete[]temp;
	return s1;
}
String String::operator-(const String& substr)
{
	bool same;
	int i = 0;
	for (; i < size; i++)
	{
		same = true;
		for (int j = 0; j < substr.size; j++)
		{
			if (s[i + j] != substr.s[j])
			{
				same = false;
				break;
			}
		}
		if (same == true)
		{
			break;
		}
	}
	if (same)
	{
		for (int j = i; j < size; j++)
		{
			s[j] = s[j + substr.size];
		}
		s[size - substr.size] = '\0';
	}

	String s1(s);
	return s1;

}
String String::operator-(const char& str)
{
	for (int i = 0; i < size; i++)
	{
		if (s[i] == str)
		{
			for (int j = i; j <= size; j++)
			{
				s[j] = s[j + 1];
			}
		}
	}

	String s1(s);
	return s1;
}
String String::operator-(const char* str)
{
	int length = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		length++;
	}

	bool same;
	int i = 0;
	for (; i < size; i++)
	{
		same = true;
		for (int j = 0; j < length; j++)
		{
			if (s[i + j] != str[j])
			{
				same = false;
				break;
			}
		}
		if (same == true)
		{
			break;
		}
	}
	if (same)
	{
		for (int j = i; j < size; j++)
		{
			s[j] = s[j + length];
		}
		s[size - length] = '\0';
	}

	String s1(s);
	return s1;
}

String& String::operator=(const String& cs)
{
	char* temp = new char[cs.size];

	for (int i = 0; i < size; i++)
	{
		temp[i] = cs.s[i];
	}
	temp[size] = '\0';
	s = temp;
	String s1(temp);

	return s1;
}
String& String::operator=(char* cs)
{
	int length = 0;
	for (int i = 0; cs[i] != '\0'; i++)
	{
		length++;
	}
	char* temp = new char[length];

	for (int i = 0; i < length; i++)
	{
		temp[i] = cs[i];
	}
	temp[length] = '\0';
	s = temp;
	String s1(temp);
	return s1;


}
int String::operator()(char c) const
{
	int i;
	for (int i = 0; i < size; i++)
	{
		if (s[i] == c)
		{
			return i;
		}
	}
	return -1;
}
int String::operator()(const String& cs) const
{
	bool same;
	int i = 0;
	for (; i < size; i++)
	{
		same = true;
		for (int j = 0; j < cs.size; j++)
		{
			if (s[i + j] != cs.s[j])
			{
				same = false;
				break;
			}
		}
		if (same == true)
		{
			break;
		}
	}
	if (same)
	{
		return i;
	}
	return -1;
}
int String::operator()(const char* str) const
{
	int length = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		length++;
	}

	bool same;
	int i = 0;
	for (; i < size; i++)
	{
		same = true;
		for (int j = 0; j < length; j++)
		{
			if (s[i + j] != str[j])
			{
				same = false;
				break;
			}
		}
		if (same == true)
		{
			break;
		}
	}
	if (same)
	{
		return i;
	}
	return -1;
}
bool String::operator!()
{
	if (s[0] == '\0')
	{
		return true;

	}
	return false;
}
bool String::operator==(const String& cs) const
{
	bool same = true;
	for (int i = 0; i < size; i++)
	{
		if (s[i] != cs.s[i])
		{
			same = false;
			break;
		}
	}

	return same;
}
bool String::operator==(const char* str) const
{
	bool same = true;
	for (int i = 0; i < size; i++)
	{
		if (s[i] != str[i])
		{
			same = false;
			break;
		}
	}
	return same;
}
String::operator int() const
{
	int length = 0;
	for (int i = 0; s[i] != '\0'; i++)
	{
		length++;
	}

	return length;
}


String::~String()
{

}

ostream& operator<<(ostream& output, const String& str)
{
	if (str.s == NULL)
	{
		output << "\n";
	}
	else
	{
		output << str.s;
	}

	return output;
}
istream& operator>>(istream& input, String& str)
{

	char temp[100];
	input >> temp;
	delete[] str.s;
	int length = 0;
	for (int i = 0; temp[i] != '\0'; i++)
	{
		length++;
	}
	str.size = length;
	str.s = new char[str.size + 1];
	for (int i = 0; temp[i] != '\0'; i++)
	{
		str.s[i] = temp[i];
	}
	str.s[str.size] = '\0';
	return input;
}

