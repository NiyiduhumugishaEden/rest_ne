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

// Function to check if an appointment ID is already taken
bool isAppointmentIdTaken(int id) {
    Appointment* temp = appointmentHead;
    while (temp != nullptr) {
        if (temp->appointment_id == id) {
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
    regex dateRegex("^\\d{2}/\\d{2}/\\d{4}$");
    if (!regex_match(date, dateRegex)) {
        return false;
    }

    int day, month, year;
    char delimiter;
    stringstream dateStream(date);
    dateStream >> day >> delimiter >> month >> delimiter >> year;

    if (year >= 2024) return false;
    if (month < 1 || month > 12) return false;

    int daysInMonth[] = { 31, (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (day < 1 || day > daysInMonth[month - 1]) return false;

    return true;
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

// Function to get a validated name input
string getValidatedName(const string& prompt) {
    string name;
    while (true) {
        name = getNonEmptyInput(prompt);
        if (isValidName(name)) {
            return name;
        } else {
            cout << "Invalid name. Names must contain only letters. Please enter again: ";
        }
    }
}

// Function to get a validated date input
string getValidatedDate(const string& prompt) {
    string date;
    while (true) {
        date = getNonEmptyInput(prompt);
        if (isValidDate(date)) {
            return date;
        } else {
            cout << "Invalid date. Please use the format DD/MM/YYYY. Please enter again: ";
        }
    }
}

// Function to get a validated gender input
string getValidatedGender(const string& prompt) {
    string gender;
    while (true) {
        gender = getNonEmptyInput(prompt);
        if (isValidGender(gender)) {
            return gender;
        } else {
            cout << "Invalid gender. Please enter 'male' or 'female'. Please enter again: ";
        }
    }
}

// Function to add a new patient
void addPatient() {
    int id;
    while (true) {
        cout << "Enter patient ID: ";
        id = getValidatedId();
        if (!isPatientIdTaken(id)) {
            break;
        }
        cout << "Patient ID already exists. Please enter a unique ID." << endl;
    }

    string name, dob, gender;
    cin.ignore(); // to ignore leftover newline character
    name = getValidatedName("Enter patient name: ");
    dob = getValidatedDate("Enter patient date of birth (DD/MM/YYYY): ");
    gender = getValidatedGender("Enter patient gender (male or female): ");

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
    int id;
    while (true) {
        cout << "Enter doctor ID: ";
        id = getValidatedId();
        if (!isDoctorIdTaken(id)) {
            break;
        }
        cout << "Doctor ID already exists. Please enter a unique ID." << endl;
    }

    string name, specialization;
    cin.ignore(); // to ignore leftover newline character
    name = getValidatedName("Enter doctor name: ");
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
    int appointment_id, patient_id, doctor_id;

    while (true) {
        cout << "Enter appointment ID: ";
        appointment_id = getValidatedId();
        if (!isAppointmentIdTaken(appointment_id)) {
            break;
        }
        cout << "Appointment ID already exists. Please enter a unique ID." << endl;
    }

    while (true) {
        cout << "Enter patient ID: ";
        patient_id = getValidatedId();
        if (isPatientIdValid(patient_id)) {
            break;
        }
        cout << "Patient ID does not exist. Please enter a valid ID." << endl;
    }

    while (true) {
        cout << "Enter doctor ID: ";
        doctor_id = getValidatedId();
        if (isDoctorIdValid(doctor_id)) {
            break;
        }
        cout << "Doctor ID does not exist. Please enter a valid ID." << endl;
    }

    string appointment_date;
    cin.ignore(); // to ignore leftover newline character
    appointment_date = getValidatedDate("Enter appointment date (DD/MM/YYYY): ");

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
