// Student.h
// Header file for Student class

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

class Student {
private:
    string id;              // now a string to support alphanumeric IDs
    string name;
    int age;
    string course;
    float gpa;

public:
    // Constructor
    Student(string studentId, string studentName, int studentAge,
            string studentCourse, float studentGpa);

    // Getter methods
    string getId() const;
    string getName() const;
    int getAge() const;
    string getCourse() const;
    float getGpa() const;

    // Setter methods
    void setName(string newName);
    void setAge(int newAge);
    void setCourse(string newCourse);
    void setGpa(float newGpa);

    // Display student information
    void display() const;
};

#endif // STUDENT_H