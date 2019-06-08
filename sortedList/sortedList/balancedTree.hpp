//
//  balancedTree.hpp
//  sortedList
//
//  Created by Mykola Medynsky on 5/26/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//

#ifndef balancedTree_hpp
#define balancedTree_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
struct Point{
    int x;
    int y;
    int z;
};
class AVLNode
{
public:
    Point data;
    AVLNode *left;
    AVLNode *right;
    int height;
};
Point plusFive(Point);
void createRandPoint(Point&);
bool equality(Point ,Point);
bool comparator1(const Point& ,const Point&);
bool comparator2(const Point& ,const Point&);
bool comparator3(const Point& ,const Point&);
bool comparator4(const Point& ,const Point&);
AVLNode* FindMax(AVLNode* );
AVLNode* deleteNode(AVLNode*, Point);
AVLNode* minValueNode(AVLNode* );
void searchElementsInRange(AVLNode*, Point, Point);
AVLNode* search(AVLNode*, Point);
int max(int , int );
int height(AVLNode*);
AVLNode* newNode1(Point );
AVLNode* rightRotate(AVLNode*);
AVLNode* leftRotate(AVLNode *);
int getBalance(AVLNode *);
AVLNode* insert1(AVLNode* , Point );

void inorder(AVLNode *);
void benchmarkAVL();
void task5();
void task4();
#endif /* balancedTree_hpp */
