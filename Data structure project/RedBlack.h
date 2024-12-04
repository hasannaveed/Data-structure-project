#include <iostream>
#include <fstream>
#include <string>
#include "String.h"
#include "Utility_functions.h"

using namespace std;

//void replaceLine(String filename, int line, String replace)
//{
//    ifstream file(filename.getdata());
//    String arr[5];
//    char *buffer = new char[1000];
//    for (int i = 0; i < 5; i++)
//    {
//        file.getline(buffer, 1000);
//        if (i == line - 1)
//        {
//            arr[i] = replace;
//        }
//        else
//        {
//            arr[i] = buffer;
//        }
//    }
//    file.close();
//
//    ofstream updated_file(filename.getdata());
//    for (int i = 0; i < 5; i++)
//    {
//        updated_file << arr[i] << '\n';
//    }
//    updated_file.close();
//}
//
//char *getLineFile(String filename, int line)
//{
//    ifstream file(filename.getdata());
//    char *buffer = new char[1000];
//    for (int i = 0; i < line; i++)
//    {
//        file.getline(buffer, 1000);
//    }
//    return buffer;
//}
//
//char *extract(String s, int col, char end)
//{
//    int curr = 1;
//    int count = 0;
//    int length = s.getLength();
//    int i = 0;
//    for (; length; i++)
//    {
//        if (curr > col)
//        {
//            break;
//        }
//        if (s[i] == end)
//        {
//            curr++;
//            continue;
//        }
//        if (curr == col)
//        {
//            count++;
//        }
//    }
//
//    char *result = new char[count + 1];
//    int j = i - count - 1;
//    int k = 0;
//    for (; k < count; j++)
//    {
//        result[k++] = s[j];
//    }
//    result[count] = '\0';
//    return result;
//}

class RedBlackTree
{
private:
    String root;

public:
    RedBlackTree() : root("nullptr") {}

    String getRoot() const { return root; }

    void leftRotate(String nodeFile)
    {
        String rightChild = getRightChild(nodeFile);
        if (rightChild == "nullptr")
            return;

        String rightLeftChild = getLeftChild(rightChild);
        String parent = getLineFile(nodeFile, 4);

        // Update parent
        if (parent != "nullptr")
        {
            if (getLeftChild(parent) == nodeFile)
                replaceLine(parent, 2, rightChild);
            else
                replaceLine(parent, 3, rightChild);
        }
        else
        {
            root = rightChild; // Update root if node is the root
        }

        // Update right child's parent
        replaceLine(rightChild, 4, parent);

        // Update node's parent to right child
        replaceLine(nodeFile, 4, rightChild);

        // Update right child's left child to current node
        replaceLine(rightChild, 2, nodeFile);

        // Update current node's right child
        replaceLine(nodeFile, 3, rightLeftChild);

        if (rightLeftChild != "nullptr")
        {
            replaceLine(rightLeftChild, 4, nodeFile);
        }
    }

    void rightRotate(String nodeFile)
    {
        String leftChild = getLeftChild(nodeFile);
        if (leftChild == "nullptr")
            return;

        String leftRightChild = getRightChild(leftChild);
        String parent = getLineFile(nodeFile, 4);

        // Update parent
        if (parent != "nullptr")
        {
            if (getLeftChild(parent) == nodeFile)
                replaceLine(parent, 2, leftChild);
            else
                replaceLine(parent, 3, leftChild);
        }
        else
        {
            root = leftChild; // Update root if node is the root
        }

        // Update left child's parent
        replaceLine(leftChild, 4, parent);

        // Update node's parent to left child
        replaceLine(nodeFile, 4, leftChild);

        // Update left child's right child to current node
        replaceLine(leftChild, 3, nodeFile);

        // Update current node's left child
        replaceLine(nodeFile, 2, leftRightChild);

        if (leftRightChild != "nullptr")
        {
            replaceLine(leftRightChild, 4, nodeFile);
        }
    }

    void Insert(String val, String parentFile, int col)
    {
        String key = extractKey(val);
        String newNodeFile = key + ".txt";

        if (root == "nullptr")
        { // Root creation
            ofstream newNode(newNodeFile.getdata());
            newNode << val << '\n';       // Value
            newNode << "nullptr" << '\n'; // Left child
            newNode << "nullptr" << '\n'; // Right child
            newNode << "nullptr" << '\n'; // Parent
            newNode << "BLACK" << '\n';   // Root is always black
            newNode.close();
            root = newNodeFile;
            return;
        }

        // Insert logic
        String currentNodeFile = root;
        while (true)
        {
            String currentValue = getLineFile(currentNodeFile, 1);
            String currentKey = extractKey(currentValue);

            if (key < currentKey)
            {
                String leftChild = getLeftChild(currentNodeFile);
                if (leftChild == "nullptr")
                {
                    // Create new node
                    ofstream newNode(newNodeFile.getdata());
                    newNode << val << '\n';
                    newNode << "nullptr" << '\n';
                    newNode << "nullptr" << '\n';
                    newNode << currentNodeFile << '\n';
                    newNode << "RED" << '\n';
                    newNode.close();

                    replaceLine(currentNodeFile, 2, newNodeFile);
                    break;
                }
                currentNodeFile = leftChild;
            }
            else if (key > currentKey)
            {
                String rightChild = getRightChild(currentNodeFile);
                if (rightChild == "nullptr")
                {
                    // Create new node
                    ofstream newNode(newNodeFile.getdata());
                    newNode << val << '\n';
                    newNode << "nullptr" << '\n';
                    newNode << "nullptr" << '\n';
                    newNode << currentNodeFile << '\n';
                    newNode << "RED" << '\n';
                    newNode.close();

                    replaceLine(currentNodeFile, 3, newNodeFile);
                    break;
                }
                currentNodeFile = rightChild;
            }
            else
            {
                return; // Node already exists
            }
        }

        // Fix Red-Black Tree violations
        String newNodeParent = getLineFile(newNodeFile, 4);
        while (newNodeParent != "nullptr" && getNodeColor(newNodeParent) == "RED")
        {
            String grandParent = getLineFile(newNodeParent, 4);
            if (getLeftChild(grandParent) == newNodeParent)
            {
                String uncle = getRightChild(grandParent);
                if (getNodeColor(uncle) == "RED")
                {
                    replaceLine(newNodeParent, 5, "BLACK");
                    replaceLine(uncle, 5, "BLACK");
                    replaceLine(grandParent, 5, "RED");
                    newNodeFile = grandParent;
                }
                else
                {
                    if (getRightChild(newNodeParent) == newNodeFile)
                    {
                        leftRotate(newNodeParent);
                        newNodeFile = newNodeParent;
                        newNodeParent = getLineFile(newNodeFile, 4);
                    }
                    replaceLine(newNodeParent, 5, "BLACK");
                    replaceLine(grandParent, 5, "RED");
                    rightRotate(grandParent);
                }
            }
            else
            {
                String uncle = getLeftChild(grandParent);
                if (getNodeColor(uncle) == "RED")
                {
                    replaceLine(newNodeParent, 5, "BLACK");
                    replaceLine(uncle, 5, "BLACK");
                    replaceLine(grandParent, 5, "RED");
                    newNodeFile = grandParent;
                }
                else
                {
                    if (getLeftChild(newNodeParent) == newNodeFile)
                    {
                        rightRotate(newNodeParent);
                        newNodeFile = newNodeParent;
                        newNodeParent = getLineFile(newNodeFile, 4);
                    }
                    replaceLine(newNodeParent, 5, "BLACK");
                    replaceLine(grandParent, 5, "RED");
                    leftRotate(grandParent);
                }
            }
        }
        replaceLine(root, 5, "BLACK");
    }

    String getLeftChild(String node)
    {
        return getLineFile(node, 2);
    }

    String getRightChild(String node)
    {
        return getLineFile(node, 3);
    }

    String getNodeColor(String node)
    {
        return getLineFile(node, 5);
    }

    String extractKey(String input)
    {
        int length = input.getLength();
        int end = 0;

        for (end = 0; end < length; end++)
        {
            if (input[end] == ';')
                break;
        }

        String key;
        for (int i = 0; i < end; i++)
        {
            if (input[i] >= '0' && input[i] <= '9')
            {
                key = key + input[i];
            }
        }

        return key;
    }

    void inOrderTraversal(String node)
    {
        if (node == "nullptr")
            return;

        inOrderTraversal(getLeftChild(node));
        cout << "Key: " << extractKey(node) << ", Color: " << getNodeColor(node) << endl;
        inOrderTraversal(getRightChild(node));
    }
};

//int main()
//{
//    RedBlackTree rbt;
//
//    rbt.Insert("10", "nullptr", 1);
//    rbt.Insert("20", rbt.getRoot(), 1);
//    rbt.Insert("30", rbt.getRoot(), 1);
//    rbt.Insert("40", rbt.getRoot(), 1);
//    rbt.Insert("50", rbt.getRoot(), 1);
//
//    cout << "In-Order Traversal:" << endl;
//    rbt.inOrderTraversal(rbt.getRoot());
//
//    return 0;
//}
