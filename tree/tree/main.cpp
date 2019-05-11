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
    // if root is NULL
    // there is no path
    if (!root)
    return false;
    
    // push the node's value in 'arr'
    pathArr.push_back(root->key);
    
    // if it is the required node
    // return true
    if (root->key == searchKey)
    return true;
    
    // else check whether the required node lies
    // in the left subtree or right subtree of
    // the current node
   // int i = 0;
    for (int i = 0; i < root->child.size();i++)
    {
        if (hasPath(pathArr, root->child[i], searchKey))
            return true;
    }
    // required node does not lie either in the
    // left or right subtree of the current node
    // Thus, remove current node's value from
    // 'arr'and then return false
    pathArr.pop_back();
    return false;
}
void printPath(Node *root, int x)
{
    // vector to store the path
    vector<int> arr;
    
    // if required node 'x' is present
    // then print the path
    if (hasPath(arr, root, x))
    {
        for (int i=0; i<arr.size()-1; i++)
        cout << arr[i] << "->";
        cout << arr[arr.size() - 1];
    }
    
    // 'x' is not present in the binary tree
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
Node* deleteElementbyPath(Node* &tmpRoot, vector<int> arr, int& j, bool& flag, Node*& deletedSubTree)
{
    
    if (tmpRoot->key == arr.back()){
        deletedSubTree = tmpRoot;
        tmpRoot = nullptr;
        flag = true;
        return deletedSubTree;
        
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
        return tmpRoot;
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
    // Base cases : Tree is empty or has single
    //              node
    if (root == NULL)
    return NULL;
    if (root->left == NULL &&
        root->right == NULL)
    return root;
    
    // Find predecessor if it exists
    if (root->left != NULL)
    {
        // Find predecessor of root (Rightmost
        // child in left subtree)
        BinaryTreeNode* l = createThreaded(root->left);
        
        // Link a thread from predecessor to
        // root.
        l->right = root;
        l->isThreaded = true;
    }
    
    // If current node is rightmost child
    if (root->right == NULL)
    return root;
    
    // Recur for right subtree.
    return createThreaded(root->right);
}
BinaryTreeNode *leftMost( BinaryTreeNode *root)
{
    while (root != NULL && root->left != NULL)
    root = root->left;
    return root;
}

// Function to do inorder traversal of a threadded
// binary tree
void inOrder(BinaryTreeNode *root)
{
    if (root == NULL) return;
    
    // Find the leftmost node in Binary Tree
    BinaryTreeNode *cur = leftMost(root);
    
    while (cur != NULL)
    {
        cout << cur->data << " ";
        
        // If this Node is a thread Node, then go to
        // inorder successor
        if (cur->isThreaded)
            cur = cur->right;
        
        else // Else go to the leftmost child in right subtree
            cur = leftMost(cur->right);
    }
}
void printTreeInBrackets(BinaryTreeNode* node) {
    if (!node) {
        //cout<<".";
        return;
    }
    cout<<node->data<<"(";
    printTreeInBrackets(node->left);
    
    printTreeInBrackets(node->right);
    cout<<")";
    
}
void printTreeInBrackets(Node* node) {
    if (!node) {
        //cout<<".";
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
    Node* root = createNode(0, 0);
    root->child.push_back(createNode(1, 1));
    root->child.push_back(createNode(2, 2));
    root->child[0]->child.push_back(createNode(3, 3));
     root->child[0]->child.push_back(createNode(4, 4));
     root->child[0]->child.push_back(createNode(5, 5));
     root->child[0]->child[2]->child.push_back(createNode(6, 6));
    
    cout << root->child[0]->child[0]->data<<endl;
 //   printPath(root, 6);
    vector<int> arr;
    hasPath(arr, root, 6);
 //   arr.push_back(3);
    
    int i = 1;
    bool flag = false;
  root = addElementbyPath(root, arr, i, flag,7,7);
    Node* prevNode = new Node;
    i = 1;
   // cout <<root->child[0]->child[2]->child[0]->child[0]->data<<endl;
  deleteElementbyPath(root, arr, i, flag, prevNode);
    
    printTreeInBrackets(root);
//    cout <<arr.back()<<endl;
 //   getElementbyPath(root, arr, i, flag);
    if (!flag)
        cout << "error"<<endl;

}
void interactiveMode() {
    int action;
    bool flag = true;
    while(flag){
        cout << "1 - Interactive mode n-ary tree"<<endl;
        cout << "2 - Interactive mode binary tree"<<endl;
        cin>>action;
        switch (action) {
            case 1:{
                Node* root = NULL;
                vector<int> keys;
                int actionNaryTree;
                bool flagNaryTree = true;
                while (flagNaryTree) {
                    cout << "1 - Add element to tree by path"<<endl;
                    cout << "2 - Get element by path"<<endl;
                    cout << "3 - Get path to element"<<endl;
                    cout << "4 - Delete element by path"<<endl;
                    cout << "5 - Print tree"<<endl;
                    cin >> actionNaryTree;
                    switch (actionNaryTree) {
                        case 1:
                        
                        break;
                        
                        default:
                        break;
                    }
                }
                
                
                
            }
            break;
            
            default:
            break;
        }
    }
}
int main()
{
    task2();
    return 0;
}
