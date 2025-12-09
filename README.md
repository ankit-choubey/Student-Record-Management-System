# 🎓 Student Record Management System (SRMS)

[![C++](https://img.shields.io/badge/Language-C++11-00599C?style=for-the-badge&logo=c%2B%2B)](https://en.cppreference.com/w/cpp/11)
[![ANSI UI](https://img.shields.io/badge/UI-ANSI%20Colors-white?style=for-the-badge&logo=terminal)](https://en.wikipedia.org/wiki/ANSI_escape_code)
[![Gemini AI](https://img.shields.io/badge/AI-Google%20Gemini-4285F4?style=for-the-badge&logo=google)](https://aistudio.google.com)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-macOS%20%7C%20Linux%20%7C%20Windows-lightgrey?style=for-the-badge&logo=apple)](https://en.wikipedia.org/wiki/Cross-platform_software)

<div align="center">
<b>Secure. Intelligent. Professional.</b><br>
<i>A Production-Ready C++ Student Management Terminal with AI-Powered Insights for the Modern Educator.</i>
</div>

---

## 📜 Mission Brief

**SRMS** is more than a student management tool—it’s an **AI-enhanced intelligence platform** for educators and administrators.  
Built entirely in modern C++ with zero heavy frameworks, it delivers enterprise-grade functionality in a lightweight, high-performance console interface.

From real-time GPA dashboards and risk detection to Gemini-powered predictive analytics, SRMS transforms raw student data into actionable insight.  
Data persists across sessions via robust file storage with automatic saving after every critical operation.

> **Offline-First, AI-Optional**  
> SRMS works perfectly offline. When a Gemini API key is available, AI features are upgraded to real model responses; otherwise, the system gracefully falls back to simulation.

---

## 🧠 Core Architecture: Modern C++ & STL

SRMS uses **C++11 STL algorithms** and strong encapsulation to keep the codebase clean, efficient, and maintainable.

### Design Highlights

- **Zero External Dependencies (Core):** Only standard C++ and `<fstream>`, `<vector>`, `<algorithm>`, `<numeric>`.
- **Clean Domain Model:**  
  - `Student` – encapsulates ID, name, age, course, GPA.  
  - `StudentManagementSystem` – owns the collection and all operations.
- **Persistent Storage:**  
  - `students.txt` with version-safe header (`nextId` reserved), appended and rewritten safely.
- **Robust IO Layer:**  
  - Input validation (age, GPA, IDs)  
  - Buffer clearing to avoid input corruption

### Smart Algorithms

- **Sorting:** Top performers via `std::sort` on GPA.
- **Aggregation:** Averages and sums via `std::accumulate`.
- **Search:** ID-based lookup using simple index search (fast enough for classroom scale).
- **Distribution Buckets:** GPA bands computed in a single pass.

---

## ✨ Feature Overview

### 📋 Core Functionality

- **Add Student**
  - Validates ID (alphanumeric with at least one letter and one digit).
  - Age range checks (1–100).
  - GPA range checks (0.0–10.0).
- **Update Student**
  - Update name, age, course, GPA, or all fields at once.
- **Delete Student**
  - Confirmation prompt, safe erase from in-memory vector and file.
- **Search Student**
  - Lookup by ID, shows formatted row with table header.
- **Display All**
  - Beautifully formatted table with columns: ID, Name, Age, Course, GPA.

### 📊 Analytics Dashboard

- **Dashboard View**
  - Total number of students.
  - Average GPA.
  - Top performer’s name and GPA.
  - Count of at-risk students (GPA below threshold).
- **Top N Students**
  - Ask for `N` and display top N by GPA.
- **At-Risk Students**
  - List of all students with GPA below `AT_RISK_GPA_THRESHOLD` (default 5.0).
- **Class Statistics**
  - Average, median, min, max GPA.
  - Distribution into Excellent / Good / Average / Poor.
- **Course-wise Analysis**
  - Group by course.
  - Per-course average GPA, student count, and status label (Excellent → Needs Attention).

### 🤖 AI-Powered Features (SRMSAi)

These features use `gemini_helper.py` as a bridge to Google Gemini, with a graceful fallback when offline or when the API is not configured.

- **AI Class Analysis**
  - Summarizes entire class performance and gives high-level insights.
- **AI Student Intervention**
  - For a chosen student ID, suggests tailored strategies to improve.
- **AI Personalized Feedback**
  - Generates feedback message for a specific student based on GPA and course.
- **AI Predictive Insights**
  - Uses course-wise averages to discuss trends and possible risks.

> If the API key is missing or the Python dependency is unavailable, the system can be configured to simulate plausible responses instead of failing.

---

## 🎨 Modern Console UI

Thanks to `config.h`, the console experience feels like a mini-dashboard:

- **ANSI Color Palette**
  - Cyan / Bright Cyan for headers and info.
  - Green / Bright Green for success.
  - Yellow / Bright Yellow for warnings.
  - Red / Bright Red for errors and at-risk students.
- **Unicode Box Drawing**
  - Clean borders around headers and structured sections.
- **Helper Functions**
  - `clearScreen()`, `printCenteredTitle()`, `printDivider()`
  - `printSuccess()`, `printError()`, `printWarning()`, `printInfo()`

The result: a **professional-looking** CLI that feels close to a lightweight TUI dashboard.

---

## 📋 Prerequisites

### Required

- **C++ Compiler:** `g++` or equivalent with C++11 or later
- **OS:** macOS, Linux, or Windows (WSL/MinGW)
- **Terminal:** ANSI-color capable (modern terminals work by default)

### Optional (for Full AI Mode)

- **Python 3.9+**
- **Package:**



2. **Step Through:**
- Show Dashboard (option 6).
- Show Top Performers, At-Risk, Stats, Course-wise (options 7–10).
- Trigger AI analysis & feedback (options 11–14).

3. **Live Interaction:**
- Add a new student.
- Re-open dashboard to show real-time metric change.
- Run AI feedback on that new student.

Use `DEMO_GUIDE.txt` as your on-stage script.

---

## 🤝 Contributing

Ideas & PRs are welcome, especially around:

- Qt/Web GUI front-ends.
- Database integration (SQLite/MySQL/PostgreSQL).
- Advanced ML models for early risk prediction.
- Export utilities (CSV, PDF, Excel).
- Role-based access (admin/teacher).

---

## 📄 License

This project is released under the **MIT License**.  
Use it freely in academic, personal, or commercial projects.

---

## 👏 Acknowledgments

- **SRMS-Ai:** Powered optionally by Google Gemini.
- **Design Inspiration:** Modern terminal dashboards and admin panels.
- **Stack:** Clean C++11, STL, and ANSI terminals.

<div align="center">

<b>"Data → Insight → Action.<br>Empowering educators with intelligent tooling."</b>

</div>
