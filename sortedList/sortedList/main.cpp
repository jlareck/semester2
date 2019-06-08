//
//  main.cpp
//  sortedList
//
//  Created by Mykola Medynsky on 5/26/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//



#include <algorithm>
#include "balancedTree.hpp"

void createRandPoint(Point& randPoint){

    randPoint.x = rand()%100;
    randPoint.y = rand()%100;
    randPoint.z = rand()%100;

}
struct Node{
    Point data;
    Node* next;
};

Node* deleteNode(Node *head, Point key)
{
    Node* temp = head, *prev;
    

    if (temp != NULL && equality(temp->data, key))
    {
        Node* newNode = temp;
        temp = temp->next;
        delete newNode;
        return temp;
    

    }

    else{
        while (temp != NULL && !equality(temp->data, key))
        {
            prev = temp;
            temp = temp->next;
        }
        

        if (temp!=NULL && equality(temp->data, key))
        {
            Node* newNode = temp;
            
            prev->next = temp->next;
            delete newNode;
        }
        else
            return head;
    }
  
    return head;
}
void sortedInsert(Node** head, Node* newNode)
{
    Node* current;

    if (*head == NULL || comparator2((*head)->data, newNode->data))
    {
        newNode->next = *head;
        *head = newNode;
    }
    else
    {
        current = *head;
        while (current->next!=NULL &&
           comparator1(current->next->data, newNode->data))
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}
Node *newNode(Point data)
{

    Node* newNode = new Node;
    
    
    newNode->data = data;
    newNode->next = NULL;
    
    return newNode;
}
bool searchInList(Node* head, Point x)
{
    if (head == NULL)
        return false;
    
    // If key is present in current node, return true
    if (equality(head->data, x))
        return true;
    
    // Recur for remaining list
    return searchInList(head->next, x);
}
void searchByRange(Node* head, Point x1, Point x2)
{
    Node* current = head; // Initialize current
    while (current != NULL)
    {
        if (comparator1(x1, current->data)&&comparator2(x2, current->data))
            cout << current->data.x<< " " << current->data.y << " " << current->data.z<<endl;
        if(comparator4(current->data, x2))
            break;
        current = current->next;
    }
    
}
void changeValuesInList(Node **head)
{
    Node *temp = *head;
    while(temp != NULL)
    {
        temp->data = plusFive(temp->data);
        temp = temp->next;
    }
}
void printList(Node *head)
{
    Node *temp = head;
    while(temp !=  NULL)
    {
        cout<<temp->data.x<<" "<< temp->data.y<< " "<< temp->data.z<<endl;;
        temp = temp->next;
    }
}
int calculateMemory(Node *head)
{
    Node *temp = head;
    int size = 0;
    while(temp !=  NULL)
    {
        size+= sizeof(head->data);
        temp = temp->next;
    }
    return size;
}
void demoList(){
    Node* head = NULL;
    Point data;
    data.x = 0;
    data.y = 46;
    data.z = 1;
    Node *node = newNode(data);
    sortedInsert(&head, node);
    data.x = 0;
    data.y = 36;
    data.z = 13;
    node = newNode(data);
    sortedInsert(&head, node);
    data.x = 0;
    data.y = 5;
    data.z = 55;
    node = newNode(data);
    sortedInsert(&head, node);
    data.x = 3;
    data.y = 3;
    data.z = 3;
    node = newNode(data);
    sortedInsert(&head, node);
    data.x = 9;
    data.y = 9;
    data.z = 9;
    node = newNode(data);
    sortedInsert(&head, node);
    data.x = 9;
    data.y = 9;
    data.z = 9;
    node = newNode(data);
    sortedInsert(&head, node);
    cout<<"Created Linked List\n";
    printList(head);
   head = deleteNode(head, data);
    data.x = 3;
    data.y = 3;
    data.z = 3;
    cout << "Search element 3 3 3 in list"<<endl;
    if (searchInList(head, data)){
        cout << "Element is in list"<<endl;
    }
    else
        cout << "There is no such elements"<<endl;
    
    data.x = 0;
    data.y = 0;
    data.z = 0;
    Point data2;
    data2.x = 9;
    data2.y = 9;
    data2.z = 9;
    searchByRange(head, data, data2);

    changeValuesInList(&head);
    cout<<"Modificated list"<<endl;
    printList(head);
}

void benchmarkList(){
    Node *head = NULL;
    Point data, data2;
    Node *node = NULL;
    vector<Point> pointsVector;
    int start = clock();
    int size = 1000;
    for (int i = 0; i < size; i++){
        createRandPoint(data);
        pointsVector.push_back(data);
        node = newNode(data);
        sortedInsert(&head, node);
    }
    node = head;
    for (int i = 0; i < size; i++){
        if (searchInList(head, pointsVector[i]))
        {
            cout<< "Point " << pointsVector[i].x <<" "<< pointsVector[i].y<< " "<< pointsVector[i].z << " is found"<<endl;
        }
        else {
            cout<< "Point " << pointsVector[i].x <<" "<< pointsVector[i].y<< " "<< pointsVector[i].z << " is not found"<<endl;
        }

    }

    data.x = 0;
    data.y = 0;
    data.z = 0;
    
    data2.x = 50;
    data2.y = 50;
    data2.z = 50;

    searchByRange(head, data, data2);

    for (int i = 0; i <size/2; i++){
        head = deleteNode(head, pointsVector[i]);
    }
    changeValuesInList(&head);
    printList(head);
    int end = clock();
    cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;
   int size1 = calculateMemory(node);
    cout << size1<<endl;;
}
struct BSTNode{
    BSTNode* left;
    BSTNode* right;
    Point data;
};
BSTNode *newBSTNode(Point data)
{
    
    BSTNode* newNode = new BSTNode;
    
    
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

BSTNode* insert(BSTNode* node, Point data)
{
  
    if (node == NULL) return newBSTNode(data);
    if (comparator3(data, node->data))
        node->left  = insert(node->left,data);
    else if (comparator4(data, node->data))
        node->right = insert(node->right, data);
    return node;
}
BSTNode* findMin(BSTNode* root)
{

    while(root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

BSTNode* searchInBST(BSTNode* root, Point key)
{

    if (root == NULL || equality(root->data, key))
        return root;
    

    if (comparator3(root->data, key))
        return searchInBST(root->right, key);
    
    return searchInBST(root->left, key);
}
BSTNode* deleteNode(BSTNode* root,Point value)
{

    if(root==NULL)
        return root;
    else if(comparator3(value, root->data))
    {
        root->left = deleteNode(root->left,value);
    }
    else if(comparator4(value, root->data))
    {
        root->right= deleteNode(root->right,value);
    }
    

    else
    {

        if(root->left == NULL && root->right == NULL)
        {
            delete root;
            root=NULL;
            return root;
        }
        //case 2: one child
        else if(root->left==NULL)
        {
            BSTNode* temp = root;
            root=root->right;
            delete temp;
            return root;
        }
        else if(root->right==NULL)
        {
            BSTNode* temp=root;
            root=root->left;
            delete temp;
            return root;
        }

        else
        {
            BSTNode* temp=findMin(root->right);
            root->data=temp->data;
            root->right=deleteNode(root->right,temp->data);
        }
    }
    return root;
    
}

//BSTNode* deleteBSTNode(BSTNode* root, Point key)
//{
//    // base case
//    if (root == NULL) return root;
//
//    // If the key to be deleted is smaller than the root's key,
//    // then it lies in left subtree
//    if (comparator3(key, root->data))
//        root->left = deleteBSTNode(root->left, key);
//
//    // If the key to be deleted is greater than the root's key,
//    // then it lies in right subtree
//    else if (comparator4(key, root->data))
//        root->right = deleteBSTNode(root->right, key);
//
//    // if key is same as root's key, then This is the node
//    // to be deleted
//    else
//    {
//        // node with only one child or no child
//        if (root->left == NULL)
//        {
//            BSTNode* temp = root;
//            root = root->right;
//            delete temp;
//            return root;
//        }
//        else if (root->right == NULL)
//        {
//            BSTNode* temp = root;
//            root= root->left;
//            delete temp;
//            return root;
//        }
//        else{
//            BSTNode* temp = (root->left);
//            root->data = temp->data;
//            root->left = deleteBSTNode(root->left, temp->data);
//        }
//    }
//    return root;
//}

void searchElementsInRange(BSTNode *root, Point k1, Point k2)
{
    /* base case */
    if ( root == NULL )
        return;
    
    /* Since the desired o/p is sorted,
     recurse for left subtree first
     If root->data is greater than k1,
     then only we can get o/p keys
     in left subtree */
    if ( comparator3(k1, root->data ))
        searchElementsInRange(root->left, k1, k2);
    
    /* if root's data lies in range,
     then prints root's data */
    if ( comparator1(k1, root->data) && comparator2(k2, root->data) ){
        cout<<root->data.x<<" "<< root->data.y << " " << root->data.z << endl;
        
    }
    
    /* If root->data is smaller than k2,
     then only we can get o/p keys
     in right subtree */
    if ( comparator4(k2, root->data) )
        searchElementsInRange(root->right, k1, k2);
    
}
void changeValuesInTree(BSTNode **root)
{
    BSTNode* current = *root;
    if (current != nullptr)
    {
        changeValuesInTree(&current->left);
        current->data = plusFive(current->data);
        changeValuesInTree(&current->right);
    }
}
void inorder(BSTNode *root)
{
    if (root != nullptr)
    {
        inorder(root->left);
        cout << root->data.x<< " "<< root->data.y << " " << root->data.z<<endl;
        inorder(root->right);
    }
}
void calculateMemory(BSTNode* root, int& size){
    if (root != NULL)
    {
        calculateMemory(root->left, size);
        size += sizeof(root->data);
        calculateMemory(root->right,size);
    }
}
void demoBST(){
    BSTNode* root = nullptr;
    Point data;
    data.x = 0;
    data.y = 0;
    data.z = 0;

    root = insert(root, data);
    data.x = 10;
    data.y = 10;
    data.z = 10;

    root = insert (root, data);
    data.x = 7;
    data.y = 7;
    data.z = 7;

    root = insert(root, data);
    data.x = 3;
    data.y = 3;
    data.z = 3;

    root = insert(root, data);
    data.x = 8;
    data.y = 8;
    data.z = 8;
 
    root = insert(root, data);
    data.x = 8;
    data.y = 8;
    data.z = 9;

    root = insert(root, data);
    cout<<"Created Linked List\n";
    inorder(root);
     root = deleteNode(root, data);
    if (searchInBST(root, data) == nullptr){
        cout << "There is no element "<< data.x<< " " << data.y<< " " << data.z<<endl;
    }
    else
        cout << "Element is found"<<endl;
    
    data.x = 0;
    data.y = 0;
    data.z = 0;
    Point data2;
    data2.x = 9;
    data2.y = 9;
    data2.z = 9;
    cout << "Elements in range 0 0 0 and 9 9 9"<<endl;
    searchElementsInRange(root, data, data2);
    changeValuesInTree(&root);
    cout<<"Created Linked List\n";
    inorder(root);
    
    
}
void benchmarkBST(){
    BSTNode *root = NULL;
    Point data, data2;
   // BSTNode *node = NULL;
    vector<Point> pointsVector;
    int start = clock();
    int size = 1000;
    for (int i = 0; i < size; i++){
        createRandPoint(data);
        pointsVector.push_back(data);
        root = insert(root, data);

    }

    for (int i = 0; i < size; i++){
        if (searchInBST(root, pointsVector[i])!=NULL)
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
    BSTNode* copy = root;
    searchElementsInRange(root, data, data2);
    
    for (int i = 0; i < size/2; i++){
        root = deleteNode(root, pointsVector[i]);
        cout << i <<endl;
    }
    changeValuesInTree(&root);
    inorder(root);
    
    int end = clock();
    
    cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;
    int size1 = 0;
    calculateMemory(root, size1);
    cout<< size1<<endl;
    
}
void insert(vector<Point> &vec, Point value ) {
   vector<Point>::iterator it = std::lower_bound( vec.begin(), vec.end(), value, comparator1); // find proper position in descending order
    vec.insert( it, value ); // insert before iterator it
}

void deleteFromVector(vector<Point> &vec, Point value) {
    int i = 0;
    while(!equality(vec[i], value)) {
        i++;
    }
    vec.erase(vec.begin()+i);
}
bool searchInVector(vector<Point> &vec, Point value){
    vector<Point>::iterator it = vec.begin();
    while(!(it->x==value.x&&it->y==value.y&&it->z==value.z)&&it!=vec.end()) {
        it++;
    }
    if(it!=vec.end()){
        return true;
    }
    else
        return false;
}
void searchElementInRange(vector<Point> &vec, Point p1,Point p2){
    for (auto it: vec) {
        if (comparator1(p1, it)&&comparator2(p2, it)){
            cout << it.x << " " << it.y << " " << it.z<<endl;
        }
    }
    
}
void changeValuesInVector(vector<Point>& vec) {
    for (int i = 0; i < vec.size(); i++){
        vec[i] = plusFive(vec[i]);
    }
    
}
void printVector(vector<Point> vec) {
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i].x << " "<< vec[i].y << " "<< vec[i].z<<endl;
    }
}
int calculateMemory(vector<Point> vec) {
    int size= 0;
    
    for (int i = 0; i < vec.size(); i++)
    {
        size += sizeof(vec[i]);
    }
    return size;
}
void demoVector() {
    vector<Point> vec;
    Point data;
    data.x = 0;
    data.y = 0;
    data.z = 0;
   
    insert(vec, data);
    data.x = 10;
    data.y = 10;
    data.z = 10;
    
    insert(vec, data);
    data.x = 7;
    data.y = 7;
    data.z = 7;
    
    insert(vec, data);
    data.x = 3;
    data.y = 3;
    data.z = 3;
    
    insert(vec, data);
    data.x = 9;
    data.y = 9;
    data.z = 8;
    
    insert(vec, data);
    data.x = 9;
    data.y = 9;
    data.z = 9;
    
    insert(vec, data);
    cout<<"Created Linked List\n";
    printVector(vec);
    deleteFromVector(vec, data);

    if (searchInVector(vec, data)){
        cout << "found"<<endl;
    }
    else
        cout << "not found"<<endl;
    data.x = 0;
    data.y = 0;
    data.z = 0;
    Point data2;
    data2.x = 9;
    data2.y = 9;
    data2.z = 9;
    cout << "Elements in range 0 0 0 and 9 9 9"<<endl;
    searchElementInRange(vec, data, data2);
    changeValuesInVector(vec);
    cout<<"Created Linked List\n";
    printVector(vec);
}
void benchmarkVector() {
    vector<Point> vec;
    Point data, data2;
    // BSTNode *node = NULL;
    vector<Point> pointsVector;
    int start = clock();
    int size = 1000;
    for (int i = 0; i < size; i++){
        createRandPoint(data);
        pointsVector.push_back(data);
        insert(vec, data);
        
    }
    data.x = 0;
    data.y = 0;
    data.z = 0;
    
    data2.x = 50;
    data2.y = 50;
    data2.z = 50;
    for (int i = 0; i < size; i++){
        if (searchInVector(vec, pointsVector[i]) != NULL)
        {
            cout<< "Point " << pointsVector[i].x <<" "<< pointsVector[i].y<< " "<< pointsVector[i].z << " is found"<<endl;
        }
        else{
            cout<< "Point " << pointsVector[i].x <<" "<< pointsVector[i].y<< " "<< pointsVector[i].z << " is nooooooot found"<<endl;
        }
        cout << i <<endl;
    }
    searchElementInRange(vec, data, data2);
    
    for (int i = 0; i < size/2; i++){
        deleteFromVector(vec, pointsVector[i]);
 
    }
    changeValuesInVector(vec);
    printVector(vec);
    int end = clock();

     cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;
        vector<Point> copy = vec;
    int size1 = calculateMemory(copy);
    cout << size1<<endl;
}

int main(int argc, const char * argv[]) {
// benchmarkList();
 //  benchmarkBST();
   // benchmarkVector();
    // benchmarkAVL();
//    demoList();
//    demoBST();
//    demoVector();
//    demoAVL();
  
    return 0;
}
