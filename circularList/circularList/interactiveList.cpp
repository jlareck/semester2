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
void setValue(int index, List* list, Point value)
{
    List* node = list->next;
    int n = countNodes(list);
    index = index%n;
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
    if (list == NULL)
    {
        cout << "List is empty." << endl;
        return;
    }
    p = list -> next;
    do
    {
        cout << p->data.x << " "<< p->data.y<< " "<<p->data.z<<endl;;
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
void demoList()
{
    cout << "Firstly in interactive mode you need to create empty list"<<endl;
    List* list = nullptr;
    cout << "Empty list has just been created"<<endl;
    cout << "After creating empty list you can add points in list"<<endl;

    Point value;
    value.x = 0;
    value.y = 0;
    value.z = 0;
    list = pushBeforeIndex(list, 0, value);
    printCircularList(list);
    cout << "Added first point to list with x,y,z coordinates 0"<<endl;
    cout<< "Now we can add the point before zero index for example with x,y,z coordinates 1"<<endl;
    value.x = 1;
    value.y = 1;
    value.z = 1;
    pushBeforeIndex(list, 0, value);
    printCircularList(list);
    cout<< "Let's add the point before first index for example with x,y,z coordinates 2"<<endl;
    value.x = 2;
    value.y = 2;
    value.z = 2;
    pushBeforeIndex(list, 1, value);
    cout << "That is how our list look like"<<endl;
    printCircularList(list);
    cout << "As this list is circular, you can enter any index that you want to push the point before. For example you want to add the element befor index 5, if you have three unique points it will add the point after going loop and add it before element with index 3"<<endl;
    value.x = 5;
    value.y = 5;
    value.z = 5;
    pushBeforeIndex(list, 5, value);
    cout << "That is how our list look like"<<endl;
    printCircularList(list);
    cout << "So, now we can delete the point in list. Let's delete point wit index 0"<<endl;
    deleteNode(list, 1);
    cout << "That is how our list look like"<<endl;
    printCircularList(list);
    cout << "You can also change any value by index. Let's change element with index 1, by setting x,y,z coordinates 7. That is how element look like before changing"<<endl;
    getValue(1, list);
    value.x = 7;
    value.y = 7;
    value.z = 7;
    setValue(1, list,value);
    cout << "After changing"<<endl;
    getValue(1, list);
    cout << "That is how our list look like"<<endl;
    printCircularList(list);
}
