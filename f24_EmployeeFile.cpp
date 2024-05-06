#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Structure to hold employee information
struct Employee {
    int id;
    string name;
    string designation;
    double salary;
};

// Function to add employee information to the file
void addEmployee() {
    Employee emp;

    cout << "\nEnter Employee ID: ";
    cin >> emp.id;
    cout << "Enter Employee Name: ";
    cin.ignore();
    getline(cin, emp.name);
    cout << "Enter Employee Designation: ";
    getline(cin, emp.designation);
    cout << "Enter Employee Salary: ";
    cin >> emp.salary;

    ofstream outFile("employee_info.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    outFile << emp.id << " " << emp.name << " " << emp.designation << " " << emp.salary << endl;

    cout << "Employee information added successfully!" << endl;
    outFile.close();
}

// Function to delete employee information from the file
void deleteEmployee(int empId) {
    ifstream inFile("employee_info.txt");
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile) {
        cerr << "Error opening temporary file!" << endl;
        inFile.close();
        return;
    }

    Employee emp;
    bool found = false;
    while (inFile >> emp.id >> emp.name >> emp.designation >> emp.salary) {
        if (emp.id != empId)
            tempFile << emp.id << " " << emp.name << " " << emp.designation << " " << emp.salary << endl;
        else
            found = true;
    }

    inFile.close();
    tempFile.close();

    if (remove("employee_info.txt") != 0) {
        cerr << "Error deleting original file!" << endl;
        return;
    }

    if (rename("temp.txt", "employee_info.txt") != 0) {
        cerr << "Error renaming temporary file!" << endl;
        return;
    }

    if (found)
        cout << "Employee information deleted successfully!" << endl;
    else
        cout << "Employee with ID " << empId << " not found!" << endl;
}

// Function to display information of a particular employee
void displayEmployee(int empId) {
    ifstream inFile("employee_info.txt");
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    Employee emp;
    bool found = false;
    while (inFile >> emp.id >> emp.name >> emp.designation >> emp.salary) {
        if (emp.id == empId) {
            found = true;
            cout << "\nEmployee ID: " << emp.id << endl;
            cout << "Name: " << emp.name << endl;
            cout << "Designation: " << emp.designation << endl;
            cout << "Salary: " << emp.salary << endl;
            break;
        }
    }

    if (!found)
        cout << "Employee with ID " << empId << " not found!" << endl;

    inFile.close();
}

// Function to display the menu
void displayMenu() {
    cout << "\n1. Add Employee\n";
    cout << "2. Delete Employee\n";
    cout << "3. Display Employee Information\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    int empId;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                cout << "Enter Employee ID to delete: ";
                cin >> empId;
                deleteEmployee(empId);
                break;
            case 3:
                cout << "Enter Employee ID to display: ";
                cin >> empId;
                displayEmployee(empId);
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
