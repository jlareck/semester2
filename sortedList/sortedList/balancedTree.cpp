//
//  balancedTree.cpp
//  sortedList
//
//  Created by Mykola Medynsky on 5/26/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//

#include "balancedTree.hpp"
#include <ctime>
Point plusFive(Point data){
    data.x += 5;
    data.y += 5;
    data.z += 5;
    return data;
}
bool equality( Point p1, Point p2){
    return p1.x == p2.x && p1.y == p2.y && p1.z == p2.z;
}
bool comparator1(const Point& data1, const Point& data2){//meybe you think why I implemented two similar comparator functions, so the reason is that I started coding in different projects and I used both but then I realised that they are equal and it would be better to use only one comparator instead of two, but I didnt want to make changes in code so I left them.
    if (data1.x!=data2.x)
        return data1.x<data2.x;
    if (data1.y!=data2.y)
        return data1.y<data2.y;
    return data1.z<=data2.z;
}
bool comparator2(const Point& data1, const Point& data2){
    if (data1.x!=data2.x)
        return data1.x>data2.x;
    if (data1.y!=data2.y)
        return data1.y>data2.y;
    return data1.z>=data2.z;
}
bool comparator3(const Point& data1, const Point& data2){
    if (data1.x!=data2.x)
        return data1.x<data2.x;
    if (data1.y!=data2.y)
        return data1.y<data2.y;
    return data1.z<data2.z;
}
bool comparator4(const Point& data1, const Point& data2){
    if (data1.x!=data2.x)
        return data1.x>data2.x;
    if (data1.y!=data2.y)
        return data1.y>data2.y;
    return data1.z>data2.z;
}

int height(AVLNode *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

AVLNode* newNode1(Point key)
{
    AVLNode* node = new AVLNode;
    node->data = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

AVLNode *rightRotate(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;
    

    x->right = y;
    y->left = T2;
    

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    
  
    return x;
}


AVLNode *leftRotate(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;
 
    y->left = x;
    x->right = T2;
   
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    

    return y;
}


int getBalance(AVLNode *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

AVLNode* insert1(AVLNode* node, Point key)
{
  
    if (node == NULL)
        return newNode1(key);
    
    if (comparator4(node->data, key))
        node->left = insert1(node->left, key);
    else if (comparator3(node->data, key))
        node->right = insert1(node->right, key);
    else
        return node;
    

    node->height = 1 + max(height(node->left),
                           height(node->right));
    

    int balance = getBalance(node);

    if (balance > 1 && comparator3(key, node->left->data))
        return rightRotate(node);
    

    if (balance < -1 && comparator4(key, node->right->data))
        return leftRotate(node);
    

    if (balance > 1 && comparator4(key, node->left->data))
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    

    if (balance < -1 && comparator3(key, node->right->data))
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    

    return node;
}
AVLNode* minValueNode(AVLNode* node)
{
    AVLNode* current = node;
    

    while (current->left != NULL)
        current = current->left;
    
    return current;
}


AVLNode* deleteNode(AVLNode* root, Point key)
{

    if (root == NULL)
        return root;
    
    if (comparator3(key, root->data))
        root->left = deleteNode(root->left, key);
    
    else if (comparator4(key, root->data))
        root->right = deleteNode(root->right, key);
    

    else
    {

        if (root->left == NULL)
        {
            AVLNode* temp = root;
            root = root->right;
            delete temp;
            return root;
        }
        else if (root->right == NULL)
        {
            AVLNode* temp = root;
            root= root->left;
            delete temp;
            return root;
        }
        else{
            AVLNode* temp = minValueNode(root->right);
            
            // Copy the inorder successor's
            // data to this node
            root->data = temp->data;
            
            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }
    }
    

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left),
                           height(root->right));

    int balance = getBalance(root);

    if (balance > 1 &&( getBalance(root->left) >= 0))
        return rightRotate(root);

    if (balance > 1 && (getBalance(root->left) < 0))
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    // Right Right Case
    if (balance < -1 && (getBalance(root->right) <= 0))
        return leftRotate(root);
    
    // Right Left Case
    if (balance < -1 && (getBalance(root->right) > 0))
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}
AVLNode* search(AVLNode* root, Point key)
{

    if (root == NULL || equality(root->data, key))
        return root;
    

    if (comparator1(root->data, key))
        return search(root->right, key);
    

    return search(root->left, key);
}
void searchElementsInRange(AVLNode *root, Point k1, Point k2)
{
    /* base case */
    if ( root == NULL )
        return;
    
    if ( comparator3(k1, root->data ))
        searchElementsInRange(root->left, k1, k2);

    if ( comparator1(k1, root->data) && comparator2(k2, root->data) )
        cout<<root->data.x<<" "<< root->data.y << " " << root->data.z<<endl;;

    if ( comparator4(k2, root->data) )
        searchElementsInRange(root->right, k1, k2);
}

void inorder(AVLNode *root)
{
    if (root != nullptr)
    {
        inorder(root->left);
        cout << root->data.x<< " "<< root->data.y << " " << root->data.z<<endl;
        inorder(root->right);
    }
}
void changeValuesInAVLTree(AVLNode **root){
    AVLNode *current = *root;
    if (current != nullptr)
    {
        changeValuesInAVLTree(&current->left);
        current->data = plusFive(current->data);
        changeValuesInAVLTree(&current->right);
    }
}

void task4(){
    Point data;
    AVLNode* root = nullptr;
    
    data.x = 0;
    data.y = 0;
    data.z = 0;
    
    root = insert1(root, data);
    data.x = 10;
    data.y = 10;
    data.z = 10;
    
    root = insert1(root, data);
    data.x = 7;
    data.y = 7;
    data.z = 7;
    
    root = insert1(root, data);
    data.x = 3;
    data.y = 3;
    data.z = 3;
    
    root = insert1(root, data);
    data.x = 9;
    data.y = 9;
    data.z = 8;
    
    root = insert1(root, data);
    data.x = 9;
    data.y = 9;
    data.z = 9;
    
    root = insert1(root, data);
    inorder(root);
    
    
    root = deleteNode(root, data);
    changeValuesInAVLTree(&root);
    cout << "------"<<endl;
    inorder(root);
}
void benchmarkAVL() {
    
    AVLNode *root = NULL;
    Point data, data2;
    // BSTNode *node = NULL;
    vector<Point> pointsVector;
    int start = clock();
    int size = 1000;
    for (int i = 0; i < size; i++){
        createRandPoint(data);
        pointsVector.push_back(data);
        root = insert1(root, data);
        
    }

    for (int i = 0; i < size; i++){
        if (search(root, pointsVector[i]) != NULL)
        {
            cout<< "Point " << pointsVector[i].x <<" "<< pointsVector[i].y<< " "<< pointsVector[i].z << " is found"<<endl;
        }
        else{
            cout<< "Point " << pointsVector[i].x <<" "<< pointsVector[i].y<< " "<< pointsVector[i].z << " is nooooooot found"<<endl;
        }
        cout << i <<endl;
    }
    
    data.x = 0;
    data.y = 0;
    data.z = 0;
    
    data2.x = 50;
    data2.y = 50;
    data2.z = 50;
    //  Node* copy = head;
    searchElementsInRange(root, data, data2);
    
    for (int i = 0; i < size/2; i++){
        root = deleteNode(root, pointsVector[i]);
        cout << i <<endl;
    }
    inorder(root);
    int end = clock();
    cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;

}
