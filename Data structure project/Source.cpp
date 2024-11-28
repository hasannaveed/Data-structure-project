#include <iostream>
#include <fstream>
#include "RedBlack.h"
#include "String.h"   // Custom String library
#include "LinkedList.h"
using namespace std;

DoublyLinkedList<String> List;
RedBlackTree<String> RBTree;

//======================function prototypes================================================
void AppendInTree(int input, int TreeInput); // For appending in the tree
void FileReading(String filename);          // Reading the CSV file and storing into files
void ReadSpecificRow( String& csvFilePath,  String& pointerFilePath); // Reading a specific row using pointer
//=========================================================================================

void FileReading(String filename) {
    ifstream file(filename.getdata(), ios::in);  // Open the file in read mode

    if (!file) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    char buffer[1024]; // Buffer to hold a single line
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

    // Read each line of the CSV file
    while (file.good()) {
        streampos rowPointer = file.tellg(); // Save the position before reading the line 

        if (!file.getline(buffer, sizeof(buffer))) {
            break;
        }

        String temp(buffer);
        int index = 0;
        int spaces = choice;

        // Skip to the chosen column
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

        // Write the pointer (file position) to the corresponding file
        outFile << rowPointer << '\n'; 

        outFile.close(); // Close the file
    }

    file.close(); // Close the CSV file

    // Example call to verify specific row reading
    cout << "\nEnter the filename containing pointers to verify a row: ";
    String pointerFileName;
    cin >> pointerFileName;
    String fullPath =  pointerFileName ;  
    fullPath = fullPath + ".txt"; 
    ReadSpecificRow(filename, fullPath);  
}

void ReadSpecificRow( String& csvFilePath,  String& pointerFilePath) {

    ifstream file(csvFilePath.getdata(), ios::in);
    ifstream pointerFile(pointerFilePath.getdata(), ios::in);

    if (!pointerFile) {
        cout << "Error: Unable to open pointer file." << endl;
        return;
    }

    if (!file) {
        cout << "Error: Unable to open CSV file." << endl;
        return;
    }

    long long position;
    pointerFile >> position; // Read the saved position as a long long integer

    if (pointerFile.fail()) {
        cout << "Error: Invalid data in pointer file." << endl;
        return;
    }

    streampos rowPointer = static_cast<streampos>(position); // Convert to streampos
    file.seekg(rowPointer); // Move to the saved position in the CSV file

    char buffer[1024];
    file.getline(buffer, sizeof(buffer)); // Read the specific row

    if (file.fail()) {
        cout << "Error: Unable to read the row from the CSV file." << endl;
    }
    else {
        cout << "Row content: " << buffer << endl;
    }

    //for testing purposes     
  //  file.seekg(1073790);
  //  file.getline(buffer, sizeof(buffer));
  //  String newL(buffer);
  //  cout << newL;
    file.close();
    pointerFile.close();
}


int main() {
    // Define the path to your CSV file
    String file = "C:/Users/ha797/Downloads/HealthCare-dataset/healthcare_dataset.csv"; // Path to CSV file
    cout << "===================================" << endl;
    cout << "          READING CSV FILE" << endl;
    cout << "===================================" << endl;

    // Read and process the CSV file
    FileReading(file);  

   /* cout << "\nEnter the filename containing pointers to verify a row: "; 
    String pointerFileName; 
    cin >> pointerFileName; 
    pointerFileName =pointerFileName + ".txt";
    cout << "Pointer file path: " << pointerFileName << endl;*/

    //ReadSpecificRow(file, pointerFileName);
    


    return 0;
}
