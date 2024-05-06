#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Structure to hold student information
struct Student
{
    int rollNumber;
    string name;
    string division;
    string address;
};

// Function to add student information to the file
void addStudent()
{
    Student student;

    cout << "\nEnter Roll Number: ";
    cin >> student.rollNumber;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, student.name);
    cout << "Enter Division: ";
    getline(cin, student.division);
    cout << "Enter Address: ";
    getline(cin, student.address);

    ofstream outFile("student_info.txt", ios::app);
    if (!outFile)
    {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    outFile << student.rollNumber << " " << student.name << " " << student.division << " " << student.address << endl;

    cout << "Student information added successfully!" << endl;
    outFile.close();
}

// Function to delete student information from the file
void deleteStudent(int rollNumber)
{
    ifstream inFile("student_info.txt");
    if (!inFile)
    {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile)
    {
        cerr << "Error opening temporary file!" << endl;
        inFile.close();
        return;
    }

    Student student;
    bool found = false;
    while (inFile >> student.rollNumber >> student.name >> student.division >> student.address)
    {
        if (student.rollNumber != rollNumber)
            tempFile << student.rollNumber << " " << student.name << " " << student.division << " " << student.address << endl;
        else
            found = true;
    }

    inFile.close();
    tempFile.close();

    if (remove("student_info.txt") != 0)
    {
        cerr << "Error deleting original file!" << endl;
        return;
    }

    if (rename("temp.txt", "student_info.txt") != 0)
    {
        cerr << "Error renaming temporary file!" << endl;
        return;
    }

    if (found)
        cout << "Student information deleted successfully!" << endl;
    else
        cout << "Student with Roll Number " << rollNumber << " not found!" << endl;
}

// Function to display information of a particular student
void displayStudent(int rollNumber)
{
    ifstream inFile("student_info.txt");
    if (!inFile)
    {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    Student student;
    bool found = false;
    while (inFile >> student.rollNumber >> student.name >> student.division >> student.address)
    {
        if (student.rollNumber == rollNumber)
        {
            found = true;
            cout << "\nRoll Number: " << student.rollNumber << endl;
            cout << "Name: " << student.name << endl;
            cout << "Division: " << student.division << endl;
            cout << "Address: " << student.address << endl;
            break;
        }
    }

    if (!found)
        cout << "Student with Roll Number " << rollNumber << " not found!" << endl;

    inFile.close();
}

// Function to display the menu
void displayMenu()
{
    cout << "\n1. Add Student\n";
    cout << "2. Delete Student\n";
    cout << "3. Display Student Information\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    int choice;
    int rollNumber;

    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            cout << "Enter Roll Number to delete: ";
            cin >> rollNumber;
            deleteStudent(rollNumber);
            break;
        case 3:
            cout << "Enter Roll Number to display: ";
            cin >> rollNumber;
            displayStudent(rollNumber);
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
