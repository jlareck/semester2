//
//  interactiveList.hpp
//  circularList
//
//  Created by Mykola Medynsky on 3/5/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//

#ifndef interactiveList_hpp
#define interactiveList_hpp


#include "pointstructure.hpp"
using namespace std;

struct List{
    Point data;
    int index;
    List* next;
};
List* addToEmpty(Point );

List* addElement(List* , int , Point, int& );
List* deleteElement(List* , int,int& );
void getValue(int , List*, int );
void setValue(int , List* , int);
void setValue(int , List* , Point ,int );
void printCircularList(List *);
void interactiveList();
void demoList();
void benchmark();
#endif /* interactiveList_hpp */
