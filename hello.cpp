#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include<string.h>

#define FILE_NAME "students.txt"

using namespace std;

// Student class to hold student details
class Student {
private:
    int id;
    string name;
    string dob;
    string gender;

public:
    // Constructor to initialize student details
    Student(int id, string name, string dob, string gender) :
            id(id),
            name(name),
            dob(dob),
            gender(gender) {};

    // Getter for student ID
    int getId() {
        return id;
    }

    // Getter for student's first name
    string getName() {
        return name;
    }

    // Getter for student's last name
    string getDob() {
        return dob;
    }

    // Getter for student's marks
    string getGender() {
        return gender;
    }

 

    // Setter for student's first name
    void setName(string newFirstName) {
        name = newFirstName;
    }

    // Setter for student's last name
    void setLastName(string newLastName) {
        dob = newLastName;
    }
};

// Node class for linked list
class Node {
public:
    Student student;
    Node* next;

    Node(Student student) : student(student), next(nullptr) {}
};

// Linked list class to manage students
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Function to add a student to the list
    void addStudent(Student student) {
        Node* newNode = new Node(student);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Function to print the list of students
    void printStudents() {
        cout << "Students" << endl;
        cout << "---------------------" << endl;
        Node* temp = head;
        int index = 1;
        while (temp) {
            cout << "(" << index << ") : " << temp->student.getId() << " " << temp->student.getName() << " " << temp->student.getGender() << endl;
            temp = temp->next;
            index++;
        }
        cout << "---------------------" << endl;
    }

    // Function to find a student by ID
    bool isIdTaken(int id) {
        Node* temp = head;
        while (temp) {
            if (temp->student.getId() == id) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

  

};

// Function to save a student to file
void saveStudentToFile(Student student) {
    ofstream file(FILE_NAME, ios::app);
    if (file.is_open()) {
        file << student.getId() << " " << student.getName() << " " << student.getDob() << " " << student.getGender() << endl;
        file.close();
    } else {
        cerr << "Failed to open file " << FILE_NAME << endl;
    }
}

// Function to load students from file into linked list
void loadStudentsFromFile(LinkedList& list) {
    ifstream file(FILE_NAME);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            istringstream ss(line);
            int id;
            string name, dob;
            string gender;
            if (ss >> id >> name >> dob >> gender) {
                Student student(id, name, dob, gender);
                list.addStudent(student);
            } else {
                cerr << "Invalid record: " << line << endl;
            }
        }
        file.close();
    } else {
        cerr << "Failed to open file " << FILE_NAME << endl;
    }
}

// Function to validate name (no numbers allowed)
bool isValidName(string name) {
    return regex_match(name, regex("^[A-Za-z]+$"));
}


// Function to process user commands
void processCommands() {
    LinkedList studentList;
    loadStudentsFromFile(studentList);

    

    string input;
    string command;

    do {
        cout << "Console >";
        getline(cin, input);

        istringstream iss(input);
        iss >> command;

        // Convert the command to lowercase for case-insensitive comparison
        for (size_t i = 0; i < command.length(); i++) {
            command[i] = tolower(command[i]);
        }

        // Process the command
        if (command == "liststudents") {
            cout << "------------------------------------------------------------------------------------------------------------------" << endl;
            studentList.printStudents();
            cout << "------------------------------------------------------------------------------------------------------------------" << endl;
        } else if (command == "addstudents") {
            int number_of_students;
            cout << "How many students do you want to add?" << endl;
            cin >> number_of_students;
            cin.ignore(); // Ignore the newline character left in the buffer

            cout << "Enter students data in format : <student_id> <name> <dob> <marks>" << endl;

            // Get students data
            for (int i = 0; i < number_of_students; i++) {
                string input, id, name, dob, gender;
                cout << "Enter the data for student (" << i + 1 << ")" << endl;
                getline(cin, input);
                istringstream student_ss(input);
                if (student_ss >> id >> name >> dob >> gender) {
                    // Validate names
                    if (!isValidName(name) || !isValidName(dob)) {
                        cerr << "Invalid name format. Names must contain only letters." << endl;
                        i--; // Ask for the current student data again
                        continue;
                    }
                    // Check if ID is taken, if so prompt to enter a different ID
                    if (studentList.isIdTaken(stoi(id))) {
                        cerr << "A student with ID " << id << " already exists. Please use a different ID." << endl;
                        i--; // Ask for the current student data again
                    } else {
                        Student student(stoi(id), name, dob, stof(gender));
                        studentList.addStudent(student);
                        saveStudentToFile(student);
                    }
                } else {
                    cerr << "Invalid input format" << endl;
                    i--; // Ask for the current student data again
                }
            }

            cout << "Finished adding students" << endl;
        } else {
            // Invalid command entered
            if (command != "exit") {
                break;
            }
        }
    } while (command != "exit");
}

// Function to display the start message
void startMessage() {
    cout << " ==================================================== " << endl;
    cout << "*     Welcome to RCA Student Management System!     *" << endl;
    cout << "      *********************************************" << endl;
    cout << "*                                                 *" << endl;
    cout << "*             student grading system              *" << endl;
    cout << " ====================================================" << endl;
}

int main() {
    // Display the start message
    startMessage();

    // Process user commands
    processCommands();

    return 0;
}
