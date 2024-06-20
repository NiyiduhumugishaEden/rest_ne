#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

#define FILE_NAME "patient.txt"

using namespace std;

// Student class to hold student details
class Patient {
private:
    int id;
    string name;
    string dob;
    string gender;

public:
    // Constructor to initialize patient details
    Patient(int id, string name , string dob,string gender) :
            id(id),
            name(name),
            dob(dob),
            gender(gender){};

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

    // Getter for student's full name
    string getGender() {
        return gender;
    }

    // Setter for student's first name
    void setName(string newFirstName) {
        name = newFirstName;
    }
     
};

class Doctor {
private:
    int id;
    string name;
    string specialization;
    string gender;

public:
    // Constructor to initialize patient details
    Doctor(int id, string name , string specialization) :
            id(id),
            name(name),
            specialization(specialization){}

    // Getter for doctor ID
    int getId() {
        return id;
    }

    // Getter for doctor's first name
    string getName() {
        return name;
    }

};


// class Apppointments {
// private:
//     int appointment_id;
//     int patient_id;
//     int doctor_id;
//     string appointment_date;


// public:
//     // Constructor to initialize patient details
//    Apppointments(int appointment_id, int patient_id , int doctor_id , string appointment_id) :
//             id(id),
//             name(name),
//             specialization(specialization){}

//     // Getter for doctor ID
//     int getId() {
//         return id;
//     }

//     // Getter for doctor's first name
//     string getName() {
//         return name;
//     }

// };


void startMessage(){
    cout<<" Menu: "<<endl;
    cout<<"1. Register a patient: "<<endl;
    cout<<"2. Register a doctor: "<<endl;
    cout<<"3. Register an appointment: "<<endl;
    cout<<"4. Display patients: "<<endl;
    cout<<"5. Display Doctors: "<<endl;
    cout<<"6. Display Appointments: "<<endl;
    cout<<"7. Exit: "<<endl;
}

// Node class for linked list
class Node {
public:
    Patient patient;
    Node* next;

    Node(Patient patient) : patient(patient), next(nullptr) {}
};


// // Node class for linked list
// class Node2 {
// public:
//     Doctor doctor;
//     Node* next;

//     Node(Doctor doctor):doctor(doctor)
// };


// Linked list class to manage students
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Function to add a student to the list
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

    // Function to print the list of students
    void printStudents() {
        cout << "Patients" << endl;
        cout << "---------------------" << endl;
        Node* temp = head;
        int index = 1;
        while (temp) {
            cout << "(" << index << ") : " << temp->patient.getId() << " " << temp->patient.getName() << " " << temp->patient.getDob() << temp->patient.getGender() <<endl;
            temp = temp->next;
            index++;
        }
        cout << "---------------------" << endl;
    }

    // Function to find a student by ID
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
}



int main (){
    return 0;
}