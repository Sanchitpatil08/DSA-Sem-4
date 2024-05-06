/*
PRERNA WAGHMARE (23C0318)
SE COMP B
DSA LAB
PRACTICAL NO: E20

Consider a Scenario for Hospital to cater services to different kinds of patients as Serious (Top priority), 
Non-Serious (medium priority), General Checkup (Least Priority). Implement the priority queue to cater services to the patients.
*/

#include <iostream>
#include <queue>
#include <string>

using namespace std;

class HospitalPriorityQueue {
private:
    struct Patient {
        string name;
        int priority;

        // Constructor to initialize Patient object
        Patient(string n, int p) : name(n), priority(p) {}

        // Overloading the < operator to compare patients based on their priority
        bool operator<(const Patient& other) const {
            // Here, we define the priority order: 1 (Serious) < 2 (Non-Serious) < 3 (General Checkup)
            return priority > other.priority;
        }
    };

    priority_queue<Patient> patients;

public:
    void addPatient(const string& name, int priority) {
        patients.push(Patient(name, priority));
    }

    string serveNextPatient() {
        if (!patients.empty()) {
            string nextPatient = patients.top().name;
            patients.pop();
            return nextPatient;
        } else {
            return "No patients in the queue.";
        }
    }
};

int main() {
    HospitalPriorityQueue hospitalQueue;

    // Taking user input for adding patients and their health conditions
    char choice;
    do {
        string name;
        int priority;
        cout << "Enter patient's name: ";
        cin >> name;
        cout << "Enter patient's health condition (1: Serious, 2: Non-Serious, 3: General Checkup): ";
        cin >> priority;

        hospitalQueue.addPatient(name, priority);

        cout << "Do you want to add another patient? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "\nPatients served in order:\n";
    cout << "--------------------------\n";
    string nextPatient = hospitalQueue.serveNextPatient();
    while (nextPatient != "No patients in the queue.") {
        cout << nextPatient << endl;
        nextPatient = hospitalQueue.serveNextPatient();
    }

    return 0;
}
