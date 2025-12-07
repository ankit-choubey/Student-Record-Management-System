// StudentManagementSystem.h
// Header file for Student Management System class
// WITH FILE STORAGE CAPABILITIES

#ifndef STUDENT_MANAGEMENT_SYSTEM_H
#define STUDENT_MANAGEMENT_SYSTEM_H

#include "Student.h"
#include <vector>
using namespace std;

class StudentManagementSystem {
private:
    vector<Student> students;
    int nextId; // still stored in file for compatibility, not used for new IDs
    string filename;

    // Helper function to find student by ID (ID is alphanumeric string)
    int findStudentIndex(const string &id);

    // Validate student ID format (alphanumeric and contains both letter and digit)
    bool isValidId(const string &id) const;

    // Clear input buffer
    void clearInputBuffer();

    // File operations
    void loadFromFile();
    void saveToFile();

    // Pretty-print helpers for tables
    void printTableHeader() const;
    void printDivider() const;

public:
    // Constructor
    StudentManagementSystem();

    // Destructor - saves data when program exits
    ~StudentManagementSystem();

    // Add a new student
    void addStudent();

    // Display all students
    void displayAllStudents();

    // Search student by ID
    void searchStudent();

    // Update student information
    void updateStudent();

    // Delete student
    void deleteStudent();
};

#endif