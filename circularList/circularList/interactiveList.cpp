//
//  interactiveList.cpp
//  circularList
//
//  Created by Mykola Medynsky on 3/5/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//
#include "interactiveList.hpp"
#include "pointstructure.hpp"
List* addToEmpty(Point value)
{
    List* node = new List;
    node->data = value;
    node->index = 0;
    node->next = node;
    return node;
}

List* addElement(List* list, int index, Point value, int& currentSize)
{
    if (currentSize==0)
    {
        list = addToEmpty(value);
        currentSize++;
    }
    else{
        List* node = new List, *prevNode;
        List* p = list->next;
        prevNode = list;
        if (index<0)
        {
            index=abs(index);
            index = index%currentSize;
            index = currentSize-index;
        }
        else
            index = (index%currentSize);
        currentSize++;
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
List* deleteElement(List* list, int index, int& currentSize)
{
    List* node = list, *prevNode;


    if (currentSize == 0)
    {
        list =nullptr;
    }
   else if(node->next==list)
    {
        list = nullptr;
    }
    else{
        if (index<0)
        {
            index=abs(index-1);
            index = index%currentSize;
            index = currentSize-index;
        }
        else
            index = index%currentSize;
        do {
            prevNode=node;
            node=node->next;
        }while(node->index!=index);
        prevNode->next = node->next;
        List* currNode = node->next;
        do
        {
            currNode->index--;
            currNode = currNode->next;
        }while(currNode!=list->next);
    }
    currentSize--;
    return list;
}
void getValue(int index, List* list, int currentSize)
{
    List* node = list->next;
    if (index<0)
    {
        index = abs(index);
        index = index%currentSize;
        index = currentSize-index;
    }
    else
        index = index%currentSize;
    do{
        node = node->next;
        
    }while(node->index!=index);
    cout<< node->index<< ":" << node->data.x << " "<< node->data.y<< " "<<node->data.z<<endl;
    
}
void setValue(int index, List* list, int currentSize)
{
    List* node = list->next;

    if (index<0)
    {
        index = abs(index);
        index = index%currentSize;
        index = currentSize-index;
    }
    else
        index = index%currentSize;
  
    do{
        node = node->next;
    }while(node->index!=index);
    
    node->data.enterCoord();
}
void setValue(int index, List* list, Point value,int currentSize)
{
    List* node = list->next;
    if (index<0)
    {
        index = abs(index);
        index = index%currentSize;
        index = currentSize-index;
    }
    else
        index = index%currentSize;
    
    do{
        node = node->next;
        
    }while(node->index!=index);
    node->data.x = value.x;
    
    node->data.y = value.y;
   
    node->data.z = value.z;
}
void printCircularList(List *list)
{
    
    List *p;

    p = list -> next;
    do
    {
        cout << p->index<< ":"<< p->data.x << " "<< p->data.y<< " "<<p->data.z<<endl;;
        p = p -> next;
        
    }while(p != list->next);
}
void interactiveList()
{
    cout << "WELCOME IN INTERACTIVE LIST MODE"<<endl;
    cout << "--------------------------------"<<endl;
    int action;
    bool checkIfCreatedList = false, loopFlag = true;
    List* list = nullptr;
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
                    list = addElement(list, index, value, currentSize);
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
                else if (currentSize==0)
                    cout << "Error! There is no elements to delete. You need to add some elements in list"<<endl;
                else{
                    cout << "Enter the index of element that you want to delete" <<endl;
                    int index;
                    cin >> index;
                   list =  deleteElement(list, index, currentSize);
                }
                break;
            }
            case 4:{
                if (!checkIfCreatedList)
                {
                    cout << "Error. You need to create list and add elements in it if you want to use this option"<<endl;
                }
                else if (checkIfCreatedList&&currentSize==0) {
                    cout << "Error! There is no elements in list. You need to add minimum one element if you want to use this case"<<endl;
                }
                else{
                    cout << "Enter the index of element that you want to get"<<endl;
                    int index;
                    cin>> index;
                    cout << "Element "<< index<<endl;
                    getValue(index, list, currentSize);
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
                    cout << "Enter the index of element which you want to set value"<<endl;
                    int index;
                    cin>> index;
                    setValue(index, list, currentSize);
                }
                break;
            }
            case 6:{
                if (currentSize==0)
                    cout << "List is empty"<<endl;
                else{
                    cout << "All elements"<<endl;
                    printCircularList(list);
                }
                break;
            }
            default:
                loopFlag = false;
                break;
                
        }
    }
}
void demoList()
{
    cout << "Firstly in interactive mode you need to create empty list"<<endl;
    List* list = nullptr;
    cout << "Empty list has just been created"<<endl;
    cout << "After creating empty list you can add points in list"<<endl;
    int currentSize = 0;
    Point value;
    value.x = 0;
    value.y = 0;
    value.z = 0;
    list = addElement(list, 0, value, currentSize);
    printCircularList(list);
    cout << "Added first point to list with x,y,z coordinates 0"<<endl;
    cout<< "Now we can add the point before zero index for example with x,y,z coordinates 1"<<endl;
    value.x = 1;
    value.y = 1;
    value.z = 1;
    addElement(list, 0, value, currentSize);
    printCircularList(list);
    cout<< "Let's add the point before first index for example with x,y,z coordinates 2"<<endl;
    value.x = 2;
    value.y = 2;
    value.z = 2;
    addElement(list, 1, value, currentSize);
    cout << "That is how our list look like"<<endl;
    printCircularList(list);
    cout << "As this list is circular, you can enter any index that you want to push the point before. For example you want to add the element befor index 5, if you have three unique points it will add the point after going loop and add it before element with index 3."<<endl;
    value.x = 5;
    value.y = 5;
    value.z = 5;
    addElement(list, 5, value, currentSize);
    cout << "That is how our list look like"<<endl;
    printCircularList(list);
    
    cout << "So, now we can delete the point in list. Let's delete point with index 1"<<endl;
    list = deleteElement(list, 1, currentSize);
    cout << "That is how our list look like"<<endl;
    printCircularList(list);
    cout << "You can also change any value by index. Let's change element with index 1, by setting x,y,z coordinates 7. That is how element look like before changing"<<endl;
    getValue(1, list,currentSize);
    value.x = 7;
    value.y = 7;
    value.z = 7;
    setValue(1, list,value,currentSize);
    cout << "After changing"<<endl;
    getValue(1, list,currentSize);
    cout << "That is how our list look like"<<endl;
    printCircularList(list);
}
void benchmark()
{
    List* list = nullptr;
    int currentSize = 0;
    double start_time = clock();
    for (int i = 0; i < 10000;i++){
        Point value;
        value.x = i;
        value.y = i;
        value.z = i;
        list = addElement(list, i, value,currentSize);
        getValue(i, list, currentSize);
    }

    for (int i = 0; i < 5000; i++)
    {
       list =  deleteElement(list, i,currentSize);
    }

    for (int i = 5; i < 4000; i++)
    {
        Point value;
        value.x = i;
        value.y = i;
        value.z = i;
        setValue(i, list, value,currentSize);
      
    }
    double end_time = clock();
    double time =( end_time-start_time)/(1000*320);
    cout<< "Seconds" << time<<endl;
}
