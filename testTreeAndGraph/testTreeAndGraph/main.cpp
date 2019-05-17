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
    vector<Employee*> childs;
};
void calculateValue(Employee& employee) {
    employee.value = 0;
    for (int i = 0; i < 9+VARIANT; i++)
    {
        employee.value += pow(((employee.skills[i].second.max*employee.persistance)+(employee.skills[i].second.min*(1-employee.persistance))), 2);
    }
    employee.value = pow(employee.value, (employee.persistance+1));

}
double doubleRand() {
    return double(rand()) / (double(RAND_MAX) + 1.0);
}

bool comparator(Employee person1, Employee person2) {
    return person1.value > person2.value;
}

Employee randomEmployee() {
    Employee employee;
    string arrayOfEmployees[] = {"E1", "E2","E3", "E4", "E5"};
    employee.fullName = arrayOfEmployees[rand()%4];
    string arrayOfSkills[] = {"Skill1", "Skill2", "Skill3","Skill4","Skill5","Skill6","Skill7","Skill8","Skill9","Skill10"};
    //min + rand() % (( max + 1 ) - min);
    int numberOfSkills = 1+rand()%((9+VARIANT)-1);
    vector<int> listOfRandomedSkills;

    for (int i = 0; i < numberOfSkills; i++) {


        employee.skills[i].first = arrayOfSkills[i];
        employee.skills[i].second.max = rand()%1000;
        employee.skills[i].second.min = rand()%1000;
        if (employee.skills[i].second.min>employee.skills[i].second.max) {
            swap(employee.skills[i].second.min, employee.skills[i].second.max);
        }
    }
    for (int i = numberOfSkills; i < 9+VARIANT; i++) {
        employee.skills[i].first = "";
        employee.skills[i].second.max = 0;
        employee.skills[i].second.min = 0;
    }
    calculateValue(employee);
    employee.persistance = doubleRand();
    return employee;
}
void printEmployee(Employee employee) {

    cout << employee.fullName <<endl;
    int i = 0;
    cout << "Skills: "<<endl;
    while (employee.skills[i].first!=""&&i<10){
        cout << employee.skills[i].first << " : Max = " <<employee.skills[i].second.max << " ; Min = " << employee.skills[i].second.min << endl;
        i++;
    }
    cout << "Value: " << employee.value <<endl;
    cout << "Persistance: " << employee.persistance<<endl;
}
bool comparatorForSkills(pair<string, Knowledge> employee1, pair<string, Knowledge> employee2) {
    return employee1.second.max>employee2.second.max;
}
double distance(Employee&employee1, Employee& employee2) {

    sort(employee1.skills, employee1.skills+10, comparatorForSkills);

    double distance = 0.0;
    for (int i = 0; i < VARIANT+9; i++)
    {
        distance += pow((employee1.skills[i].second.min - employee2.skills[i].second.min),2);
    }
    distance += 1.0;
    double minPersistance = min(employee1.persistance, employee2.persistance);
    distance = -1*log(pow(distance, minPersistance-2*VARIANT));
    return distance;
}
void task1() {
    vector<Employee> persons;
    Employee employee;
    for (int i = 0; i<139; i++)
    {
        employee = randomEmployee();
        printEmployee(employee);
        persons.push_back(employee);
    }
    sort(persons.begin(), persons.end(), comparator);
    for (int i = 0; i<138; i++)
    {
        persons[i].distance = distance(persons[i], persons[i+1]);
        cout << persons[i].value<<endl;
    }

}
int main(int argc, const char * argv[]) {
    // insert code here...
    srand(time(nullptr));
    task1();
    std::cout << "Hello, World!\n";
    return 0;
}
////
////  main.cpp
////  testTreeAndGraph
////
////  Created by Mykola Medynsky on 5/17/19.
////  Copyright © 2019 Mykola Medynskyi. All rights reserved.
////
//
//#include <iostream>
//#include <utility>
//#include <cmath>
//#include <vector>
//#include <algorithm>
//using namespace std;
//#define VARIANT 1
//#define SUBVARINT 3
//struct Knowledge {
//    int max;
//    int min;
//};
//struct Employee {
//
//    string fullName;
//    pair<string, Knowledge> skills[9+VARIANT];
//    double persistance;
//    double value;
//    double distance;
//    Employee* next;
//    vector<Employee*> childs;
//};
//void calculateValue(Employee*& employee) {
//    employee->value = 0;
//    for (int i = 0; i < 9+VARIANT; i++)
//    {
//        employee->value += pow((employee->skills[i].second.max*employee->persistance+employee->skills[i].second.min*(1-employee->persistance)), 2);
//    }
//    employee->value = pow(employee->value, (employee->persistance+1));
//
//}
//double doubleRand() {
//    return double(rand()) / (double(RAND_MAX) + 1.0);
//}
//
//bool comparator(Employee* person1, Employee* person2) {
//    return person1->value > person2->value;
//}
//
//Employee* randomEmployee() {
//    Employee* employee = new Employee;
//    string arrayOfEmployees[] = {"E1", "E2","E3", "E4", "E5"};
//    employee->fullName = arrayOfEmployees[rand()%4];
//    string arrayOfSkills[] = {"Skill1", "Skill2", "Skill3","Skill4","Skill5","Skill6","Skill7","Skill8","Skill9","Skill10"};
//    //min + rand() % (( max + 1 ) - min);
//    int numberOfSkills = 1+rand()%((9+VARIANT)-1);
//    vector<int> listOfRandomedSkills;
//
//    for (int i = 0; i < numberOfSkills; i++) {
//
//
//        employee->skills[i].first = arrayOfSkills[i];
//        employee->skills[i].second.max = rand()%1000;
//        employee->skills[i].second.min = rand()%1000;
//        if (employee->skills[i].second.min>employee->skills[i].second.max) {
//            swap(employee->skills[i].second.min, employee->skills[i].second.max);
//        }
//    }
//    for (int i = numberOfSkills; i < 9+VARIANT; i++) {
//        employee->skills[i].first = "";
//        employee->skills[i].second.max = 1;
//        employee->skills[i].second.min = 1;
//    }
//    calculateValue(employee);
//    employee->persistance = doubleRand();
//    return employee;
//}
//void printEmployee(Employee* employee) {
//
//    cout << employee->fullName <<endl;
//    int i = 0;
//    cout << "Skills: "<<endl;
//    while (employee->skills[i].first!=""&&i<10){
//        cout << employee->skills[i].first << " : Max = " <<employee->skills[i].second.max << " ; Min = " << employee->skills[i].second.min << endl;
//        i++;
//    }
//    cout << "Value: " << employee->value <<endl;
//    cout << "Persistance: " << employee->persistance<<endl;
//}
//bool comparatorForSkills(pair<string, Knowledge> employee1, pair<string, Knowledge> employee2) {
//    return employee1.second.max>employee2.second.max;
//}
//double distance(Employee&employee1, Employee& employee2) {
//
//    sort(employee1.skills, employee1.skills+10, comparatorForSkills);
//
//    double distance = 0.0;
//    for (int i = 0; i < VARIANT+9; i++)
//    {
//        distance += pow((employee1.skills[i].second.min - employee2.skills[i].second.min),2);
//    }
//    distance += 1.0;
//    double minPersistance = min(employee1.persistance, employee2.persistance);
//    distance = -1*log(pow(distance, minPersistance-2*VARIANT));
//    return distance;
//}
//void task1() {
//    vector<Employee*> persons;
//    Employee* employee = new Employee;
//    for (int i = 0; i<139; i++)
//    {
//        employee = randomEmployee();
//        printEmployee(employee);
//        persons.push_back(employee);
//    }
//    sort(persons.begin(), persons.end(), comparator);
//    for (int i = 0; i<138; i++)
//    {
//
//        cout << persons[i]->value<<endl;
//    }
//
//}
//int main(int argc, const char * argv[]) {
//    // insert code here...
//    srand(time(nullptr));
//    task1();
//    std::cout << "Hello, World!\n";
//    return 0;
//}
