#include "Guest.h"
#include <iostream>
#include <regex>
using namespace std;

// Constructor definition
Guest::Guest() : creditPoints(0) {}

// Method definitions
void Guest::signup() {
    cout << "\n============SIGN-UP MENU============\n";
    cout << "Enter username: ";
    cin >> username;
    cin.ignore(); // Ignore any leftover newline characters in the input buffer

    do {
        cout << "Enter password (at least 8 characters): ";
        cin >> password;
        if (!isValidPassword(password)) {
            cout << "Invalid password. Please try again.\n";
        }
    } while (!isValidPassword(password));

    cout << "Enter full name (letters and spaces only): ";
    getline(cin, fullName);
    while (!isValidFullName(fullName)) {
        cout << "Invalid full name. Please enter again: ";
        getline(cin, fullName);
    }

    cout << "Enter phone number: ";
    cin >> phoneNumber;
    cin.ignore(); // Ignore any leftover newline characters in the input buffer

    cout << "Enter email (no spaces, must contain '@'): ";
    cin >> email;
    while (!isValidEmail(email)) {
        cout << "Invalid email. Please enter again: ";
        cin >> email;
    }

    cout << "Enter ID type (1 for Citizen ID, 2 for Passport): ";
    int idTypeOption;
    cin >> idTypeOption;
    while (!isValidIdType(idTypeOption)) {
        cout << "Invalid ID type. Please enter 1 for Citizen ID or 2 for Passport: ";
        cin >> idTypeOption;
    }
    idType = (idTypeOption == 1) ? "Citizen ID" : "Passport";

    cout << "Enter " << idType << " number: ";
    cin >> idNumber;
    cin.ignore(); // Ignore any leftover newline characters in the input buffer

    string confirmPassword;
    cout << "Confirm registration with your password: ";
    cin >> confirmPassword;

    if (confirmPassword == password) {
        creditPoints = 10; 
        cout << "Registration successful! You have been credited with 10 points.\n";
    } else {
        cout << "Password confirmation failed. Registration aborted.\n";
    }
}

void Guest::viewCarpoolListings() {
    cout << "Available carpool listings (Passenger rating: 1-3):\n";
    cout << "Carpool 1: From A to B - Rating: 3\n";
    cout << "Carpool 2: From C to D - Rating: 2\n";
    cout << "Carpool 3: From E to F - Rating: 1\n";
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
