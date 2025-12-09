#!/usr/bin/env python3
# gui_main.py
# Modern GUI for Student Management System

import tkinter as tk
from tkinter import ttk, messagebox, scrolledtext, simpledialog
from backend_bridge import StudentSystemBridge
import threading

class StudentManagementGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Student Management System v2.0 - SRMSAi Powered")
        self.root.geometry("1200x800")
        self.root.configure(bg='#f0f0f0')
        
        # Backend bridge
        self.bridge = StudentSystemBridge()
        
        # Color scheme
        self.colors = {
            'primary': '#2196F3',
            'success': '#4CAF50',
            'danger': '#F44336',
            'warning': '#FF9800',
            'dark': '#212121',
            'light': '#FAFAFA',
            'accent': '#00BCD4'
        }
        
        # Setup GUI
        self.setup_styles()
        self.create_widgets()
        self.refresh_dashboard()
        self.refresh_table()
    
    def setup_styles(self):
        """Configure custom styles"""
        style = ttk.Style()
        style.theme_use('clam')
        
        # Configure Treeview (table)
        style.configure("Treeview",
                       background="white",
                       foreground="black",
                       rowheight=30,
                       fieldbackground="white",
                       font=('Arial', 10))
        style.map('Treeview', background=[('selected', self.colors['primary'])])
        
        # Configure buttons
        style.configure("Primary.TButton",
                       font=('Arial', 10, 'bold'),
                       padding=10)
        
        style.configure("Success.TButton",
                       font=('Arial', 10, 'bold'),
                       padding=10,
                       background=self.colors['success'])
        
        style.configure("Danger.TButton",
                       font=('Arial', 10, 'bold'),
                       padding=10,
                       background=self.colors['danger'])
    
    def create_widgets(self):
        """Create all GUI widgets"""
        
        # Main container
        main_container = tk.Frame(self.root, bg='#f0f0f0')
        main_container.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
        
        # Header
        self.create_header(main_container)
        
        # Dashboard (Statistics cards)
        self.create_dashboard(main_container)
        
        # Notebook for tabs
        self.notebook = ttk.Notebook(main_container)
        self.notebook.pack(fill=tk.BOTH, expand=True, pady=10)
        
        # Tab 1: Student Management
        self.create_student_tab()
        
        # Tab 2: Analytics
        self.create_analytics_tab()
        
        # Tab 3: AI Features
        self.create_ai_tab()
    
    def create_header(self, parent):
        """Create header with title"""
        header = tk.Frame(parent, bg=self.colors['primary'], height=80)
        header.pack(fill=tk.X, pady=(0, 10))
        header.pack_propagate(False)
        
        title = tk.Label(header, 
                        text="🎓 Student Management System v2.0",
                        font=('Arial', 24, 'bold'),
                        bg=self.colors['primary'],
                        fg='white')
        title.pack(side=tk.LEFT, padx=20, pady=20)
        
        subtitle = tk.Label(header,
                           text="SRMSAi-Powered Analytics & Management",
                           font=('Arial', 12),
                           bg=self.colors['primary'],
                           fg='white')
        subtitle.pack(side=tk.LEFT, padx=20)
    
    def create_dashboard(self, parent):
        """Create dashboard with statistics cards"""
        dashboard = tk.Frame(parent, bg='#f0f0f0')
        dashboard.pack(fill=tk.X, pady=10)
        
        # Statistics cards
        self.stat_cards = {}
        
        cards_info = [
            ('total', '📚 Total Students', '0', self.colors['primary']),
            ('avg', '📊 Average GPA', '0.0', self.colors['success']),
            ('top', '🏆 Top Performer', 'N/A', self.colors['accent']),
            ('risk', '⚠️ At Risk', '0', self.colors['warning'])
        ]
        
        for idx, (key, title, value, color) in enumerate(cards_info):
            card = tk.Frame(dashboard, bg=color, relief=tk.RAISED, borderwidth=2)
            card.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=5)
            
            tk.Label(card, text=title, font=('Arial', 12, 'bold'),
                    bg=color, fg='white').pack(pady=5)
            
            self.stat_cards[key] = tk.Label(card, text=value,
                                           font=('Arial', 20, 'bold'),
                                           bg=color, fg='white')
            self.stat_cards[key].pack(pady=5)
    
    def create_student_tab(self):
        """Create student management tab"""
        student_frame = tk.Frame(self.notebook, bg='white')
        self.notebook.add(student_frame, text='👥 Student Management')
        
        # Top controls
        control_frame = tk.Frame(student_frame, bg='white')
        control_frame.pack(fill=tk.X, padx=10, pady=10)
        
        # Search
        tk.Label(control_frame, text="Search ID:", font=('Arial', 10),
                bg='white').pack(side=tk.LEFT, padx=5)
        self.search_entry = tk.Entry(control_frame, font=('Arial', 10), width=20)
        self.search_entry.pack(side=tk.LEFT, padx=5)
        
        tk.Button(control_frame, text="🔍 Search",
                 command=self.search_student,
                 bg=self.colors['primary'], fg='white',
                 font=('Arial', 10, 'bold'), padx=15).pack(side=tk.LEFT, padx=5)
        
        tk.Button(control_frame, text="🔄 Refresh All",
                 command=self.refresh_all,
                 bg=self.colors['success'], fg='white',
                 font=('Arial', 10, 'bold'), padx=15).pack(side=tk.LEFT, padx=5)
        
        # Student table
        table_frame = tk.Frame(student_frame, bg='white')
        table_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
        
        # Scrollbars
        tree_scroll_y = tk.Scrollbar(table_frame)
        tree_scroll_y.pack(side=tk.RIGHT, fill=tk.Y)
        
        tree_scroll_x = tk.Scrollbar(table_frame, orient=tk.HORIZONTAL)
        tree_scroll_x.pack(side=tk.BOTTOM, fill=tk.X)
        
        # Treeview (table)
        self.student_table = ttk.Treeview(table_frame,
                                         columns=('ID', 'Name', 'Age', 'Course', 'GPA'),
                                         show='headings',
                                         yscrollcommand=tree_scroll_y.set,
                                         xscrollcommand=tree_scroll_x.set)
        
        tree_scroll_y.config(command=self.student_table.yview)
        tree_scroll_x.config(command=self.student_table.xview)
        
        # Define columns
        self.student_table.heading('ID', text='Student ID')
        self.student_table.heading('Name', text='Name')
        self.student_table.heading('Age', text='Age')
        self.student_table.heading('Course', text='Course')
        self.student_table.heading('GPA', text='GPA')
        
        self.student_table.column('ID', width=100)
        self.student_table.column('Name', width=200)
        self.student_table.column('Age', width=80)
        self.student_table.column('Course', width=250)
        self.student_table.column('GPA', width=80)
        
        self.student_table.pack(fill=tk.BOTH, expand=True)
        
        # Action buttons
        action_frame = tk.Frame(student_frame, bg='white')
        action_frame.pack(fill=tk.X, padx=10, pady=10)
        
        tk.Button(action_frame, text="➕ Add Student",
                 command=self.add_student_dialog,
                 bg=self.colors['success'], fg='white',
                 font=('Arial', 11, 'bold'), padx=20, pady=10).pack(side=tk.LEFT, padx=5)
        
        tk.Button(action_frame, text="✏️ Edit Student",
                 command=self.edit_student_dialog,
                 bg=self.colors['primary'], fg='white',
                 font=('Arial', 11, 'bold'), padx=20, pady=10).pack(side=tk.LEFT, padx=5)
        
        tk.Button(action_frame, text="🗑️ Delete Student",
                 command=self.delete_student,
                 bg=self.colors['danger'], fg='white',
                 font=('Arial', 11, 'bold'), padx=20, pady=10).pack(side=tk.LEFT, padx=5)
    
    def create_analytics_tab(self):
        """Create analytics tab"""
        analytics_frame = tk.Frame(self.notebook, bg='white')
        self.notebook.add(analytics_frame, text='📊 Analytics')
        
        # Analytics text area
        tk.Label(analytics_frame, text="Class Analytics & Statistics",
                font=('Arial', 16, 'bold'), bg='white').pack(pady=10)
        
        self.analytics_text = scrolledtext.ScrolledText(analytics_frame,
                                                        font=('Courier', 11),
                                                        wrap=tk.WORD,
                                                        height=25)
        self.analytics_text.pack(fill=tk.BOTH, expand=True, padx=20, pady=10)
        
        # Analytics buttons
        btn_frame = tk.Frame(analytics_frame, bg='white')
        btn_frame.pack(fill=tk.X, padx=20, pady=10)
        
        tk.Button(btn_frame, text="🏆 Top Performers",
                 command=self.show_top_performers,
                 bg=self.colors['success'], fg='white',
                 font=('Arial', 10, 'bold'), padx=15, pady=8).pack(side=tk.LEFT, padx=5)
        
        tk.Button(btn_frame, text="⚠️ At-Risk Students",
                 command=self.show_at_risk,
                 bg=self.colors['warning'], fg='white',
                 font=('Arial', 10, 'bold'), padx=15, pady=8).pack(side=tk.LEFT, padx=5)
        
        tk.Button(btn_frame, text="📈 Class Statistics",
                 command=self.show_statistics,
                 bg=self.colors['primary'], fg='white',
                 font=('Arial', 10, 'bold'), padx=15, pady=8).pack(side=tk.LEFT, padx=5)
    
    def create_ai_tab(self):
        """Create AI features tab"""
        ai_frame = tk.Frame(self.notebook, bg='white')
        self.notebook.add(ai_frame, text='🤖 AI Features')
        
        tk.Label(ai_frame, text="🤖 SRMSAi-Powered Insights",
                font=('Arial', 16, 'bold'), bg='white').pack(pady=10)
        
        # AI response area
        self.ai_text = scrolledtext.ScrolledText(ai_frame,
                                                font=('Arial', 11),
                                                wrap=tk.WORD,
                                                height=22)
        self.ai_text.pack(fill=tk.BOTH, expand=True, padx=20, pady=10)
        
        # AI buttons
        btn_frame = tk.Frame(ai_frame, bg='white')
        btn_frame.pack(fill=tk.X, padx=20, pady=10)
        
        tk.Button(btn_frame, text="🔍 AI Class Analysis",
                 command=self.ai_class_analysis,
                 bg='#9C27B0', fg='white',
                 font=('Arial', 10, 'bold'), padx=15, pady=8).pack(side=tk.LEFT, padx=5)
        
        tk.Button(btn_frame, text="💡 Student Intervention",
                 command=self.ai_intervention,
                 bg='#9C27B0', fg='white',
                 font=('Arial', 10, 'bold'), padx=15, pady=8).pack(side=tk.LEFT, padx=5)
        
        tk.Button(btn_frame, text="📝 Personalized Feedback",
                 command=self.ai_feedback,
                 bg='#9C27B0', fg='white',
                 font=('Arial', 10, 'bold'), padx=15, pady=8).pack(side=tk.LEFT, padx=5)
    
    # ============ FUNCTIONALITY METHODS ============
    
    def refresh_dashboard(self):
        """Refresh dashboard statistics"""
        stats = self.bridge.get_statistics()
        self.stat_cards['total'].config(text=str(stats['total']))
        self.stat_cards['avg'].config(text=str(stats['avg_gpa']))
        self.stat_cards['top'].config(text=stats['top_student'])
        self.stat_cards['risk'].config(text=str(stats['at_risk']))
    
    def refresh_table(self):
        """Refresh student table"""
        # Clear existing
        for item in self.student_table.get_children():
            self.student_table.delete(item)
        
        # Load students
        students = self.bridge.get_all_students()
        for s in students:
            gpa = float(s['gpa'])
            # Color code by GPA
            if gpa >= 8.0:
                tag = 'excellent'
            elif gpa >= 6.5:
                tag = 'good'
            elif gpa >= 5.0:
                tag = 'average'
            else:
                tag = 'poor'
            
            self.student_table.insert('', 'end',
                                     values=(s['id'], s['name'], s['age'], s['course'], s['gpa']),
                                     tags=(tag,))
        
        # Configure tags
        self.student_table.tag_configure('excellent', background='#C8E6C9')
        self.student_table.tag_configure('good', background='#BBDEFB')
        self.student_table.tag_configure('average', background='#FFF9C4')
        self.student_table.tag_configure('poor', background='#FFCDD2')
    
    def refresh_all(self):
        """Refresh all data"""
        self.refresh_dashboard()
        self.refresh_table()
        messagebox.showinfo("Success", "Data refreshed successfully!")
    
    def search_student(self):
        """Search for student"""
        student_id = self.search_entry.get().strip()
        if not student_id:
            messagebox.showwarning("Warning", "Please enter a student ID!")
            return
        
        found, student = self.bridge.search_student(student_id)
        if found:
            # Clear table and show only this student
            for item in self.student_table.get_children():
                self.student_table.delete(item)
            self.student_table.insert('', 'end',
                                     values=(student['id'], student['name'],
                                           student['age'], student['course'], student['gpa']))
            messagebox.showinfo("Found", f"Student {student['name']} found!")
        else:
            messagebox.showerror("Not Found", f"Student ID {student_id} not found!")
            self.refresh_table()
    
    def add_student_dialog(self):
        """Open add student dialog"""
        dialog = tk.Toplevel(self.root)
        dialog.title("Add New Student")
        dialog.geometry("400x350")
        dialog.configure(bg='white')
        
        tk.Label(dialog, text="Add New Student", font=('Arial', 14, 'bold'),
                bg='white').pack(pady=10)
        
        # Form fields
        fields = {}
        labels = ['Student ID', 'Name', 'Age', 'Course', 'GPA (0.0-10.0)']
        keys = ['id', 'name', 'age', 'course', 'gpa']
        
        for label, key in zip(labels, keys):
            frame = tk.Frame(dialog, bg='white')
            frame.pack(fill=tk.X, padx=20, pady=5)
            tk.Label(frame, text=label + ":", font=('Arial', 10),
                    bg='white', width=15, anchor='w').pack(side=tk.LEFT)
            fields[key] = tk.Entry(frame, font=('Arial', 10))
            fields[key].pack(side=tk.LEFT, fill=tk.X, expand=True)
        
        def submit():
            try:
                student_id = fields['id'].get().strip()
                name = fields['name'].get().strip()
                age = int(fields['age'].get().strip())
                course = fields['course'].get().strip()
                gpa = float(fields['gpa'].get().strip())
                
                if not all([student_id, name, course]):
                    messagebox.showerror("Error", "All fields are required!")
                    return
                
                if age < 1 or age > 100:
                    messagebox.showerror("Error", "Age must be between 1-100!")
                    return
                
                if gpa < 0 or gpa > 10:
                    messagebox.showerror("Error", "GPA must be between 0.0-10.0!")
                    return
                
                success, msg = self.bridge.add_student(student_id, name, age, course, gpa)
                if success:
                    messagebox.showinfo("Success", msg)
                    dialog.destroy()
                    self.refresh_all()
                else:
                    messagebox.showerror("Error", msg)
            except ValueError:
                messagebox.showerror("Error", "Invalid input! Check age and GPA.")
        
        tk.Button(dialog, text="✓ Add Student",
                 command=submit,
                 bg=self.colors['success'], fg='white',
                 font=('Arial', 11, 'bold'), padx=20, pady=10).pack(pady=20)
    
    def edit_student_dialog(self):
        """Open edit student dialog"""
        selected = self.student_table.selection()
        if not selected:
            messagebox.showwarning("Warning", "Please select a student to edit!")
            return
        
        values = self.student_table.item(selected[0])['values']
        student_id = values[0]
        
        dialog = tk.Toplevel(self.root)
        dialog.title("Edit Student")
        dialog.geometry("400x350")
        dialog.configure(bg='white')
        
        tk.Label(dialog, text=f"Edit Student: {student_id}",
                font=('Arial', 14, 'bold'), bg='white').pack(pady=10)
        
        # Form fields
        fields = {}
        labels = ['Name', 'Age', 'Course', 'GPA (0.0-10.0)']
        keys = ['name', 'age', 'course', 'gpa']
        defaults = [values[1], values[2], values[3], values[4]]
        
        for label, key, default in zip(labels, keys, defaults):
            frame = tk.Frame(dialog, bg='white')
            frame.pack(fill=tk.X, padx=20, pady=5)
            tk.Label(frame, text=label + ":", font=('Arial', 10),
                    bg='white', width=15, anchor='w').pack(side=tk.LEFT)
            fields[key] = tk.Entry(frame, font=('Arial', 10))
            fields[key].insert(0, default)
            fields[key].pack(side=tk.LEFT, fill=tk.X, expand=True)
        
        def submit():
            try:
                name = fields['name'].get().strip()
                age = int(fields['age'].get().strip())
                course = fields['course'].get().strip()
                gpa = float(fields['gpa'].get().strip())
                
                success, msg = self.bridge.update_student(student_id, name, age, course, gpa)
                if success:
                    messagebox.showinfo("Success", msg)
                    dialog.destroy()
                    self.refresh_all()
                else:
                    messagebox.showerror("Error", msg)
            except ValueError:
                messagebox.showerror("Error", "Invalid input!")
        
        tk.Button(dialog, text="✓ Update Student",
                 command=submit,
                 bg=self.colors['primary'], fg='white',
                 font=('Arial', 11, 'bold'), padx=20, pady=10).pack(pady=20)
    
    def delete_student(self):
        """Delete selected student"""
        selected = self.student_table.selection()
        if not selected:
            messagebox.showwarning("Warning", "Please select a student to delete!")
            return
        
        values = self.student_table.item(selected[0])['values']
        student_id = values[0]
        name = values[1]
        
        confirm = messagebox.askyesno("Confirm Delete",
                                     f"Are you sure you want to delete:\n{name} (ID: {student_id})?")
        if confirm:
            success, msg = self.bridge.delete_student(student_id)
            if success:
                messagebox.showinfo("Success", msg)
                self.refresh_all()
            else:
                messagebox.showerror("Error", msg)
    
    def show_top_performers(self):
        """Show top performing students"""
        students = self.bridge.get_all_students()
        if not students:
            self.analytics_text.delete(1.0, tk.END)
            self.analytics_text.insert(1.0, "No student data available!")
            return
        
        # Sort by GPA
        sorted_students = sorted(students, key=lambda x: float(x['gpa']), reverse=True)
        
        output = "🏆 TOP PERFORMERS\n"
        output += "=" * 70 + "\n\n"
        
        for i, s in enumerate(sorted_students[:10], 1):
            output += f"{i}. {s['name']} (ID: {s['id']})\n"
            output += f"   Course: {s['course']}\n"
            output += f"   GPA: {s['gpa']}\n\n"
        
        self.analytics_text.delete(1.0, tk.END)
        self.analytics_text.insert(1.0, output)
    
    def show_at_risk(self):
        """Show at-risk students"""
        students = self.bridge.get_all_students()
        if not students:
            self.analytics_text.delete(1.0, tk.END)
            self.analytics_text.insert(1.0, "No student data available!")
            return
        
        at_risk = [s for s in students if float(s['gpa']) < 5.0]
        
        output = "⚠️ AT-RISK STUDENTS (GPA < 5.0)\n"
        output += "=" * 70 + "\n\n"
        
        if not at_risk:
            output += "✓ No at-risk students! All students are performing well.\n"
        else:
            for s in at_risk:
                output += f"⚠ {s['name']} (ID: {s['id']})\n"
                output += f"   Course: {s['course']}\n"
                output += f"   GPA: {s['gpa']}\n"
                output += f"   Status: NEEDS IMMEDIATE ATTENTION\n\n"
        
        self.analytics_text.delete(1.0, tk.END)
        self.analytics_text.insert(1.0, output)
    
    def show_statistics(self):
        """Show class statistics"""
        students = self.bridge.get_all_students()
        if not students:
            self.analytics_text.delete(1.0, tk.END)
            self.analytics_text.insert(1.0, "No student data available!")
            return
        
        gpas = [float(s['gpa']) for s in students]
        
        output = "📊 CLASS STATISTICS\n"
        output += "=" * 70 + "\n\n"
        
        output += f"Total Students: {len(students)}\n"
        output += f"Average GPA: {sum(gpas)/len(gpas):.2f}\n"
        output += f"Median GPA: {sorted(gpas)[len(gpas)//2]:.2f}\n"
        output += f"Highest GPA: {max(gpas):.2f}\n"
        output += f"Lowest GPA: {min(gpas):.2f}\n\n"
        
        output += "GPA Distribution:\n"
        output += f"  Excellent (≥8.0): {sum(1 for g in gpas if g >= 8.0)} students\n"
        output += f"  Good (6.5-7.9): {sum(1 for g in gpas if 6.5 <= g < 8.0)} students\n"
        output += f"  Average (5.0-6.4): {sum(1 for g in gpas if 5.0 <= g < 6.5)} students\n"
        output += f"  Poor (<5.0): {sum(1 for g in gpas if g < 5.0)} students\n"
        
        self.analytics_text.delete(1.0, tk.END)
        self.analytics_text.insert(1.0, output)
    
    def ai_class_analysis(self):
        """AI class analysis"""
        self.ai_text.delete(1.0, tk.END)
        self.ai_text.insert(1.0, "🤖 Analyzing class with SRMSAi...\n\nPlease wait...")
        
        def run_ai():
            stats = self.bridge.get_statistics()
            prompt = f"Analyze this student class: Total {stats['total']} students, Average GPA: {stats['avg_gpa']}, At-risk: {stats['at_risk']}. Provide insights."
            response = self.bridge.call_gemini_ai(prompt)
            self.ai_text.delete(1.0, tk.END)
            self.ai_text.insert(1.0, f"🤖 SRMSAi CLASS ANALYSIS\n{'='*70}\n\n{response}")
        
        threading.Thread(target=run_ai, daemon=True).start()
    
    def ai_intervention(self):
        """AI student intervention"""
        student_id = simpledialog.askstring("AI Intervention",
                                               "Enter Student ID for intervention analysis:")
        if not student_id:
            return
        
        found, student = self.bridge.search_student(student_id)
        if not found:
            messagebox.showerror("Error", "Student not found!")
            return
        
        self.ai_text.delete(1.0, tk.END)
        self.ai_text.insert(1.0, "🤖 Generating intervention strategy...\n\nPlease wait...")
        
        def run_ai():
            prompt = f"Student: {student['name']}, Course: {student['course']}, GPA: {student['gpa']}. Suggest intervention strategies."
            response = self.bridge.call_gemini_ai(prompt)
            self.ai_text.delete(1.0, tk.END)
            self.ai_text.insert(1.0, f"💡 AI INTERVENTION FOR {student['name']}\n{'='*70}\n\n{response}")
        
        threading.Thread(target=run_ai, daemon=True).start()
    
    def ai_feedback(self):
        """AI personalized feedback"""
        student_id = simpledialog.askstring("AI Feedback",
                                               "Enter Student ID for personalized feedback:")
        if not student_id:
            return
        
        found, student = self.bridge.search_student(student_id)
        if not found:
            messagebox.showerror("Error", "Student not found!")
            return
        
        self.ai_text.delete(1.0, tk.END)
        self.ai_text.insert(1.0, "🤖 Generating personalized feedback...\n\nPlease wait...")
        
        def run_ai():
            prompt = f"Generate personalized feedback for: {student['name']}, Course: {student['course']}, GPA: {student['gpa']}. Include strengths and improvements."
            response = self.bridge.call_gemini_ai(prompt)
            self.ai_text.delete(1.0, tk.END)
            self.ai_text.insert(1.0, f"📝 FEEDBACK FOR {student['name']}\n{'='*70}\n\n{response}")
        
        threading.Thread(target=run_ai, daemon=True).start()

# ============ MAIN ============

if __name__ == "__main__":
    root = tk.Tk()
    app = StudentManagementGUI(root)
    root.mainloop()
