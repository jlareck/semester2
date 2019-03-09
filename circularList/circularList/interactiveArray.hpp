//
//  interactiveArray.hpp
//  circularList
//
//  Created by Mykola Medynsky on 3/5/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//

#ifndef interactiveArray_hpp
#define interactiveArray_hpp
#include "pointstructure.hpp"
void deleteElement(Point[] , int , int& );
void addElement(Point , Point [], int , int& );
void setValue( Point[],int );
void setValue( Point ,int , Point , int );
void getValue(int , Point[], int );
void printArray(Point [], int );
void interactiveArray();
void demoArray();
void benchmarkArray();
#endif /* interactiveArray_hpp */
