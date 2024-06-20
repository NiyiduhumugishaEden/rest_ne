#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

#define FILE_NAME "patient.txt"

using namespace std;

class Patient {
private:
    int id;
    string name;
    string dob;
    string gender;

public:
    Patient(int id, string name, string dob, string gender) :
            id(id), name(name), dob(dob), gender(gender) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getDob() const { return dob; }
    string getGender() const { return gender; } // Fixed typo here

    void setName(string newName) { name = newName; }
};

class Doctor {
private:
    int id;
    string name;
    string specialization;
    string gender;

public:
    Doctor(int id, string name, string specialization) :
            id(id), name(name), specialization(specialization) {}

    int getId() const { return id; }
    string getName() const { return name; }
};

void startMessage() {
    cout << "Menu:" << endl;
    cout << "1. Register a patient:" << endl;
    cout << "2. Register a doctor:" << endl;
    cout << "3. Register an appointment:" << endl;
    cout << "4. Display patients:" << endl;
    cout << "5. Display Doctors:" << endl;
    cout << "6. Display Appointments:" << endl;
    cout << "7. Exit:" << endl;
}

class Node {
public:
    Patient patient;
    Node* next;

    Node(Patient patient) : patient(patient), next(nullptr) {}
};

class Node2 {
public:
    Doctor doctor;
    Node2* next;

    Node2(Doctor doctor) : doctor(doctor), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void addStudent(Patient patient) {
        Node* newNode = new Node(patient);
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

    void printStudents() {
        cout << "Patients" << endl;
        cout << "---------------------" << endl;
        Node* temp = head;
        int index = 1;
        while (temp) {
            cout << "(" << index << ") : " << temp->patient.getId() << " " << temp->patient.getName() << " " << temp->patient.getDob() << " " << temp->patient.getGender() << endl;
            temp = temp->next;
            index++;
        }
        cout << "---------------------" << endl;
    }

    bool isIdTaken(int id) {
        Node* temp = head;
        while (temp) {
            if (temp->patient.getId() == id) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
};

// Function to validate name (no numbers allowed)
bool isValidName(string name) {
    return regex_match(name, regex("^[A-Za-z]+$"));
}


void processCommands() {
    LinkedList patientList;
   

    string input;
    string command;

    do {
        cout << " ";
        getline(cin, input);

        istringstream iss(input);
        iss >> command;

        // Convert the command to lowercase for case-insensitive comparison
        for (size_t i = 0; i < command.length(); i++) {
            command[i] = tolower(command[i]);
        }

        // Process the command
        if (command == "1") {
            cout << "------------------------------------------------------------------------------------------------------------------" << endl;
            patientList.printStudents();
            cout << "------------------------------------------------------------------------------------------------------------------" << endl;
        } else if (command == "2") {
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
                    if (patientList.isIdTaken(stoi(id))) {
                        cerr << "A student with ID " << id << " already exists. Please use a different ID." << endl;
                        i--; // Ask for the current student data again
                    } else {
                        Patient patient(stoi(id), first_name, last_name, stof(marks));
                        patientList.addStudent(patient);
                       
                    }
                } else {
                    cerr << "Invalid input format" << endl;
                    i--; // Ask for the current student data again
                }
            }

            cout << "Finished adding patients" << endl;
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
        } 
        } else {
            // Invalid command entered
            if (command != "exit") {
                cout << "Invalid command. Below is the help option to provide you a list of commands." << endl;
                help();
            }
        }
    } while (command != "exit");
}


int main() {

    LinkedList patientsList; // Create a linked list for patients
    LinkedList doctorsList; // Create a linked list for doctors

    while (true) {
        int choice;
        
        startMessage();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                int id;
                string name, dob, gender;
                cout << "Enter patient ID: ";
                cin >> id;
                cout << "Enter patient name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter patient DOB: ";
                getline(cin, dob);
                cout << "Enter patient gender: ";
                getline(cin, gender);

                if (!isValidName(name)) {
                    cout << "Invalid name. Only alphabets are allowed." << endl;
                    continue;
                }

                Patient patient(id, name, dob, gender);
                patientsList.addStudent(patient); // Corrected this line
                
                cout << "Patient registered successfully." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." <<endl;
        }
    }
    return 0;
};
