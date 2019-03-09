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
int countNodes(List* );
List* addElement(List* , int , Point );
List* deleteElement(List* , int );
void getValue(int , List* );
void setValue(int , List* );
void printCircularList(List *);
void interactiveList();
void demoList();
void benchmark();
#endif /* interactiveList_hpp */
