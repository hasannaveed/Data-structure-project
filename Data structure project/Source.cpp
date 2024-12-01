#include <iostream>
#include <fstream>
#include "RedBlack.h"
#include "String.h"   // Custom String library
#include "LinkedList.h"
using namespace std;

DoublyLinkedList<String> List;
RedBlackTree<String>RBTree;

//======================function prototypes================================================
void AppendInTree(int input, int TreeInput); //for appending in the tree
void toString(int number, char* result); //converting the numbers to string
void FileReading(String filename); //reading the csv file and storing into the linked list
//=========================================================================================

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
    int count = 0;
    int length = 0;
    // Read each line of the CSV file
    while (file.getline(buffer, sizeof(buffer)) && count<8) {
        char arr[1024];  // Array to store a field's characters
        int arrIndex = 0;
        int i = 0;
       
        DoublyLinkedList<String> temp;  // Temporary list to store columns for this row
        // Traverse through the buffer
        while (buffer[i] != '\0') { 
            if (buffer[i] == ',') { 
                arr[arrIndex] = '\0'; 
                String newArr(arr); 
                length++ ;
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
            length++; 
            temp.insertInColumn(newArr);  
        }

        if (firstLine) {
            // Insert the first line into List directly 
            temp.display(); 
            List = temp;  
            firstLine = false;
        }
        else {
            // Attach subsequent rows to List

            List.attachOtherList(temp);   
        }
        count++;
    }

    file.close();  // Close the file

    cout << "Select the coulumn By which you want to create a tree (1-" << length << ") : ";
    int input;
    cin >> input;

    input--;

    cout << "Which Tree You Want to Use (1.RB Trees , 2.B Trees , 3.AVL Trees) : ";
    int treeInput;
    cin >> treeInput;

    AppendInTree(input, treeInput);

}


void AppendInTree(int input, int TreeInput) {
    Double_Node<String>* curr = List.getRoot();
    Double_Node<String>* iterator = List.getRoot();
    // Traverse to the selected column
    while (curr != nullptr && input > 0) {
        curr = curr->down;
        input--;
    }

    if (!curr) {
        cout << "Error: Invalid column selection!" << endl;
        return;
    }
    iterator = iterator->next;
    curr = curr->next; 

    while (curr != nullptr) {

        String category = curr->data; 
        String fileName = category + ".txt";  // Create a filename for the category
        ofstream outFile(fileName.getdata(), ios::app);  // Open file in append mode

        if (!outFile) {
            cout << "Error: Unable to create or open file for category " << category.getdata() << endl;
            return;
        }

        // Write the entire column to the file
        Double_Node<String>* temp = iterator;
        while (temp != nullptr) {
            outFile << temp->data<<" ";
            temp = temp->down;
        }
        outFile << "\n";

      

        outFile.close(); // Close the file after writing
        cout << "Data successfully written to " << fileName.getdata() << endl;
        curr = curr->next;
        iterator = iterator->next;
    }

    if (TreeInput == 1) {

        //RBTree.insert();
    }
}





int main() {
    String file = "C:/Users/ha797/Downloads/HealthCare-dataset/healthcare_dataset.csv"; // Path to CSV file
    cout << "===================================" << endl;
    cout << "          READING CSV FILE" << endl;
    cout << "===================================" << endl;
    FileReading(file);

    List.displayRow(0);
    List.displayRow(1);
    List.displayRow(2);
    List.displayRow(3);

    return 0;
}
