#include <iostream>
#include <fstream>
#include "RedBlack.h"
#include "String.h"   // Custom String library
#include "LinkedList.h"
using namespace std;

DoublyLinkedList<String> List;

// Convert an integer to a character array representation
void toString(int number, char* result) {
    char temp[20];
    int index = 0;

    // Extract digits and store them
    do {
        temp[index++] = '0' + (number % 10);
        number /= 10;
    } while (number > 0);

    temp[index] = '\0';

    // Reverse the string into the result
    int j = 0;
    for (int i = index - 1; i >= 0; --i) {
        result[j++] = temp[i];
    }
    result[j] = '\0';
}

// Read and process a CSV file
void FileReading(String filename) {
    ifstream file(filename.getdata(), ios::in); // Open the file in read mode

    if (!file) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    char buffer[1024]; // Buffer to hold a single line
    bool firstLine = true;  // Flag to track the first line

    // Read each line of the CSV file
    while (file.getline(buffer, sizeof(buffer))) {
        char arr[1024];  // Array to store a field's characters
        int arrIndex = 0;
        int i = 0;

        DoublyLinkedList<String> temp;  // Temporary list to store columns for this row

        // Traverse through the buffer
        while (buffer[i] != '\0') { 
            if (buffer[i] == ',') { 
                arr[arrIndex] = '\0'; 
                String newArr(arr); 
                temp.insertInColumn(newArr);   
                arrIndex = 0; 
            }
            else {

                arr[arrIndex] = buffer[i]; 
                arrIndex++; 
            }
            i++;
        }

        if (arrIndex > 0) {  // Handle last element after the last comma
            arr[arrIndex] = '\0';
            String newArr(arr);
            temp.insertInColumn(newArr);  
        }

        if (firstLine) {
            // Insert the first line into List directly 
            List = temp;  
            firstLine = false;
        }
        else {
            // Attach subsequent rows to List
            List.attachOtherList(temp);   
        }
    }

    file.close();  // Close the file
}

int main() {
    String file = "C:/Users/ha797/Downloads/HealthCare-dataset/healthcare_dataset.csv"; // Path to CSV file
    cout << "===================================" << endl;
    cout << "          READING CSV FILE" << endl;
    cout << "===================================" << endl;
    FileReading(file);

    List.display();

    return 0;
}
