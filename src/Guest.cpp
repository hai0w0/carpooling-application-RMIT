#include "Guest.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
using namespace std;

// Constructor definition
Guest::Guest() : creditPoints(0) {}

// Method definitions
void Guest::signup() {
    cout << "\n============SIGN-UP MENU============\n";

    do {
        cout << "Enter username: ";
        getline(cin, username);
        if (username.empty()) {
            cout << "Username cannot be left blank. Please enter again.\n";
        }
    } while (username.empty());

    do {
        cout << "Enter password (at least 8 characters): ";
        cin >> password;
        cin.ignore(); // Ignore leftover newline
        if (password.empty()) {
            cout << "Password cannot be left blank. Please enter again.\n";
        } else if (!isValidPassword(password)) {
            cout << "Invalid password. Please try again.\n";
        }
    } while (password.empty() || !isValidPassword(password));

    do {
        cout << "Enter full name (letters and spaces only): ";
        getline(cin, fullName);
        if (fullName.empty()) {
            cout << "Full name cannot be left blank. Please enter again.\n";
        } else if (!isValidFullName(fullName)) {
            cout << "Invalid full name. Please enter again.\n";
        }
    } while (fullName.empty() || !isValidFullName(fullName));

    do {
        cout << "Enter phone number: ";
        getline(cin, phoneNumber);
        if (phoneNumber.empty()) {
            cout << "Phone number cannot be left blank. Please enter again.\n";
        }
    } while (phoneNumber.empty());

    do {
        cout << "Enter email (no spaces, must contain '@'): ";
        cin >> email;
        cin.ignore(); // Ignore leftover newline
        if (email.empty()) {
            cout << "Email cannot be left blank. Please enter again.\n";
        } else if (!isValidEmail(email)) {
            cout << "Invalid email. Please enter again.\n";
        }
    } while (email.empty() || !isValidEmail(email));

    int idTypeOption;
    do {
        cout << "Enter ID type (1 for Citizen ID, 2 for Passport): ";
        cin >> idTypeOption;
        cin.ignore(); // Ignore leftover newline
        if (!isValidIdType(idTypeOption)) {
            cout << "Invalid ID type. Please enter 1 for Citizen ID or 2 for Passport: ";
        }
    } while (!isValidIdType(idTypeOption));
    idType = (idTypeOption == 1) ? "Citizen ID" : "Passport";

    do {
        cout << "Enter " << idType << " number: ";
        getline(cin, idNumber);
        if (idNumber.empty()) {
            cout << idType << " number cannot be left blank. Please enter again.\n";
        }
    } while (idNumber.empty());

    string confirmPassword;
    do {
        cout << "Confirm registration with your password: ";
        cin >> confirmPassword;
        cin.ignore(); // Ignore leftover newline
        if (confirmPassword.empty()) {
            cout << "Password confirmation cannot be left blank. Please enter again.\n";
        } else if (confirmPassword != password) {
            cout << "Passwords do not match. Please enter again.\n";
        }
    } while (confirmPassword.empty() || confirmPassword != password);

    creditPoints = 10;
    rating = -1;
    cout << "Registration successful! You have been credited with 10 points.\n";

    // Save data to CSV file
    ofstream file("members.csv", ios::app); // Open the file in append mode
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

void Guest::viewCarpoolListings() {
    ifstream file("carpool.csv");
    string line;
    cout << "\n============Carpool Listings============\n";
    cout << "Available carpool listings (Passenger rating: 1-3):\n";
    cout << "If want to book or see more, please sign up!\n";
    if (file.is_open()) {
        getline(file, line); // Skip header
        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> details;
            string detail;
            while (getline(ss, detail, ',')) {
                details.push_back(detail);
            }
            if (stoi(details[9]) <= 3) { // Check rating at the 10th column
                cout << "Carpool from " << details[0] << " to " << details[1] << " at " << details[2]
                     << " on " << details[3] << ", " << details[7] << " seats available, " 
                     << details[8] << " credit points per passenger, Rating: " << details[9] << "\n";
            }
        }
        file.close();
    } else {
        cout << "Unable to open carpool data file.\n";
    }
}

bool Guest::isValidPassword(const std::string& password) {
    return password.length() >= 8; 
}

bool Guest::isValidFullName(const std::string& name) {
    for (char c : name) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

bool Guest::isValidEmail(const std::string& email) {
    const std::regex emailRegex(R"(^[^@]+@[^@]+\.[a-zA-Z]{2,})");
    return std::regex_match(email, emailRegex);
}

bool Guest::isValidIdType(int idTypeOption) {
    return idTypeOption == 1 || idTypeOption == 2;
}
