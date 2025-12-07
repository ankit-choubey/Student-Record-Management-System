// main.cpp
// Main program file with menu

#include "StudentManagementSystem.h"
#include <iostream>
#include <limits>
using namespace std;

int main() {
    StudentManagementSystem sms;
    int choice;
    bool showMenu = true;

    cout << "\n===============================\n";
    cout << "STUDENT RECORD MANAGEMENT SYSTEM \n";
    cout << "===============================\n";

    while (showMenu) {
        cout << "\n========== MAIN MENU ==========\n";
        cout << "1. Add New Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "===============================\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                sms.addStudent();
                break;
            case 2:
                sms.displayAllStudents();
                break;
            case 3:
                sms.searchStudent();
                break;
            case 4:
                sms.updateStudent();
                break;
            case 5:
                sms.deleteStudent();
                break;
            case 6:
                cout << "\nThank you for using Student Management System!\n";
                cout << "Goodbye!\n\n";
                showMenu = false;
                break;
            default:
                cout << "\nInvalid choice! Please select 1-6.\n";
        }

        // After processing a choice (unless user chose to exit), ask whether to
        // show the menu again.
        if (showMenu) {
            // Clear leftover newline before reading a char
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            char resp = 'n';
            while (true) {
                cout << "\nShow the menu again? (y/n): ";
                if (!(cin >> resp)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n Invalid input. Please enter 'y' or 'n'.\n";
                    continue;
                }

                // normalize response
                resp = tolower(resp);
                if (resp == 'y') {
                    // continue the outer while loop and show the menu
                    showMenu = true;
                    break;
                } else if (resp == 'n') {
                    showMenu = false;
                    cout << "\nThank you for using Student Management System!\n";
                    cout << "Goodbye!\n\n";
                    break;
                } else {
                    cout << "\n⚠ Please enter 'y' or 'n'.\n";
                    // discard rest of line
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
            }
        }

    }

    return 0;
}