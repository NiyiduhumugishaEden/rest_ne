#include <iostream>
#include <string>
#include <sstream>
#include <regex>

using namespace std;

class Patient {
public:
    int id;
    string name;
    string dob;
    string gender;
    Patient* next;

    Patient(int id, string name, string dob, string gender)
            : id(id), name(name), dob(dob), gender(gender), next(nullptr) {}
};

class Doctor {
public:
    int id;
    string name;
    string specialization;
    Doctor* next;

    Doctor(int id, string name, string specialization)
            : id(id), name(name), specialization(specialization), next(nullptr) {}
};

class Appointment {
public:
    int appointment_id;
    int patient_id;
    int doctor_id;
    string appointment_date;
    Appointment* next;

    Appointment(int appointment_id, int patient_id, int doctor_id, string appointment_date)
            : appointment_id(appointment_id), patient_id(patient_id), doctor_id(doctor_id), appointment_date(appointment_date), next(nullptr) {}
};

Patient* patientHead = nullptr;
Doctor* doctorHead = nullptr;
Appointment* appointmentHead = nullptr;

void startMessage() {
    cout << " Menu: " << endl;
    cout << "1. Register a patient: " << endl;
    cout << "2. Register a doctor: " << endl;
    cout << "3. Register an appointment: " << endl;
    cout << "4. Display patients: " << endl;
    cout << "5. Display doctors: " << endl;
    cout << "6. Display appointments: " << endl;
    cout << "7. Exit: " << endl;
}

bool isPatientIdTaken(int id) {
    Patient* temp = patientHead;
    while (temp != nullptr) {
        if (temp->id == id) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool isDoctorIdTaken(int id) {
    Doctor* temp = doctorHead;
    while (temp != nullptr) {
        if (temp->id == id) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool isPatientIdValid(int id) {
    Patient* temp = patientHead;
    while (temp != nullptr) {
        if (temp->id == id) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool isDoctorIdValid(int id) {
    Doctor* temp = doctorHead;
    while (temp != nullptr) {
        if (temp->id == id) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool isValidName(const string& name) {
    return regex_match(name, regex("^[A-Za-z]+$"));
}

int getValidatedId() {
    string input;
    while (true) {
        cin >> input;
        if (regex_match(input, regex("^[0-9]+$"))) {
            return stoi(input);
        } else {
            cout << "Invalid ID. IDs must be numbers only. Please enter again: ";
        }
    }
}

void addPatient() {
    cout << "Enter patient ID: ";
    int id = getValidatedId();
    if (isPatientIdTaken(id)) {
        cout << "Patient ID already exists. Please enter a unique ID." << endl;
        return;
    }

    string name, dob, gender;
    cout << "Enter patient name: ";
    cin.ignore();
    getline(cin, name);
    if (!isValidName(name)) {
        cout << "Invalid name. Names must contain only letters." << endl;
        return;
    }
    cout << "Enter patient date of birth: ";
    getline(cin, dob);
    cout << "Enter patient gender: ";
    getline(cin, gender);

    Patient* newPatient = new Patient(id, name, dob, gender);
    if (patientHead == nullptr) {
        patientHead = newPatient;
    } else {
        Patient* temp = patientHead;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newPatient;
    }

    cout << "Patient added successfully." << endl;
}

void addDoctor() {
    cout << "Enter doctor ID: ";
    int id = getValidatedId();
    if (isDoctorIdTaken(id)) {
        cout << "Doctor ID already exists. Please enter a unique ID." << endl;
        return;
    }

    string name, specialization;
    cout << "Enter doctor name: ";
    cin.ignore();
    getline(cin, name);
    if (!isValidName(name)) {
        cout << "Invalid name. Names must contain only letters." << endl;
        return;
    }
    cout << "Enter doctor specialization: ";
    getline(cin, specialization);

    Doctor* newDoctor = new Doctor(id, name, specialization);
    if (doctorHead == nullptr) {
        doctorHead = newDoctor;
    } else {
        Doctor* temp = doctorHead;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newDoctor;
    }

    cout << "Doctor added successfully." << endl;
}

void addAppointment() {
    cout << "Enter appointment ID: ";
    int appointment_id = getValidatedId();

    cout << "Enter patient ID: ";
    int patient_id = getValidatedId();
    if (!isPatientIdValid(patient_id)) {
        cout << "Patient ID does not exist. Please enter a valid ID." << endl;
        return;
    }

    cout << "Enter doctor ID: ";
    int doctor_id = getValidatedId();
    if (!isDoctorIdValid(doctor_id)) {
        cout << "Doctor ID does not exist. Please enter a valid ID." << endl;
        return;
    }

    string appointment_date;
    cout << "Enter appointment date: ";
    cin.ignore();
    getline(cin, appointment_date);

    Appointment* newAppointment = new Appointment(appointment_id, patient_id, doctor_id, appointment_date);
    if (appointmentHead == nullptr) {
        appointmentHead = newAppointment;
    } else {
        Appointment* temp = appointmentHead;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newAppointment;
    }

    cout << "Appointment added successfully." << endl;
}

void displayPatients() {
    Patient* temp = patientHead;
    cout << "Patients:" << endl;
    while (temp != nullptr) {
        cout << "ID: " << temp->id << ", Name: " << temp->name << ", DOB: " << temp->dob << ", Gender: " << temp->gender << endl;
        temp = temp->next;
    }
}

void displayDoctors() {
    Doctor* temp = doctorHead;
    cout << "Doctors:" << endl;
    while (temp != nullptr) {
        cout << "ID: " << temp->id << ", Name: " << temp->name << ", Specialization: " << temp->specialization << endl;
        temp = temp->next;
    }
}

void displayAppointments() {
    Appointment* temp = appointmentHead;
    cout << "Appointments:" << endl;
    while (temp != nullptr) {
        cout << "Appointment ID: " << temp->appointment_id << ", Patient ID: " << temp->patient_id << ", Doctor ID: " << temp->doctor_id << ", Date: " << temp->appointment_date << endl;
        temp = temp->next;
    }
}

void processCommands() {
    int choice;
    do {
        startMessage();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                addDoctor();
                break;
            case 3:
                addAppointment();
                break;
            case 4:
                displayPatients();
                break;
            case 5:
                displayDoctors();
                break;
            case 6:
                displayAppointments();
                break;
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 7);
}

int main() {
    processCommands();
    return 0;
}
