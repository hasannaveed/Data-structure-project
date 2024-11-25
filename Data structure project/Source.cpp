#include <iostream>
#include <fstream>
#include"String.h"
using namespace std;

void toString(int number, char* result) {

    char temp[20];
    int index = 0;

    // Extract digits and store them in reverse order
    while (number > 0) {
        temp[index++] = '0' + (number % 10); // Store last digit
        number /= 10; // Remove last digit
    }

    temp[index] = '\0';  // Null-terminate the temporary string

    // Reverse the string and store it in the result array
    int j = 0;
    for (int i = index - 1; i >= 0; --i) {
        result[j++] = temp[i];
    }

    result[j] = '\0';  // Null-terminate the result string
}



// for reading the csv file
void FileReading(String filename) {

    ifstream file(filename.getdata(), ios::in); // Open the file in read mode

    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    int i = 0;
    char buffer[1024];  // Buffer to hold each line

    while (file.getline(buffer, sizeof(buffer))) {
        i++;

        String rowReading(buffer); // Store row data as String

        char newchar[10];  // temp character array for string 
        toString(i, newchar);  //int to string func 

        String newFile = newchar;  // Convert number to String
        String lastTxt = ".txt";  //adding the file extension 


        newFile = newFile + lastTxt;  // concatenating

        ofstream file1(newFile.getdata(), ios::out);  //for writing

        file1 << rowReading;  // Write the row data to the new file

        cout << "Row: " << i << " : " << rowReading << endl;
    }

    file.close();  
}


int main()
{
   /*String file = "C:/Users/ha797/Downloads/HealthCare-dataset/healthcare_dataset.csv";
   FileReading(file);*/

 


    return 0;
}