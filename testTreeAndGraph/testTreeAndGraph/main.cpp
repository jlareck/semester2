//
//  main.cpp
//  testTreeAndGraph
//
//  Created by Mykola Medynsky on 5/17/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//

#include <iostream>
#include <utility>
#include <cmath>
#include <vector>
using namespace std;
#define VARIANT 1
#define SUBVARINT 3
struct Knowledge {
    int max;
    int min;
};

struct Employee {

    string fullName;
    pair<string, Knowledge> skills[9+VARIANT];
    double persistance;
    double value;
    double distance;
    int key;
    vector<Employee*> childs;
};
struct DistanceEmployee{
    Employee* employee1;
    Employee* employee2;
    double distance;
};

double calculateValue(Employee* employee) {
    double value = 0;
    for (int i = 0; i < 9+VARIANT; i++)
    {
        value += pow(((employee->skills[i].second.max*employee->persistance)+(employee->skills[i].second.min*(1-employee->persistance))), 2);
    }
    value = pow(value, (employee->persistance+1));
    return value;
}
double doubleRand() {
    return double(rand()) / (double(RAND_MAX) + 1.0);
}

bool comparator(Employee* person1, Employee* person2) {
    return person1->value > person2->value;
}

Employee* randomEmployee() {
    Employee* employee = new Employee;
    string arrayOfEmployees[] = {"E1", "E2","E3", "E4", "E5"};
    employee->fullName = arrayOfEmployees[rand()%4];
    string arrayOfSkills[] = {"Skill1", "Skill2", "Skill3","Skill4","Skill5","Skill6","Skill7","Skill8","Skill9","Skill10"};
    //min + rand() % (( max + 1 ) - min);
    int numberOfSkills = 1+rand()%((9+VARIANT)-1);
    vector<int> listOfRandomedSkills;

    for (int i = 0; i < numberOfSkills; i++) {


        employee->skills[i].first = arrayOfSkills[i];
        employee->skills[i].second.max = rand()%1000;
        employee->skills[i].second.min = rand()%1000;
        if (employee->skills[i].second.min>employee->skills[i].second.max) {
            swap(employee->skills[i].second.min, employee->skills[i].second.max);
        }
    }
    for (int i = numberOfSkills; i < 9+VARIANT; i++) {
        employee->skills[i].first = "";
        employee->skills[i].second.max = 0;
        employee->skills[i].second.min = 0;
    }
   
    employee->persistance = doubleRand();
    employee->value = calculateValue(employee);
    return employee;
}
void printEmployee(Employee* employee) {

    cout << employee->fullName <<endl;
    int i = 0;
    cout << "Skills: "<<endl;
    while (employee->skills[i].first!="" && i<10){
        cout << employee->skills[i].first << " : Max = " <<employee->skills[i].second.max << " ; Min = " << employee->skills[i].second.min << endl;
        i++;
    }
    cout << "Value: " << employee->value <<endl;
    cout << "Persistance: " << employee->persistance<<endl;
}
bool comparatorForSkills(pair<string, Knowledge> employee1, pair<string, Knowledge> employee2) {
    return employee1.second.max>employee2.second.max;
}
double distance(Employee*& employee1, Employee*& employee2) {

    sort(employee1->skills, employee1->skills+10, comparatorForSkills);

    double distance = 0;
    for (int i = 0; i < VARIANT+9; i++)
    {
        distance += pow((employee1->skills[i].second.min - employee2->skills[i].second.min),2);
    }
    distance += 1.0;
    double minPersistance = min(employee1->persistance, employee2->persistance);
    distance = -1*log(pow(distance, minPersistance-2*VARIANT));
    return distance;
}

bool comparatorForDistances(DistanceEmployee e1, DistanceEmployee e2) {
    return e1.distance>e2.distance;
}
void task1() {
    vector<Employee*> persons;
    Employee* employee;
    for (int i = 0; i<139; i++)
    {
        employee = randomEmployee();
        printEmployee(employee);
        persons.push_back(employee);
    }
    sort(persons.begin(), persons.end(), comparator);
    vector<DistanceEmployee> arrayOfDistances;
    for (int i = 1; i<139; i++)
    {
        for (int j = 0; j < i; j++) {
            DistanceEmployee distanceEmployeeObject;
            distanceEmployeeObject.distance = distance(persons[i], persons[j]);
            distanceEmployeeObject.employee1 = persons[i];
            distanceEmployeeObject.employee2 = persons[j];
            arrayOfDistances.push_back(distanceEmployeeObject);
            
        }
    }
    sort(arrayOfDistances.begin(), arrayOfDistances.end(), comparatorForDistances);
    cout << "Employees with the biggest distance"<<endl;
    for (int i = 0; i < 17; i++){
        printEmployee(arrayOfDistances[i].employee1);
        printEmployee(arrayOfDistances[i].employee2);
        cout<< "Distance: " << arrayOfDistances[i].distance << endl;
    }
    cout << "Employees with the smallest distance"<<endl;
    for (int i = arrayOfDistances.size()-18; i < arrayOfDistances.size(); i++){
        printEmployee(arrayOfDistances[i].employee1);
        printEmployee(arrayOfDistances[i].employee2);
        cout<< "Distance: " << arrayOfDistances[i].distance << endl;
        cout << i<<endl;
    }
    
}
int countNodesInTree(Employee *root)
{
    int count = 1;
    for (int i = 0; i < root->childs.size();i++){
        if (root->childs[i] != NULL) {
            count += countNodesInTree(root->childs[i]);
        }
    }
    return count;
}
int countNodes(Employee *tree)
{
    unsigned int count = 0;
    if (tree != NULL) {
        count = countNodesInTree(tree);
    }
    return count;
}

Employee* BuildKaryTree(vector<Employee*>& arr, int k, Employee*& root, int h)
{

    
    if (root == NULL) {
        cout << "Memory error" << endl;
        return NULL;
    }
    int j = 0;
    for (int i = 0; i < k; i++) {

        if (i < arr.size()){
            
            root->childs.push_back(arr[i]);
            j++;
        }
        else {
            root->childs.push_back(NULL);
        }
    }
    h++;
    for (int i = 0; i< k; i++){
        if (i<j){
            arr.erase(arr.begin());
        }
    }
    for(int i = 0; i < k; i++)
    {
        if (root->childs[i]!=NULL&&arr.size()!=0&&h-1<1){
            
            int newK = 2 + rand() % 5;
            BuildKaryTree(arr, newK, root->childs[i],h);
        }
        if(i == k-1){
            h--;
        }
    }
    return root;
}

//Employee* BuildKaryTree(vector<Employee*> arr, int k, int ind)
//{
//    int height = (int)ceil(log((double)arr.size() * (k - 1) + 1)
//                           / log((double)k));
//    return BuildKaryTree(arr, k, height, ind);
//}
void printTreeInBrackets(Employee* node) {
    if (!node) {
        return;
    }
    cout<<node->key<<"(";
    for (int i = 0; i < node->childs.size(); i++){
        printTreeInBrackets(node->childs[i]);
    }
    cout<<")";
    
}
void task2() {
    Employee* root = randomEmployee();
   
    //min + rand() % (( max + 1 ) - min);2 + rand() % 4
    int numberOfChilds = 2 + rand() % 5;
    vector<Employee*> persons;
   Employee* employee = new Employee;
    root->key = 100;
    for (int i = 0; i<12; i++)
    {
       
        employee = randomEmployee();
        employee->key = i;
        //printEmployee(employee);
        persons.push_back(employee);
        cout << persons[i]->key<<endl;
    }
    int h = 0;
    BuildKaryTree(persons, numberOfChilds, root, h);
    
   
    printTreeInBrackets(root);

}
int main(int argc, const char * argv[]) {

    srand(time(nullptr));
    task2();
    return 0;
}
