//
//  main.cpp
//  sortingPart2
//
//  Created by Mykola Medynsky on 4/13/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//

#include <ctime>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
using namespace placeholders;
struct UltimeteAttack{
    string ult;
    int key;
};
struct Monster{
    string id;
    string name;
    int healthPoint;
    string damage;
    string chanceOfUltimateAttack;
    UltimeteAttack ultimateAttack;
    string date;
    string time;
};


void printOneMonster(Monster monster)
{
    cout << "ID: " << monster.id<<endl;
    cout << "Name: " << monster.name << endl;
    cout << "Healthpoints: " << monster.healthPoint << endl;
    cout << "Damage: " << monster.damage << endl;
    cout << "Chance of ultimate attack: " << monster.chanceOfUltimateAttack << endl;
    cout << "Ultimate attack: " << monster.ultimateAttack.ult << endl;
    cout << "Key of ultimate attack: "<< monster.ultimateAttack.key<<endl;
    cout << "Time of creation the monster: "<<monster.time << endl;
    cout << "Date of creation the monster: "<<monster.date << endl;
    cout << endl;
}
void createAndAddMonster(vector<Monster>& monsters)
{
    Monster monster;
    if (monsters.size()==0) {
        monster.id = "0";
    }
    else
        monster.id = to_string(monsters.size());
    cout << "Enter Name"<<endl;
    cin.ignore();
    getline(cin,monster.name);
    cout << "Enter health points"<<endl;
    cin >> monster.healthPoint;
    cout << "Enter damage" <<endl;
    cin >> monster.damage;
    cout << "Enter chance of ultimate attack in range 0 to 1"<<endl;
    cin >> monster.chanceOfUltimateAttack;
    cout << "Choose ultimate attack:\n 1 - increase damage\n 2 - repeat attack\n 3- healself\n 4 - disable enemy" <<endl;
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            monster.ultimateAttack.ult = "increase damage";
            break;
        case 2:
            monster.ultimateAttack.ult = "repeat attack";
            break;
        case 3:
            monster.ultimateAttack.ult = "healself";
            break;
        case 4:
            monster.ultimateAttack.ult = "disable enemy";
            break;
        default:{
            cout << "There is no option: "<< choice<<endl;
            monster.ultimateAttack.ult = "increase damage";
            break;
        }
    }
    if (monster.ultimateAttack.ult == "increase damage")
        monster.ultimateAttack.key = 1;
    else if (monster.ultimateAttack.ult == "repeat attack")
        monster.ultimateAttack.key = 2;
    else if (monster.ultimateAttack.ult == "healself")
        monster.ultimateAttack.key = 3;
    else
        monster.ultimateAttack.key = 4;
    time_t t = std::time(0);
    tm* now = std::localtime(&t);
    
    stringstream ss;
    if (now->tm_mday<10)
    {
        if (now->tm_mon<10)
            ss<<(now->tm_year + 1900) << "-0"<< (now->tm_mon + 1) << "-0" <<  now->tm_mday;
        else
            ss<<(now->tm_year + 1900) << '-'<< (now->tm_mon + 1) << "-0" <<  now->tm_mday;
    }
    else{
        if (now->tm_mon<10)
            ss<<(now->tm_year + 1900) << "-0"<< (now->tm_mon + 1) << '-' <<  now->tm_mday;
        else
            ss<<(now->tm_year + 1900) << '-'<< (now->tm_mon + 1) << '-' <<  now->tm_mday;
    }
    monster.date = ss.str();
    ss.str("");
    char timestamp_buf[10] = "";
    strftime (timestamp_buf, 10,"%H.%M.%S", localtime(&t));
    string timestamp = string(timestamp_buf);
    monster.time = timestamp;
    monsters.push_back(monster);
}
void addRandomMonster(vector<Monster>& monsters)
{
    Monster monster;
    if (monsters.size()==0) {
        monster.id = "0";
    }
    else
        monster.id = to_string(monsters.size());
    string names[] = {"Witch doctor", "Medusa", "Terrorblade", "Storm spirit", "Pudge", "Anti-Mage", "Phantom Assasin"};
    monster.name = names[rand()%7];
    int a = rand()%100;
    monster.healthPoint = a;
    monster.damage = to_string(a);
    monster.chanceOfUltimateAttack = to_string(0.5);
    string ults[] = {"increase damage", "repeat attack", "healself",  "disable enemy"};
    monster.ultimateAttack.ult = ults[rand()%4];
    if (monster.ultimateAttack.ult == "increase damage")
        monster.ultimateAttack.key = 1;
    else if (monster.ultimateAttack.ult == "repeat attack")
        monster.ultimateAttack.key = 2;
    else if (monster.ultimateAttack.ult == "healself")
        monster.ultimateAttack.key = 3;
    else
        monster.ultimateAttack.key = 4;
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    stringstream ss;
    if (now->tm_mday<10)
    {
        if (now->tm_mon<10)
            ss<<(now->tm_year + 1900) << "-0"<< (now->tm_mon + 1) << "-0" <<  now->tm_mday;
        else
            ss<<(now->tm_year + 1900) << '-'<< (now->tm_mon + 1) << "-0" <<  now->tm_mday;
    }
    else{
        if (now->tm_mon<10)
            ss<<(now->tm_year + 1900) << "-0"<< (now->tm_mon + 1) << '-' <<  now->tm_mday;
        else
            ss<<(now->tm_year + 1900) << '-'<< (now->tm_mon + 1) << '-' <<  now->tm_mday;
    }
    monster.date = ss.str();
    ss.str("");
    
    char timestamp_buf[10] = "";
    strftime (timestamp_buf, 10,"%H.%M.%S", localtime(&t));
    string timestamp = string(timestamp_buf);
    monster.time = timestamp;
    printOneMonster(monster);
    monsters.push_back(monster);
    
}

bool compareTwoStructs(Monster a, Monster b, string s, int counter, vector<string> s1)
{
    
    if (counter == s1.size())
    {
        if (s=="id"){
            return a.id>b.id;
        }
        if (s=="name"){
            return a.name>b.name;
        }
        if (s=="damage"){
            return a.damage>b.damage;
        }
        if (s=="healthPoint"){
            return a.healthPoint>b.healthPoint;
        }
        if (s=="ultimateAttack"){
            return a.ultimateAttack.ult>b.ultimateAttack.ult;
        }
        if (s=="chanceOfUltimateAttack"){
            return a.chanceOfUltimateAttack>b.chanceOfUltimateAttack;
        }
        if (s=="date"){
            return a.date>b.date;
        }
        if (s=="time"){
            return a.time>b.time;
        }
    }
    else{
        counter++;
        if (s=="id"){
            return a.id == b.id ? compareTwoStructs(a, b, s1[counter-1], counter, s1) : a.id > b.id;
        }
        if (s=="name"){
            return a.name == b.name ? compareTwoStructs(a, b, s1[counter-1], counter, s1) : a.name > b.name;
        }
        if (s=="damage"){
            return a.damage == b.damage ? compareTwoStructs(a, b, s1[counter-1], counter, s1) : a.damage > b.damage;
        }
        if (s=="healthPoint")
        {
            return a.healthPoint == b.healthPoint ? compareTwoStructs(a, b, s1[counter-1], counter, s1) : a.healthPoint > b.healthPoint;
        }
        if (s=="ultimateAttack"){
            return a.ultimateAttack.ult == b.ultimateAttack.ult ? compareTwoStructs(a, b, s1[counter-1], counter, s1) : a.ultimateAttack.ult > b.ultimateAttack.ult;
        }
        if (s=="chanceOfUltimateAttack"){
            return a.chanceOfUltimateAttack == b.chanceOfUltimateAttack ? compareTwoStructs(a, b, s1[counter-1], counter, s1) : a.chanceOfUltimateAttack > b.chanceOfUltimateAttack;
        }
        if (s=="date"){
            return a.date == b.date ? compareTwoStructs(a, b, s1[counter-1], counter, s1) : a.date > b.date;
        }
        if (s=="time"){
            return a.time == b.time ? compareTwoStructs(a, b, s1[counter-1], counter, s1) : a.time > b.time;
        }
    }
   
    
    
    return a.id > b.id;
}


void benchmarkSortingByDifferentParameters() {
    vector<Monster> monsters;
    for (int i = 0; i < 100; i++)
    {
        addRandomMonster(monsters);
    }
    
    for (int i = 0; i < monsters.size(); i++)
    {
        printOneMonster(monsters[i]);
    }
    vector<string> str;
    
    str.push_back("name");
    str.push_back("healthPoints");
    str.push_back("damage");
   
    
    cout << "----------"<<endl;
    int counter = 1;
    clock_t start = clock();
    sort(monsters.begin(), monsters.end(), bind(compareTwoStructs, _1, _2, str[0],counter,str));
    clock_t end = clock();
    cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;
    for (int i =0; i < monsters.size(); i++)
    {
        printOneMonster(monsters[i]);
    }
}
void countingSort(vector<Monster>&monsters) {
    int min = 1;
    int max = 4;
    int range = max - min + 1;
    
    vector<int> count(range);
    vector<Monster> output(monsters.size());
    for(int i = 0; i < monsters.size(); i++)
        count[monsters[i].ultimateAttack.key-min]++;
    
    for(int i = 1; i < count.size(); i++)
        count[i] += count[i-1];
    
    for(int i = monsters.size()-1; i >= 0; i--)
    {
        output[count[monsters[i].ultimateAttack.key-min] -1 ] = monsters[i];
        count[monsters[i].ultimateAttack.key-min]--;
    }
    
    for(int i=0; i < monsters.size(); i++)
        monsters[i] = output[i];
}
void benchmarkCountingSort(){
    vector<Monster> monsters;
    for (int i = 0; i < 10000; i++)
    {
        addRandomMonster(monsters);
    }

    for (int i = 0; i < monsters.size(); i++)
    {
        printOneMonster(monsters[i]);
    }
    cout << "-----------"<<endl;
     clock_t start = clock();
    countingSort(monsters);
     clock_t end = clock();
     cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;
    for (int i =0; i < monsters.size(); i++)
    {
        printOneMonster(monsters[i]);
    }
}
int getMax(vector<Monster> monsters)
{
    int max = monsters[0].healthPoint;
    for (int i = 1; i < monsters.size(); i++)
        if (monsters[i].healthPoint > max)
            max = monsters[i].healthPoint;
    return max;
}
void countSort(vector<Monster>&monsters, int exp)
{
    vector<Monster> output(monsters.size());
    int i, count[10] = {0};
    for (i = 0; i < monsters.size(); i++)
        count[ (monsters[i].healthPoint/exp)%10 ]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = monsters.size() - 1; i >= 0; i--)
    {
        output[count[ (monsters[i].healthPoint/exp)%10 ] - 1] = monsters[i];
        count[ (monsters[i].healthPoint/exp)%10 ]--;
    }
    

    for (i = 0; i < monsters.size(); i++)
        monsters[i] = output[i];
}

void radixsort(vector<Monster>& monsters)
{
    int max = getMax(monsters);
    for (int i = 1; max/i > 0; i *= 10)
        countSort(monsters, i);
}

void task3() {
    vector<Monster> monsters;
    for (int i = 0; i < 10000; i++)
    {
        addRandomMonster(monsters);
    }
    for (int i = 0; i < monsters.size(); i++)
    {
        printOneMonster(monsters[i]);
    }
    cout << "-----------"<<endl;
    clock_t start = clock();
    radixsort(monsters);
    clock_t end = clock();
    cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;
    for (int i =0; i < monsters.size(); i++)
    {
        printOneMonster(monsters[i]);
    }
}
void printAll(vector<Monster>monster)
{
    for (int i = 0; i< monster.size(); i++)
    {
        cout << "ID: " << monster[i].id<<endl;
        cout << "Name: " << monster[i].name << endl;
        cout << "Healthpoints: " << monster[i].healthPoint << endl;
        cout << "Damage: " << monster[i].damage << endl;
        cout << "Chance of ultimate attack: " << monster[i].chanceOfUltimateAttack << endl;
        cout << "Ultimate attack: " << monster[i].ultimateAttack.ult << endl;
        cout << "Time of creation the monster: "<<monster[i].time << endl;
        cout << "Date of creation the monster: "<<monster[i].date << endl;
        cout << endl;
    }
}
void interactiveInterface()
{
    vector<Monster> monster;
    bool flag = true;
    
    int action;
    while (flag)
    {
        cout << 1 << " - Create new monster" << endl;
        cout << 2 << " - Print all monsters" << endl;
        cout << 3 << " - Create random monster" << endl;
        cout << 4 << " - Sort by different parameters" << endl;
        cout << 5 << " - Sort using counting sort by ultimate attack" << endl;
        cout << 6 << " - Sort using radix sort by health points" << endl;
        cout << 7 << " - Create 10 random monsters"<<endl;
        cout << 8 << " - Exit" << endl;
        cout << "Enter action" << endl;
        cin >> action;
        switch (action) {
            case 1:
                addRandomMonster(monster);
                break;
            case 2:
                printAll(monster);
                break;
           
            case 3:{
                addRandomMonster(monster);
                break;
            }
            case 4:{
                bool sortingFlag = true;
                int sortingChoice;
                vector<string> sortingParameters;
                while(sortingFlag)
                {
                    cout << "Choose parameters (1-8)" <<endl;
                    cout << "1 - Sort by ID"<<endl;
                    cout << "2 - Sort by name"<<endl;
                    cout << "3 - Sort by healthpoints"<<endl;
                    cout << "4 - Sort by damage" <<endl;
                    cout << "5 - Sort by ultimate attack"<<endl;
                    cout << "6 - Sort by chance of ultimate attack"<<endl;
                    cout << "7 - Sort by date"<<endl;
                    cout << "8 - Sort by time"<<endl;
                    cout << "9 - Sort"<<endl;
                    cout << "Choose: ";
                    cin>>sortingChoice;
                    switch (sortingChoice) {
                        case 1:
                            sortingParameters.push_back("id");
                            break;
                        case 2:
                            sortingParameters.push_back("name");
                            break;
                        case 3:
                            sortingParameters.push_back("healthPoint");
                            break;
                        case 4:
                            sortingParameters.push_back("damage");
                            break;
                        case 5:
                            sortingParameters.push_back("ultimateAttack");
                            break;
                        case 6:
                            sortingParameters.push_back("chanceOfUltimateAttack");
                            break;
                        case 7:
                            sortingParameters.push_back("date");
                            break;
                        case 8:
                            sortingParameters.push_back("time");
                            break;
                        case 9: {
                            int count = 1;
                            sort(monster.begin(), monster.end(), bind(compareTwoStructs, _1, _2, sortingParameters[0],count,sortingParameters));
                            sortingFlag = false;
                            break;
                        }
                        default:
                            cout <<"Error! Try again"<<endl;
                            break;
                    }
                }
                break;
            }
            case 5:
                countingSort(monster);
                break;
            case 6:
                radixsort(monster);
                break;
            case 7:{
                for (int i = 0; i < 10; i++)
                    addRandomMonster(monster);
                break;
            }
            case 8:{
                cout << "Good bye!"<<endl;
                flag = false;
                break;
            }
            default:
                cout << "Error! Try again"<<endl;
                break;
        }
    }
}
int main(int argc, const char * argv[]) {
    srand(time(nullptr));
  //  interactiveInterface();
    benchmarkSortingByDifferentParameters();
    return 0;
}

