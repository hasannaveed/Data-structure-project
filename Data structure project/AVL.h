#include <iostream>
#include <fstream>
#include <cmath>
#include <sys/stat.h>
#include "String.h"
#include "Utility_functions.h"
using namespace std;

template <typename t>
struct AVL_node
{
    t data;
    AVL_node *left;
    AVL_node *right;

    // constructor to initialise avl node

    AVL_node(t d = 0, AVL_node *l = nullptr, AVL_node<t> *r = nullptr) : data(d), left(l), right(r)
    {
    }
};

template <typename t>
class AVL_tree
{
public:
    String root;
    String pathDirectory;
    String filePath;
    int commits;
    AVL_tree(String r = "nullptr") : root(r)
    {
        pathDirectory = "./AVL/main/init/";
        filePath = "./Files/";
        commits = 0;
    }

    int height(String node)
    {
        if (node == "nullptr")
            return 0;
        int leftHeight = height(getLeftChild(node));
        int rightHeight = height(getRightChild(node));
        return 1 + max(leftHeight, rightHeight);
    }

    String getLeftChild(String node)
    {
        return getLineFile(node, 2);
    }

    String getRightChild(String node)
    {
        return getLineFile(node, 3);
    }

    String getParent(String node)
    {
        return getLineFile(node, 4);
    }

    void updateParent(String node, String parent)
    {
        replaceLine(node, 4, parent);
    }

    void balanceTree(String node)
    {
        int leftHeight = height(getLeftChild(node));
        int rightHeight = height(getRightChild(node));

        if (abs(leftHeight - rightHeight) > 1)
        {
            // Left Heavy Tree (Left-Left Case or Left-Right Case)
            if (leftHeight > rightHeight)
            {
                if (height(getLeftChild(getLeftChild(node))) >= height(getRightChild(getLeftChild(node))))
                {
                    //  a right rotation
                    rightRotate(node);
                }
                else
                {
                    // a left rotation on the left child, then a right rotation
                    leftRotate(getLeftChild(node));
                    rightRotate(node);
                }
            }
            // Right Heavy Tree (Right-Right Case or Right-Left Case)
            else
            {
                if (height(getRightChild(getRightChild(node))) >= height(getLeftChild(getRightChild(node))))
                {
                    // a left rotation
                    leftRotate(node);
                }
                else
                {
                    //  a right rotation on the right child, then a left rotation
                    rightRotate(getRightChild(node));
                    leftRotate(node);
                }
            }
        }

        updateHeight(node);

        if (getParent(node) != "nullptr")
            balanceTree(getParent(node));
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
            else
            {
                key = "";
                break;
            }
        }

        for (int i = 0; i < end; i++)
        {
            if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] == '+') || (input[i] == '-') || (input[i] == '.'))
            {
                key = key + input[i];
            }
        }

        return key;
    }

    String getDataPath(String Node)
    {
        return getLineFile(Node, 6);
    }

    void Insert(String val, String parentFile, int col, String path1)
    {
        String key = val;
        String tempfile = key + ".txt";
        String data = filePath + tempfile;
        String path = path1;

        String newNodeFile = path + key;
        newNodeFile = newNodeFile + ".txt";

        if (root == "nullptr")
        { // Root creation
            ofstream newNode(newNodeFile.getdata());
            newNode << newNodeFile << '\n'; // Value
            newNode << "nullptr" << '\n';   // left child
            newNode << "nullptr" << '\n';   // right child
            newNode << "nullptr" << '\n';   // parent
            newNode << "0" << '\n';         // height is set to 0 for initial node
            newNode << data << '\n';        // the file containing the data is stored here
            newNode.close();
            root = newNodeFile;

            return;
        }

        // Insert logic
        String currentNodeFile = root;
        String insertedNode;
        while (true)
        {
            String currentValue = getLineFile(currentNodeFile, 1);
            String currentKey = extractOnlyTxt(currentValue);

            if (key == currentKey)
            {

                return;
            }

            else if (key < currentKey)
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
                    newNode << "0" << '\n';
                    newNode << data << '\n'; // the file containing the data is stored here
                    newNode.close();

                    replaceLine(currentNodeFile, 2, newNodeFile);
                    insertedNode = newNodeFile;
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
                    newNode << "0" << '\n';
                    newNode << data << '\n'; // the file containing the data is stored here
                    newNode.close();

                    replaceLine(currentNodeFile, 3, newNodeFile);
                    insertedNode = newNodeFile;
                    break;
                }
                currentNodeFile = rightChild;
            }
            else
            {
                return; // Node already exists
            }
        }

        balanceTree(insertedNode);
    }

    int getNodeHeight(String nodeFile)
    {
        if (nodeFile == "nullptr")
            return -1;
        String curr = getLineFile(nodeFile, 5);
        int h = stringToInt(curr);
        return h;
    }

    void updateHeight(String nodeFile)
    {
        int leftHeight = height(getLeftChild(nodeFile));
        int rightHeight = height(getRightChild(nodeFile));
        int newHeight = max(leftHeight, rightHeight) + 1;

        char *temp = new char[1000];
        toString(newHeight, temp);
        replaceLine(nodeFile, 5, String(temp)); // Update height in the file
    }

    void leftRotate(String nodeFile)
    {
        /*AVL_node<t>* k = r->left;
  //     r->left = k->right;
  //     k->right = r;
  //     r = k;*/

        String rightChild = getRightChild(nodeFile); // right child of root
        String parent = getLineFile(nodeFile, 4);    // store parent of current root

        replaceLine(nodeFile, 3, getLeftChild(rightChild)); // roots right is k's right
        if (getLeftChild(rightChild) != "nullptr")
            replaceLine(getLeftChild(rightChild), 4, nodeFile); // update parent of ks right to root

        replaceLine(rightChild, 2, nodeFile); // ks right is r
        replaceLine(rightChild, 4, parent);   // rs parent is k

        if (parent == "nullptr")
            root = rightChild;
        else if (getLeftChild(parent) == nodeFile)
            replaceLine(parent, 2, rightChild);
        else
            replaceLine(parent, 3, rightChild);

        replaceLine(nodeFile, 4, rightChild);

        // Update height after rotation
        updateHeight(nodeFile);
        updateHeight(rightChild);
    }

    // void rightRotate(String &r, int pos)
    // {
    //     /*AVL_node<t>* k = r->left;
    //     r->left = k->right;
    //     k->right = r;
    //     r = k;*/

    //     String parent(getLineFile(r, 4));     // store parent of current root
    //     String k(getLineFile(r, 2));          // leftt child of root
    //     replaceLine(r, 2, getLineFile(k, 3)); // roots left is k's right
    //     if (getLineFile(k, 3) != nullptr)
    //         replaceLine(getLineFile(k, 3), 4, r); // update parent of ks right to root
    //     replaceLine(k, 3, r);                     // ks right is r
    //     replaceLine(r, 4, k);                     // rs parent is k

    //     // replace the root
    //     if (parent == "nullptr")
    //     {
    //         // if rotation occurs at trees root
    //         this->root = k;
    //         replaceLine(k, 4, parent);
    //     }
    //     else
    //     {
    //         replaceLine(parent, pos, k); // initially 2 at pos
    //         replaceLine(k, 4, parent);   // k s parent is roots parent initially
    //     }
    // }

    void rightRotate(String nodeFile)
    {
        String leftChild = getLeftChild(nodeFile); // leftt child of root
        String parent = getLineFile(nodeFile, 4);  // store parent of current root

        // Update links
        replaceLine(nodeFile, 2, getRightChild(leftChild)); // roots left is k's right
        if (getRightChild(leftChild) != "nullptr")
            replaceLine(getRightChild(leftChild), 4, nodeFile);

        replaceLine(leftChild, 3, nodeFile); // update parent of ks right to root
        replaceLine(leftChild, 4, parent);   // rs parent is k

        if (parent == "nullptr")
            root = leftChild; // if rotation occurs at trees root
        else if (getLeftChild(parent) == nodeFile)
            replaceLine(parent, 2, leftChild);
        else
            replaceLine(parent, 3, leftChild); // initially 2 at pos

        replaceLine(nodeFile, 4, leftChild); // k s parent is roots parent initially

        // Update height after rotation
        updateHeight(nodeFile);
        updateHeight(leftChild);
    }
    // void leftRotate(String &r, int pos)
    // {
    //     String parent(getLineFile(r, 4));     // store parent of current root
    //     String k(getLineFile(r, 3));          // right child of root
    //     replaceLine(r, 3, getLineFile(k, 2)); // roots right is k's left
    //     if (getLineFile(k, 2) != nullptr)
    //         replaceLine(getLineFile(k, 2), 4, r); // update parent of ks right to root
    //     // r->right = k->left;
    //     replaceLine(k, 2, r); // ks left is r
    //     replaceLine(r, 4, k); // rs parent is k
    //     // k->left = r;
    //     // replace the root
    //     if (parent == "nullptr")
    //     {
    //         // if rotation occurs at trees root
    //         this->root = k;
    //         replaceLine(k, 4, parent);
    //     }
    //     else
    //     {
    //         replaceLine(parent, pos, k); // initially 3 at pos
    //         replaceLine(k, 4, parent);   // k s parent is roots parent initially
    //     }
    // }
    String extractOnlyTxt(String &fileName)
    {
        int count = 0;
        String temp;
        for (int i = 0; i < fileName.getLength(); i++)
        {
            if (fileName[i] == '/')
            {
                count++;
                if (count == 4)
                {

                    for (int j = i + 1; j < fileName.getLength(); j++)
                    {
                        if (fileName[j] == '.' || fileName[j] == '/')
                        {
                            break;
                        }
                        temp = temp + fileName[j];
                    }
                    break;
                }
            }
        }
        return temp;
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

        // If the current node is null, return "nullptr"
        if (r == "nullptr")
        {
            String null("nullptr");
            return null;
        }

        // Print current node for debugging
        cout << "Checking node: " << r << " with value: " << val2 << endl;

        // Compare values
        int comparison = compare(val, val2.getdata());

        if (comparison == 0)
        {
            return r; // Match found
        }

        // If the value is less, search in the left child
        if (comparison < 0)
        {
            String leftChild = getLineFile(r, 2);
            String left = leftChild; // Get left child
            return search_node(val, left);
        }
        // If the value is greater, search in the right child
        else
        {
            String rightChild = getLineFile(r, 3);
            String right = rightChild; // Get right child
            return search_node(val, right);
        }
    }
    String findMinNode(String node)
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
            cout << "Node with key " << key << " not found." << endl;
            return;
        }
        cout << nodeFile << endl;

        // Case 1: Node is a leaf
        if (getLeftChild(nodeFile) == "nullptr" && getRightChild(nodeFile) == "nullptr")
        {
            String parent = getParent(nodeFile);
            if (parent != "nullptr")
            {
                if (getLeftChild(parent) == nodeFile)
                    replaceLine(parent, 2, "nullptr");
                else
                    replaceLine(parent, 3, "nullptr");
            }
            else
            {
                root = "nullptr"; // Deleting the root node
            }

            remove(nodeFile.getdata()); // Remove the file
            balanceTree(parent);
            return;
        }

        // Case 2: Node has one child
        if (getLeftChild(nodeFile) == "nullptr" || getRightChild(nodeFile) == "nullptr")
        {
            String child = (getLeftChild(nodeFile) != "nullptr") ? getLeftChild(nodeFile) : getRightChild(nodeFile);
            String parent = getParent(nodeFile);

            if (parent != "nullptr")
            {
                if (getLeftChild(parent) == nodeFile)
                    replaceLine(parent, 2, child);
                else
                    replaceLine(parent, 3, child);
            }
            else
            {
                root = child; // Deleting the root node
            }

            replaceLine(child, 4, parent); // Update the child's parent
            remove(nodeFile.getdata());    // Remove the file
            balanceTree(parent);           // Rebalance the tree
            return;
        }

        // Case 3: Node has two children

        // Find the inorder successor

        String successorFile = findMinNode(getRightChild(nodeFile));
        String successor = extractOnlyTxt(successorFile);
        cout << "Successor: " << successor << endl;

        // Copy the successor's value to the current node
        replaceLine(nodeFile, 1, successor);

        // Delete the successor node
        deletion(successor.getdata());
        balanceTree(getParent(nodeFile)); // Rebalance the tree
    }

    // In-order traversal to verify tree structure
    void inOrderTraversal(String node)
    {
        if (node != "nullptr")
        {
            inOrderTraversal(getLeftChild(node));
            String value = getLineFile(node, 1);
            String key = extractOnlyTxt(value);
            cout << key << " ";
            inOrderTraversal(getRightChild(node));
        }
    }

    String getCurrentPathDirectory()
    {
        return pathDirectory;
    }

    void showavlBranches(int &count)
    {
        ifstream file("./Branches/avl_branch", ios::in);

        char buffer[256];
        cout << "====================================" << endl;
        cout << " EXISTING BRANCHES IN RED BLACK TREE" << endl;
        cout << "====================================" << endl;
        int i = 1;
        while (file.getline(buffer, sizeof(buffer)))
        {
            String curr(buffer);
            extarctavlBranchName(curr);
            cout << i << ": " << curr << endl;
            count++;
            i++;
        }

        file.close();
    }
    void extarctavlBranchName(String &name)
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
    void addBranch()
    {
        writeBranches(this->root);
        cout << "Enter the branch name: ";
        String branchName;
        cin >> branchName;

        String sourceDir = "./AVL/main/init/";
        String always = "./AVL/";
        String targetDir = always + branchName;
        String totalPath = targetDir + '/';
        // cout << totalPath << endl;
        mkdir(totalPath.getdata(), 0777);
        AVL_tree<t> newTree;
        totalPath = totalPath + "init/";
        pathDirectory = totalPath;

        mkdir(totalPath.getdata(), 0777);
        copyavlTree(*this, newTree, root, sourceDir, totalPath);
        String curr = newTree.root;
        writeBranches(curr);
    }

    void copyavlTree(AVL_tree &soruce, AVL_tree &target, String currentNode, String sourceDir, String targetDir)
    {
        if (currentNode == "nullptr")
            return;

        String leftChild = soruce.getLeftChild(currentNode);
        copyavlTree(soruce, target, leftChild, sourceDir, targetDir);
        String rightChild = soruce.getRightChild(currentNode);
        copyavlTree(soruce, target, rightChild, sourceDir, targetDir);

        target.Insert(extractOnlyTxt(currentNode), target.root, 1, targetDir);
    }

    void SwitchAvlBranches()
    {
        int resultCount = 0;
        // showavlBranches(resultCount);

        cout << "Enter the branch number (1- " << resultCount << ") : ";
        int number;
        cin >> number;

        String curr = getLineFile("Branches/avl_branch", number);

        this->root = curr;
        cout << root << endl;

        // this->inOrderTraversal(this->root.getdata());

        cout << "Switched to branch " << number << endl;
    }

    void writeBranches(String &name)
    {
        ofstream file("./Branches/avl_branch", ios::app);
        file << name << '\n';

        file.close();
    }

    void removeOneBranch(String &name)
    {
        ofstream file("./Branches/avl_branch", ios::trunc);
        remove(name.getdata());
        file << name << '\n';
    }
    void removeBranches()
    {
        ofstream file("./Branches/avl_branch", ios::trunc);
        file.close();
    }

    // void deletion(String &parent, int pos, String &rt) // pos is either replace right (3) or left (2) child
    // {
    //     String left(getLineFile(rt, 2));
    //     String right(getLineFile(rt, 3));

    //     // only left child or no child case
    //     if (right == "nullptr")
    //     {
    //         replaceLine(parent, pos, left);
    //         if (!(left == "nullptr"))
    //         {
    //             replaceLine(left, 4, parent);
    //         }
    //         remove(rt.getdata());
    //     }
    //     else if (left == "nullptr") // only right child case
    //     {
    //         replaceLine(parent, pos, right);
    //         if (!(right == "nullptr"))
    //         {
    //             replaceLine(right, 4, parent);
    //         }

    //         remove(rt.getdata());
    //     }
    //     else
    //     {
    //         // both child case

    //         // we find the successor ie node to replace the current node
    //         String succ(getLineFile(rt, 3));
    //         String dummy(getLineFile(succ, 2));
    //         while (dummy != "nullptr")
    //         {
    //             succ = dummy;
    //             dummy = (getLineFile(succ, 2));
    //         }

    //         // basically we will swap the nodes then delete

    //         // first we delelte the succesro node after saving it ie we change the parents left pointer to ncurrent node to be deletedull
    //         replaceLine(getLineFile(succ, 4), 2, rt);
    //         // then we we give the successors node the node to be deleteds children
    //         replaceLine(succ, 2, left);
    //         replaceLine(succ, 3, right);
    //         // we also change the childrens parent pointer to the successor
    //         replaceLine(left, 4, succ);
    //         replaceLine(right, 4, succ);

    //         // then we update the parent of node to be doleted to succ
    //         // and succ parent to the parent of deleted node
    //         replaceLine(succ, 4, parent);
    //         replaceLine(parent, pos, succ);

    //         // we also change the pointer of node to be deleted to null;
    //         replaceLine(rt, 2, "nullptr");
    //         replaceLine(rt, 3, "nullptr");
    //         replaceLine(rt, 4, getLineFile(succ, 4));

    //         String new_root(getLineFile(succ, 3));

    //         cout << rt << endl;
    //         delete_node(rt - ".txt", new_root);
    //         // finally we remove the node
    //         // std::remove(r.getdataCstr());
    //     }
    // }
    String foravlCommits(String name)
    {
        int count = 0;
        String temp;
        for (int i = 0; i < name.getLength(); i++)
        {
            if (name[i] == '/')
            {
                count++;
            }
            if (count == 3)
            {
                break;
            }
            else
            {
                temp = temp + name[i];
            }
        }
        return temp + "/";
    }
    void CommitChangesavl(String data)
    {
        String tempfilepath;
        String node = this->search_node(data.getdata(), this->root.getdata());
        if (node == "nullptr")
        {
            cout << "Node with key '" << data << "' not found." << endl;
            return;
        }
        String newDirectory = this->pathDirectory;
        if (commits == 0)
        {
            newDirectory = newDirectory + "init/";
        }

        tempfilepath = "./Files/temp";
        char arr[10];
        toString(commits, arr);
        String num = arr;
        // cout << num << endl;
        tempfilepath = tempfilepath + num;
        tempfilepath = tempfilepath + ".txt";
        // cout << tempfilepath << endl;

        ofstream tempFile(tempfilepath.getdata(), ios::out);
        if (!tempFile.is_open())
        {
            cout << "Failed to open temp file for writing." << endl;
            return;
        }

        String dataFile = getDataPath(node);
        cout << dataFile << endl;
        cout << "Enter the name of the user you want to commit the changes to: ";
        String user;
        cin >> user;
        cout << "Enter the new name : ";
        String newname;
        cin >> newname;

        fstream file(dataFile.getdata(), ios::in | ios::out);
        if (!file.is_open())
        {
            cout << "Failed to open data file." << endl;
            return;
        }

        char buffer[1024];
        bool userFound = false;
        long pos = -1;
        int lineNumber = 0;
        while (file.getline(buffer, sizeof(buffer)))
        {
            String curr(buffer);
            String extracted(extract(curr, 0, ','));
            cout << extracted << endl;

            if (extracted == user)
            {
                // pos = file.tellg();
                replaceLine(dataFile, lineNumber, "-1");
                userFound = true;
            }

            tempFile << curr << '\n';
            lineNumber++;
        }

        if (userFound)
        {
            file.seekp(pos);

            file << "-1" << endl;
        }
        else
        {
            cout << "User '" << user << "' not found in the file." << endl;
            return;
        }

        file.close();
        tempFile.close();

        AVL_tree<t> newTree;
        String newp = foravlCommits(pathDirectory);
        cout << newp << endl;
        String nameFolder = newp + "Commit";

        // ifstream log(logFile.getdata());
        // if (!log.is_open())
        // {
        //     cout << "Failed to open log file." << endl;
        //     return;
        // }

        cout << "Enter Commit Message : ";
        char arr1[30];
        cin.ignore();
        cin.getline(arr1, sizeof(arr1));

        String message(arr1); // Convert the char array to String if needed

        // ofstream logFileWrite(logFile.getdata(), ios::app);
        // logFileWrite << "Commit " << commits + 1 << ": " << message << '\n';
        // logFileWrite.close();

        nameFolder = nameFolder + num;
        mkdir(nameFolder.getdata(), 0777);
        nameFolder = nameFolder + "/";
        String logFile = nameFolder;
        logFile = logFile + "log.txt";
        cout << logFile << endl;

        String sourceFolder = this->pathDirectory + "Commit";
        int x = num;
        x = x - 1;
        char arr2[10];
        toString(x, arr2);
        String xname = arr2;
        sourceFolder = sourceFolder + xname;
        if (x - 1 == 0)
        {
            sourceFolder = "./AVL/main/init/";
        }
        else
        {
            sourceFolder = sourceFolder + "/";
        }
        ofstream logFileWrite(logFile.getdata(), ios::app);
        logFileWrite << "Commit " << commits + 1 << ": " << message << '\n';
        logFileWrite << this->root.getdata() << '\n';
        logFileWrite.close();

        copyavlTree(*this, newTree, root, sourceFolder, nameFolder);
        this->root = newTree.root;
        String node1 = search_node(data.getdata(), root.getdata());
        // cout << "Hello there" << endl;

        String update = tempfilepath;
        // cout << "NODE : " << node1 << endl;
        replaceLine(node1, 6, update);
        commits++;
    }
    void revertCommitsavl()
    {
        String targetDir = "./AVL/main/";
        if (commits == 0)
        {
            cout << "No commits to revert." << endl;
            return; // Exit early if there are no commits to revert
        }

        if (commits == 1)
        {
            // Handle reverting to the initial state
            String nameFolder = pathDirectory + "Commit0";
            String total = nameFolder + "/";
            cout << "Reverting to: " << nameFolder << endl;

            AVL_tree<t> newTree;
            copyavlTree(*this, newTree, root, total, targetDir);
            this->root = newTree.root;

            // Optionally remove the commit folder
            // RemoveDirectory(nameFolder.getdata());

            commits--; // Decrement commit count
            return;
        }

        // Handle reverting for commits > 1
        int x = commits - 1;
        char arr[10];
        toString(x, arr);
        String xname = arr;

        int prevX = x - 1;
        char arr2[10];
        toString(prevX, arr2);
        String xname1 = (prevX == 0) ? "0" : arr2; // Handle edge case where prevX == 0

        String nameFolder = targetDir + "Commit";
        String newFolder = nameFolder + xname;
        String total = newFolder + "/";
        cout << "Reverting to: " << total << endl;

        String prevCommit = nameFolder + xname1 + "/";
        cout << "Previous commit path: " << prevCommit << endl;

        AVL_tree<t> newTree;
        copyavlTree(*this, newTree, root, total, prevCommit);
        this->root = newTree.root;

        commits--; // Decrement commit count
    }
};

int main()
{
    AVL_tree<string> avl;
    String path1 = "./AVL/main/init/";
    avl.Insert("a", "nullptr", 1, path1);
    avl.Insert("b", avl.root, 1, path1);
    avl.Insert("c", avl.root, 1, path1);
    avl.Insert("d", avl.root, 1, path1);
    //     rbt.Insert("e", rbt.getRoot(), 1, path1);

    avl.CommitChangesavl("a");
    avl.CommitChangesavl("b");

    avl.revertCommitsavl();

    // cout << "Tree before deletion:" << endl;
    // avl.inOrderTraversal(avl.root);
    // cout << endl;
    // avl.deletion("15");

    // avl.addBranch();
    // avl.SwitchAvlBranches();
    // String path2 = avl.getCurrentPathDirectory();
    // avl.Insert("f", avl.root, 1, path2);
    // avl.Insert("g", avl.root, 1, path2);
    // avl.Insert("h", avl.root, 1, path2);

    // avl.SwitchAvlBranches();

    // avl.inOrderTraversal(avl.root);
    // // cout << "Tree after deletion:" << endl;
    // // avl.inOrderTraversal(avl.root);
    // avl.removeBranches();
    // cout << endl;
    return 0;
}
