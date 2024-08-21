#include "Guest.h"
#include <iostream>

// Constructor definition
Guest::Guest() : creditPoints(0) {}

// Method definitions
void Guest::signup() {
    std::cout << "Enter username: ";
    std::cin >> username;

    do {
        std::cout << "Enter password (at least 8 characters): ";
        std::cin >> password;
        if (!isValidPassword(password)) {
            std::cout << "Invalid password. Please try again.\n";
        }
    } while (!isValidPassword(password));

    std::cout << "Enter full name: ";
    std::cin.ignore(); 
    std::getline(std::cin, fullName);

    std::cout << "Enter phone number: ";
    std::cin >> phoneNumber;

    std::cout << "Enter email: ";
    std::cin >> email;

    std::cout << "Enter ID type (Citizen ID/Passport): ";
    std::cin >> idType;

    std::cout << "Enter " << idType << " number: ";
    std::cin >> idNumber;

    std::string confirmPassword;
    std::cout << "Confirm registration with your password: ";
    std::cin >> confirmPassword;

    if (confirmPassword == password) {
        creditPoints = 10; 
        std::cout << "Registration successful! You have been credited with 10 points.\n";
    } else {
        std::cout << "Password confirmation failed. Registration aborted.\n";
    }
}

void Guest::viewCarpoolListings() {
    std::cout << "Available carpool listings (Passenger rating: 1-3):\n";
    std::cout << "Carpool 1: From A to B - Rating: 3\n";
    std::cout << "Carpool 2: From C to D - Rating: 2\n";
    std::cout << "Carpool 3: From E to F - Rating: 1\n";
}

bool Guest::isValidPassword(const std::string& password) {
    return password.length() >= 8; 
}
