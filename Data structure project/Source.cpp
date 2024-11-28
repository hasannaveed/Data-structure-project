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
void FileReading(String filename); //reading the csv file and storing into the linked list
//=========================================================================================




void FileReading(String filename) {
    ifstream file(filename.getdata(), ios::in);  // Open the file in read mode

    if (!file) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    char buffer[1024]; // Buffer to hold a single line
    bool firstLine = true;  // Flag to track the first line
    int count = 0;
    file.getline(buffer, sizeof(buffer));

    String curr(buffer);

    // Print out the first row as headers
    for (int i = 0; i < curr.getLength(); i++) {
        if (curr[i] == ',') {
            cout << endl;
        }
        else {
            cout << curr[i];
        }
    }

    cout << "\nSelect the column based on which you want to create the Trees: ";
    int choice;
    cin >> choice;

    int rowNumber = 1;

    // Read each line of the CSV file
    while (file.getline(buffer, sizeof(buffer)) ) { // Reading the file line by line
        rowNumber++;
        int spaces = choice;
        String temp(buffer);
        int index = 0;

        // Skip through the chosen column
        while (spaces != 0) {
            if (temp[index] == ',') {
                spaces--;
            }
            index++;
        }

        // Extract the value of the chosen column
        String str;
        while (temp[index] != ',' && index < temp.getLength()) {
            str = str + temp[index];
            index++;
        }

        // Construct the filename and open the file for appending
        String path = "C:/Users/ha797/source/repos/Data-structure-project2/Data structure project/Files/";
        String outputFileName = path + str + ".txt";
        ofstream outFile(outputFileName.getdata(), ios::app);  // Open file in append mode

        if (!outFile) {
            cout << "Error: Unable to create or open file " << outputFileName.getdata() << endl;
            continue;
        }

        // Write the row number to the corresponding file
        outFile << rowNumber << '\n';

        outFile.close(); // Close the file
        count++;
    }

    file.close(); // Close the CSV file
}

int main() {
    // Define the path to your CSV file (update the file path as needed)
    String file = "C:/Users/ha797/Downloads/HealthCare-dataset/healthcare_dataset.csv"; // Path to CSV file
    cout << "===================================" << endl;
    cout << "          READING CSV FILE" << endl;
    cout << "===================================" << endl;

    // Read and process the CSV file
    FileReading(file);

    return 0;
}



//void AppendInTree(int input, int TreeInput) {
//    Double_Node<String>* curr = List.getRoot();
//    Double_Node<String>* iterator = List.getRoot();
//    // Traverse to the selected column
//    while (curr != nullptr && input > 0) {
//        curr = curr->down;
//        input--;
//    }
//
//    if (!curr) {
//        cout << "Error: Invalid column selection!" << endl;
//        return;
//    }
//    iterator = iterator->next;
//    curr = curr->next;
//
//    while (curr != nullptr) {
//
//        String category = curr->data;
//        String fileName = category + ".txt";  // Create a filename for the category
//        ofstream outFile(fileName.getdata(), ios::app);  // Open file in append mode
//
//        if (!outFile) {
//            cout << "Error: Unable to create or open file for category " << category.getdata() << endl;
//            return;
//        }
//
//        // Write the entire column to the file
//        Double_Node<String>* temp = iterator;
//        while (temp != nullptr) {
//            outFile << temp->data << " ";
//            temp = temp->down;
//        }
//        outFile << "\n";
//
//
//
//        outFile.close(); // Close the file after writing
//        cout << "Data successfully written to " << fileName.getdata() << endl;
//        curr = curr->next;
//        iterator = iterator->next;
//    }
//
//    if (TreeInput == 1) {
//
//        //RBTree.insert();
//    }
//}

