#include <iostream>
#include <fstream>
#include "RedBlack.h"
#include "String.h" // Custom String library
#include "LinkedList.h"
#include "AVL.h"
#include "Btree.h"
using namespace std;

DoublyLinkedList<String> List;
RedBlackTree<String> RBTree;
AVL_tree<String> AVLTree;
// Btree<String> Btree;

//================================================================================================================================================================================\
// USE THE READ FILE ROWS FUNC TO READ THE ADRESS STORED IN THE FILES AND IT THEN PRINTS THE WHOLE ROW OF THAT ADDRESS                                                             \
// MAKE SURE THAT YOU HAVE THE PATH OF THE FOLDER TO STORE THE CREATED FILE AND THEN TO CHECK THE FILE AND READ THE ROWS FIRST ADD IT TO THE PROJ DIRECTORY AND THEN READ THE ROWS /
///================================================================================================================================================================================/

//======================function prototypes================================================
void AppendInTree(int input, int TreeInput);                        // For appending in the tree
void FileReading(String filename);                                  // Reading the CSV file and storing into files
void ReadSpecificRow(String &csvFilePath, String &pointerFilePath); // Reading a specific row using pointer
void ReadFileRows(String &csvfilePath, String &filepath);
int TreeSelection(); // return the choice  of the tree
//=========================================================================================

String FileNames[100] = {}; // array for storing files
int fileId = 0;             // File ID counter

bool checkFileExists(String filename)
{

    for (int i = 0; i < 100; i++)
    {
        if (FileNames[i] == filename)
        {
            return true;
        }
    }
    return false;
}
void FileReading(String filename)
{
    ifstream file(filename.getdata(), ios::in); // Open the file in read mode

    if (!file)
    {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    char buffer[1024]; // Buffer to hold a single line
    file.getline(buffer, sizeof(buffer));

    String curr(buffer);

    // Print out the first row as headers
    for (int i = 0; i < curr.getLength(); i++)
    {
        if (curr[i] == ',')
        {
            cout << endl;
        }
        else
        {
            cout << curr[i];
        }
    }

    cout << "\nSelect the column based on which you want to create the Trees: ";
    int choice;
    cin >> choice;

    // Read each line of the CSV file
    while (file.good())
    {
        streampos rowPointer = file.tellg(); // Save the position before reading the line

        if (!file.getline(buffer, sizeof(buffer)))
        {
            break;
        }

        String temp(buffer);
        int index = 0;
        int spaces = choice;

        // Skip to the chosen column
        while (spaces != 0)
        {
            if (temp[index] == ',')
            {
                spaces--;
            }
            index++;
        }

        // Extract the value of the chosen column
        String str;
        while (temp[index] != ',' && index < temp.getLength())
        {
            str = str + temp[index];
            index++;
        }

        // Construct the filename and open the file for appending
        String path = "../Files/"; // ADD A FOLDER TO STORE FILES AT
        String outputFileName = path + str + ".txt";

        // **STORE FILE NAME IN ARRAY**
        if (!checkFileExists(outputFileName))
        {                                         // Array bounds check
            FileNames[fileId++] = outputFileName; // Store file name in array
        }

        ofstream outFile(outputFileName.getdata(), ios::app); // Open file in append mode
        if (!outFile)
        {
            cout << "Error: Unable to create or open file " << outputFileName.getdata() << endl;
            continue;
        }

        // Write the pointer (file position) to the corresponding file
        outFile << rowPointer << '\n';

        outFile.close(); // Close the file
    }

    file.close(); // Close the CSV file

    // Example call to verify specific row reading
    // cout << "\nEnter the filename containing pointers to verify a row: ";
    // String pointerFileName;
    // cin >> pointerFileName;
    // String fullPath = pointerFileName;
    // fullPath = fullPath + ".txt";
    // ReadFileRows(filename, fullPath);
}

// for reading the whole file of pointers and then displying each entry

void ReadFileRows(String &csvfilePath, String &filepath)
{

    ifstream file(csvfilePath.getdata(), ios::in);
    ifstream pFile(filepath.getdata(), ios::in);

    if (!pFile)
    {
        cout << "Error:Pointer File " << endl;
        return;
    }
    if (!file)
    {
        cout << "Error:CSV File " << endl;
        return;
    }

    cout << "=======================================" << endl;
    cout << "    THE FILE HAS FOLLOWING ENTRIES " << endl;
    cout << "=======================================" << endl;

    long long position;
    int count = 1;
    while (pFile >> position)
    {

        file.seekg(position);
        char temp[1024];

        file.getline(temp, sizeof(temp));
        String tempStr(temp);

        cout << "Row " << count << "." << tempStr << endl;
        count++;
    }
    file.close();
    pFile.close();
}

void ReadSpecificRow(String &csvFilePath, String &pointerFilePath)
{

    ifstream file(csvFilePath.getdata(), ios::in);
    ifstream pointerFile(pointerFilePath.getdata(), ios::in);

    if (!pointerFile)
    {
        cout << "Error: Unable to open pointer file." << endl;
        return;
    }

    if (!file)
    {
        cout << "Error: Unable to open CSV file." << endl;
        return;
    }

    long long position;
    pointerFile >> position; // Read the saved position as a long long integer

    if (pointerFile.fail())
    {
        cout << "Error: Invalid data in pointer file." << endl;
        return;
    }

    streampos rowPointer = static_cast<streampos>(position);
    file.seekg(rowPointer); // Move to the saved position in the CSV file

    char buffer[1024];
    file.getline(buffer, sizeof(buffer)); // Read the specific row

    if (file.fail())
    {
        cout << "Error: Unable to read the row from the CSV file." << endl;
    }
    else
    {
        cout << "Row content: " << buffer << endl;
    }

    // for testing purposes
    //  file.seekg(1073790);
    //  file.getline(buffer, sizeof(buffer));
    //  String newL(buffer);
    //  cout << newL;
    file.close();
    pointerFile.close();
}
int TreeSelection()
{
    cout << "In Which Tree You Want to Input the files ?" << endl;
    cout << "1.AVL TREES" << endl;
    cout << "B TREES" << endl;
    cout << "3.RED BLACK TREES" << endl;
    cout << endl;

    cout << "Input Your Choice : ";
    int input;
    cin >> input;

    if (input < 1 || input > 3)
    {
        cout << "Invalid choice !! " << endl;
        return -1;
    }

    return input;
}
void LoadInTrees(int choice)
{
    if (choice < 1 || choice > 3)
    {
        cout << "Invalid choice (1-3) exists" << endl;
    }

    switch (choice)
    {
    case 1:
        for (int i = 0; i < fileId; i++)
        {
            String curr = FileNames[i];
            AVLTree.insert(curr);
        }

        break;
    case 2:

        break;

    case 3:
        for (int i = 0; fileId; i++)
        {
            String curr = FileNames[i];
            RBTree.insert(curr);
        }
        break;
    }
}

int main()
{
    // Define the path to your CSV file

    cout << "Initialize Repository <init> filename : init ";
    String input;
    cin >> input;

    // String file = "./healthcare_dataset.csv"; // Path to CSV file
    // cout << "===================================" << endl;
    // cout << "          READING CSV FILE" << endl;
    // cout << "===================================" << endl;

    // Read and process the CSV file
    FileReading(input);
    int choice = TreeSelection();
    LoadInTrees(choice);

    // for (int i = 0; i < 10; i++)
    // {
    //     cout << FileNames[i] << " ";
    // }

    RBTree.inorder();
    cout << "==========" << endl;
    AVLTree.inorder();

    // enter the name of the files from the tree output ex ../Files/A+.txt
    cout << "\nEnter the filename containing pointers to verify a row: ";
    String pointerFileName;
    cin >> pointerFileName;
    String fullPath = pointerFileName;
    fullPath = fullPath + ".txt";
    ReadFileRows(input, fullPath);
    return 0;
}
