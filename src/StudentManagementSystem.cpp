// StudentManagementSystem.cpp
// Implementation file for Student Management System class
// WITH FILE STORAGE - Data persists between sessions!

#include "StudentManagementSystem.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cstdio>
#include <sstream>
#include <map>
using namespace std;

// Constructor - loads data from file
StudentManagementSystem::StudentManagementSystem() 
    : filename("data/students.txt"), nextId(1001) {
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

// ============================================
// NEW IMPLEMENTATIONS - Added for Enhancement
// ============================================

// Helper method to call Gemini API via Python
string StudentManagementSystem::callGeminiAPI(const string& prompt) {
    // Escape quotes in prompt for shell command
    string escapedPrompt = prompt;
    size_t pos = 0;
    while ((pos = escapedPrompt.find("\"", pos)) != string::npos) {
        escapedPrompt.replace(pos, 1, "\\\"");
        pos += 2;
    }
    
    // Call Python helper script (suppress stderr to hide library warnings)
    string command = "python3 scripts/gemini_helper.py \"" + escapedPrompt + "\" 2>/dev/null";
    
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "{\"error\": \"Failed to execute AI request\"}";
    }
    
    string result;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    
    return result;
}

// Dashboard with key metrics
void StudentManagementSystem::showDashboard() {
    clearScreen();
    printCenteredTitle("📊 STUDENT MANAGEMENT DASHBOARD");
    printDivider();
    
    if (students.empty()) {
        printWarning("No student data available. Add students first!");
        return;
    }
    
    // Calculate metrics
    int totalStudents = students.size();
    float totalGpa = 0.0;
    float maxGpa = 0.0;
    string topStudent = "N/A";
    
    for (const auto& s : students) {
        totalGpa += s.getGpa();
        if (s.getGpa() > maxGpa) {
            maxGpa = s.getGpa();
            topStudent = s.getName();
        }
    }
    
    float avgGpa = totalGpa / totalStudents;
    
    // Count at-risk students
    int atRiskCount = 0;
    for (const auto& s : students) {
        if (s.getGpa() < Config::AT_RISK_GPA_THRESHOLD) {
            atRiskCount++;
        }
    }
    
    // Display dashboard
    cout << Color::BOLD << "\n📈 KEY METRICS:\n" << Color::RESET;
    cout << Color::CYAN << "  Total Students    : " << Color::RESET << totalStudents << "\n";
    cout << Color::CYAN << "  Average GPA       : " << Color::RESET << fixed << setprecision(2) << avgGpa << "\n";
    cout << Color::CYAN << "  Top Performer     : " << Color::RESET << topStudent << " (GPA: " << maxGpa << ")\n";
    cout << Color::YELLOW << "  At-Risk Students  : " << Color::RESET << atRiskCount << "\n";
    
    printDivider();
}

// Show top N students by GPA
void StudentManagementSystem::showTopStudents() {
    if (students.empty()) {
        printWarning("No student records available!");
        return;
    }
    
    cout << "\n" << Color::BOLD << Color::BRIGHT_CYAN << "🏆 TOP PERFORMERS\n" << Color::RESET;
    
    int n;
    cout << "Enter number of top students to display: ";
    while (!(cin >> n) || n < 1) {
        clearInputBuffer();
        printError("Invalid input! Enter a positive number.");
        cout << "Enter number of top students to display: ";
    }
    
    // Create a copy and sort by GPA descending
    vector<Student> sortedStudents = students;
    sort(sortedStudents.begin(), sortedStudents.end(), 
         [](const Student& a, const Student& b) {
             return a.getGpa() > b.getGpa();
         });
    
    ::printDivider('-', 70);
    printTableHeader();
    
    int count = min(n, (int)sortedStudents.size());
    for (int i = 0; i < count; i++) {
        cout << Color::GREEN;
        sortedStudents[i].display();
        cout << Color::RESET;
    }
    
    ::printDivider('-', 70);
    printSuccess("Top " + to_string(count) + " students displayed.");
}

// Show students at risk (GPA below threshold)
void StudentManagementSystem::showAtRiskStudents() {
    if (students.empty()) {
        printWarning("No student records available!");
        return;
    }
    
    cout << "\n" << Color::BOLD << Color::BRIGHT_YELLOW << "⚠️  AT-RISK STUDENTS (GPA < " 
         << Config::AT_RISK_GPA_THRESHOLD << ")\n" << Color::RESET;
    
    vector<Student> atRiskStudents;
    for (const auto& s : students) {
        if (s.getGpa() < Config::AT_RISK_GPA_THRESHOLD) {
            atRiskStudents.push_back(s);
        }
    }
    
    if (atRiskStudents.empty()) {
        printSuccess("No at-risk students found! All students are performing well.");
        return;
    }
    
    ::printDivider('-', 70);
    printTableHeader();
    
    for (const auto& s : atRiskStudents) {
        cout << Color::RED;
        s.display();
        cout << Color::RESET;
    }
    
    ::printDivider('-', 70);
    printWarning(to_string(atRiskStudents.size()) + " students need attention.");
}

// Show comprehensive class statistics
void StudentManagementSystem::showClassStatistics() {
    if (students.empty()) {
        printWarning("No student records available!");
        return;
    }
    
    cout << "\n" << Color::BOLD << Color::BRIGHT_CYAN << "📊 CLASS STATISTICS\n" << Color::RESET;
    ::printDivider('-', 70);
    
    // Calculate statistics
    vector<float> gpas;
    for (const auto& s : students) {
        gpas.push_back(s.getGpa());
    }
    
    sort(gpas.begin(), gpas.end());
    
    float sum = accumulate(gpas.begin(), gpas.end(), 0.0f);
    float average = sum / gpas.size();
    float minGpa = gpas.front();
    float maxGpa = gpas.back();
    float median;
    
    if (gpas.size() % 2 == 0) {
        median = (gpas[gpas.size()/2 - 1] + gpas[gpas.size()/2]) / 2.0;
    } else {
        median = gpas[gpas.size()/2];
    }
    
    // GPA distribution
    int excellent = 0, good = 0, average_range = 0, poor = 0;
    for (float gpa : gpas) {
        if (gpa >= 8.0) excellent++;
        else if (gpa >= 6.5) good++;
        else if (gpa >= 5.0) average_range++;
        else poor++;
    }
    
    // Display statistics
    cout << Color::CYAN << "Total Students   : " << Color::RESET << students.size() << "\n";
    cout << Color::CYAN << "Average GPA      : " << Color::RESET << fixed << setprecision(2) << average << "\n";
    cout << Color::CYAN << "Median GPA       : " << Color::RESET << median << "\n";
    cout << Color::CYAN << "Highest GPA      : " << Color::RESET << maxGpa << "\n";
    cout << Color::CYAN << "Lowest GPA       : " << Color::RESET << minGpa << "\n\n";
    
    cout << Color::BOLD << "GPA Distribution:\n" << Color::RESET;
    cout << Color::GREEN    << "  Excellent (≥8.0)  : " << excellent << " students\n" << Color::RESET;
    cout << Color::BLUE     << "  Good (6.5-7.9)    : " << good << " students\n" << Color::RESET;
    cout << Color::YELLOW   << "  Average (5.0-6.4) : " << average_range << " students\n" << Color::RESET;
    cout << Color::RED      << "  Poor (<5.0)       : " << poor << " students\n" << Color::RESET;
    
    ::printDivider('-', 70);
}

// Show course-wise analysis
void StudentManagementSystem::showCourseWiseAnalysis() {
    if (students.empty()) {
        printWarning("No student records available!");
        return;
    }
    
    cout << "\n" << Color::BOLD << Color::BRIGHT_CYAN << "📚 COURSE-WISE ANALYSIS\n" << Color::RESET;
    ::printDivider('-', 70);
    
    // Group students by course
    map<string, vector<float>> courseData;
    for (const auto& s : students) {
        courseData[s.getCourse()].push_back(s.getGpa());
    }
    
    // Display course statistics
    cout << left << setw(25) << Color::BOLD << "Course" 
         << setw(12) << "Students" 
         << setw(12) << "Avg GPA" 
         << "Status" << Color::RESET << endl;
    ::printDivider('-', 70);
    
    for (const auto& course : courseData) {
        float sum = accumulate(course.second.begin(), course.second.end(), 0.0f);
        float avg = sum / course.second.size();
        
        string status;
        string color;
        if (avg >= 7.5) {
            status = "Excellent";
            color = Color::GREEN;
        } else if (avg >= 6.0) {
            status = "Good";
            color = Color::BLUE;
        } else if (avg >= 5.0) {
            status = "Average";
            color = Color::YELLOW;
        } else {
            status = "Needs Attention";
            color = Color::RED;
        }
        
        cout << color << left << setw(25) << course.first
             << setw(12) << course.second.size()
             << setw(12) << fixed << setprecision(2) << avg
             << status << Color::RESET << endl;
    }
    
    ::printDivider('-', 70);
}

// AI: Smart class analysis using Gemini
void StudentManagementSystem::aiClassAnalysis() {
    if (students.empty()) {
        printWarning("No student data available for AI analysis!");
        return;
    }
    
    cout << "\n" << Color::BOLD << Color::MAGENTA << "🤖 AI-POWERED CLASS ANALYSIS\n" << Color::RESET;
    printInfo("Analyzing class performance with SRMSAi...");
    
    // Prepare data summary for AI
    stringstream dataStream;
    dataStream << "Analyze this student class data:\n";
    dataStream << "Total Students: " << students.size() << "\n";
    
    float totalGpa = 0;
    for (const auto& s : students) {
        totalGpa += s.getGpa();
    }
    dataStream << "Average GPA: " << (totalGpa / students.size()) << "\n";
    dataStream << "Provide insights on overall class performance, trends, and recommendations.";
    
    string response = callGeminiAPI(dataStream.str());
    
    ::printDivider('-', 70);
    cout << Color::CYAN << response << Color::RESET << "\n";
    ::printDivider('-', 70);
}

// AI: Student intervention suggestions
void StudentManagementSystem::aiStudentIntervention() {
    if (students.empty()) {
        printWarning("No student records available!");
        return;
    }
    
    cout << "\n" << Color::BOLD << Color::MAGENTA << "🤖 AI STUDENT INTERVENTION\n" << Color::RESET;
    
    string id;
    cout << "Enter Student ID for AI intervention analysis: ";
    cin >> id;
    
    int index = findStudentIndex(id);
    if (index == -1) {
        printError("Student not found!");
        return;
    }
    
    const Student& s = students[index];
    printInfo("Generating intervention strategy with SRMSAi...");
    
    stringstream prompt;
    prompt << "Student Profile:\n"
           << "Name: " << s.getName() << "\n"
           << "Course: " << s.getCourse() << "\n"
           << "Current GPA: " << s.getGpa() << "\n"
           << "Suggest specific intervention strategies and action items to help this student improve.";
    
    string response = callGeminiAPI(prompt.str());
    
    ::printDivider('-', 70);
    cout << Color::CYAN << response << Color::RESET << "\n";
    ::printDivider('-', 70);
}

// AI: Personalized feedback generator
void StudentManagementSystem::aiPersonalizedFeedback() {
    if (students.empty()) {
        printWarning("No student records available!");
        return;
    }
    
    cout << "\n" << Color::BOLD << Color::MAGENTA << "🤖 AI PERSONALIZED FEEDBACK\n" << Color::RESET;
    
    string id;
    cout << "Enter Student ID: ";
    cin >> id;
    
    int index = findStudentIndex(id);
    if (index == -1) {
        printError("Student not found!");
        return;
    }
    
    const Student& s = students[index];
    printInfo("Generating personalized feedback with SRMSAi...");
    
    stringstream prompt;
    prompt << "Generate detailed personalized feedback for:\n"
           << "Student: " << s.getName() << "\n"
           << "Course: " << s.getCourse() << "\n"
           << "GPA: " << s.getGpa() << "\n"
           << "Include strengths, areas for improvement, and encouragement.";
    
    string response = callGeminiAPI(prompt.str());
    
    ::printDivider('-', 70);
    cout << Color::CYAN << response << Color::RESET << "\n";
    ::printDivider('-', 70);
}

// AI: Predictive insights
void StudentManagementSystem::aiPredictiveInsights() {
    if (students.empty()) {
        printWarning("No student data available for predictions!");
        return;
    }
    
    cout << "\n" << Color::BOLD << Color::MAGENTA << "🤖 AI PREDICTIVE INSIGHTS\n" << Color::RESET;
    printInfo("Generating predictive insights with SRMSAi...");
    
    // Prepare aggregated data
    map<string, vector<float>> courseGpas;
    for (const auto& s : students) {
        courseGpas[s.getCourse()].push_back(s.getGpa());
    }
    
    stringstream prompt;
    prompt << "Based on this academic data, provide predictive insights:\n";
    for (const auto& course : courseGpas) {
        float avg = accumulate(course.second.begin(), course.second.end(), 0.0f) / course.second.size();
        prompt << "Course: " << course.first << ", Avg GPA: " << avg << "\n";
    }
    prompt << "Predict trends, potential challenges, and provide proactive recommendations.";
    
    string response = callGeminiAPI(prompt.str());
    
    ::printDivider('-', 70);
    cout << Color::CYAN << response << Color::RESET << "\n";
    ::printDivider('-', 70);
}