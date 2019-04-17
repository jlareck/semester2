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


void task() {
    vector<Monster> monsters;
    for (int i = 0; i < 10; i++)
    {
        addRandomMonster(monsters);
    }
    
//    monsters[1].id = "0";
    for (int i = 0; i < 7; i++)
    {
        monsters[i].id = "0";
    }
    for (int i =0; i < monsters.size(); i++)
    {
        printOneMonster(monsters[i]);
    }
    vector<string> str;
    
    str.push_back("name");
     str.push_back("id");
    str.push_back("damage");
   
    
    cout << "----------"<<endl;
    int flag = 1;
    int a = monsters.size();
    sort(monsters.begin(), monsters.end(), bind(compareTwoStructs, _1, _2, str[0],flag,str));
    for (int i =0; i < monsters.size(); i++)
    {
        printOneMonster(monsters[i]);
    }
}
void countingSort(vector<Monster>&arr) {
    int min = 1;
    int max = 4;
    int range = max - min + 1;
    
    vector<int> count(range);
    vector<Monster> output(arr.size());
    for(int i = 0; i < arr.size(); i++)
        count[arr[i].ultimateAttack.key-min]++;
    
    for(int i = 1; i < count.size(); i++)
        count[i] += count[i-1];
    
    for(int i = arr.size()-1; i >= 0; i--)
    {
        output[count[arr[i].ultimateAttack.key-min] -1 ] = arr[i];
        count[arr[i].ultimateAttack.key-min]--;
    }
    
    for(int i=0; i < arr.size(); i++)
        arr[i] = output[i];
}
void task2(){
    vector<Monster> monsters;
    for (int i = 0; i < 10; i++)
    {
        addRandomMonster(monsters);
    }
    
    //    monsters[1].id = "0";

    for (int i = 0; i < monsters.size(); i++)
    {
        printOneMonster(monsters[i]);
    }
    cout << "-----------"<<endl;
    countingSort(monsters);
    for (int i =0; i < monsters.size(); i++)
    {
        printOneMonster(monsters[i]);
    }
}
int getMax(vector<Monster> arr, int n)
{
    int mx = arr[0].healthPoint;
    for (int i = 1; i < n; i++)
        if (arr[i].healthPoint > mx)
            mx = arr[i].healthPoint;
    return mx;
}
void countSort(vector<Monster>&arr, int n, int exp)
{
    vector<Monster> output(n);
    int i, count[10] = {0};
    for (i = 0; i < n; i++)
        count[ (arr[i].healthPoint/exp)%10 ]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--)
    {
        output[count[ (arr[i].healthPoint/exp)%10 ] - 1] = arr[i];
        count[ (arr[i].healthPoint/exp)%10 ]--;
    }
    

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixsort(vector<Monster>& arr)
{

    int m = getMax(arr, arr.size());
    

    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(arr, arr.size(), exp);
}

void task3() {
    vector<Monster> monsters;
    for (int i = 0; i < 10; i++)
    {
        addRandomMonster(monsters);
    }
    for (int i = 0; i < monsters.size(); i++)
    {
        printOneMonster(monsters[i]);
    }
    cout << "-----------"<<endl;
    radixsort(monsters);
    for (int i =0; i < monsters.size(); i++)
    {
        printOneMonster(monsters[i]);
    }
}

int main(int argc, const char * argv[]) {
    srand(time(nullptr));
    task3();
    return 0;
}
