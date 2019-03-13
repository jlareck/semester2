////
////  main.cpp
////  priorityqueue
////
////  Created by Mykola Medynsky on 3/10/19.
////  Copyright © 2019 Mykola Medynskyi. All rights reserved.
////
//
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::setw;
using std::cin;
struct Node{
    int value;
    int priority;
    Node* next;
};
Node* createNode(int priority, int value)
{
    Node* node = new Node;
    node->priority = priority;
    node->value = value;
    node->next = NULL;
    return node;
}
void peek(Node* node)
{
    if (node==NULL)
        cout << "There is no nodes in queue"<<endl;
    else{
        cout << "Priority"<< setw(11)<<"Value"<<endl;
        cout<< node->priority<< setw(14) << node->value <<endl;
    }
}
Node* pop(Node* node)
{
    if (node==NULL)
        cout << "There is no nodes to delete"<<endl;
    else
        node = node->next;
    return node;
}
Node* push(Node* node, int priority, int value)
{
    
    Node* temp = createNode(priority, value);
    if (node==NULL||node->priority>priority) {
        temp->next = node;
        node = temp;
        return node;
    }
    else {
        Node* currentNode = node;
        while ((currentNode->next != NULL) && (currentNode->next->priority <= priority) )
        {
            currentNode = currentNode->next;
        }
        temp->next = currentNode->next;
        currentNode->next = temp;
        return node;
    }

}
void printNodes(Node* node)
{
    Node* currentNode = node;
    cout << "Priority"<< setw(11)<<"Value"<<endl;
    while (currentNode!=nullptr) {
        cout<< currentNode->priority<< setw(14) << currentNode->value <<endl;
        currentNode = currentNode->next;
    }
}
void interactive() {
    cout << "WELCOME TO INTERACTIVE MODE"<<endl;
    int action;
    Node* node = NULL;
    bool flag = true;

    while (flag) {
        cout<< 1 << " - Add element to queue"<<endl;
        cout<< 2 << " - Pop the element"<<endl;
        cout<< 3 << " - Peek the element"<<endl;
        cout<< 4 << " - Print all elements in queue"<<endl;
        cout<< 5 << " - Quit"<<endl;
        cout << "Enter action"<<endl;
        cin>>action;
        switch (action) {
            case 1: {
                cout << "Enter the priority of new element"<<endl;
                int priority;
                cin>>priority;
                cout << "Enter the value"<<endl;
                int value;
                cin>>value;
               node = push(node, priority, value);
                break;
            }
            case 2: {
                cout << "Element to pop: ";
                peek(node);
                node = pop(node);
                break;
            }
            case 3: {
                peek(node);
                break;
            }
            case 4: {
                cout << "All elements"<<endl;
                printNodes(node);
                break;
            }
            case 5: {
                cout << "Good bye"<<endl;
                flag = false;
                break;
            }
            default:
                break;
        }
    }
}
void demo()
{
    cout << "WELCOME TO DEMO MODE"<<endl;
    cout << " In priority queue every item has a priority associated with it.\n An element with higher priority is pushed before an element with lower priority.\n If two elements have the same priority, they are served according to their order in the queue."<<endl;
    Node* node = NULL;
    cout << "Using function \"Add element\" you can push the element to queue "<<endl;
    
    cout << "Let's add some elements. For example: (priority = 2, value = 3), (priority = 4, value = 5),(priority = 3, value = 8),(priority = 1, value = 1)"<<endl;
    node = push(node, 2, 3);
    node = push(node, 4, 5);
    node = push(node, 3, 8);
    node = push(node, 1, 1);
    cout << "\"Peek element\" - gets the top (element with highest priority that was added first) element"<<endl;
    peek(node);
    
    cout << "\"Pop element\" - deletes the top  element"<<endl;
    node = pop(node);
    cout << "You can print all elements"<<endl;
    printNodes(node);
}
int main(int argc, const char * argv[]) {
    demo();
    return 0;
}
