// StudentManagementSystem.h
// Enhanced header file with Analytics and AI capabilities

#ifndef STUDENT_MANAGEMENT_SYSTEM_H
#define STUDENT_MANAGEMENT_SYSTEM_H

#include "Student.h"
#include "config.h"
#include <vector>
#include <string>

using namespace std;

class StudentManagementSystem {
private:
    vector<Student> students;
    int nextId;
    string filename;
    
    // Helper functions (existing)
    int findStudentIndex(const string &id);
    bool isValidId(const string &id) const;
    void clearInputBuffer();
    
    // File operations (existing)
    void loadFromFile();
    void saveToFile();
    
    // Pretty-print helpers (existing)
    void printTableHeader() const;
    void printDivider() const;
    
    // NEW: AI Helper - calls Python script for Gemini API
    string callGeminiAPI(const string& prompt);

public:
    // Constructor & Destructor (existing)
    StudentManagementSystem();
    ~StudentManagementSystem();
    
    // Core CRUD operations (existing)
    void addStudent();
    void displayAllStudents();
    void searchStudent();
    void updateStudent();
    void deleteStudent();
    
    // NEW: Dashboard & UI
    void showDashboard();
    
    // NEW: Analytics Features
    void showTopStudents();
    void showAtRiskStudents();
    void showClassStatistics();
    void showCourseWiseAnalysis();
    
    // NEW: AI-Powered Features
    void aiClassAnalysis();
    void aiStudentIntervention();
    void aiPersonalizedFeedback();
    void aiPredictiveInsights();
};

#endif