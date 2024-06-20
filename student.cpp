#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

#define FILE_NAME "students.txt"

using namespace std;

// Student class to hold student details
class Student {
private:
    int id;
    string first_name;
    string last_name;
    float marks;

public:
    // Constructor to initialize student details
    Student(int id, string first_name, string last_name, float marks) :
            id(id),
            first_name(first_name),
            last_name(last_name),
            marks(marks) {};

    // Getter for student ID
    int getId() {
        return id;
    }

    // Getter for student's first name
    string getFirstName() {
        return first_name;
    }

    // Getter for student's last name
    string getLastName() {
        return last_name;
    }

    // Getter for student's full name
    string getFullName() {
        return first_name + " " + last_name;
    }

    // Getter for student's marks
    float getMarks() {
        return marks;
    }

    // Setter for student's marks
    void setMarks(float newMarks) {
        marks = newMarks;
    }

    // Setter for student's first name
    void setFirstName(string newFirstName) {
        first_name = newFirstName;
    }

    // Setter for student's last name
    void setLastName(string newLastName) {
        last_name = newLastName;
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
            cout << "(" << index << ") : " << temp->student.getId() << " " << temp->student.getFullName() << " " << temp->student.getMarks() << endl;
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

    // Function to search students by name
    void searchStudentsByName(string name) {
        Node* temp = head;
        LinkedList foundStudents;
        while (temp) {
            if (temp->student.getFirstName() == name || temp->student.getLastName() == name) {
                foundStudents.addStudent(temp->student);
            }
            temp = temp->next;
        }
        if (foundStudents.head) {
            foundStudents.printStudents();
        } else {
            cout << "No students found with the name " << name << endl;
        }
    }

    // Function to sort students by marks in descending order
    void sortStudentsByMarks() {
        if (!head || !head->next) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            Node* prev = nullptr;

            while (current->next) {
                if (current->student.getMarks() < current->next->student.getMarks()) {
                    swapped = true;
                    if (prev) {
                        Node* temp = current->next;
                        current->next = temp->next;
                        temp->next = current;
                        prev->next = temp;
                        prev = temp;
                    } else {
                        Node* temp = current->next;
                        current->next = temp->next;
                        temp->next = current;
                        head = temp;
                        prev = temp;
                    }
                } else {
                    prev = current;
                    current = current->next;
                }
            }
        } while (swapped);

        printStudents();
    }

    // Function to update a student's details
    void updateStudent(int id, string newFirstName, string newLastName, float newMarks) {
        Node* temp = head;
        while (temp) {
            if (temp->student.getId() == id) {
                temp->student.setFirstName(newFirstName);
                temp->student.setLastName(newLastName);
                temp->student.setMarks(newMarks);
                cout << "Student with ID " << id << " updated successfully!" << endl;
                return;
            }
            temp = temp->next;
        }
        cerr << "No student found with ID " << id << endl;
    }

    // Function to delete a student
    void deleteStudent(int id) {
        if (!head) {
            cerr << "No student found with ID " << id << endl;
            return;
        }

        if (head->student.getId() == id) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Student with ID " << id << " deleted successfully!" << endl;
            return;
        }

        Node* current = head;
        Node* prev = nullptr;
        while (current && current->student.getId() != id) {
            prev = current;
            current = current->next;
        }

        if (!current) {
            cerr << "No student found with ID " << id << endl;
            return;
        }

        prev->next = current->next;
        delete current;
        cout << "Student with ID " << id << " deleted successfully!" << endl;
    }
};

// Function to save a student to file
void saveStudentToFile(Student student) {
    ofstream file(FILE_NAME, ios::app);
    if (file.is_open()) {
        file << student.getId() << " " << student.getFirstName() << " " << student.getLastName() << " " << student.getMarks() << endl;
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
            string first_name, last_name;
            float marks;
            if (ss >> id >> first_name >> last_name >> marks) {
                Student student(id, first_name, last_name, marks);
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

// Function to display the help menu

// Function to process user commands
void processCommands() {
    LinkedList studentList;
    loadStudentsFromFile(studentList);

    cout << "Need help? Type 'help' then press Enter key." << endl;

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

            cout << "Enter students data in format : <student_id> <first_name> <last_name> <marks>" << endl;

            // Get students data
            for (int i = 0; i < number_of_students; i++) {
                string input, id, first_name, last_name, marks;
                cout << "Enter the data for student (" << i + 1 << ")" << endl;
                getline(cin, input);
                istringstream student_ss(input);
                if (student_ss >> id >> first_name >> last_name >> marks) {
                    // Validate names
                    if (!isValidName(first_name) || !isValidName(last_name)) {
                        cerr << "Invalid name format. Names must contain only letters." << endl;
                        i--; // Ask for the current student data again
                        continue;
                    }
                    // Check if ID is taken, if so prompt to enter a different ID
                    if (studentList.isIdTaken(stoi(id))) {
                        cerr << "A student with ID " << id << " already exists. Please use a different ID." << endl;
                        i--; // Ask for the current student data again
                    } else {
                        Student student(stoi(id), first_name, last_name, stof(marks));
                        studentList.addStudent(student);
                        saveStudentToFile(student);
                    }
                } else {
                    cerr << "Invalid input format" << endl;
                    i--; // Ask for the current student data again
                }
            }

            cout << "Finished adding students" << endl;
        } else if (command == "searchstudents") {
            string name;
            cout << "Enter the name to search for: ";
            cin >> name;
            cin.ignore(); // Ignore the newline character left in the buffer
            studentList.searchStudentsByName(name);
        } else if (command == "sortstudentsbymarks") {
            studentList.sortStudentsByMarks();
        } else if (command == "updatestudent") {
            int id;
            string newFirstName, newLastName;
            float newMarks;
            cout << "Enter the ID of the student to update: ";
            cin >> id;
            cout << "Enter the new first name: ";
            cin >> newFirstName;
            cout << "Enter the new last name: ";
            cin >> newLastName;
            cout << "Enter the new marks: ";
            cin >> newMarks;
            cin.ignore(); // Ignore the newline character left in the buffer
            if (!isValidName(newFirstName) || !isValidName(newLastName)) {
                cerr << "Invalid name format. Names must contain only letters." << endl;
            } else {
                studentList.updateStudent(id, newFirstName, newLastName, newMarks);
            }
        } else if (command == "deletestudent") {
            int id;
            cout << "Enter the ID of the student to delete: ";
            cin >> id;
            cin.ignore(); // Ignore the newline character left in the buffer
            studentList.deleteStudent(id);
        }  else {
            // Invalid command entered
            if (command != "exit") {
                cout << "Invalid command. Below is the help option to provide you a list of commands." << endl;
             
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
