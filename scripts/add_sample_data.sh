#!/bin/bash
# add_sample_data.sh - Adds sample students for demonstration
# Writes directly to students.txt in the format expected by the C++ program

OUTPUT_FILE="data/students.txt"

echo "Adding sample student data to $OUTPUT_FILE..."

# Format:
# NextID (single line)
# Student ID
# Name
# Age
# Course
# GPA
# (Repeat for each student)

cat > "$OUTPUT_FILE" << EOF
1011
CS101
Ankit Choubey
20
Computer Science
9.2
ME201
Vaibhav Hinduraodhabde
21
Mechanical Engineering
7.8
CS102
GNS
19
Computer Science
8.5
EE301
Ritin
22
Electrical Engineering
6.2
CS103
Aryan Sharma
20
Computer Science
4.5
ME202
Ishaan Patel
21
Mechanical Engineering
5.8
EE302
Ananya Gupta
19
Electrical Engineering
8.9
CS104
Vihaan Singh
22
Computer Science
3.8
CS105
Rohan Kumar
20
Computer Science
7.5
ME203
Diya Verma
21
Mechanical Engineering
9.5
EOF

echo "✓ Added 10 sample students to database."
echo "You can now run ./student_system to see the data."
