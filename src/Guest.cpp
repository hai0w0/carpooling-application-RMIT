#include "Guest.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

// Constructor initializing credits to 10 and rating to -1 (indicative of a new guest)
Guest::Guest() : creditPoints(10), rating(-1) {}


// Checks if the username is already taken by reading the members.csv file
bool Guest::isUsernameTaken(const string& username) {
    ifstream file("members.csv");
    string line;
    getline(file, line);  // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string existingUsername;
        getline(ss, existingUsername, ',');
        if (existingUsername == username) {
            return true; // Username is taken
        }
    }
    return false; // Username is not taken
}

// Checks if the phone number is already registered
bool Guest::isPhoneNumberTaken(const string& phoneNumber) {
    ifstream file("members.csv");
    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        for (int i = 0; i < 3; i++) getline(ss, field, ',');
        if (field == phoneNumber) {
            return true; // Phone number is taken
        }
    }
    return false; // Phone number is not taken
}

// Checks if the email address is already registered
bool Guest::isEmailTaken(const string& email) {
    ifstream file("members.csv");
    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        for (int i = 0; i < 4; i++) getline(ss, field, ',');
        if (field == email) {
            return true;
        }
    }
    return false;
}

// Checks if the ID number is already registered
bool Guest::isIdNumberTaken(const string& idNumber) {
    ifstream file("members.csv");
    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        for (int i = 0; i < 6; i++) getline(ss, field, ',');
        if (field == idNumber) {
            return true; // ID number is taken
        }
    }
    return false; // ID number is not taken
}

// Handles the guest signup function
void Guest::signup() {
    string input;
    do {
        cout << "Enter username: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, input);
        if (input.empty()) {
            cout << "Username cannot be left blank. Please enter again.\n";
        } else if (isUsernameTaken(input)) {
            cout << "Username is already taken. Please choose a different username.\n";
        } else {
            username = input;
        }
    } while (username.empty());

    do {
        cout << "Enter password (at least 8 characters): ";
        getline(cin, password);
    } while (!isValidPassword(password));

    do {
        cout << "Enter full name: ";
        getline(cin, fullName);
    } while (fullName.empty());

    do {
        cout << "Enter phone number: ";
        getline(cin, phoneNumber);
        if (isPhoneNumberTaken(phoneNumber)) {
            cout << "This phone number is already registered. Please use a different number.\n";
            phoneNumber.clear();
        }
    } while (phoneNumber.empty());

    do {
        cout << "Enter email (must contain '@'): ";
        getline(cin, email);
        if (!isValidEmail(email)) {
            cout << "Invalid email format. Please enter a valid email address.\n";
        } else if (isEmailTaken(email)) {
            cout << "This email is already registered. Please use a different email.\n";
            email.clear();
        }
    } while (!isValidEmail(email) || email.empty());

    int idTypeOption;
    do {
        cout << "Enter ID type (1 for Citizen ID, 2 for Passport): ";
        if (cin >> idTypeOption) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (isValidIdType(idTypeOption)) {
                break;
            }
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Invalid input. Please enter 1 or 2.\n";
    } while (true);

    idType = (idTypeOption == 1) ? "Citizen ID" : "Passport";

    do {
        cout << "Enter " << idType << " number: ";
        getline(cin, idNumber);
        if (isIdNumberTaken(idNumber)) {
            cout << "This ID number is already registered. Please check your input.\n";
            idNumber.clear();
        }
    } while (idNumber.empty());

    cout << "Registration successful! You have been credited with 10 points.\n";
    cout << "Please escape Guest mode and login into your account in Member mode to fully experience the app!!!\n";
    saveToFile();
}

// Displays available carpool listings with a rating filter
void Guest::viewCarpoolListings() {
    ifstream file("carpool.csv");
    string line;
    cout << "Available carpool listings (Ratings 1-3 only):\n";
    cout << "If you want to book or see more, please sign up!\n";
    if (file.is_open()) {
        getline(file, line); // Skip header
        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> details;
            string detail;
            while (getline(ss, detail, ',')) {
                details.push_back(detail);
            }
            int rating = stoi(details[9]);
            if (rating >= 1 && rating <= 3) {
                cout << "Carpool from " << details[0] << " to " << details[1] << " at " << details[2]
                     << " on " << details[3] << ", " << details[7] << " seats available, " 
                     << details[8] << " credit points per passenger.\n";
            }
        }
        file.close();
    } else {
        cout << "Unable to open carpool data file.\n";
    }
}

// Validates if the password meets the minimum length requirement
bool Guest::isValidPassword(const string& password) {
    return password.length() >= 8;
}

// Validates if the email contains an '@' symbol, a basic check for email format
bool Guest::isValidEmail(const string& email) {
    return email.find('@') != string::npos;
}

// Validates the ID type based on predefined options
bool Guest::isValidIdType(int idTypeOption) {
    return idTypeOption == 1 || idTypeOption == 2;
}

// Saves guest details to the members.csv file
void Guest::saveToFile() const {
    ofstream file("members.csv", ios::app);
    if (file.is_open()) {
        file << username << ","
             << password << ","
             << fullName << ","
             << phoneNumber << ","
             << email << ","
             << idType << ","
             << idNumber << ","
             << creditPoints << ","
             << rating << "\n";
        file.close();
        cout << "Your information has been saved.\n";
    } else {
        cout << "Error: Could not open file to save data.\n";
    }
}