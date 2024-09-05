#include "Member.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Member::Member() : isAuthenticated(false) {}

void Member::loadMemberData() {
    // Example: Load data from a file or a database
    std::ifstream file("members.csv");
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string username, password;
        getline(iss, username, ',');
        getline(iss, password, ',');
        // Assuming first line as header
        if (username != "username") { 
            this->username = username;
            this->password = password;
        }
    }
    file.close();
}

bool Member::login(const std::string& username, const std::string& password) {
    // This would typically check against stored data
    if (validateCredentials(username, password)) {
        isAuthenticated = true;
        std::cout << "Login successful.\n";
        return true;
    } else {
        std::cout << "Login failed.\n";
        return false;
    }
}

void Member::viewProfile() const {
    if (!isAuthenticated) {
        std::cout << "Access denied. Please log in first.\n";
        return;
    }

    std::ifstream file("members.csv");
    if (!file.is_open()) {
        std::cout << "Failed to open profile data file.\n";
        return;
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::vector<std::string> userDetails;
        std::string detail;

        // Parse the line into details
        while (getline(ss, detail, ';')) {
            userDetails.push_back(detail);
        }

        // Check if it's the correct user
        if (userDetails.size() >= 8 && userDetails[0] == username && userDetails[1] == password) {
            std::cout << "Your Profile Information:\n";
            std::cout << "Username: " << userDetails[0] << "\n";
            std::cout << "Full Name: " << userDetails[2] << "\n";
            std::cout << "Phone Number: " << userDetails[3] << "\n";
            std::cout << "Email: " << userDetails[4] << "\n";
            std::cout << "ID Type: " << userDetails[5] << "\n";
            std::cout << "ID Number: " << userDetails[6] << "\n";
            std::cout << "Credit Points: " << userDetails[7] << "\n";
            break;
        }
    }

    file.close();
}


void Member::manageBookings() {
    // Implementation to manage existing bookings
}

void Member::bookCarpool() {
    // Implementation to book a new carpool
}

void Member::listCarpool() {
    // Implementation to list a new carpool as a driver
}

void Member::manageRequests() {
    // Implementation to view and manage passenger requests for your carpools
}

void Member::handleCancellation() {
    // Implementation for handling cancellations of bookings or listings
}

void Member::Rating() {
    // Implementation to rate a passenger or driver
}


void Member::purchaseCredits() {
    if (!isAuthenticated) {
        std::cout << "Access denied. Please log in first.\n";
        return;
    }

    std::string inputPassword;
    std::cout << "Please enter your password for verification: ";
    std::cin >> inputPassword;

    if (inputPassword != password) {
        std::cout << "Password verification failed. Purchase aborted.\n";
        return;
    }

    int purchaseAmount;
    std::cout << "Enter the amount of credits to purchase ($1 = 1 credit): ";
    std::cin >> purchaseAmount;
    if (purchaseAmount <= 0) {
        std::cout << "Invalid amount. Purchase aborted.\n";
        return;
    }

    // Read and update the file
    std::ifstream file("members.csv");
    std::vector<std::string> lines;
    std::string line;
    bool updated = false;

    if (!file.is_open()) {
        std::cout << "Failed to open profile data file.\n";
        return;
    }

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::vector<std::string> userDetails;
        std::string detail;
        
        while (getline(ss, detail, ';')) {
            userDetails.push_back(detail);
        }

        if (userDetails.size() >= 8 && userDetails[0] == username && userDetails[1] == password) {
            int currentCredits = std::stoi(userDetails[7]);
            currentCredits += purchaseAmount;
            userDetails[7] = std::to_string(currentCredits);
            std::stringstream updatedLine;
            for (size_t i = 0; i < userDetails.size(); ++i) {
                updatedLine << userDetails[i];
                if (i < userDetails.size() - 1) updatedLine << ";";
            }
            line = updatedLine.str();
            updated = true;
        }
        lines.push_back(line);
    }
    file.close();

    // Rewrite the file with updated credits
    std::ofstream outFile("members.csv");
    if (!outFile.is_open()) {
        std::cout << "Failed to open profile data file for writing.\n";
        return;
    }

    for (const auto& line : lines) {
        outFile << line << "\n";
    }
    outFile.close();

    if (updated) {
        std::cout << "Purchase successful! You have added " << purchaseAmount << " credits to your account.\n";
    } else {
        std::cout << "Failed to update credits.\n";
    }
}


bool Member::validateCredentials(const std::string& username, const std::string& password) const {
    return this->username == username && this->password == password; // Simplified check
}
