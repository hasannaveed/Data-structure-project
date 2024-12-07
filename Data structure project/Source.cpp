// #include <iostream>
// #include <fstream>
// #include "RedBlack.h"
// #include "Avl.h"
// #include "String.h" // Custom String library
// #include "Utility_functions.h"
// // #include "MerkleTree.h"
// using namespace std;

// // RedBlackTree rbtree;
// AVL_tree<String> avl;
// RedBlackTree rbtree;
// // MerkleTree mt;
// void extractColumns(String filename, int col)
// {
//     ifstream file(filename.getdata(), ios::in); // Open the file in read mode
//     char buffer[1000];
//     int lineIndex = 0;

//     while (file.getline(buffer, 1000))
//     {
//         if (lineIndex == 0)
//         {
//             lineIndex++;
//             continue; // Skip first line
//         }

//         String curr(buffer);
//         String extracted = extract(curr, col, ',');
//         String path = "./Files/";
//         path = path + extracted + ".txt";

//         if (rbtree.search_node(extracted.getdata(), rbtree.getRoot()) == "nullptr")
//         {
//             rbtree.Insert(extracted, rbtree.getRoot(), 1, "./RedBlack/main/init/");

//             // mt.InsertInMerkle(path);
//         }
//         else
//         {
//             // cout << "duplicate value: " << extracted << endl;
//         }

//         ofstream newFile(path.getdata(), ios::app);
//         newFile << curr << '\n';

//         lineIndex++;
//     }
// }

// void FileReading(String filename)
// {
//     ifstream file(filename.getdata(), ios::in); // Open the file in read mode

//     if (!file)
//     {
//         cout << "Error: Unable to open file." << endl;
//         return;
//     }

//     char buffer[1024]; // Buffer to hold a single line
//     file.getline(buffer, sizeof(buffer));

//     String curr(buffer);

//     // Print out the first row as headers
//     for (int i = 0; i < curr.getLength(); i++)
//     {
//         if (curr[i] == ',')
//         {
//             cout << endl;
//         }
//         else
//         {
//             cout << curr[i];
//         }
//     }

//     cout << "\nSelect the column based on which you want to create the Trees: ";
//     int choice;
//     cin >> choice;

//     extractColumns(filename, choice);

//     file.close(); // Close the CSV file

//     // Example call to verify specific row reading
//     // cout << "\nEnter the filename containing pointers to verify a row: ";
//     // String pointerFileName;
//     // cin >> pointerFileName;
//     // String fullPath = pointerFileName;
//     // fullPath = fullPath + ".txt";
//     // ReadFileRows(filename, fullPath);
// }

// void CommitChanges()
// {
// }
// void addToTree()
// {
// }
// // int main()
// // {
// // FileReading("data.csv");
// // List.displayRow(0);
// // List.displayRow(1);
// // List.displayRow(2);
// // List.displayRow(3);

// int main()
// {
//     cout << "**********************************************" << endl;
//     cout << "*               GIT LITE                    *" << endl;
//     cout << "*      ----------------------------------    *" << endl;
//     cout << "*      Hello and Welcome to GIT LITE!        *" << endl;
//     cout << "*      ----------------------------------    *" << endl;
//     cout << "**********************************************" << endl;
//     cout << endl;
//     while (true)
//     {
//         String input;

//         cout << "git_> ";
//         cin >> input;

//         if (input == "init")
//         {
//             String fileName;
//             cin >> fileName;
//             cout << "The Columns of the Entered File are: " << endl;
//             FileReading(fileName);
//             rbtree.inOrderTraversal(rbtree.getRoot());
//             break;
//         }
//     }
// }
