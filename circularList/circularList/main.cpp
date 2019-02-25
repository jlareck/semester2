//
//  main.cpp
//  circularList
//
//  Created by Mykola Medynsky on 2/21/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;
struct Point{
    int x;
    int y;
    int z;
};

struct List{
    Point data;
    int index;
    List* next;
};
List* addToEmpty(Point value)
{
    List* node = new List;
    node->data = value;
    node->index = 0;
    node->next = node;
    return node;
}
int countNodes(List* head)
{
    List* temp = head;
    int result = 0;
    if (head != NULL) {
        do {
            temp = temp->next;
            result++;
        } while (temp != head);
    }
    
    return result;
}

List* pushBeforeIndex(List* list, int index, Point value)
{
    List* node = new List, *prevNode;
    List* p = list->next;
    prevNode = list;
    int numberOfNodes = countNodes(list);
    if (index>=numberOfNodes)
    {
        index = index%numberOfNodes;
    }
    do{
        if (p->index == index)
        {
            node->data = value;
            prevNode->next = node;
            node->index = index;
            node->next = p;
            while(p!=list->next) {
                p->index++;
                p=p->next;
            }
            return list;
        }
        prevNode = p;
        p = p->next;
        
        
    }while(p!=list->next);
    return list;
}
void deleteNode(List* list, int index)
{
    List* node = list, *prevNode;
    int n = countNodes(list);
    index = index%n;
    do {
        prevNode=node;
        node=node->next;
    }while(node->index!=index);
    prevNode->next = node->next;
    free(node);
    List* currNode = node->next;
    do
    {
        currNode->index--;
        currNode = currNode->next;
    }while(currNode!=list->next);
    
}
void getValue(int index, List* list)
{
    List* node = list->next;
    int n = countNodes(list);
    index = index%n;
    do{
        node = node->next;
        
    }while(node->index!=index);
    cout<< node->index<< ":" << node->data.x << " "<< node->data.y<< " "<<node->data.z<<endl;
    
}
void setValue(int index, List* list)
{
    List* node = list->next;
    int n = countNodes(list);
    index = index%n;
    do{
        node = node->next;
        
    }while(node->index!=index);
    cout << "Enter data.x: "<<endl;
    cin >> node->data.x;
    cout << "Enter data.y: "<<endl;
    cin >> node->data.y;
    cout << "Enter data.z: "<<endl;
    cin >> node->data.z;
    
}
void traverse(List *last)
{
    List *p;
    if (last == NULL)
    {
        cout << "List is empty." << endl;
        return;
    }
    p = last -> next;
    do
    {
        cout<< p->index<< ":" << p->data.x << " "<< p->data.y<< " "<<p->data.z<<endl;;
        p = p -> next;
        
    }while(p != last->next);
}

void linkedList() {
    Point point;
    point.x = 5;
    point.y = 6;
    point.z = 7;
    
    List* list = addToEmpty(point);
    
 //   traverse(list);
    point.x = 10;
    point.y = 11;
    point.z = 12;
    int givenIndex = 1;
    pushBeforeIndex(list, 0,point);
 // traverse(list);
    point.x = 14;
    point.y = 15;
    point.z = 16;
    givenIndex = 3;
    pushBeforeIndex(list, 1, point);
    point.x = 22;
    point.y = 24;
    point.z = 25;
    pushBeforeIndex(list, 2, point);
    point.x = 112;
    point.y = 124;
    point.z = 125;
    pushBeforeIndex(list, 8, point);
    traverse(list);
    cout << "fdasf"<<endl;
    setValue(0, list);
    getValue(0, list);
//    cout << endl;
//    deleteNode(list, 8);
//    traverse(list);
//    cout<<endl;
//    deleteNode(list, 2);
//    traverse(list);
//    cout<<endl;
//    deleteNode(list, 0);
//    traverse(list);
}

void addToEmptyVector(vector<int>& vec, int value)
{
    vec.push_back(value);
}

void addElementInVector(vector<int>& vec, int index, int value)
{
    index=(index-1)%vec.size();
    vec.insert(vec.begin()+index, value);
}
void deleteElement(vector<int>& vec, int index)
{
    index=index%vec.size();
    vec.erase(vec.begin() + index);
}
void getFromVector(vector<int> vec, int index)
{
     index=index%vec.size();
    cout << vec[index]<<endl;
}
void printVector(vector<int> vec)
{
    for (int i = 0; i<vec.size(); i++)
    {
        cout << vec[i]<<endl;
    }
}
void circularVector()
{
    vector<int> circularList;
    addToEmptyVector(circularList, 3);
    addElementInVector(circularList, 2, 2);
    addElementInVector(circularList, 1, 1);
    printVector(circularList);
}



void addToEmptyArray(Point value, Point arr[])
{
    arr[0] = value;
}
void addToEmptyArray(int value, int arr[])
{
    arr[0] = value;
}
int getNumberOfElements(int arr[])
{
    int i = 0;
    while(arr[i]!=NULL)
    {
        i++;
    }
    return i;
}
void deleteElement(int arr[], int index, const int size)
{
    int n = getNumberOfElements(arr);
    for (int i = index; i<n; i++)
    {
        arr[i]=arr[i+1];
    }
}
void pushBeforeKeyElement(int value, int arr[], int index)
{
    int i;
    i=(index-1)%getNumberOfElements(arr);
    int temp = arr[i];
    arr[i] = value;
    int k;
    while(arr[i]!=NULL)
    {
        i++;
        k = arr[i];
        arr[i] = temp;
        temp = k;
    }
}
void set(int index, int arr[], int value)
{
    int n = getNumberOfElements(arr);
    index = index%n;
    arr[index] = value;
}
void get(int index, int arr[])
{
    int n = getNumberOfElements(arr);
    index = index%n;
    cout << arr[index]<<endl;
}
void printArray(int arr[])
{
    int i = 0;
    while (arr[i]!=NULL)
    {
        cout<< i<< ": " << arr[i]<<endl;
        i++;
    }
}
void circularArray(){
    const int size = 100;
    int arr[size];
//    addToEmptyArray(12, arr);
////    int i = 0;
////    int a = getNumberOfElements(arr);
//   // cout << a <<endl;
//    pushBeforeKeyElement(4, arr, 0);
//    printArray(arr);
//    cout << "-----"<<endl;
//    pushBeforeKeyElement(13, arr, 1);
//    printArray(arr);
//    deleteElement(arr, 2,size);
//    cout << "-----"<<endl;
//    printArray(arr);
//    pushBeforeKeyElement(25, arr, 3);
    addToEmptyArray(3, arr);
    pushBeforeKeyElement(2, arr, 2);
    pushBeforeKeyElement(1, arr, 1);
    printArray(arr);
}
int main()
{
    circularVector();
    cout << "-----"<<endl;
    circularVector();
    return 0;
}
