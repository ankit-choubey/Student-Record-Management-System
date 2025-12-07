// StudentManagementSystem.cpp
// Implementation file for Student Management System class
// WITH FILE STORAGE - Data persists between sessions!

#include "StudentManagementSystem.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
using namespace std;

// Constructor - loads data from file
StudentManagementSystem::StudentManagementSystem() : nextId(1001), filename("students.txt") {
    loadFromFile();
    
    // If no data loaded, start with empty database
    if (students.empty()) {
        cout << "\nNo existing data found. Starting with empty database.\n";
        cout << " Use 'Add Student' to add your first student.\n";
    } else {
        cout << "\n Loaded " << students.size() << " students from file.\n";
    }
}

// Destructor - automatically saves data when program exits
StudentManagementSystem::~StudentManagementSystem() {
    saveToFile();
    cout << "\n All data saved to file.\n";
}

// Load student data from file
void StudentManagementSystem::loadFromFile() {
    ifstream file(filename);
    
    if (!file.is_open()) {
        return; // File doesn't exist yet
    }
    
    // Read nextId first (kept for backward compatibility)
    file >> nextId;
    file.ignore(); // Ignore newline
    
    // Read students
    string id;
    int age;
    string name, course;
    float gpa;
    
    while (file >> id) {
        file.ignore(); // Ignore newline
        getline(file, name);
        file >> age;
        file.ignore();
        getline(file, course);
        file >> gpa;
        file.ignore();
        
        Student s(id, name, age, course, gpa);
        students.push_back(s);
    }
    
    file.close();
}

// Save student data to file
void StudentManagementSystem::saveToFile() {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cout << "\nError: Could not save data to file!\n";
        return;
    }
    
    // Write nextId first (kept for backward compatibility)
    file << nextId << endl;
    
    // Write all students
    for (const auto& student : students) {
        file << student.getId() << endl;
        file << student.getName() << endl;
        file << student.getAge() << endl;
        file << student.getCourse() << endl;
        file << student.getGpa() << endl;
    }
    
    file.close();
}

// Helper function to find student by ID
int StudentManagementSystem::findStudentIndex(const string &id) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

// ID validation - must be alphanumeric and contain at least one letter and one digit
bool StudentManagementSystem::isValidId(const string &id) const {
    if (id.empty()) return false;
    bool hasAlpha = false;
    bool hasDigit = false;
    for (char c : id) {
        if (!isalnum(static_cast<unsigned char>(c))) return false;
        if (isalpha(static_cast<unsigned char>(c))) hasAlpha = true;
        if (isdigit(static_cast<unsigned char>(c))) hasDigit = true;
    }
    return hasAlpha && hasDigit;
}

// Clear input buffer
void StudentManagementSystem::clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Add a new student
void StudentManagementSystem::addStudent() {
    string name, course;
    int age;
    float gpa;

    cout << "\n========== ADD NEW STUDENT ==========\n";
    
    clearInputBuffer();

    // Prompt for the alphanumeric ID (letters + digits)
    string id;
    while (true) {
        cout << "Enter Student ID : ";
        if (!getline(cin, id) || id.empty()) {
            clearInputBuffer();
            cout << "Invalid input. Try again.\n";
            continue;
        }

        if (!isValidId(id)) {
            cout << "ID must be alphanumeric and include at least one letter and one digit.\n";
            continue;
        }

        if (findStudentIndex(id) != -1) {
            cout << "A student with ID '" << id << "' already exists. Choose another ID.\n";
            continue;
        }

        break;
    }

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Age: ";
    while (!(cin >> age) || age < 1 || age > 100) {
        cout << "Invalid age! Enter again (1-100): ";
        clearInputBuffer();
    }

    clearInputBuffer();
    cout << "Enter Course: ";
    getline(cin, course);

    cout << "Enter GPA (0.0-10.0): ";
    while (!(cin >> gpa) || gpa < 0.0 || gpa >= 10.0) {
        cout << "Invalid GPA! Enter again (0.0-10.0): ";
        clearInputBuffer();
    }

    Student newStudent(id, name, age, course, gpa);
    students.push_back(newStudent);
    saveToFile(); // Auto-save after adding

    cout << "\n Student added successfully! (ID: " << id << ")\n";
    cout << " Data saved to file.\n";
}

// Display all students
void StudentManagementSystem::displayAllStudents() {
    if (students.empty()) {
        cout << "\n No student records found!\n";
        return;
    }

        cout << "\n========== ALL STUDENT RECORDS ==========\n";
        printTableHeader();
    for (const auto& student : students) {
        student.display();
    }
    cout << "\nTotal Students: " << students.size() << endl;
}

// Search student by ID
void StudentManagementSystem::searchStudent() {
    string id;
    cout << "\n========== SEARCH STUDENT ==========\n";
    cout << "Enter Student ID: ";
    
    if (!(cin >> id)) {
        clearInputBuffer();
        cout << "Invalid ID format!\n";
        return;
    }

    int index = findStudentIndex(id);
    if (index == -1) {
        cout << "\n Student with ID " << id << " not found!\n";
        return;
    }

        cout << "\n Student Found:\n";
        printTableHeader();
        students[index].display();
}

// Update student information
void StudentManagementSystem::updateStudent() {
    string id;
    cout << "\n========== UPDATE STUDENT ==========\n";
    cout << "Enter Student ID to update: ";
    
    if (!(cin >> id)) {
        clearInputBuffer();
        cout << "Invalid ID format!\n";
        return;
    }

    int index = findStudentIndex(id);
    if (index == -1) {
        cout << "\nStudent with ID " << id << " not found!\n";
        return;
    }

    int choice;
        cout << "\nCurrent Details:\n";
        printTableHeader();
    students[index].display();
    
    cout << "\nWhat would you like to update?\n";
    cout << "1. Name\n";
    cout << "2. Age\n";
    cout << "3. Course\n";
    cout << "4. GPA\n";
    cout << "5. All Information\n";
    cout << "Enter choice: ";
    cin >> choice;

    clearInputBuffer();

    switch (choice) {
        case 1: {
            string name;
            cout << "Enter new name: ";
            getline(cin, name);
            students[index].setName(name);
            break;
        }
        case 2: {
            int age;
            cout << "Enter new age: ";
            while (!(cin >> age) || age < 1 || age > 100) {
                cout << "Invalid age! Enter again: ";
                clearInputBuffer();
            }
            students[index].setAge(age);
            break;
        }
        case 3: {
            string course;
            cout << "Enter new course: ";
            getline(cin, course);
            students[index].setCourse(course);
            break;
        }
        case 4: {
            float gpa;
            cout << "Enter new GPA: ";
            while (!(cin >> gpa) || gpa < 0.0 || gpa >= 10.0) {
                cout << "Invalid GPA! Enter again: ";
                clearInputBuffer();
            }
            students[index].setGpa(gpa);
            break;
        }
        case 5: {
            string name, course;
            int age;
            float gpa;

            cout << "Enter new name: ";
            getline(cin, name);
            students[index].setName(name);

            cout << "Enter new age: ";
            while (!(cin >> age) || age < 1 || age > 100) {
                cout << "Invalid age! Enter again: ";
                clearInputBuffer();
            }
            students[index].setAge(age);

            clearInputBuffer();
            cout << "Enter new course: ";
            getline(cin, course);
            students[index].setCourse(course);

            cout << "Enter new GPA: ";
            while (!(cin >> gpa) || gpa < 0.0 || gpa > 4.0) {
                cout << "Invalid GPA! Enter again: ";
                clearInputBuffer();
            }
            students[index].setGpa(gpa);
            break;
        }
        default:
            cout << "Invalid choice!\n";
            return;
    }

    saveToFile(); // Auto-save after updating
    cout << "\n Student record updated successfully!\n";
    cout << "Data saved to file.\n";
}

// Delete student
void StudentManagementSystem::deleteStudent() {
    string id;
    cout << "\n========== DELETE STUDENT ==========\n";
    cout << "Enter Student ID to delete: ";
    
    if (!(cin >> id)) {
        clearInputBuffer();
        cout << "Invalid ID format!\n";
        return;
    }

    int index = findStudentIndex(id);
    if (index == -1) {
        cout << "\n Student with ID " << id << " not found!\n";
        return;
    }

        cout << "\nStudent to be deleted:\n";
        printTableHeader();
    students[index].display();
    
    cout << "\nAre you sure you want to delete this student? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        students.erase(students.begin() + index);
        saveToFile(); // Auto-save after deleting
        cout << "\n Student record deleted successfully!\n";
        cout << " Data saved to file.\n";
    } else {
        cout << "\nDeletion cancelled.\n";
    }
}

void StudentManagementSystem::printTableHeader() const {
    cout << left << setw(12) << "ID"
         << setw(25) << "Name"
         << setw(6)  << "Age"
         << setw(22) << "Course"
         << "GPA" << endl;
    printDivider();
}

void StudentManagementSystem::printDivider() const {
    cout << string(80, '-') << endl;
}