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

// Function to display the menu
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

// Function to check if a patient ID is already taken
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

// Function to check if a doctor ID is already taken
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

// Function to check if a patient ID is valid (exists in the list)
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

// Function to check if a doctor ID is valid (exists in the list)
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

// Function to validate if the name contains only letters
bool isValidName(const string& name) {
    return regex_match(name, regex("^[A-Za-z]+$"));
}

// Function to validate date in the format DD/MM/YYYY
bool isValidDate(const string& date) {
    return regex_match(date, regex("^\\d{2}/\\d{2}/\\d{4}$"));
}

// Function to validate gender (male or female)
bool isValidGender(const string& gender) {
    return (gender == "male" || gender == "female");
}

// Function to get a validated ID (numbers only)
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

// Function to get a validated choice (1-7)
int getValidatedChoice() {
    string input;
    int choice;
    while (true) {
        cin >> input;
        if (regex_match(input, regex("^[1-7]$"))) {
            choice = stoi(input);
            return choice;
        } else {
            cout << "Invalid choice. Please enter a number between 1 and 7: ";
        }
    }
}

// Function to get a non-empty input
string getNonEmptyInput(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (!input.empty()) {
            return input;
        } else {
            cout << "Input cannot be empty. Please enter again: ";
        }
    }
}

// Function to add a new patient
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
    name = getNonEmptyInput("");
    if (!isValidName(name)) {
        cout << "Invalid name. Names must contain only letters." << endl;
        return;
    }
    dob = getNonEmptyInput("Enter patient date of birth (DD/MM/YYYY): ");
    if (!isValidDate(dob)) {
        cout << "Invalid date of birth. Please use the format DD/MM/YYYY." << endl;
        return;
    }
    gender = getNonEmptyInput("Enter patient gender (male or female): ");
    if (!isValidGender(gender)) {
        cout << "Invalid gender. Please enter 'male' or 'female'." << endl;
        return;
    }

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

// Function to add a new doctor
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
    name = getNonEmptyInput("");
    if (!isValidName(name)) {
        cout << "Invalid name. Names must contain only letters." << endl;
        return;
    }
    specialization = getNonEmptyInput("Enter doctor specialization: ");

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

// Function to add a new appointment
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
    cout << "Enter appointment date (DD/MM/YYYY): ";
    cin.ignore();
    appointment_date = getNonEmptyInput("");
    if (!isValidDate(appointment_date)) {
        cout << "Invalid appointment date. Please use the format DD/MM/YYYY." << endl;
        return;
    }

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

// Function to display all patients
void displayPatients() {
    Patient* temp = patientHead;
    cout << "Patients:" << endl;
    while (temp != nullptr) {
        cout << "ID: " << temp->id << ", Name: " << temp->name << ", DOB: " << temp->dob << ", Gender: " << temp->gender << endl;
        temp = temp->next;
    }
}

// Function to display all doctors
void displayDoctors() {
    Doctor* temp = doctorHead;
    cout << "Doctors:" << endl;
    while (temp != nullptr) {
        cout << "ID: " << temp->id << ", Name: " << temp->name << ", Specialization: " << temp->specialization << endl;
        temp = temp->next;
    }
}

// Function to display all appointments
void displayAppointments() {
    Appointment* temp = appointmentHead;
    cout << "Appointments:" << endl;
    while (temp != nullptr) {
        cout << "Appointment ID: " << temp->appointment_id << ", Patient ID: " << temp->patient_id << ", Doctor ID: " << temp->doctor_id << ", Date: " << temp->appointment_date << endl;
        temp = temp->next;
    }
}

// Function to process user commands
void processCommands() {
    int choice;
    do {
        startMessage();
        cout << "Enter your choice: ";
        choice = getValidatedChoice();
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
