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

    // Insert data into a column (vertically)
    void insertInColumn(T data) {
        cout << "Inserting in column: " << data << endl;

        Double_Node<T>* newNode = new Double_Node<T>(data);

        // Case 1: If the list is empty, initialize root to the new node
        if (root == nullptr) {
            root = newNode;
            cout << "Inserted at root." << endl;
        }
        else {
            // Traverse down the column to find the last node
            Double_Node<T>* curr = root;
            while (curr->down != nullptr) {
                curr = curr->down;
            }

            // Link the new node at the end of the column
            curr->down = newNode;
            cout << "Inserted below the existing node in column." << endl;
        }
    }

    // Insert data into a row (horizontally)
    void insertInRow(T data) {
        cout << "Inserting in row: " << data << endl;

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
        cout << "Inserted to the right of the existing node in row." << endl;
    }

    // Attach another list horizontally
    void attachOtherList(DoublyLinkedList<T>& other) {
        if (root == nullptr || other.root == nullptr) return;

        Double_Node<T>* curr = root;
        Double_Node<T>* otherCurr = other.root;

        // Traverse through the list and attach the other list
        while (curr != nullptr && otherCurr != nullptr) {
            // Traverse horizontally, linking the columns
            if (curr->next == nullptr) { // If curr is the last node in the row
                curr->next = otherCurr; // Link the two lists horizontally
            }
            else {
                Double_Node<T>* nextCurr = curr->next;
                curr->next = otherCurr;
                otherCurr->down = nextCurr;
            }

            // Move down the columns in the current list and the other list
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
        while (row != nullptr) {
            Double_Node<T>* col = row;
            while (col != nullptr) {
                cout << col->data << " ";
                col = col->down; // Move down to next column
            }
            cout << "\n";
            row = row->next; // Move right to next row
        }
    }

    // Destructor to clean up memory
    ~DoublyLinkedList() {
        clear();
    }

    // Clear all the nodes in the list
    void clear() {
        Double_Node<T>* row = root;
        while (row != nullptr) {
            Double_Node<T>* col = row;
            while (col != nullptr) {
                Double_Node<T>* temp = col;
                col = col->down;
                delete temp;
            }
            Double_Node<T>* tempRow = row;
            row = row->next;
            delete tempRow;
        }
        root = nullptr;
    }
};


