#include <iostream>
#include <regex>

using namespace std;

// patient class to hold patient details
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
    // Getter for patient ID
    int getId() {
        return id;
    }
    // Getter for patient's first name
    string getName() {
        return name;
    }
    // Getter for patient's last name
    string getDob() {
        return dob;
    }
    // Getter for patient's full name
    string getGender() {
        return gender;
    }
    // Setter for patient's first name
    void setName(string newFirstName) {
        name = newFirstName;
    }
};
class Doctor {
private:
    int id;
    string name;
    string specialization;

    Doctor *next;

    Doctor(int id, string name, string  specialization)
    {
        id = id;
        name = name;
        specialization = specialization;
    
        next = NULL;
    }

     void addDoctor(Doctor doctor) {
        Doctor* newNode = new Doctor();
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
    // Function to print the list of patients
    void printDoctors() {
        cout << "Doctors" << endl;
        cout << "---------------------" << endl;
        Doctor* temp = head;
        int index = 1;
        while (temp) {
            cout << "(" << index << ") : " << temp->patient.getId() << " " << temp->patient.getName() << " " << temp->patient.getGender() << endl;
            temp = temp->next;
            index++;
        }
        cout << "---------------------" << endl;
    }
    // Function to find a patient by ID
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


class Appointment
{
public:
    int appointment_id;
    int patient_id;
    int doctor_id;

    string appointment_date;

    Appointment *next;

    Appointment(int id, int p_id, int d_id, string a_date)
    {
        appointment_id = id;
        patient_id = p_id;
        doctor_id = d_id;
        appointment_date = a_date;
        next = NULL;
    }
};

bool checkAppointmentId(Appointment *&head, int id)
{
    Appointment *temp = head;
    while (temp != NULL)
    {
        if (temp->appointment_id == id)
        {
            return true;
        }
        temp = temp->next;
    }
    
    
void addAppointment(Appointment *&appHead, Patient *&head, Doctor *&dhead, int id, int p_id, int d_id, string a_date)
{
    bool is_appointment_already_taken = checkAppointmentId(appHead, id);
    if (is_appointment_already_taken)
    {
        std::cout << "Appointment with the given appointment_id already existent." << endl;
        return;
    }
    if (findPatient(head, p_id) == NULL || findDoctor(dhead, d_id) == NULL)
    {
        std::cout << "One of the patient_id or doctor_id does not exist." << endl;
        return;
    }
    Appointment *newNode = new Appointment(id, p_id, d_id, a_date);
    newNode->next = NULL;
    if (appHead == NULL)
    {
        appHead = newNode;
        return;
    }
    Appointment *temp = appHead;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
};



// Node class for linked list
class Node {
public:
    Patient patient;
    Node* next;
    Node(Patient patient) : patient(patient), next(nullptr) {}
};
// Node class for linked list

class LinkedList {
public:
    struct Node {
        Patient patient;
        Node* next;
        Node(Patient patient) : patient(patient), next(nullptr) {}
    };
    Node* head;
    LinkedList() : head(nullptr) {}
    // Function to add a patient to the list
    void addpatient(Patient patient) {
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
    // Function to print the list of patients
    void printPatients() {
        cout << "patients" << endl;
        cout << "---------------------" << endl;
        Node* temp = head;
        int index = 1;
        while (temp) {
            cout << "(" << index << ") : " << temp->patient.getId() << " " << temp->patient.getName() << " " << temp->patient.getGender() << endl;
            temp = temp->next;
            index++;
        }
        cout << "---------------------" << endl;
    }
    // Function to find a patient by ID
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
      
                // Function to validate name (no numbers allowed)
bool isValidName(string name) {
      return regex_match(name, regex("^[A-Za-z]+$"));
    };
void processCommands() {
    LinkedList patientList;
    string input;
    string command;
    do {
        cout << ">";
        getline(cin, input);
        istringstream iss(input);
        iss >> command;
        // Convert the command to lowercase for case-insensitive comparison
        for (size_t i = 0; i < command.length(); i++) {
            command[i] = tolower(command[i]);
        };
        // Process the command
        if (command == "4") {
            cout << "------------------------------------------------------------------------------------------------------------------" << endl;
            patientList. printPatients();
            cout << "------------------------------------------------------------------------------------------------------------------" << endl;
        } else if (command == "1") {
            int number_of_patients;
            cout << "How many patients do you want to add?" << endl;
            cin >> number_of_patients;
            cin.ignore(); // Ignore the newline character left in the buffer
            cout << "Enter patients data in format : <patient_id> <name> <dob> <gender>" << endl;
            // Get patients data
            for (int i = 0; i < number_of_patients; i++) {
                string input, id, name, dob, gender;
                cout << "Enter the data for patient (" << i + 1 << ")" << endl;
                getline(cin, input);
                istringstream patient_ss(input);
                if (patient_ss >> id >> name >> dob>> gender) {
                    // Validate names
                    if (!isValidName(name)) {
                        cerr << "Invalid name format. Names must contain only letters." << endl;
                        i--; // Ask for the current patient data again
                        continue;
                    }
                    // Check if ID is taken, if so prompt to enter a different ID
                    if (patientList.isIdTaken(stoi(id))) {
                        cerr << "A patient with ID " << id << " already exists. Please use a different ID." << endl;
                        i--; // Ask for the current patient data again
                    } else {
                        Patient p1 = Patient(stoi(id), name,dob,gender);
                        patientList.addpatient(p1);
                    }
                } else {
                    cerr << "Invalid input format" << endl;
                    i--; // Ask for the current patient data again
                }
            }
            cout << "Finished adding patients" << endl;
        } else {
            // Invalid command entered
            if (command != "exit") {
                cout << "Invalid command. Below is the help option to provide you a list of commands." << endl;
            }
        }
    } while (command != "exit");
}
int main(){
    startMessage();
    processCommands();
    return 0;
}