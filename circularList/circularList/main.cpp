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
    void enterCoord()
    {
        cout << "Enter x coord"<<endl;
        cin>> x;
        cout << "Enter y coord"<<endl;
        cin>> y;
        cout << "Enter z coord"<<endl;
        cin>> z;
    }
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
    if (countNodes(list)==0)
    {
      list = addToEmpty(value);
    }
    else{
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
    }
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

void printCircularList(List *list)
{
    List *p;
    if (list == NULL)
    {
        cout << "List is empty." << endl;
        return;
    }
    p = list -> next;
    do
    {
        cout<< p->index<< ":" << p->data.x << " "<< p->data.y<< " "<<p->data.z<<endl;;
        p = p -> next;
        
    }while(p != list->next);
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
    printCircularList(list);
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
void interactiveList()
{
    int action;
    bool checkIfCreatedList = false, loopFlag = true;
    List* list;
    while(loopFlag){
        cout << "Actions" << endl;
        cout << 1 << " - Create empty"<<endl;
        cout << 2 << " - Add element before key element"<<endl;
        cout << 3 << " - Delete element by key" <<endl;
        cout << 4 << " - Get element" << endl;
        cout << 5 << " - Set element" <<endl;
        cout << 6 << " - Print all elements" <<endl;
        cout << "Press any other key to exit"<<endl;
        cout << endl;
        cout << "Enter action"<<endl;
        cin >> action;
        switch(action){
            case 1:{
                if (!checkIfCreatedList)
                {
                    
                    checkIfCreatedList = true;
                    cout << "The list was created sucsesfully"<<endl;
                }
                else
                    cout << "You have already created circular list"<<endl;
                break;
            }
            case 2:{
                if (checkIfCreatedList)
                {
                    cout << "Enter index before you want to add element"<<endl;
                    int index;
                    
                    cin>>index;
                    cout << "Enter value"<<endl;
                    Point value;
                    value.enterCoord();
                    cout << value.x << " f "<< value.y<<endl;
                    list = pushBeforeIndex(list, index, value);
                }
                else
                    cout << "Error! Firstly you need to create a list"<<endl;
                break;
            }
            case 3:{
                if (!checkIfCreatedList)
                {
                    cout << "You didn't create a list, you need to create and add elements to it if you want to use this function"<<endl;
                }
                else if (countNodes(list)==0)
                    cout << "Error! There is no elements to delete. You need to add some elements in list"<<endl;
                else{
                    cout << "Enter the index of element that you want to delete" <<endl;
                    int index;
                    cin >> index;
                    deleteNode(list, index);
                }
                break;
            }
            case 4:{
                if (!checkIfCreatedList)
                {
                    cout << "Error. You need to create list and add elements in it if you want to use this option"<<endl;
                }
                else if (checkIfCreatedList&&countNodes(list)==0) {
                    cout << "Error! There is no elements in list. You need to add minimum one element if you want to use this case"<<endl;
                }
                else{
                    cout << "Enter the index of element that you want to get"<<endl;
                    int index;
                    cin>> index;
                    cout << "Element "<< index<<endl;
                    getValue(index, list);
                }
                break;
            }
            case 5:{
                if (!checkIfCreatedList)
                {
                    cout << "Error! You didn't create a list. Create a list and add minimum one element"<<endl;
                }
               else if(countNodes(list)==0) {
                    cout << "Error! There is no elements in list"<<endl;
                }
                else{
                    cout << "Enter the index of element which you want to set value"<<endl;
                    int index;
                    cin>> index;
                    setValue(index, list);
                }
                break;
            }
            case 6:{
                cout << "All elements"<<endl;
                printCircularList(list);
                break;
            }
            default:
                loopFlag = false;
                break;
                
        }
    }
}

void addElementInVector(vector<Point>& vec, int index, Point value)
{
    if (vec.size()==0)
    {
        vec.push_back(value);
    }
    else{
        if (index<0)
        {
            index=abs(index-1);
            index = index%vec.size();
            index = vec.size()-index;
        }
       //index = vec.size()-index;
        else
            index = index%vec.size();
        vec.insert(vec.begin()+index, value);
    }
}
void deleteElement(vector<Point>& vec, int index)
{
    //cout << "Index " << index<<endl;
    if (index<0)
    {
        index=abs(index);
        index = index%vec.size();
        index = vec.size()-index+1;
    }
    //index = vec.size()-index;
    else
        index = index%vec.size();
    cout << "Index " << index<<"Size"<< vec.size() <<endl;
  //  index = vec.size()-index;
    vec.erase(vec.begin() + index);
}
void getValue(vector<Point> vec, int index)
{
    if (index<0)
    {
        index=abs(index);
        index = index%vec.size();
        index = vec.size()-index;
    }
    //index = vec.size()-index;
    else
        index = index%vec.size();
     cout << vec[index].x<< " "<< vec[index].y<< " "<<vec[index].z<<endl;
}
void setValue(vector<Point>& vec)
{
    cout << "Enter the index of element which you want to set value"<<endl;
    int index;
    cin>> index;
    if (index<0)
    {
        index=abs(index);
        index = index%vec.size();
        index = vec.size()-index;
    }
    //index = vec.size()-index;
    else
        index = index%vec.size();
    cout << "Enter data.x: "<<endl;
    Point data;
    cin >> data.x;
    cout << "Enter data.y: "<<endl;
    cin >> data.y;
    cout << "Enter data.z: "<<endl;
    cin >> data.z;
    vec[index] = data;
}
void printAllElementsInVector(vector<Point> vec)
{
    cout << "All elements"<<endl;
    for (int i = 0; i<vec.size(); i++)
    {
        cout << vec[i].x<< " "<< vec[i].y<< " "<< vec[i].z<<endl;
    }
}

void interactiveVector()
{
    int action;
    bool checkIfCreatedList = false, loopFlag = true;
    vector<Point> list;
    while(loopFlag){
        cout << "Actions" << endl;
        cout << 1 << " - Create empty"<<endl;
        cout << 2 << " - Add element before key element"<<endl;
        cout << 3 << " - Delete element by key" <<endl;
        cout << 4 << " - Get element" << endl;
        cout << 5 << " - Set element" <<endl;
        cout << 6 << " - Print all elements" <<endl;
        cout << "Press any other key to exit"<<endl;
        cout << endl;
        cout << "Enter action"<<endl;
        cin >> action;
        switch(action){
            case 1:{
                if (!checkIfCreatedList)
                {
                    
                    checkIfCreatedList = true;
                    cout << "The list was created sucsesfully"<<endl;
                }
                else
                    cout << "You have already created circular list"<<endl;
                break;
            }
            case 2:{
                if (checkIfCreatedList)
                {
                    cout << "Enter index before you want to add element"<<endl;
                    int index;
                    
                    cin>>index;
                    cout << "Enter value"<<endl;
                    Point value;
                    value.enterCoord();
                    addElementInVector(list, index, value);
                }
                else
                    cout << "Error! Firstly you need to create a list"<<endl;
                break;
            }
            case 3:{
                if (!checkIfCreatedList) {
                    cout << "You didn't create a list, you need to create and add elements to it if you want to use this function"<<endl;
                }
                else if (list.size()==0)
                    cout << "Error! There is no elements to delete. You need to add some elements in list"<<endl;
                else {
                    cout << "Enter the index of element that you want to delete" <<endl;
                    int index;
                    cin >> index;
                    deleteElement(list, index);
                }
                break;
            }
            case 4:{
                if (!checkIfCreatedList)
                {
                    cout << "Error. You need to create list and add elements in it if you want to use this option"<<endl;
                }
                else if (list.size()==0) {
                    cout << "Error! There is no elements in list. You need to add minimum one element if you want to use this case"<<endl;
                }
                else{
                    cout << "Enter the index of element that you want to get"<<endl;
                    int index;
                    cin>> index;
                    cout << "Element "<< index<<endl;
                    getValue(list, index);
                }
                break;
            }
            case 5:{
                if (!checkIfCreatedList)
                {
                    cout << "Error! You didn't create a list. Create a list and add minimum one element"<<endl;
                }
                else if(list.size()==0) {
                    cout << "Error! There is no elements in list"<<endl;
                }
                else{
                    setValue(list);
                }
                break;
            }
            case 6:{
                printAllElementsInVector(list);
                break;
            }
            default:
                loopFlag = false;
                cout << "Good bye!"<<endl;
                break;
        }
    }
}

//void addToEmptyArray(Point value, Point arr[])
//{
//    arr[0] = value;
//}

void deleteElement(int arr[], int index, const int size, int& currentSize)
{
    if (index<0)
    {
        
        index=abs(index);
        index = index%currentSize;
        index = currentSize-index;
    }
    else
        index = index%currentSize;
    
    for (int i = index; i<currentSize; i++)
    {
        arr[i]=arr[i+1];
    }
    currentSize--;
}
void deleteElement(Point arr[], int index, int& currentSize)
{
    if (index<0)
    {
        
        index=abs(index);
        index = index%currentSize;
        index = currentSize-index;
    }
    else
        index = index%currentSize;
    
    for (int i = index; i<currentSize; i++)
    {
        arr[i]=arr[i+1];
    }
    currentSize--;
}
void pushBeforeKeyElement(int value, int arr[], int index, int& currentSize)
{
    if (currentSize==0)
    {
        arr[0] = value;
    }
    else{
        if (index<0)
        {
            
            index=abs(index);
            index = index%currentSize;
            index = currentSize-index;
        }
        //index = vec.size()-index;
        else
            index = index%currentSize;
        
        int temp = arr[index];
        arr[index] = value;
        int k;
        while(index<=currentSize)
        {
            index++;
            k = arr[index];
            arr[index] = temp;
            temp = k;
        }
    }
    currentSize++;
}
void pushBeforeKeyElement(Point value, Point arr[], int index, int& currentSize)
{
    if (currentSize==0)
    {
        arr[0] = value;
    }
    else{
        if (index<0)
        {
            
            index=abs(index);
            index = index%currentSize;
            index = currentSize-index;
        }
        //index = vec.size()-index;
        else
            index = index%currentSize;
        
        Point temp = arr[index];
        arr[index] = value;
        Point k;
        while(index<=currentSize)
        {
            index++;
            k = arr[index];
            arr[index] = temp;
            temp = k;
        }
    }
    currentSize++;
}
void set(int index, int arr[], int value,int currentSize)
{
    if (index<0)
    {
        
        index=abs(index);
        index = index%currentSize;
        index = currentSize-index;
    }
    //index = vec.size()-index;
    else
        index = index%currentSize;
    
}
void set( Point arr[],int currentSize)
{
    cout << "Enter the index of element which you want to set value"<<endl;
    int index;
    cin>> index;
    Point value;
    if (index<0)
    {
        
        index=abs(index);
        index = index%currentSize;
        index = currentSize-index;
    }
    //index = vec.size()-index;
    else
        index = index%currentSize;
    value.enterCoord();
    arr[index] = value;
}
void get(int index, int arr[], int currentSize)
{
    if (index<0)
    {
        
        index=abs(index);
        index = index%currentSize;
        index = currentSize-index;
    }
    //index = vec.size()-index;
    else
        index = index%currentSize;
}
void get(int index, Point arr[], int currentSize)
{
    if (index<0)
    {
        
        index=abs(index);
        index = index%currentSize;
        index = currentSize-index;
    }
    //index = vec.size()-index;
    else
        index = index%currentSize;
    cout << arr[index].x <<" "<< arr[index].y<<" "<<arr[index].z<<endl;
}
void printArray(Point arr[], int currentSize)
{
    int i = 0;
    while (i<currentSize)
    {
        cout << arr[i].x <<" "<< arr[i].y<<" "<<arr[i].z<<endl;
        i++;
    }
}
void circularArray(){
    const int size = 8;
    int arr[size];
    for (int i =0; i<size; i++)
    {
        arr[i] = 0;
    }
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
    
    int currentSize = 0;
    pushBeforeKeyElement(2, arr, 2, currentSize);
    pushBeforeKeyElement(3, arr, 0, currentSize);
    pushBeforeKeyElement(6, arr, -1, currentSize);
    pushBeforeKeyElement(10, arr, -2, currentSize);
    
    pushBeforeKeyElement(1, arr, 3, currentSize);
    pushBeforeKeyElement(1222, arr, -2, currentSize);
//    pushBeforeKeyElement(1000, arr, -1, currentSize);
//   printArray(arr, size, currentSize);
//  deleteElement(arr, 0, size, currentSize);
//    printArray(arr, size, currentSize);
//    vector<Point> vec;
//    Point point;
//    point.x = 2;
//    point.y = 0;
//    point.z = 0;
//    cout <<endl;
//    addElementInVector(vec, 2, point);
//    cout << "----------"<<endl;
//    printAllElementsInVector(vec);
//    point.x = 3;
//
//    addElementInVector(vec, -1, point);
//    cout << "----------"<<endl;
//    printAllElementsInVector(vec);
//    point.x = 6;
//    addElementInVector(vec, 1, point);
//    cout << "----------"<<endl;
//    printAllElementsInVector(vec);
//    point.x = 10;
//    addElementInVector(vec, 2, point);
//    cout << "----------"<<endl;
//    printAllElementsInVector(vec);
//    point.x = 1;
//    addElementInVector(vec, 9, point);
//    cout << "----------"<<endl;
//    printAllElementsInVector(vec);
//    point.x = 122;
//    addElementInVector(vec, -2, point);
//    cout << "----------"<<endl;
//    printAllElementsInVector(vec);
//    point.x = 1000;
//    addElementInVector(vec, -1, point);
//    cout << "----------"<<endl;
//    printAllElementsInVector(vec);
//    deleteElement(vec, 10);
  //  printAllElementsInVector(vec);
//    pushBeforeKeyElement(5, array, 1);
//    pushBeforeKeyElement(6, array, 1);
//    pushBeforeKeyElement(7, array, 1);
    
  //  deleteElement(array, 1, size);
  //  printArray(array,size);
}

void interactiveArray()
{
    int action;
    bool checkIfCreatedList = false, loopFlag = true;
    Point list[100];
    int currentSize = 0;
    while(loopFlag){
        cout << "Actions" << endl;
        cout << 1 << " - Create empty"<<endl;
        cout << 2 << " - Add element before key element"<<endl;
        cout << 3 << " - Delete element by key" <<endl;
        cout << 4 << " - Get element" << endl;
        cout << 5 << " - Set element" <<endl;
        cout << 6 << " - Print all elements" <<endl;
        cout << "Press any other key to exit"<<endl;
        cout << endl;
        cout << "Enter action"<<endl;
        cin >> action;
        switch(action){
            case 1:{
                if (!checkIfCreatedList)
                {
                    
                    checkIfCreatedList = true;
                    cout << "The list was created sucsesfully"<<endl;
                }
                else
                    cout << "You have already created circular list"<<endl;
                break;
            }
            case 2:{
                
                if (checkIfCreatedList)
                {
                    cout << "Enter index before you want to add element"<<endl;
                    int index;
                    
                    cin>>index;
                    cout << "Enter value"<<endl;
                    Point value;
                    value.enterCoord();
                    pushBeforeKeyElement(value, list, index, currentSize);
                }
                else
                    cout << "Error! Firstly you need to create a list"<<endl;
                break;
            }
            case 3:{
                if (!checkIfCreatedList) {
                    cout << "You didn't create a list, you need to create and add elements to it if you want to use this function"<<endl;
                }
                else if (currentSize==0)
                    cout << "Error! There is no elements to delete. You need to add some elements in list"<<endl;
                else {
                    cout << "Enter the index of element that you want to delete" <<endl;
                    int index;
                    cin >> index;
                    deleteElement(list, index, currentSize);
                }
                break;
            }
            case 4:{
                if (!checkIfCreatedList)
                {
                    cout << "Error. You need to create list and add elements in it if you want to use this option"<<endl;
                }
                else if (currentSize==0) {
                    cout << "Error! There is no elements in list. You need to add minimum one element if you want to use this case"<<endl;
                }
                else{
                    cout << "Enter the index of element that you want to get"<<endl;
                    int index;
                    cin>> index;
                    cout << "Element "<< index<<endl;
                    get(index,list, currentSize);
                }
                break;
            }
            case 5:{
                if (!checkIfCreatedList)
                {
                    cout << "Error! You didn't create a list. Create a list and add minimum one element"<<endl;
                }
                else if(currentSize==0) {
                    cout << "Error! There is no elements in list"<<endl;
                }
                else{
                    set(list, currentSize);
                }
                break;
            }
            case 6:{
                printArray(list,currentSize);
                break;
            }
            default:
                loopFlag = false;
                cout << "Good bye!"<<endl;
                break;
        }
    }
}
int main()
{
  //  cout << 12%5<<endl;
   // circularArray();
    //interactiveVector();
    interactiveArray();
    return 0;
}
