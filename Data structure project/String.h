
#include <iostream>
#include <string.h>
using namespace std;
class String
{
    char *ch;

public:
    // provide definitions of following functions
    String();
    // default constructor
    String(const char *str);
    String(const String &);
    String(int x);
    char *getdata();

    // Binary Operators //
    const char operator[](int i) const;

    // Arithmetic Operators
    String operator+(const String &str);    // appends a String at the end of the String
    String operator+(const char &str);      // appends a char at the end of the String
    String operator+(const char *str);      // appends a String at the end of the String
    String operator-(const String &substr); // removes the substr from the String
    String operator-(const char &str);      // removes all occurrences of char from the String
    String operator-(const char *str);      // removes the str from the String

    // Assignment Operators
    String &operator=(const String &); // copies one String to another
    String &operator=(char *);         // copies one c-string to another

    // Logical Operators
    bool operator==(const String &) const; // returns true if two Strings are equal
    bool operator==(const char *) const;

    // Unary Operators //
    bool operator!(); // returns true if the String is empty

    // Function-Call Operators
    // If something is not found then return -1
    int operator()(char) const;           // returns the first index of the character being
    int operator()(const String &) const; // returns the first index of the String
    int operator()(const char *) const;   // returns the index of the c-string being

    // Conversion Operator
    operator int() const; // returns the length of string

    ~String(); // destructor
};

ostream &operator<<(ostream &output, const String &str); // outputs the string
istream &operator>>(istream &input, String &str);        // inputs the string

// Parameterized Constructor
String::String(int x)
{

    this->ch = new char[x + 1];

    for (int i = 0; i < x; i++)
    {
        this->ch[i] = '\0';
    }
    this->ch[x] = '\0';
}

// Returning the data
char *String::getdata()
{
    return this->ch;
}

// Length of Ch
String::operator int() const
{
    int length = 0;

    while (this->ch[length] != '\0')
    {
        length++;
    }

    return length;
}

// Constrctor
String::String()
{

    this->ch = nullptr;
}

// Constructor Parameterized
String::String(const char *str)
{

    int len = 0;
    while (str[len] != '\0')
    { // finding the length
        len++;
    }

    this->ch = new char[len + 1];

    for (int i = 0; i < len; i++)
    { // coyping elements of given string in this->ch
        this->ch[i] = str[i];
    }
    this->ch[len] = '\0'; // null terminator
}

// Copy Constructor
String::String(const String &other)
{

    int len = 0;
    while (other.ch[len] != '\0')
    { // finding the length
        len++;
    }
    ch = new char[len + 1];
    for (int i = 0; i < len; i++)
    { // coyping elements of given objects' string in this->ch
        ch[i] = other.ch[i];
    }
    ch[len] = '\0'; // null terminator
}

// Destructor
String::~String()
{
    delete[] this->ch;
}

// Returning the index
const char String::operator[](int i) const
{

    int count = 0;
    while (this->ch[count] != '\0')
    {
        count++;
    }
    if (i >= 0 && i < count)
    { // if simple withinn range number is provided
        return this->ch[i];
    }
    else if (i < 0 && i >= -count)
    { // for the condition , if the index is called in the negative numbers then it should give the values from the end
        return this->ch[count + i];
    }
    char nullChar = '\0'; // null terminator
    return NULL;
}

String String::operator+(const String &str)
{

    int count1 = 0;
    while (this->ch[count1] != '\0')
    { // finding the length

        count1++;
    }
    int count2 = 0;

    while (str.ch[count2] != '\0')
    { // finding the length

        count2++;
    }

    int total = count1 + count2 + 1; // total length,  +1 for the null terminator

    char *temp = new char[total];

    int index = 0;

    for (int i = 0; i < count1; i++)
    { // copying the elements in the temp
        temp[index++] = this->ch[i];
    }
    for (int i = 0; i < count2; i++)
    {
        temp[index++] = str.ch[i];
    }
    temp[index] = '\0'; // null terminator

    delete[] ch;
    this->ch = temp;

    return *this;
}

String String::operator+(const char &c)
{

    int count = 0;
    while (this->ch[count] != '\0')
    { // finding the length
        count++;
    }

    char *temp = new char[count + 2];
    int index = 0;

    for (int i = 0; i < count; i++)
    { // copying this->ch in the temp
        temp[index++] = this->ch[i];
    }

    temp[index++] = c; // given character added

    temp[index] = '\0'; // null terminator

    delete[] this->ch;
    this->ch = temp;

    return *this;
}

String String::operator+(const char *str)
{

    int count1 = 0;
    while (this->ch[count1] != '\0')
    { // finding length of this->ch
        count1++;
    }
    int count2 = 0;
    while (str[count2] != '\0')
    { // finding length of the given string
        count2++;
    }
    int total = count1 + count2 + 1; // total final length of temp array

    char *temp = new char[total];

    int index = 0;

    for (int i = 0; i < count1; i++)
    { // copying
        temp[index++] = this->ch[i];
    }
    for (int i = 0; i < count2; i++)
    {
        temp[index++] = str[i];
    }
    temp[index] = '\0'; // null terminator

    delete[] ch;
    this->ch = temp;

    return *this;
}

String String::operator-(const String &substr)
{

    int count = 0;
    while (this->ch[count] != '\0')
    {
        count++;
    }

    int count2 = 0;
    while (substr.ch[count2] != '\0')
    {
        count2++;
    }

    char *temp = new char[count + 1];
    int index = 0;

    for (int i = 0; i < count; i++)
    {
        bool found = false;

        for (int j = 0; j < count2; j++)
        {
            if (ch[i + j] != substr.ch[j])
            {
                found = false;
                break;
            }
            else
            {
                found = true;
            }
        }

        if (!found)
        {
            temp[index] = this->ch[i];
            index++;
        }
        else
        {
            i += count2 - 1; // Skip the substring
        }
    }

    temp[index] = '\0'; // null terminator
    delete[] this->ch;  // Free the old memory
    this->ch = temp;    // Update the pointer to the new concatenated string

    return *this;
}

String String::operator-(const char &c)
{
    int len = 0;
    while (this->ch[len] != '\0')
    { // finding the length
        len++;
    }

    char *temp = new char[len + 1]; // +1 for null terminator
    int index = 0;

    for (int i = 0; i < len; i++)
    {
        if (this->ch[i] != c)
        {
            temp[index++] = this->ch[i];
        }
    }
    temp[index] = '\0'; // null terminator
    delete[] this->ch;  // Free the old memory
    this->ch = temp;    // Update the pointer to the new concatenated string

    return *this;
}

String String::operator-(const char *str)
{
    int len = 0;
    while (this->ch[len] != '\0')
    {
        len++;
    }

    int count = 0;
    while (str[count] != '\0')
    {
        count++;
    }

    char *temp = new char[len + 1];
    int index = 0;

    for (int i = 0; i < len; i++)
    {
        bool found = false;

        for (int j = 0; j < count; j++)
        {
            if (this->ch[i + j] != str[j])
            {
                found = false;
                break;
            }
            else
            {
                found = true;
            }
        }

        if (!found)
        {

            temp[index++] = this->ch[i];
        }
        else
        {
            i = i + count - 1; // Skip the substring
        }
    }

    temp[index] = '\0'; // null terminator
    delete[] this->ch;  // Free the old memory
    this->ch = temp;    // Update the pointer to the new concatenated string

    return *this;
}

String &String::operator=(const String &other)
{

    int count = 0;
    while (other.ch[count] != '\0')
    { // lwngth
        count++;
    }
    ch = new char[count + 1];
    for (int i = 0; i < count; i++)
    {
        ch[i] = other.ch[i];
    }
    ch[count] = '\0'; // null terminator

    return *this;
}

String &String::operator=(char *str)
{

    int count = 0;
    while (str[count] != '\0')
    {
        count++;
    }
    this->ch = new char[count + 1];

    for (int i = 0; i < count; i++)
    {
        this->ch[i] = str[i];
    }
    ch[count] = '\0'; // null terminator
    return *this;
}

bool String::operator==(const String &other) const
{
    int i = 0;
    while (this->ch[i] != '\0' && other.ch[i] != '\0')
    { // until they reach the last null terminator
        i++;
        if (this->ch[i] == other.ch[i])
        { // comparing both arrays
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool String::operator==(const char *str) const
{
    int i = 0;
    while (this->ch[i] != '\0' && str[i] != '\0' && this->ch[i] == str[i])
    { // until they reach the last null terminator , comparing both arrays
        i++;
    }
    return this->ch[i] == str[i]; // return true or false
}

bool String::operator!()
{
    int count = 0;

    while (this->ch[count] != '\0')
    { // finding length
        count++;
    }
    if (count == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int String::operator()(char a) const
{

    int count = 0;
    for (int i = 0; this->ch[i] != '\0'; i++)
    { // finding length
        count++;
    }
    // check for wether the character is present or not
    for (int i = 0; i < count; i++)
    {
        if (this->ch[i] == a)
        {
            return i;
            break;
        }
    }

    return -1;
}

int String::operator()(const String &other) const
{

    int count = 0;
    for (int i = 0; this->ch[i] != '\0'; i++)
    { // finding length
        count++;
    }
    int count2 = 0;
    for (int i = 0; other.ch[i] != '\0'; i++)
    { // finding length
        count2++;
    }
    // check for if the  str is present or not
    for (int i = 0; i <= count - count2; i++)
    {
        bool found = true;
        for (int j = 0; j < count2; j++)
        {
            if (this->ch[i + j] != other.ch[j])
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return i;
        }
    }
    return -1;
}

int String::operator()(const char *str) const
{
    int count = 0;
    for (int i = 0; this->ch[i] != '\0'; i++)
    { // finding length
        count++;
    }
    int count2 = 0;
    for (int i = 0; str[i] != '\0'; i++)
    { // finding length
        count2++;
    }
    // check for if the  str is present or not

    for (int i = 0; i <= count - count2; i++)
    {
        bool found = true;
        for (int j = 0; j < count2; j++)
        {
            if (this->ch[i + j] != str[j])
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return i;
        }
    }
    return -1;
}

ostream &operator<<(std::ostream &output, const String &str)
{
    output << str;
    return output;
}

istream &operator>>(std::istream &input, String &str)
{
    char hello[1000];
    input >> hello;
    str = hello;
    return input;
}
