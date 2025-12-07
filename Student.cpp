// Student.cpp
// Implementation file for Student class

#include "Student.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Constructor
Student::Student(string studentId, string studentName, int studentAge, 
                 string studentCourse, float studentGpa) {
    id = studentId;
    name = studentName;
    age = studentAge;
    course = studentCourse;
    gpa = studentGpa;
}

// Getter methods
string Student::getId() const { 
    return id; 
}

string Student::getName() const { 
    return name; 
}

int Student::getAge() const { 
    return age; 
}

string Student::getCourse() const { 
    return course; 
}

float Student::getGpa() const { 
    return gpa; 
}

// Setter methods
void Student::setName(string newName) { 
    name = newName; 
}

void Student::setAge(int newAge) { 
    age = newAge; 
}

void Student::setCourse(string newCourse) { 
    course = newCourse; 
}

void Student::setGpa(float newGpa) { 
    gpa = newGpa; 
}

// Display student information
void Student::display() const {
    cout << left << setw(12) << id
         << setw(25) << name
         << setw(6) << age
         << setw(22) << course
         << right << setw(6) << fixed << setprecision(2) << gpa << left << endl;
}