//
//  interactiveVector.cpp
//  circularList
//
//  Created by Mykola Medynsky on 3/5/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//

#include "interactiveVector.hpp"

void addElement(vector<Point>& vec, int index, Point value)
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
        else
            index = index%vec.size();
        vec.insert(vec.begin()+index, value);
    }
}

void deleteElement(vector<Point>& vec, int index)
{
    if (index<0)
    {
        index=abs(index);
        index = index%vec.size();
        index = vec.size()-index+1;
    }
    
    else
        index = index%vec.size();
    cout << "Index " << index<<"Size"<< vec.size() <<endl;
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
void setValue(vector<Point>& vec, Point data, int index)
{
    if (index<0)
    {
        index=abs(index);
        index = index%vec.size();
        index = vec.size()-index;
    }
    else
        index = index%vec.size();
    

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
    cout << "WELCOME IN INTERACTIVE VECTOR MODE"<<endl;
    cout << "----------------------------------"<<endl;
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
                    addElement(list, index, value);
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
                if (list.size()==0)
                    cout << "List is empty"<<endl;
                else
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
void demoVector()
{
    cout << "Firstly in interactive mode you need to create empty list"<<endl;
   
    cout << "Empty list has just been created"<<endl;
    cout << "After creating empty list you can add points in list"<<endl;
    vector<Point> list;
    Point value;
    value.x = 0;
    value.y = 0;
    value.z = 0;
    addElement(list, 0, value);
    printAllElementsInVector(list);
    cout << "Added first point to list with x,y,z coordinates 0"<<endl;
    cout<< "Now we can add the point before zero index for example with x,y,z coordinates 1"<<endl;
    value.x = 1;
    value.y = 1;
    value.z = 1;
    addElement(list, 0, value);
    printAllElementsInVector(list);
    cout<< "Let's add the point before first index for example with x,y,z coordinates 2"<<endl;
    value.x = 2;
    value.y = 2;
    value.z = 2;
    addElement(list, 1, value);
    
    cout << "That is how our list look like"<<endl;
    printAllElementsInVector(list);
    cout << "As this list is circular, you can enter any index that you want to push the point before. For example you want to add the element befor index 5, if you have three unique points it will add the point after going loop and add it before element with index 3"<<endl;
    value.x = 5;
    value.y = 5;
    value.z = 5;
    addElement(list, 5, value);
    cout << "That is how our list look like"<<endl;
    printAllElementsInVector(list);
    cout << "So, now we can delete the point in list. Let's delete point with index 0"<<endl;
    deleteElement(list, 1);
    cout << "That is how our list look like"<<endl;
    printAllElementsInVector(list);
    cout << "You can also change any value by index. Let's change element with index 1, by setting x,y,z coordinates 7. That is how element look like before changing"<<endl;
    getValue(list, 1);
    value.x = 7;
    value.y = 7;
    value.z = 7;
    setValue(list, value, 1);
    cout << "After changing"<<endl;
    getValue(list, 1);
    cout << "That is how our list look like"<<endl;
    printAllElementsInVector(list);
}
void benchmarkVector()
{
    
    vector<Point> list;
    double start_time = clock();
    for (int i = 0; i < 10000;i++){
        Point value;
        value.x = i;
        value.y = i;
        value.z = i;
        addElement(list, 0, value);
        getValue(list, i+1);
    }
    for (int i = 0; i < 5000; i++)
    {
        deleteElement(list, i);
    }
    for (int i = 5; i < 4000; i++)
    {
        Point value;
        value.x = i;
        value.y = i;
        value.z = i;
        setValue(list, value, i);
        //  getValue(i, list);
    }
    double end_time = clock();
    double time =( end_time-start_time)/(1000*320);
    cout<< "Seconds" << time<<endl;
}
