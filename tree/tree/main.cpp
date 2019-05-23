//
//  main.cpp
//  tree
//
//  Created by Mykola Medynsky on 4/17/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//


#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int key;
    int data;
    vector<Node*> child;
};
struct BinaryTreeNode{
    int data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
    bool isThreaded;
};
Node* createNode(int key, int data) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->data = data;
    
    return newNode;
}
bool hasPath(vector<int>& pathArr, Node* root, int searchKey) {

    if (!root)
        return false;

    pathArr.push_back(root->key);
    

    if (root->key == searchKey)
        return true;

    for (int i = 0; i < root->child.size();i++)
    {
        if (hasPath(pathArr, root->child[i], searchKey))
            return true;
    }

    pathArr.pop_back();
    return false;
}
void printPath(Node *root, int x)
{

    vector<int> arr;

    if (hasPath(arr, root, x))
    {
        for (int i=0; i<arr.size()-1; i++)
            cout << arr[i] << "->";
        cout << arr[arr.size() - 1];
    }

    else
        cout << "No Path";
}
void getElementbyPath(Node* tmpRoot, vector<int> arr, int& j, bool& flag)
{
    if (tmpRoot->key == arr.back()){
        cout << tmpRoot->data<<endl;
        flag = true;
    }
    else {
        for (int i = 0; i < tmpRoot->child.size(); i++)
        {
            if (tmpRoot->child[i]->key==arr[j])
            {
                j++;
                getElementbyPath(tmpRoot->child[i], arr, j, flag);
            }
        }
    }
}
Node* addElementbyPath(Node* tmpRoot, vector<int> arr, int& j, bool& flag, int data, int key)
{
    if (tmpRoot->key == arr.back()){
        tmpRoot->child.push_back(createNode(key, data));
        flag = true;
        return tmpRoot;
    }
    else {
        for (int i = 0; i < tmpRoot->child.size(); i++)
        {
            if (tmpRoot->child[i]->key==arr[j])
            {
                j++;
                addElementbyPath(tmpRoot->child[i], arr, j, flag, data, key);
            }
        }
    }
    return tmpRoot;
}
void deleteElementbyPath(Node* &tmpRoot, vector<int> arr, int& j, bool& flag, Node*& deletedSubTree)
{
    
    if (tmpRoot->key == arr.back()){
        deletedSubTree = tmpRoot;
        tmpRoot = nullptr;
        flag = true;
    }
    else {
        for (int i = 0; i < tmpRoot->child.size(); i++)
        {
            if (tmpRoot->child[i]->key==arr[j])
            {
                
                j++;
                deleteElementbyPath(tmpRoot->child[i], arr, j, flag, deletedSubTree);
            }
        }
    }
}
BinaryTreeNode* newNode(int item)
{
    BinaryTreeNode* temp = new BinaryTreeNode;
    temp->data = item;
    temp->left = temp->right = NULL;
    return temp;
}
BinaryTreeNode* insert(BinaryTreeNode* node, int key)
{
    if (node == NULL) return newNode(key);
    if (key < node->data)
        node->left  = insert(node->left, key);
    else if (key >=  node->data)
        node->right = insert(node->right, key);
    return node;
}
BinaryTreeNode *createThreaded(BinaryTreeNode *root)
{

    if (root == NULL)
        return NULL;
    if (root->left == NULL &&
        root->right == NULL)
        return root;
    if (root->left != NULL)
    {
        BinaryTreeNode* l = createThreaded(root->left);
        l->right = root;
        l->isThreaded = true;
    }
    

    if (root->right == NULL)
        return root;
    

    return createThreaded(root->right);
}
BinaryTreeNode *leftMost( BinaryTreeNode *root)
{
    while (root != NULL && root->left != NULL)
        root = root->left;
    return root;
}
void inOrder(BinaryTreeNode *root)
{
    if (root == NULL) return;
    

    BinaryTreeNode *cur = leftMost(root);
    
    while (cur != NULL)
    {
        cout << cur->data << " ";
        
        if (cur->isThreaded)
            cur = cur->right;
        
        else
            cur = leftMost(cur->right);
    }
}
void printTreeInBrackets(BinaryTreeNode* node) {
    if (!node) {
 
        return;
    }
    cout<<node->data<<"(";
    printTreeInBrackets(node->left);
    
    printTreeInBrackets(node->right);
    cout<<")";
    
}
void printTreeInBrackets(Node* node) {
    if (!node) {
        return;
    }
    cout<<node->data<<"(";
    for (int i = 0; i < node->child.size(); i++){
        printTreeInBrackets(node->child[i]);
    }
    cout<<")";
    
}
void task2(){
    BinaryTreeNode* root = NULL;
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 11);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 10);
    root = insert(root, 11);
    root = insert(root, 12);
    root = insert(root, 12);
    printTreeInBrackets(root);
}
void task1() {
    cout << "Welcome to demo mode n-ary tree"<<endl;
    
    Node* root = createNode(0, 0);
    root->child.push_back(createNode(1, 1));
    root->child.push_back(createNode(2, 2));
    root->child[0]->child.push_back(createNode(3, 3));
    root->child[0]->child.push_back(createNode(4, 4));
    root->child[0]->child.push_back(createNode(5, 5));
    root->child[0]->child[2]->child.push_back(createNode(6, 6));
    
    cout << root->child[0]->child[0]->data<<endl;

    vector<int> arr;
    hasPath(arr, root, 6);

    int i = 1;
    bool flag = false;
    root = addElementbyPath(root, arr, i, flag,7,7);
    Node* prevNode = new Node;
    i = 1;

    deleteElementbyPath(root, arr, i, flag, prevNode);
    
    printTreeInBrackets(root);

    if (!flag)
        cout << "error"<<endl;
    
}
void demoNaryTree(){
    cout << "WELCOME TO DEMO MODE N-ARY TREE" << endl;
    cout << "As you know tree is a hierarchical data structure with a root value and subtrees of children with a parent node, represented as a set of linked nodes" << endl;
    cout << "In this program element have to values: the first is key - unique identifier for each node, and second one is data - value that you want to put in node" <<endl;
    cout << "If you want to add element in tree you need to enter the path to it (order of keys)."<<endl;
    cout << "So, let's begin"<<endl;
    cout << "The first action that we will do is creating root. It will have key 0 and data 0."<<endl;
    Node* root = createNode(0, 0);
    cout << "Next we can add some elements by path." << endl;
    vector<int> path;
    path.push_back(0);
    cout << "On this stage path can only have one value and it is 0."<<endl;
    cout << "So let's add (1,1), (2,2), (3,3) by that path."<<endl;
    int i = 1;
    bool flag = false;
    root = addElementbyPath(root, path, i, flag,1,1);
    i = 1;
    flag = false;
    root = addElementbyPath(root, path, i, flag,2,2);
    i = 1;
    flag = false;
    root = addElementbyPath(root, path, i, flag,3,3);
    cout << "Now let's see how tree looks like. Tree: "<<endl;
    printTreeInBrackets(root);
    cout << "After that I want to add some more elements((4, 4),(5, 5) (6, 6)) in differnt nodes"<<endl;
    root->child[0]->child.push_back(createNode(4, 4));
    root->child[0]->child.push_back(createNode(5, 5));
    root->child[0]->child[1]->child.push_back(createNode(6, 6));
    cout << "You can also get path to node by key if this node is existed in tree. Lets find path to node with key 6" << endl;
    path.clear();
    cout << "Path: ";
    printPath(root, 6);
    cout << endl;
    cout << "There is also function to get data by path. Lets get data by path 0->1->4"<<endl;
    path.push_back(0);
    path.push_back(1);
    path.push_back(4);
    i = 1;
    flag = false;
    cout << "Data by path 0->1->4 is ";
    getElementbyPath(root, path, i,flag);
    cout << endl;
    cout << "And finaly you cand delete node in tree by path let's delete subtree 0->1"<<endl;
    Node* subtree = nullptr;
    i = 1;
    flag = false;
    deleteElementbyPath(root, path, i, flag, subtree);
    cout << "Final tree: " <<endl;
    printTreeInBrackets(root);
    
}
void demoBinaryTree(){
    cout << "WELCOME TO DEMO MODE BINARY TREE" << endl;
    cout << "In computer science, a binary tree is a tree data structure in which each node has at most two children, which are referred to as the left child and the right child." <<endl;
    cout << "In this implementation binary tree is like binary serach tree. Elements adds to tree depending on key" << endl;
    cout << "The first action that we will do is creating root. It will have key 10"<<endl;
    BinaryTreeNode* root = nullptr;
    root = insert(root, 10);
    cout << "Next we can add some values. For example: 5, 15,3,2,11,17"<<endl;
    root = insert(root, 5);
    root = insert(root, 15);
    
    root = insert(root, 3);
    root = insert(root, 2);
    root = insert(root, 11);
    root = insert(root, 17);
    cout << "Let's see how tree look like now"<<endl;
    printTreeInBrackets(root);
    cout << "We can also build threaded tree to make inorder traverse easier"<<endl;
    createThreaded(root);
    cout << "Tree inorder: "<<endl;
    inOrder(root);
    
    
    
}
void interactiveMode() {
    int action;
    bool flag = true;
    while(flag){
        cout << "1 - Interactive mode n-ary tree" << endl;
        cout << "2 - Interactive mode binary tree" << endl;
        cout << "3 - Exit"<<endl;
        cin >> action;
        switch (action)
        {
            case 1:{
                Node* root = NULL;
                vector<int> keys;
                int actionNaryTree;
                bool flagNaryTree = true;
                while (flagNaryTree) {
                    cout << "1 - Add element to tree by path" << endl;
                    cout << "2 - Get element by path" << endl;
                    cout << "3 - Get path to element" << endl;
                    cout << "4 - Delete element by path" << endl;
                    cout << "5 - Print tree" << endl;
                    cout << "6 - Exit" << endl;
                    cin >> actionNaryTree;
                    switch (actionNaryTree) {
                        case 1: {
                            int key;
                            int data;
                            vector<int> path;
                            int sizeOfPath;
                            int keyInPath;
                            if (keys.size()==0) {
                                cout << "Enter key"<<endl;
                                cin >> key;
                                
                                keys.push_back(key);
                                cout << "Enter data" << endl;
                                cin >> data;
                                root = createNode(key, data);
                            }
                            else {
                                int j=1;
                                bool addElementFlag = false;
                                cout << "Enter size of path" << endl;
                                cin>>sizeOfPath;
                                cout << "Enter path" << endl;
                                while(path.size()!=sizeOfPath)
                                {
                                    cin >> keyInPath;
                                    path.push_back(keyInPath);
                                }
                                cout << "Enter key" << endl;
                                cin >> key;
                                while(find(keys.begin(), keys.end(), key)!=keys.end()){
                                    cout << "Enter another key, because this key already exists"<<endl;
                                    cin >> key;
                                }
                                cout << "Enter data" << endl;
                                cin >> data;
                                root = addElementbyPath(root, path, j, addElementFlag, data, key);
                                if (!addElementFlag)
                                    cout << "Error! You choose wrong path" << endl;
                            }
                            break;
                        }
                            
                        case 2: {
                            vector<int> path;
                            int sizeOfPath;
                            int keyInPath;
                            bool getElementFlag = false;
                            cout << "Enter size of path" << endl;
                            cin>>sizeOfPath;
                            cout << "Enter path" << endl;
                            while(path.size()!=sizeOfPath)
                            {
                                cin >> keyInPath;
                                path.push_back(keyInPath);
                            }
                            if (path[0]==root->key){
                                int j = 1;
                                getElementbyPath(root, path, j, getElementFlag);
                            }
                            if (!getElementFlag)
                                cout << "Error! Wrong path!" << endl;
                            break;
                        }
                        case 3: {
                 
                            int key;
                            cout << "Enter the key to what you want to have the path" << endl;
                            cin >> key;
                            printPath(root, key);
                            break;
                        }
                        case 4:{
                            int j=1;
                            int sizeOfPath;
                            vector<int> path;
                            int keyInPath;
                            bool deleteElementFlag = false;
                            Node* deletedSubTree = nullptr;
                            cout << "Enter size of path" << endl;
                            cin>>sizeOfPath;
                            cout << "Enter path" << endl;
                            while(path.size()!=sizeOfPath)
                            {
                                cin>>keyInPath;
                                path.push_back(keyInPath);
                            }
                            if(path[0]==root->key&&path.size()<=keys.size()){
                                
                                deleteElementbyPath(root, path, j, deleteElementFlag, deletedSubTree);
                            }
                            if (!deleteElementFlag) {
                                cout << "You entered wrong path" << endl;
                            }
                            else{
                                int actionPrint;
                                cout << "If you want to print deleted subtree press 1" << endl;
                                cin >> actionPrint;
                                if (actionPrint == 1)
                                    printTreeInBrackets(deletedSubTree);
                            }
                            break;
                        }
                        case 5:{
                            cout << "Tree:"<<endl;
                            printTreeInBrackets(root);
                            break;
                        }
                        case 6: {
                            cout << "Good bye!"<<endl;
                            flagNaryTree = false;
                            break;
                        }
                        default:
                            cout << "There is no action: "<< actionNaryTree << endl;
                            break;
                    }
                }
                break;
            }
            case 2: {
                BinaryTreeNode* root = nullptr;
                vector<int> keys;
                int actionNaryTree;
                bool flagBinaryTree = true;
                while (flagBinaryTree) {
                    cout << "1 - Add element to binary tree" << endl;
                    cout << "2 - Build threaded tree" << endl;
                    cout << "3 - Print tree" << endl;
                    cout << "4 - Exit" << endl;
                    cin >> actionNaryTree;
                    switch (actionNaryTree) {
                        case 1:
                            int data;
                            cout<< "Enter data"<<endl;
                            cin >> data;
                            root = insert(root, data);
                            break;
                        case 2:{
                            createThreaded(root);
                            int printAction;
                            cout << "Do you want to print it inorder"<<endl;
                            cout << "1 - Yes, any other key - No"<<endl;
                            cin>> printAction;
                            if(printAction)
                                inOrder(root);
                            break;
                        }
                        case 3:{
                            cout << "Tree:"<<endl;
                            printTreeInBrackets(root);
                            break;
                        }
                        case 4:{
                            cout << "Good bye!"<<endl;
                            flagBinaryTree = false;
                            break;
                        }
                        default:
                            cout << "Error! try another action" << endl;
                            break;
                    }
                }
                break;
            }
            case 3:
                cout << "Good bye"<<endl;
                flag = false;
                break;
            default:{
                cout << "Try again"<<endl;
                break;
            }
        }
    }
}
void chooseMode(){
  
    int action;
    cout << "1 - Interactive mode" << endl;
    cout << "2 - Demo mode n-ary tree" << endl;
    cout << "3 - Demo mode binary tree" << endl;
    cout << "Choose mode (enter number from 1 to 3): " << endl;
    cin >> action;
    switch (action) {
        case 1:
            interactiveMode();
            break;
        case 2:
            demoNaryTree();
            break;
        case 3:
            demoBinaryTree();
            break;
        default:
            cout << "Reload program and choose correctly"<<endl;
            break;
    }
}
int main()
{
    chooseMode();
    
    return 0;
}
