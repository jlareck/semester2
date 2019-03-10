//
//  main.cpp
//  circularList
//
//  Created by Mykola Medynsky on 2/21/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//

#include <iostream>
#include <vector>
#include "interactiveList.hpp"
#include "interactiveArray.hpp"
#include "interactiveVector.hpp"


void mode()
{
    cout << "Choose the mode of circular list"<<endl;
    cout << 1 << " - Interactive list"<<endl;
    cout << 2 << " - Interactive array"<<endl;
    cout << 3 << " - Interactive vector"<<endl;
    cout << 4 << " - Demo list"<<endl;
    cout << 5 << " - Demo array"<<endl;
    cout << 6 << " - Demo vector"<<endl;
    cout << "Press any other key to exit"<<endl;
    int action;
    cin>> action;
    switch (action) {
        case 1:
            interactiveList();
            break;
        case 2:
            interactiveArray();
            break;
        case 3:
            interactiveVector();
            break;
        case 4:
            demoList();
            break;
        case 5:
            demoArray();
            break;
        case 6:
            demoVector();
            break;
        default:
            cout << "Good bye!"<<endl;
            break;
    }
}
int main()
{
    mode();
    return 0;
}
