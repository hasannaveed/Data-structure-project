#include <iostream>
#include <fstream>
#include "String.h"
#include <sys/stat.h>
#include <unistd.h>
#include "Utility_functions.h"
using namespace std;

class RedBlackTree
{
private:
    String root;
    String pathDirectory;
    String filesPath;

public:
    RedBlackTree() : root("nullptr")
    {
        pathDirectory = "./RedBlack/main/";
        filesPath = "./Files/";
    }

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
    String getDataPath(String Node)
    {
        return getLineFile(Node, 6);
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

    void Insert(String val, String parentFile, int col, String path1)
    {
        String key = val;
        String tempfile = key + ".txt";
        String data = filesPath + tempfile;
        String path = path1;

        String newNodeFile = path + key;
        newNodeFile = newNodeFile + ".txt";
        // String tempFile = "./RbTree/main/" + newNodeFile;

        if (root == "nullptr")
        { // Root creation
            ofstream newNode(newNodeFile.getdata());
            newNode << newNodeFile << '\n'; // Value
            newNode << "nullptr" << '\n';   // Left child
            newNode << "nullptr" << '\n';   // Right child
            newNode << "nullptr" << '\n';   // Parent
            newNode << "BLACK" << '\n';     // Root is always black
            newNode << data << '\n';        // the file containing the data is stored here
            newNode.close();
            root = newNodeFile;

            return;
        }

        // Insert logic
        String currentNodeFile = root;
        while (true)
        {
            String currentValue = getLineFile(currentNodeFile, 1);
            String currentKey = currentValue;

            if (key < currentKey)
            {
                String leftChild = getLeftChild(currentNodeFile);
                if (leftChild == "nullptr")
                {
                    // Create new node
                    ofstream newNode(newNodeFile.getdata());
                    newNode << newNodeFile << '\n';
                    newNode << "nullptr" << '\n';
                    newNode << "nullptr" << '\n';
                    newNode << currentNodeFile << '\n';
                    newNode << "RED" << '\n'; // input is always red
                    newNode << data << '\n';
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
                    newNode << newNodeFile << '\n';
                    newNode << "nullptr" << '\n';
                    newNode << "nullptr" << '\n';
                    newNode << currentNodeFile << '\n';
                    newNode << "RED" << '\n';
                    newNode << data << '\n';
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
        String newpar = getLineFile(newNodeFile, 4);
        while (newpar != "nullptr" && getNodeColor(newpar) == "RED")
        {
            String grandParent = getLineFile(newpar, 4);
            if (getLeftChild(grandParent) == newpar)
            {
                String uncle = getRightChild(grandParent);
                if (getNodeColor(uncle) == "RED")
                {
                    replaceLine(newpar, 5, "BLACK");
                    replaceLine(uncle, 5, "BLACK");
                    replaceLine(grandParent, 5, "RED");
                    newNodeFile = grandParent;
                }
                else
                {
                    if (getRightChild(newpar) == newNodeFile)
                    {
                        leftRotate(newpar);
                        newNodeFile = newpar;
                        newpar = getLineFile(newNodeFile, 4);
                    }
                    replaceLine(newpar, 5, "BLACK");
                    replaceLine(grandParent, 5, "RED");
                    rightRotate(grandParent);
                }
            }
            else
            {
                String uncle = getLeftChild(grandParent);
                if (getNodeColor(uncle) == "RED")
                {
                    replaceLine(newpar, 5, "BLACK");
                    replaceLine(uncle, 5, "BLACK");
                    replaceLine(grandParent, 5, "RED");
                    newNodeFile = grandParent;
                }
                else
                {
                    if (getLeftChild(newpar) == newNodeFile)
                    {
                        rightRotate(newpar);
                        newNodeFile = newpar;
                        newpar = getLineFile(newNodeFile, 4);
                    }
                    replaceLine(newpar, 5, "BLACK");
                    replaceLine(grandParent, 5, "RED");
                    leftRotate(grandParent);
                }
            }
        }
        replaceLine(root, 5, "BLACK");
    }

    void writeBranches(String &name)
    {
        ofstream file("./Branches/rb_branch", ios::app);
        file << name << '\n';

        file.close();
    }

    void copyTree(RedBlackTree &soruce, RedBlackTree &target, String currentNode, String sourceDir, String targetDir)
    {
        if (currentNode == "nullptr")
            return;

        String leftChild = soruce.getLeftChild(currentNode);
        copyTree(soruce, target, leftChild, sourceDir, targetDir);
        String rightChild = soruce.getRightChild(currentNode);
        copyTree(soruce, target, rightChild, sourceDir, targetDir);

        target.Insert(extractOnlyTxt(currentNode), target.getRoot(), 1, targetDir);
    }
    String extractOnlyTxt(String &fileName)
    {
        int count = 0;
        String temp;
        for (int i = 0; i < fileName.getLength(); i++)
        {
            if (fileName[i] == '/')
            {
                count++;
            }
            if (count == 4)
            {
                i++;
                temp = temp + fileName[i];
            }
        }
        temp = temp - 't';
        temp = temp - 't';
        // cout << temp << endl;
        return temp;
    }
    void addBranch()
    {
        writeBranches(this->root);
        cout << "Enter the branch name: ";
        String branchName;
        cin >> branchName;

        String sourceDir = "./RedBlack/main/init/";
        String always = "./RedBlack/";
        String targetDir = always + branchName;
        String totalPath = targetDir + '/';
        cout << totalPath << endl;
        mkdir(totalPath.getdata(), 0777);
        RedBlackTree newTree;
        totalPath = totalPath + "init/";
        pathDirectory = totalPath;

        mkdir(totalPath.getdata(), 0777);
        copyTree(*this, newTree, root, sourceDir, totalPath);
        String curr = newTree.getRoot();
        writeBranches(curr);
    }

    String getCurrentPathDirectory()
    {
        return pathDirectory;
    }

    void SwitchBranches()
    {
        int resultCount = 0;
        showBranches(resultCount);
        cout << "Enter the branch number (1- " << resultCount << ") : ";
        int number;
        cin >> number;

        String curr = getLineFile("Branches/rb_branch", number);

        this->root = curr;
        cout << root << endl;

        // this->inOrderTraversal(this->root.getdata());

        cout << "Switched to branch " << number << endl;
    }

    void showBranches(int &count)
    {
        ifstream file("./Branches/rb_branch", ios::in);

        char buffer[256];
        cout << "====================================" << endl;
        cout << " EXISTING BRANCHES IN RED BLACK TREE" << endl;
        cout << "====================================" << endl;
        int i = 1;
        while (file.getline(buffer, sizeof(buffer)))
        {
            String curr(buffer);
            extarctBranchName(curr);
            cout << i << ": " << curr << endl;
            count++;
            i++;
        }

        file.close();
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

    String getParent(String node)
    {
        return getLineFile(node, 4);
    }

    // String extractKey(String input)
    // {
    //     int length = input.getLength();
    //     int end = 0;

    //     for (end = 0; end < length; end++)
    //     {
    //         if (input[end] == ';')
    //             break;
    //     }

    //     String key;
    //     for (int i = 0; i < end; i++)
    //     {
    //         if (input[i] >= '0' && input[i] <= '9')
    //         {
    //             key = key + input[i];
    //         }
    //         else
    //         {
    //             key = "";
    //             break;
    //         }
    //     }

    //     for (int i = 0; i < end; i++)
    //     {
    //         if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] == '+') || (input[i] == '-') || (input[i] == '.'))
    //         {
    //             key = key + input[i];
    //         }
    //     }

    //     return key;
    // }

    void inOrderTraversal(String node)
    {
        if (node == "nullptr")
            return;

        inOrderTraversal(getLeftChild(node));
        cout << "Key: " << node << ", Color: " << getNodeColor(node) << endl;
        inOrderTraversal(getRightChild(node));
    }

    int compare(char *key1, char *key2)
    {
        int cmp = strcmp(key1, key2);
        if (cmp < 0)
            return -1; // key1 < key2
        if (cmp > 0)
            return 1; // key1 > key2
        return 0;     // key1 == key2
    }

    String search_node(char *val, String r)
    {
        // Extract the key from the node at 'r'
        String val2 = extractOnlyTxt(r);
        cout << val2;
        // If the current node is null, return "nullptr"
        if (r == "nullptr")
        {
            String null("nullptr");
            return null;
        }

        //  current node for debugging
        //  cout << "Checking node: " << r << " with value: " << val2 << endl;

        int comparison = compare(val, val2.getdata());

        if (comparison == 0)
        {
            return r; // Match found
        }

        // If the value is less, search in the left child
        if (comparison < 0)
        {
            String leftChild = getLineFile(r, 2);
            String left = leftChild;
            return search_node(val, left);
        }
        // If the value is greater, search in the right child
        else
        {
            String rightChild = getLineFile(r, 3);
            String right = rightChild;
            return search_node(val, right);
        }
    }

    // to find the smallest node
    String smallNode(String node)
    {
        while (getLeftChild(node) != "nullptr")
        {
            node = getLeftChild(node);
        }
        return node;
    }

    void deletion(String key)
    {
        String nodeFile = search_node(key.getdata(), root.getdata());
        if (nodeFile == "nullptr")
        {
            cout << "Node with key '" << key << "' not found." << endl;
            return;
        }

        //  is a leaf
        if (getLeftChild(nodeFile) == "nullptr" && getRightChild(nodeFile) == "nullptr")
        {
            // String parent = getParent(nodeFile);
            if (getParent(nodeFile) != "nullptr")
            {
                if (getLeftChild(getParent(nodeFile)) == nodeFile)
                    replaceLine(getParent(nodeFile), 2, "nullptr");
                else
                    replaceLine(getParent(nodeFile), 3, "nullptr");
            }
            else
            {
                root = "nullptr"; // Deleting the root node
            }

            remove(nodeFile.getdata()); // Remove the file
            // String color = getNodeColor(nodeFile);
            if (getNodeColor(nodeFile) == "BLACK")
            {
                RBBalancing(getParent(nodeFile));
            }
            return;
        }

        // when one child either left or right
        if (getLeftChild(nodeFile) == "nullptr" || getRightChild(nodeFile) == "nullptr")
        {
            // String null = "nullptr";
            String child = (getLeftChild(nodeFile) != "nullptr") ? getLeftChild(nodeFile) : getRightChild(nodeFile); // get the non null child
            // String parent = getParent(nodeFile);

            if (getParent(nodeFile) != "nullptr")
            {
                if (getLeftChild(getParent(nodeFile)) == nodeFile)
                    replaceLine(getParent(nodeFile), 2, child);
                else
                    replaceLine(getParent(nodeFile), 3, child);
            }
            else
            {
                root = child;
            }

            replaceLine(child, 4, getParent(nodeFile));
            remove(nodeFile.getdata());
            String color = getNodeColor(nodeFile);
            if (color == "BLACK")
            {
                RBBalancing(getParent(nodeFile));
            }
            return;
        }
        //=============find the inordersuccessor the min node when this case =======//
        //  has two children
        String successorFile = smallNode(getRightChild(nodeFile));
        String successor = extractOnlyTxt(successorFile);
        // String parent = getParent(successorFile);

        if (getParent(successorFile) != nodeFile)
        {
            String rightChild = getRightChild(successorFile);                      // here we are getting successor
            replaceLine(getParent(successorFile), 2, rightChild);                  // getting rightchild
            replaceLine(rightChild, 4, getParent(successorFile));                  // getting parent
            replaceLine(getRightChild(successorFile), 3, getRightChild(nodeFile)); // replacing with right child
            replaceLine(getRightChild(nodeFile), 4, successorFile);                // replacing with successor
        }

        replaceLine(nodeFile, 1, successor);
        remove(successorFile.getdata());
        // String color = getNodeColor(successorFile);
        if (getNodeColor(successorFile) == "BLACK")
        {
            RBBalancing(getParent(successorFile));
        }

        return;
    }
    void extarctBranchName(String &name)
    {
        String temp;
        int count = 0;
        for (int i = 0; i < name.getLength(); i++)
        {

            if (name[i] == '/')
            {
                count++;
            }
            if (count == 2)
            {
                i++;
                temp = temp + name[i];
            }
            if (count == 3)
            {
                break;
            }
        }
        name = temp;
    }

    void removerbBranches()
    {
        ofstream file("./Branches/rb_branch", ios::trunc);
        file.close();
    }

    void RBBalancing(String nodeFile)
    {
        // when it is null
        if (nodeFile == "nullptr" || nodeFile == root)
        {
            return; // Nothing to fix
        }

        String s;
        String par = getLineFile(nodeFile, 4);
        if (getLeftChild(par) == nodeFile)
        {
            s = getRightChild(par);
        }
        else
        {
            s = getLeftChild(par);
        }

        // String sColor = getNodeColor(s);

        //=================SimpleColor Switches==================//
        //  s is red
        if (getNodeColor(s) == "RED")
        {
            replaceLine(par, 5, "RED");
            replaceLine(s, 5, "BLACK");
            if (getLeftChild(par) == nodeFile)
            {
                leftRotate(par);
            }
            else
            {
                rightRotate(par);
            }
            RBBalancing(nodeFile); // Recur for the node's new position
            return;
        }

        //=================When in line==================//
        //  s is black and both its children are black
        // String sLeft = getLeftChild(s);
        // String sRight = getRightChild(s);
        if (getLeftChild(s) == "nullptr" || getNodeColor(getLeftChild(s)) == "BLACK")
        {
            if (getRightChild(s) == "nullptr" || getNodeColor(getRightChild(s)) == "BLACK")
            {
                replaceLine(s, 5, "RED");
                if (getNodeColor(par) == "RED")
                {
                    replaceLine(par, 5, "BLACK");
                }
                else
                {
                    RBBalancing(par); // Recur for the parent
                }
                return;
            }
        }

        //===========When they form a triangular pattern ===========//
        //  s is black, left child is red, and right child is black
        if (getLeftChild(s) != "nullptr" && getNodeColor(getLeftChild(s)) == "RED")
        {
            if (getRightChild(s) == "nullptr" || getNodeColor(getRightChild(s)) == "BLACK")
            {
                replaceLine(getLeftChild(s), 5, "BLACK");
                replaceLine(s, 5, "RED");
                rightRotate(s);
                RBBalancing(nodeFile); // Recur for the node's new position
                return;
            }
        }

        //  s is black, right child is red
        if (getRightChild(s) != "nullptr" && getNodeColor(getRightChild(s)) == "RED")
        {
            replaceLine(s, 5, getNodeColor(par));
            replaceLine(getRightChild(s), 5, "BLACK");
            replaceLine(par, 5, "BLACK");
            if (getLeftChild(par) == nodeFile)
            {
                leftRotate(par);
            }
            else
            {
                rightRotate(par);
            }
            return;
        }
    }
    void removeOneBranchRB(String &name)
    {
        ofstream file("./Branches/rb_branch", ios::trunc);
        remove(name.getdata());
        file << name << '\n';
    }

    bool SearchBranches(String branchName, int lineNumber)
    {
        ifstream file("./Branches/rb_branch", ios::in);

        char buffer[256];
        cout << "====================================" << endl;
        cout << " EXISTING BRANCHES IN RED BLACK TREE" << endl;
        cout << "====================================" << endl;

        while (file.getline(buffer, sizeof(buffer)))
        {
            String curr(buffer);
            if (curr == branchName)
            {
                return true;
            }
            lineNumber++;
        }

        file.close();

        return false;
    }

    void mergeBranches()
    {
        int line1;
        int line2;
        String mergeBranch;
        cout << "Enter the name of the  branches You want to  merge " << endl;
        cout << "Enter First Branch : ";
        String branch1;
        cin >> branch1;

        cout
            << "Enter Second Branch : ";
        String branch2;
        cin >> branch2;

        if (SearchBranches(branch1, line1) && SearchBranches(branch2, line2))
        {
            branch1 = "./RedBlack/" + branch1;
            branch1 = "./RedBlack/" + branch1;

            cout << "Enter the  name of the  new branch that is to be merged : ";
            cin >> mergeBranch;

            mergeBranch = "./RedBlack/" + mergeBranch;

            mkdir(mergeBranch.getdata(), 0777);
            String root1 = getLineFile("./Branches/rb_branch", line1);
            String root2 = getLineFile("./Branches/rb_branch", line2); // as root 2 will be some updated branch (assumng)

            RedBlackTree mergeTree;
            mergeTree.getRoot() = root2;
            String tempRoot = root1;

            // basically we are comparing with the new root values to be inserted  ones
            //  while (getLeftChild(root1) != "nullptr" && getRightChild(root1) != "nullptr")
            //  {
            //      String left = getLeftChild(root1);
            //      left = extractOnlyTxt(left);
            //      String checkLeft = search_node(left.getdata(), mergeTree.getRoot());
            //      if (checkLeft == "nullptr")
            //      {
            //          mergeTree.Insert(left, mergeTree.getRoot(), 1, mergeBranch);
            //      }
            //      String right = getRightChild(root1);
            //  }
        }
    }
};

// int main()
// {
//     RedBlackTree rbt;
//     String path1 = "./RedBlack/main/init/";
//     rbt.Insert("a", "nullptr", 1, path1);
//     rbt.Insert("b", rbt.getRoot(), 1, path1);
//     rbt.Insert("c", rbt.getRoot(), 1, path1);
//     rbt.Insert("d", rbt.getRoot(), 1, path1);
//     rbt.Insert("e", rbt.getRoot(), 1, path1);

//     cout << "In-Order Traversal:" << endl;
//     rbt.inOrderTraversal(rbt.getRoot());
//     rbt.deletion("c");
//     rbt.addBranch();
//     rbt.SwitchBranches();
//     String path2 = rbt.getCurrentPathDirectory();

//     cout << path2 << endl;

//     rbt.Insert("f", rbt.getRoot(), 1, path2);
//     rbt.Insert("g", rbt.getRoot(), 1, path2);
//     rbt.Insert("h", rbt.getRoot(), 1, path2);

//     rbt.SwitchBranches();
//     rbt.inOrderTraversal(rbt.getRoot());
//     // // rbt.visualizeTree("main");
//     rbt.removeBranches();

//     return 0;
// }
