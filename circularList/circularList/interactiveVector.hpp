//
//  interactiveVector.hpp
//  circularList
//
//  Created by Mykola Medynsky on 3/5/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//

#ifndef interactiveVector_hpp
#define interactiveVector_hpp
#include "pointstructure.hpp"
#include <vector>
using namespace std;
void addElementInVector(vector<Point>& , int , Point );
void deleteElement(vector<Point>& , int );
void getValue(vector<Point> , int );
void setValue(vector<Point>& );
void printAllElementsInVector(vector<Point>);
void interactiveVector();
void demoVector();
#endif /* interactiveVector_hpp */
