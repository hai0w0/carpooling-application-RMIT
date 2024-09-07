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
    cout    << "-------------------------\n"
            << "To book a carpool; type 'book', following by the corresponding number.\n"
            << "T filter available carpool by departure location and destination location; type:\n"
            << " 'destination' or 'depature', following by the city name.\n" << endl
        
            << "For instance, to book carpool number 8, type 'book 8'.\n"
            << "To filter depature from Hanoi, type 'departure Hanoi'.\n"
            << "To filter destination to Danang, type 'destination Danang'.\n" << endl 

            << "Type 'cancel' to cancel the booking process.\n"
            << "To view this instruction again, type '?' or 'help'."<< endl
            << "-------------------------";
    
    while (true) {
        // Let user choose an option from: filtering, display instruction or cancel
        std::string choice, parameter;
        std::cout << "Enter the input (caution: the input is case-sensitive): ";
        std::cin >> choice >> parameter;

        //If the first value is not valid
        if (choice != "destination" || choice != "departure" || choice != 'help' || choice != '?' || choice != 'cancel') {
            cout << "Invalid choice. Booking cancelled.\n"
            continue;
        }

        //If the first value is valid, but the second value is invalid for two specific case
        //Case 1. Destination and departure is entered, but the second parameter is not a string
        if (choice == 'destination' || choice == 'departure') {
            parameterLength = strlen(parameter);
            for (int i = 0; i < parameterLength; i++) {
                if (isdigit(parameter[i])) {
                    cout << "Invalid choice. Booking cancelled.\n"
                    continue;
                } 
            }
        }

        //Case 2. Book is entered, but the second parameter is not a number
        if (choice == 'book') {
            parameterLength = strlen(parameter);
            for (int i = 0; i < parameterLength; i++) {
                if !isdigit(parameter[i]) {
                    cout << "Invalid choice. Booking cancelled.\n"
                    continue;
                } 
            }
        }

        /*
        Psuedo code of the switch-case while-loop below:
        1. If the case is filter destination/departure location, do the following:
        - Read one line of the carpool data file, until the eol is met; while the carpool file still contain data
        - Save the first and second value of the aforementioned line to two string variable, namely desData and departData
        - Compare accordingly if the user parameter is == to desData or departData
        - If true, print out the desData and departData manually, then print out the remaning data from the line using vector. Then continue loop
        - If false, print out the error. Then continue loop.
        
        2. If the case is '?' or 'help':
        - Print out the instruction again, then continue loop.
        
        3. If the case is book:
        - ...
        */
        switch ('choice') {
            case 'destination':
                //Open the carpool file
                std::getline(file, outputLine); // Skip header
                std::string line, departure, destination;
                
                while (std::getline(file, line)) {
                    std::istringstream iss(line);
                    
                    std::getline(iss, departure, ',');
                    std::getline(iss, destination, ',');

                    if (parameter == destination) {
                        cout << departure << ", " << destination << ", ";
                        while (std::getline(iss, line)) {
                            carpools.push_back(line);
                            std::cout << carpools.size() << ". " << line << std::endl;
                        }
                        continue;
                    }
                    //If there are no carpool with destination = to the given name
                    cout    << "There are no available carpool with the destination to " << parameter << ".\n"
                            << "Please try again.\n";  
                        continue;
                    
            case 'departure':
                //Open the carpool file
                std::getline(file, outputLine); // Skip header
                std::string line, departure, destination;
                
                while (std::getline(file, line)) {
                    
                    std::istringstream iss(line);
                    std::getline(iss, departure, ',');

                    if (parameter == departure) {
                        cout << departure << ", ";
                        while (std::getline(iss, line)) {
                            carpools.push_back(line);
                            std::cout << carpools.size() << ". " << line << std::endl;
                        }
                        continue;
                    }
                    //If there are no carpool with destination = to the given name
                    cout    << "There are no available carpool with the departure from " << parameter << ".\n"
                            << "Please try again.\n";  
                        continue;

            case 'help':
                cout    << "-------------------------\n"
                        << "To book a carpool; type 'book', following by the corresponding number.\n"
                        << "T filter available carpool by departure location and destination location; type:\n"
                        << " 'destination' or 'depature', following by the city name.\n" << endl
        
                        << "For instance, to book carpool number 8, type 'book 8'.\n"
                        << "To filter depature from Hanoi, type 'departure Hanoi'.\n"
                        << "To filter destination to Danang, type 'destination Danang'.\n" << endl 

                        << "Type 'cancel' to cancel the booking process.\n"
                        << "To view this instruction again, type '?' or 'help'."<< endl
                        << "-------------------------";
                    continue;
                    
            case '?':
                cout    << "-------------------------\n"
                        << "To book a carpool; type 'book', following by the corresponding number.\n"
                        << "T filter available carpool by departure location and destination location; type:\n"
                        << " 'destination' or 'depature', following by the city name.\n" << endl
        
                        << "For instance, to book carpool number 8, type 'book 8'.\n"
                        << "To filter depature from Hanoi, type 'departure Hanoi'.\n"
                        << "To filter destination to Danang, type 'destination Danang'.\n" << endl 

                        << "Type 'cancel' to cancel the booking process.\n"
                        << "To view this instruction again, type '?' or 'help'."<< endl
                        << "-------------------------";
                    continue;

            case 'book':
                if (book <= carpools.size()) {
                    // Book the chosen carpool (implementation details to be added)
                    std::cout << "You've booked: " << carpools[choice-1] << std::endl;
                    break;
                }
                    cout << "Booking failed." << endl
                    continue;

            case 'cancel':
                cout << "Booking canceled." << endl
                break;
        }
        //end of switch-case while-loop
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

void Member::handleCancellation() {
    // Implementation for handling cancellations of bookings or listings
}

void Member::rating() {
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
