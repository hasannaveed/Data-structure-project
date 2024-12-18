#include <iostream>

using namespace std;

template <typename T>
class Double_Node {
public:
    T data;
    Double_Node* next; // horizontal link (right)
    Double_Node* down; // vertical link (down)

    Double_Node(T val) : data(val), next(nullptr), down(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
private:
    Double_Node<T>* root;

public:
    DoublyLinkedList() : root(nullptr) {}

    Double_Node<T>* getRoot() { return this->root; }
    // Insert data into a column (vertically)

    T getData() {
        return this->data;
    }


    void insertInColumn(T data) {
      //  cout << "Inserting in column: " << data << endl;

        Double_Node<T>* newNode = new Double_Node<T>(data);

        // Case 1: If the list is empty, initialize root to the new node
        if (root == nullptr) {
            root = newNode;
            //cout << "Inserted at root." << endl;
        }
        else {
            // Traverse down the column to find the last node
            Double_Node<T>* curr = root;
            while (curr->down != nullptr) {
                curr = curr->down;
            }

            // Link the new node at the end of the column
            curr->down = newNode;
           // cout << "Inserted below the existing node in column." << endl;
        }
    }

    // Insert data into a row (horizontally)
    void insertInRow(T data) {
        //cout << "Inserting in row: " << data << endl;

        Double_Node<T>* newNode = new Double_Node<T>(data);

        if (root == nullptr) {
            root = newNode; // If the list is empty, new node is the root
            return;
        }

        // Traverse to the last node in the row (horizontal)
        Double_Node<T>* curr = root;
        while (curr->next != nullptr) {
            curr = curr->next;
        }

        // Link the new node at the end of the row
        curr->next = newNode;
      // cout << "Inserted to the right of the existing node in row." << endl;
    }

    // Attach another list horizontally
    void attachOtherList(DoublyLinkedList<T>& other) {
        if (!root || !other.root) return; // If either list is empty, do nothing

        Double_Node<T>* curr = root;  // Pointer to the current list
        Double_Node<T>* otherCurr = other.root;  // Pointer to the other list

        // Traverse down the rows of the current list and the other list
        while (curr != nullptr && otherCurr != nullptr) {
            Double_Node<T>* currRow = curr;  // Traverse horizontally on the current list's row
            Double_Node<T>* otherRow = otherCurr;  // Traverse horizontally on the other list's row

            // Traverse horizontally, linking the rows
            while (currRow->next != nullptr) {
                currRow = currRow->next;
            }

            // Now link the last node of the current row to the first node of the other row
            currRow->next = otherRow;

            // Move down to the next row for both lists
            curr = curr->down;
            otherCurr = otherCurr->down;
        }
    } 

    // Display the linked list
    void display() {
        if (root == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        Double_Node<T>* row = root;

        int count = 0;

        while (row != nullptr ) {

            Double_Node<T>* col = row;
            int count2 = 0;

            while (col != nullptr ) {
                cout << col->data <<endl;
                col = col->down; // Move down to next column
            }
            cout << "\n";
            row = row->next;
        }
    }

    void displayRow(int w) {
        Double_Node<T>* row = root;

        // Navigate to the desired row
        while (row != nullptr && w > 0) {
            row = row->down;
            w--;
        }

        // If the row is found, traverse horizontally and display the data
        if (row != nullptr) {
            Double_Node<T>* col = row;
            while (col != nullptr) {
                cout << col->data << "\t"; // Using tab for better alignment
                col = col->next;
            }
            cout << endl;
        }
        else {
            cout << "Row not found!" << endl;
        }
    }

   
};


