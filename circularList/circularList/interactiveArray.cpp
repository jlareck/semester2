//
//  interactiveArray.cpp
//  circularList
//
//  Created by Mykola Medynsky on 3/5/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//

#include "interactiveArray.hpp"
#include "pointstructure.hpp"
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
    
    for (int i = index; i<currentSize-1; i++)
    {
        arr[i]=arr[i+1];
    }
    currentSize--;
}
void addElement(Point value, Point arr[], int index, int& currentSize)
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
        else
            index = index%currentSize;
        
        Point temp = arr[index];
        arr[index] = value;
        index++;
        while(index<=currentSize)
        {
            
            Point k = arr[index];
            arr[index] = temp;
            temp = k;
            index++;
        }
    }
    currentSize++;
}
void setValue( Point arr[],int currentSize)
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
void setValue( Point arr[],int currentSize, Point value, int index)
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
    
    arr[index] = value;
}
void getValue(int index, Point arr[], int currentSize)
{
    if (index<0)
    {
        
        index=abs(index);
        index = index%currentSize;
        index = currentSize-index;
    }
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

void interactiveArray()
{
    cout << "WELCOME IN INTERACTIVE ARRAY MODE"<<endl;
    cout << "---------------------------------"<<endl;
    int action;
    bool checkIfCreatedList = false, loopFlag = true;
    const int size = 5;
    Point list[size];
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
                    if (size == currentSize)
                        cout << "List is full, please delete any element to add new"<<endl;
                    else{
                        cout << "Enter index before you want to add element"<<endl;
                        int index;
                        
                        cin>>index;
                        cout << "Enter value"<<endl;
                        Point value;
                        value.enterCoord();
                        addElement(value, list, index, currentSize);
                    }
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
                    getValue(index,list, currentSize);
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
                    setValue(list, currentSize);
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
void demoArray()
{
    cout << "Firstly in interactive mode you need to create empty list"<<endl;
    const int size = 4;
    Point list[size];

    cout << "Empty list has just been created. Maximum size of it is 4"<<endl;
    cout << "After creating empty list you can add points in list"<<endl;
    int currentSize = 0;
    Point value;
    value.x = 0;
    value.y = 0;
    value.z = 0;
    addElement(value, list, 0, currentSize);
    printArray(list, currentSize);
    cout << "Added first point to list with x,y,z coordinates 0"<<endl;
    cout<< "Now we can add the point before index 0 for example with x,y,z coordinates 1"<<endl;
    value.x = 1;
    value.y = 1;
    value.z = 1;
    addElement(value, list, 0, currentSize);
    printArray(list, currentSize);
    cout<< "Let's add the point before index 1 for example with x,y,z coordinates 2"<<endl;
    value.x = 2;
    value.y = 2;
    value.z = 2;
    addElement(value, list, 1, currentSize);
    cout << "That is how our list look like"<<endl;
    printArray(list, currentSize);
    cout << "As this list is circular, you can enter any index that you want to push the point before. For example you want to add the element befor index 5, if you have three unique points it will add the point after going loop and add it before element with index 3"<<endl;
    value.x = 5;
    value.y = 5;
    value.z = 5;
    addElement(value, list, 5, currentSize);
    cout << "That is how our list look like"<<endl;
    printArray(list, currentSize);
    cout <<"But if you want to add new point to array, while array is full you will have an error and you must delete some element to add new"<< endl;

    cout << "So, now we delete the point in list. Let's delete point with index 1"<<endl;
    deleteElement(list, 1, currentSize);
    cout << "That is how our list look like"<<endl;
    printArray(list, currentSize);
    cout << "You can also change any value by index. Let's change element with index 1, by setting x,y,z coordinates 7. That is how element look like before changing"<<endl;
    getValue(1,list,currentSize);
    value.x = 7;
    value.y = 7;
    value.z = 7;
    setValue(list, currentSize, value, 1);
    cout << "After changing"<<endl;
    getValue(1,list,currentSize);
    cout << "That is how our list look like"<<endl;
    printArray(list, currentSize);
    
}
void benchmarkArray()
{
    const int size = 10000;
    Point list[size];
    double start_time = clock();
    int currentSize = 0;
    for (int i = 0; i < 10000;i++){
        Point value;
        value.x = i;
        value.y = i;
        value.z = i;
        addElement(value, list, i, currentSize);
        getValue(i+1, list, currentSize);
    }
    for (int i = 0; i < 5000; i++)
    {
        deleteElement(list, i, currentSize);
    }
    for (int i = 5; i < 4000; i++)
    {
        Point value;
        value.x = i;
        value.y = i;
        value.z = i;
        setValue(list, currentSize, value, i);
        //  getValue(i, list);
    }
    double end_time = clock();
    double time =( end_time-start_time)/(1000*320);
    cout<< "Seconds" << time<<endl;
}
