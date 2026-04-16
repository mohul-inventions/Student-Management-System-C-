#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Define the blueprint for a Student
struct Student {
    int rollNo;
    string name;
    string course;
};

const string FILE_NAME = "students.txt";

// --- Helper Functions for File Handling ---

// Reads all students from the text file into a vector
vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file(FILE_NAME);
    
    if (!file.is_open()) {
        return students; // Return empty vector if file doesn't exist yet
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string rollStr, name, course;
        
        // We use commas to separate data in the text file
        getline(ss, rollStr, ',');
        getline(ss, name, ',');
        getline(ss, course, ',');

        if (!rollStr.empty()) {
            students.push_back({stoi(rollStr), name, course});
        }
    }
    file.close();
    return students;
}

// Overwrites the text file with the current data in the vector
void saveStudents(const vector<Student>& students) {
    ofstream file(FILE_NAME);
    for (const auto& s : students) {
        file << s.rollNo << "," << s.name << "," << s.course << "\n";
    }
    file.close();
}

// --- CRUD Operations ---

void addStudent() {
    vector<Student> students = loadStudents();
    Student s;

    cout << "\n--- Add New Student ---\n";
    cout << "Enter Roll Number: ";
    cin >> s.rollNo;
    
    // Clear the input buffer before reading strings with spaces
    cin.ignore(); 
    
    cout << "Enter Full Name: ";
    getline(cin, s.name);
    
    cout << "Enter Course: ";
    getline(cin, s.course);

    // Check for duplicate Roll Number
    for (const auto& existing : students) {
        if (existing.rollNo == s.rollNo) {
            cout << "Error: A student with Roll Number " << s.rollNo << " already exists!\n";
            return;
        }
    }

    students.push_back(s);
    saveStudents(students);
    cout << "Student added successfully!\n";
}

void displayStudents() {
    vector<Student> students = loadStudents();
    
    cout << "\n--- Student Records ---\n";
    if (students.empty()) {
        cout << "No records found.\n";
        return;
    }

    for (const auto& s : students) {
        cout << "Roll No: " << s.rollNo << " | Name: " << s.name << " | Course: " << s.course << "\n";
    }
}

void updateStudent() {
    vector<Student> students = loadStudents();
    int targetRoll;
    bool found = false;

    cout << "\n--- Update Student ---\n";
    cout << "Enter Roll Number of the student to update: ";
    cin >> targetRoll;

    for (auto& s : students) {
        if (s.rollNo == targetRoll) {
            found = true;
            cin.ignore(); // Clear buffer
            
            cout << "Enter New Name (Current: " << s.name << "): ";
            getline(cin, s.name);
            
            cout << "Enter New Course (Current: " << s.course << "): ";
            getline(cin, s.course);
            
            break; // Stop searching once found
        }
    }

    if (found) {
        saveStudents(students);
        cout << "Student updated successfully!\n";
    } else {
        cout << "Student not found.\n";
    }
}

void deleteStudent() {
    vector<Student> students = loadStudents();
    int targetRoll;
    bool found = false;

    cout << "\n--- Delete Student ---\n";
    cout << "Enter Roll Number to delete: ";
    cin >> targetRoll;

    // Loop through vector to find and erase the student
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->rollNo == targetRoll) {
            students.erase(it);
            found = true;
            break;
        }
    }

    if (found) {
        saveStudents(students);
        cout << "Student deleted successfully!\n";
    } else {
        cout << "Student not found.\n";
    }
}

// --- Main Menu ---

int main() {
    int choice;
    do {
        cout << "\n===============================\n";
        cout << "   Student Management System   \n";
        cout << "===============================\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: cout << "Exiting system. Goodbye!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}