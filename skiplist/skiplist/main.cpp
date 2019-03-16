//
//  main.cpp
//  skiplist
//
//  Created by Mykola Medynsky on 3/14/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//


#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
struct Node{
    int key;
    int value;
    Node** forward;
};
Node* initializer(int level)
{
    Node* node = new Node;
    node->forward = new Node*[level+1];
    for (int i = 0; i < level+1; i++)
    {
        node->forward[i] = NULL;
    }
    return node;
}
Node* createNode(int value, int key, int level)
{
    Node* node = new Node;
    node->key = key;
    node->value =value;
    node->forward = new Node*[level+1];
    for (int i = 0; i < level+1; i++)
    {
        node->forward[i] = NULL;
    }
    return node;
}
int randomLevel(const int maxLvl, float p){
    float randomNumber = (float)rand()/RAND_MAX;
    int lvl = 0;
    while (randomNumber < p)
    {
        lvl++;
        randomNumber = (float)rand()/RAND_MAX;
    }
    return min(lvl, maxLvl);
}
Node* insertElement(Node* node, int value, int key, const int maxLvl, float p, int& level)
{
    Node* currentNode = node;
    Node* update[maxLvl+1];
    for (int i = level; i>=0; i--)
    {
        while(currentNode->forward[i]!=NULL&&currentNode->forward[i]->key<key)
        {
            currentNode = currentNode->forward[i];
        }
        update[i] = currentNode;
    }
    currentNode = currentNode->forward[0];
    if (currentNode == NULL || currentNode->key != key)
    {
        int newRandomLevel = randomLevel(maxLvl, p);
        if (newRandomLevel>level)
        {
            for (int i=level+1;i<newRandomLevel+1;i++)
                update[i] = node;
            level = newRandomLevel;
        }
        Node* newNode = createNode(value, key, newRandomLevel);
        for (int i=0;i<=newRandomLevel;i++)
        {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    return node;
}
void searchElement(int key, Node* node, int level)
{
    Node *current = node;
    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] &&
              current->forward[i]->key < key)
        current = current->forward[i];
    }
    current = current->forward[0];
    if(current && current->key == key)
        cout<<"Found by key 5: "<<current->value<<endl;
    else
        cout << "There is no element with key "<< key<<endl;
};
void displayList(int level, Node* nodes )
{
    cout<<"Skip List"<<endl;
    cout << "Printing in format key:value"<<endl;
    bool flag = false;
    for (int i=0;i<=level;i++)
    {
        Node *node = nodes->forward[i];
        cout << "Level " << i << ": ";
        while (node != NULL)
        {
            cout << node->key<<":"<< node->value << " ";
            node = node->forward[i];
            flag = true;
        }
        cout << endl;
    }
    if (!flag)
        cout << "The list is empty"<<endl;
};
void interactive()
{
    cout << "WELCOME TO INTERACTIVE MODE"<<endl;
    srand((unsigned)time(0));
    const int maxLvl = 3;
    float p = 0.5;
    int level = 0;
    Node* nodes = initializer(maxLvl);
    bool flag = true;
    int action;
    while(flag){
        cout<< 1 << " - Insert element"<<endl;
        cout<< 2 << " - Search element"<<endl;
        cout<< 3 << " - Print skip list with levels"<<endl;
        cout<< 4 << " - Quit"<<endl;
        cout << endl;
        cout << "Enter action"<<endl;
        cin>>action;
        switch (action) {
            case 1:{
                cout << "Enter the key of the element"<<endl;
                int key;
                cin>> key;
                cout << "Enter value of the element"<<endl;
                int value;
                cin>> value;
                nodes = insertElement(nodes, value, key, maxLvl, p, level);
                break;
            }
            case 2:{
                cout << "Search element by key"<<endl;
                int key;
                cin>>key;
                searchElement(key, nodes, level);
                break;
            }
            case 3: {
                displayList(level, nodes);
                break;
            }
            case 4: {
                flag = false;
                cout << "Good bye!"<<endl;
                break;
            }
            default:
                cout<< "Error! There no such an action"<<endl;
                break;
        }
    }
}
void demo(){
    cout << "WELCOME TO DEMO MODE"<<endl;
    cout << "In this implementation of skip list the max level is 3"<<endl;
    cout << "So, you can insert the elements to list with function \"Insert element\""<<endl;
    cout << "Let's insert elements (1,2),(2,3),(3,4),(4,5),(5,6)"<<endl;
    const int maxLvl = 3;
    float p = 0.5;
    int level = 0;
    Node* nodes = initializer(maxLvl);
    nodes = insertElement(nodes, 2, 1, maxLvl, p, level);
    nodes = insertElement(nodes, 3, 2, maxLvl, p, level);
    nodes = insertElement(nodes, 4, 3, maxLvl, p, level);
    nodes = insertElement(nodes, 5, 4, maxLvl, p, level);
    nodes = insertElement(nodes, 6, 5, maxLvl, p, level);
    cout << "You can print all elements withfunction \" Print skip list with levels\""<<endl;
    displayList(level, nodes);
    cout << "Finally, you can search element by key. Let's find element by key 5"<<endl;
    searchElement(5, nodes, level);
}
void modes()
{
    cout << "Choose the mode"<<endl;
    cout << 1 << " - Interactive mode"<<endl;
    cout << 2 << " - Demo"<<endl;
    int action;
    cin>> action;
    switch (action) {
        case 1:
            interactive();
            break;
        case 2:
            demo();
            break;
        default:
            cout << "Error!"<<endl;
            break;
    }
}
int main()
{
    modes();
    return 0;
}
