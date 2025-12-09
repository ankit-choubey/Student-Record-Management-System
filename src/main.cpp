// main.cpp
// Enhanced main program with Dashboard, Analytics, and AI features

#include "StudentManagementSystem.h"
#include "config.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    StudentManagementSystem sms;
    int choice;
    bool showMenu = true;
    
    // Clear screen and show welcome
    clearScreen();
    printCenteredTitle("+-----------------------------------------------------------+");
    printCenteredTitle("|    STUDENT RECORD MANAGEMENT SYSTEM v2.0                |");
    printCenteredTitle("|    Enhanced with AI & Analytics                         |");
    printCenteredTitle("+-----------------------------------------------------------+");
    cout << "\n";
    
    // Show dashboard on startup
    sms.showDashboard();
    
    while (showMenu) {
        cout << "\n";
        printDivider('=', 70);
        cout << Color::BOLD << Color::BRIGHT_CYAN;
        cout << "                         MAIN MENU\n";
        cout << Color::RESET;
        printDivider('=', 70);
        
        // Core Operations
        cout << Color::BOLD << "\n📋 CORE OPERATIONS:\n" << Color::RESET;
        cout << "  1. Add New Student\n";
        cout << "  2. Display All Students\n";
        cout << "  3. Search Student\n";
        cout << "  4. Update Student\n";
        cout << "  5. Delete Student\n";
        
        // Analytics
        cout << Color::BOLD << "\n📊 ANALYTICS:\n" << Color::RESET;
        cout << "  6. Show Dashboard\n";
        cout << "  7. Top Performers\n";
        cout << "  8. At-Risk Students\n";
        cout << "  9. Class Statistics\n";
        cout << "  10. Course-Wise Analysis\n";
        
        // AI Features
        cout << Color::BOLD << "\n🤖 AI-POWERED FEATURES:\n" << Color::RESET;
        cout << "  11. AI Class Analysis\n";
        cout << "  12. AI Student Intervention\n";
        cout << "  13. AI Personalized Feedback\n";
        cout << "  14. AI Predictive Insights\n";
        
        // Exit
        cout << Color::BOLD << "\n" << Color::RED << "  0. Exit\n" << Color::RESET;
        
        printDivider('=', 70);
        cout << Color::YELLOW << "Enter your choice (0-14): " << Color::RESET;
        
        // Input validation
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printError("Invalid input! Please enter a number.");
            continue;
        }
        
        cout << "\n";
        
        switch (choice) {
            // Core Operations
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
            
            // Analytics
            case 6:
                sms.showDashboard();
                break;
            case 7:
                sms.showTopStudents();
                break;
            case 8:
                sms.showAtRiskStudents();
                break;
            case 9:
                sms.showClassStatistics();
                break;
            case 10:
                sms.showCourseWiseAnalysis();
                break;
            
            // AI Features
            case 11:
                sms.aiClassAnalysis();
                break;
            case 12:
                sms.aiStudentIntervention();
                break;
            case 13:
                sms.aiPersonalizedFeedback();
                break;
            case 14:
                sms.aiPredictiveInsights();
                break;
            
            // Exit
            case 0:
                printSuccess("Thank you for using Student Management System!");
                cout << Color::BRIGHT_CYAN << "Goodbye!\n\n" << Color::RESET;
                showMenu = false;
                break;
            
            default:
                printError("Invalid choice! Please select 0-14.");
        }
        
        // Ask to continue (unless exiting)
        if (showMenu && choice != 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            char resp;
            while (true) {
                cout << "\n" << Color::YELLOW << "Continue to main menu? (y/n): " << Color::RESET;
                if (!(cin >> resp)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    printError("Invalid input. Please enter 'y' or 'n'.");
                    continue;
                }
                
                resp = tolower(resp);
                if (resp == 'y') {
                    clearScreen();
                    break;
                } else if (resp == 'n') {
                    showMenu = false;
                    printSuccess("Thank you for using Student Management System!");
                    cout << Color::BRIGHT_CYAN << "Goodbye!\n\n" << Color::RESET;
                    break;
                } else {
                    printError("Please enter 'y' or 'n'.");
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }
    }
    
    return 0;
}