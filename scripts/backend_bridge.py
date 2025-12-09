# backend_bridge.py
# Bridge between Python GUI and C++ backend

import subprocess
import os
import json

class StudentSystemBridge:
    """
    Bridge class to communicate with C++ student management system
    """
    
    def __init__(self):
        self.students_file = "students.txt"
        self.cpp_executable = "./student_system"
    
    def read_students_from_file(self):
        """Read student data from students.txt file"""
        students = []
        
        if not os.path.exists(self.students_file):
            return students
        
        try:
            with open(self.students_file, 'r') as f:
                lines = f.readlines()
                
                # Skip first line (nextId)
                if len(lines) > 1:
                    i = 1
                    while i < len(lines):
                        if i + 4 < len(lines):
                            student = {
                                'id': lines[i].strip(),
                                'name': lines[i+1].strip(),
                                'age': lines[i+2].strip(),
                                'course': lines[i+3].strip(),
                                'gpa': lines[i+4].strip()
                            }
                            students.append(student)
                            i += 5
                        else:
                            break
        except Exception as e:
            print(f"Error reading students: {e}")
        
        return students
    
    def add_student(self, student_id, name, age, course, gpa):
        """Add student by writing to file"""
        try:
            # Read existing data
            students = self.read_students_from_file()
            
            # Check for duplicate ID
            for s in students:
                if s['id'] == student_id:
                    return False, "Student ID already exists!"
            
            # Read nextId from file
            nextId = 1001
            if os.path.exists(self.students_file):
                with open(self.students_file, 'r') as f:
                    nextId = int(f.readline().strip())
            
            # Append new student
            with open(self.students_file, 'w') as f:
                f.write(f"{nextId}\n")
                for s in students:
                    f.write(f"{s['id']}\n{s['name']}\n{s['age']}\n{s['course']}\n{s['gpa']}\n")
                # Add new student
                f.write(f"{student_id}\n{name}\n{age}\n{course}\n{gpa}\n")
            
            return True, "Student added successfully!"
        except Exception as e:
            return False, f"Error: {str(e)}"
    
    def delete_student(self, student_id):
        """Delete student by ID"""
        try:
            students = self.read_students_from_file()
            
            # Find and remove student
            found = False
            new_students = []
            for s in students:
                if s['id'] != student_id:
                    new_students.append(s)
                else:
                    found = True
            
            if not found:
                return False, "Student not found!"
            
            # Write back to file
            nextId = 1001
            with open(self.students_file, 'w') as f:
                f.write(f"{nextId}\n")
                for s in new_students:
                    f.write(f"{s['id']}\n{s['name']}\n{s['age']}\n{s['course']}\n{s['gpa']}\n")
            
            return True, "Student deleted successfully!"
        except Exception as e:
            return False, f"Error: {str(e)}"
    
    def update_student(self, student_id, name=None, age=None, course=None, gpa=None):
        """Update student information"""
        try:
            students = self.read_students_from_file()
            
            # Find and update student
            found = False
            for s in students:
                if s['id'] == student_id:
                    if name: s['name'] = name
                    if age: s['age'] = str(age)
                    if course: s['course'] = course
                    if gpa: s['gpa'] = str(gpa)
                    found = True
                    break
            
            if not found:
                return False, "Student not found!"
            
            # Write back to file
            nextId = 1001
            with open(self.students_file, 'w') as f:
                f.write(f"{nextId}\n")
                for s in students:
                    f.write(f"{s['id']}\n{s['name']}\n{s['age']}\n{s['course']}\n{s['gpa']}\n")
            
            return True, "Student updated successfully!"
        except Exception as e:
            return False, f"Error: {str(e)}"
    
    def search_student(self, student_id):
        """Search for student by ID"""
        students = self.read_students_from_file()
        for s in students:
            if s['id'] == student_id:
                return True, s
        return False, None
    
    def get_all_students(self):
        """Get all students"""
        return self.read_students_from_file()
    
    def get_statistics(self):
        """Calculate class statistics"""
        students = self.read_students_from_file()
        
        if not students:
            return {
                'total': 0,
                'avg_gpa': 0.0,
                'top_student': 'N/A',
                'at_risk': 0
            }
        
        gpas = [float(s['gpa']) for s in students]
        total = len(students)
        avg_gpa = sum(gpas) / total
        
        # Find top student
        max_gpa = max(gpas)
        top_student = next(s['name'] for s in students if float(s['gpa']) == max_gpa)
        
        # Count at-risk students (GPA < 5.0)
        at_risk = sum(1 for gpa in gpas if gpa < 5.0)
        
        return {
            'total': total,
            'avg_gpa': round(avg_gpa, 2),
            'top_student': top_student,
            'at_risk': at_risk,
            'max_gpa': max_gpa
        }
    
    def call_gemini_ai(self, prompt):
        """Call Gemini AI helper"""
        try:
            result = subprocess.run(
                ['python3', 'gemini_helper.py', prompt],
                capture_output=True,
                text=True,
                timeout=30
            )
            return result.stdout.strip()
        except Exception as e:
            return f"Error calling AI: {str(e)}"
