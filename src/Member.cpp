#include "Member.h"
#include "Carpool.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <ctype.h>
#include <cstring>
#include <algorithm>

Member::Member() : isMemberAuthenticated(false) {}

void Member::loadMemberData() {
    std::ifstream file("members.csv");
    std::string line;
    getline(file, line);  // Skip the header
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string username, password;
        getline(iss, username, ',');
        getline(iss, password, ',');
        memberCredentials[username] = {username, password};
    }
    file.close();
}

bool Member::validateCredentials(const std::string& username, const std::string& password) const {
    auto it = memberCredentials.find(username);
    return it != memberCredentials.end() && it->second.second == password;
}

bool Member::login(const std::string& inputUsername, const std::string& inputPassword) {
    if (validateCredentials(inputUsername, inputPassword)) {
        isMemberAuthenticated = true;
        username = inputUsername;
        password = inputPassword;
        std::cout << "Login successful.\n";
        return true;
    } else {
        std::cout << "Login failed.\n";
        return false;
    }
}

void Member::viewProfile() const {
    if (!isMemberAuthenticated) {
        std::cout << "Access denied. Please log in first.\n";
        return;
    }

    std::ifstream file("members.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open profile data file.\n";
        return;
    }

    std::string line;
    bool found = false;
    // Skip the header line
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::vector<std::string> userDetails;
        std::string detail;

        while (std::getline(ss, detail, ',')) {
            userDetails.push_back(detail);
        }

        if (userDetails.size() >= 7 && userDetails[0] == username) {
            found = true;
            std::cout << "\n=============== Your Profile Information ===============\n";
            std::cout << std::left << std::setw(20) << "Username:" << userDetails[0] << "\n";
            std::cout << std::left << std::setw(20) << "Full Name:" << userDetails[2] << "\n";
            std::cout << std::left << std::setw(20) << "Phone Number:" << userDetails[3] << "\n";
            std::cout << std::left << std::setw(20) << "Email:" << userDetails[4] << "\n";
            std::cout << std::left << std::setw(20) << "ID Type:" << userDetails[5] << "\n";
            std::cout << std::left << std::setw(20) << "ID Number:" << userDetails[6] << "\n";
            std::cout << std::left << std::setw(20) << "Credit Points:" << userDetails[7] << "\n";
            std::cout << "========================================================\n";
            break;
        }
    }

    file.close();

    if (!found) {
        std::cerr << "Error: User profile not found in the database.\n";
    }
}



void Member::bookCarpool() {
    int choice;
    std::cout << "Choose an option:\n";
    std::cout << "1. Search and book active carpools\n";
    std::cout << "2. View your active bookings\n";
    std::cin >> choice;

    if (choice == 1) {
        searchActiveCarpool();
    } else if (choice == 2) {
        manageBookings();
    } else {
        std::cout << "Invalid choice. Please try again.\n";
    }
}


void Member::searchActiveCarpool() {
    std::ifstream file("carpool.csv");
    std::string line;
    std::vector<std::string> carpools;

    // Read and display active carpools
    while (std::getline(file, line)) {
        carpools.push_back(line);
        std::cout << carpools.size() << ". " << line << std::endl;
    }
    //Pull request start
    //Clear the line and carpool vector for use in the switch-case while-loop below
    line.clear();
    carpools.clear();

    //Print instruction
    std::cout << "-------------------------\n"
              << "To book a carpool; type 'book', following by the corresponding number.\n"
              << "To filter available carpool by departure location and destination location; type:\n"
              << " 'destination' or 'departure', following by the city name.\n" << std::endl
              << "For instance, to book carpool number 8, type 'book 8'.\n"
              << "To filter departure from Hanoi, type 'departure Hanoi'.\n"
              << "To filter destination to Danang, type 'destination Danang'.\n" << std::endl 
              << "Type 'cancel' to cancel the booking process.\n"
              << "To view this instruction again, type '?' or 'help'." << std::endl
              << "-------------------------" << std::endl;
    
    while (true) {
        // Let user choose an option from: filtering, display instruction or cancel
        std::string choice, parameter;
        std::cout << "Enter the input (caution: the input is case-sensitive): ";
        std::cin >> choice;

        if (choice != "book" && choice != "destination" && choice != "departure" && choice != "help" && choice != "?" && choice != "cancel") {
            std::cout << "Invalid choice. Please try again.\n";
            continue;
        }

        if (choice != "help" && choice != "?" && choice != "cancel") {
            std::cin >> parameter;
        }

        if (choice == "destination" || choice == "departure") {
            if (parameter.empty() || std::any_of(parameter.begin(), parameter.end(), ::isdigit)) {
                std::cout << "Invalid parameter. Please enter a valid city name.\n";
                continue;
            }
        }

        if (choice == "book") {
            if (parameter.empty() || !std::all_of(parameter.begin(), parameter.end(), ::isdigit)) {
                std::cout << "Invalid parameter. Please enter a valid number.\n";
                continue;
            }
        }

        /*
        Pseudo code of the switch-case while-loop below:
        1. If the case is filter destination/departure location, do the following:
        - Read one line of the carpool data file, until the eol is met; while the carpool file still contain data
        - Save the first and second value of the aforementioned line to two string variable, namely desData and departData
        - Compare accordingly if the user parameter is == to desData or departData
        - If true, print out the desData and departData manually, then print out the remaining data from the line using vector. Then continue loop
        - If false, print out the error. Then continue loop.
        
        2. If the case is '?' or 'help':
        - Print out the instruction again, then continue loop.
        
        3. If the case is book:
        - ...
        */
        if (choice == "destination" || choice == "departure") {
            file.clear();
            file.seekg(0, std::ios::beg);
            std::getline(file, line); // Skip header
            bool found = false;
            
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string departure, destination;
                
                std::getline(iss, departure, ',');
                std::getline(iss, destination, ',');

                if ((choice == "destination" && parameter == destination) || 
                    (choice == "departure" && parameter == departure)) {
                    std::cout << departure << ", " << destination << ", ";
                    std::string remainingData;
                    std::getline(iss, remainingData);
                    std::cout << remainingData << std::endl;
                    found = true;
                }
            }
            
            if (!found) {
                std::cout << "There are no available carpools with the " << choice << " " 
                          << (choice == "destination" ? "to " : "from ") << parameter << ".\n"
                          << "Please try again.\n";
            }
        }
        else if (choice == "help" || choice == "?") {
            std::cout << "-------------------------\n"
                      << "To book a carpool; type 'book', following by the corresponding number.\n"
                      << "To filter available carpool by departure location and destination location; type:\n"
                      << " 'destination' or 'departure', following by the city name.\n" << std::endl
                      << "For instance, to book carpool number 8, type 'book 8'.\n"
                      << "To filter departure from Hanoi, type 'departure Hanoi'.\n"
                      << "To filter destination to Danang, type 'destination Danang'.\n" << std::endl 
                      << "Type 'cancel' to cancel the booking process.\n"
                      << "To view this instruction again, type '?' or 'help'." << std::endl
                      << "-------------------------" << std::endl;
        }
        else if (choice == "book") {
            int bookingNumber = std::stoi(parameter);
            if (bookingNumber > 0 && bookingNumber <= static_cast<int>(carpools.size())) {
                // Book the chosen carpool (implementation details to be added)
                std::cout << "You've booked: " << carpools[bookingNumber - 1] << std::endl;
                break;
            } else {
                std::cout << "Booking failed. Invalid carpool number." << std::endl;
            }
        }
        else if (choice == "cancel") {
            std::cout << "Booking canceled." << std::endl;
            break;
        }
    }
    file.close();
}

void Member::manageBookings() {
    // Implementation to be added
}

void Member::listCarpool() {
    // Implementation to list a new carpool as a driver
}

void Member::manageRequests() {
    // Implementation to view and manage passenger requests for your carpools
}

void Member::handleCancellation() { //(Dat)
    // Implementation for handling cancellations of bookings or listings
}

void Member::rating() { //(Quang)
    // Implementation to rate a passenger or driver
}

void Member::purchaseCredits() {
    if (!isMemberAuthenticated) {
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
        
        while (getline(ss, detail, ',')) {
            userDetails.push_back(detail);
        }

        if (userDetails.size() >= 7 && userDetails[0] == username) {
            int currentCredits = std::stoi(userDetails[6]);
            currentCredits += purchaseAmount;
            userDetails[6] = std::to_string(currentCredits);
            std::stringstream updatedLine;
            for (size_t i = 0; i < userDetails.size(); ++i) {
                updatedLine << userDetails[i];
                if (i < userDetails.size() - 1) updatedLine << ",";
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
