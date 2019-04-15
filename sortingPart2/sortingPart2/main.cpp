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
struct Monster{
    string id;
    string name;
    string healthPoint;
    string damage;
    string chanceOfUltimateAttack;
    string ultimateAttack;
    string date;
    string time;
};
struct SortingPriority{
    bool flag;
    int priority;
};
void printOneMonster(Monster monster)
{
    cout << "ID: " << monster.id<<endl;
    cout << "Name: " << monster.name << endl;
    cout << "Healthpoints: " << monster.healthPoint << endl;
    cout << "Damage: " << monster.damage << endl;
    cout << "Chance of ultimate attack: " << monster.chanceOfUltimateAttack << endl;
    cout << "Ultimate attack: " << monster.ultimateAttack << endl;
    cout << "Time of creation the monster: "<<monster.time << endl;
    cout << "Date of creation the monster: "<<monster.date << endl;
    cout << endl;
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
    monster.healthPoint = to_string(a);
    monster.damage = to_string(a);
    monster.chanceOfUltimateAttack = to_string(0.5);
    monster.ultimateAttack = "increase damage";
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
   // printOneMonster(monster);
    monsters.push_back(monster);
    
}

bool compareTwoStructs(const Monster a,const Monster b, string s, int& flag, vector<string> s1)
{
        flag++;
    //cout <<"----"<< s1[flag-1]<<"---"<<endl;
        if (flag>5 || s1[flag-1]=="")
        {
            
            return a.id > b.id;
        }
        if (s1[flag-1]=="id"){
            return a.id == b.id ? compareTwoStructs(a, b, s1[flag],flag , s1) : a.id > b.id;
        }
        if (s1[flag-1]=="name"){
            return a.name == b.name ? compareTwoStructs(a, b, s1[flag], flag, s1) : a.name > b.name;
        }
        if (s1[flag-1]=="damage"){
            return a.damage == b.damage ? compareTwoStructs(a, b, s1[flag], flag, s1) : a.damage > b.damage;
        }
        if (s1[flag-1]=="ultimateAttack"){
            return a.ultimateAttack == b.ultimateAttack ? compareTwoStructs(a, b, s1[flag], flag, s1) : a.ultimateAttack > b.ultimateAttack;
        }
        if (s1[flag-1]=="chanceOfUltimateAttack"){
            return a.chanceOfUltimateAttack == b.chanceOfUltimateAttack ? compareTwoStructs(a, b, s1[flag], flag, s1) : a.chanceOfUltimateAttack > b.chanceOfUltimateAttack;
        }
    return a.id > b.id;
}
void task() {
    vector<Monster> monsters;
    for (int i = 0; i < 10; i++)
    {
        addRandomMonster(monsters);
    }
    
    monsters[1].id = "0";
    
    for (int i =0; i < monsters.size(); i++)
    {
        printOneMonster(monsters[i]);
    }
    vector<string> str;
   
    str.push_back("name");
     str.push_back("id");
    cout << "----------"<<endl;
    int flag = 0;
    int a = monsters.size();
    sort(monsters.begin(), monsters.end(), bind(compareTwoStructs, _1, _2, str[0],flag,str));
    for (int i =0; i < monsters.size(); i++)
    {
        printOneMonster(monsters[i]);
    }
}
//bool sortMonsters(vector<Monster>& monsters, SortingPriority id, SortingPriority name, SortingPriority healthPoint, SortingPriority damage, SortingPriority ultimateAttack, SortingPriority chanceOfUltimateAttack, SortingPriority date, SortingPriority time, int maxValue) {
//    while (id.priority||name.priority||healthPoint.priority||damage.priority||ultimateAttack.priority||chanceOfUltimateAttack.priority||date.priority||time.priority) {
//        if (id.priority == 1)
//            return monsters
//    }
//}
int main(int argc, const char * argv[]) {
     srand(time(nullptr));
    task();
    
    return 0;
}
