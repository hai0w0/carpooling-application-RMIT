#include "Guest.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <limits>
using namespace std;

Guest::Guest() : creditPoints(10), rating(-1) {}

void Guest::signup() {
    cout << "\n============SIGN-UP MENU============\n";
    string input;
    do {
        cout << "Enter username: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, input);
        if (input.empty()) {
            cout << "Username cannot be left blank. Please enter again.\n";
        }else{
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
    } while (phoneNumber.empty());

    do {
        cout << "Enter email (must contain '@'): ";
        getline(cin, email);
    } while (!isValidEmail(email));

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
    } while (idNumber.empty());

    cout << "Registration successful! You have been credited with 10 points.\n";
    cout << "Please escape Guest mode and login into your account in Member mode to fully experience the app!!!\n";
    saveToFile();
}

void Guest::viewCarpoolListings() {
    ifstream file("carpool.csv");
    string line;
    cout << "\n============Carpool Listings============\n";
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
                     << details[8] << " credit points per passenger, Rating: " << rating << "\n";
            }
        }
        file.close();
    } else {
        cout << "Unable to open carpool data file.\n";
    }
}

bool Guest::isValidPassword(const string& password) {
    return password.length() >= 8;
}

bool Guest::isValidEmail(const string& email) {
    return email.find('@') != string::npos;
}

bool Guest::isValidIdType(int idTypeOption) {
    return idTypeOption == 1 || idTypeOption == 2;
}

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