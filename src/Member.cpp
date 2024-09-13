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
#include <limits>
#include <cstdlib>

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

        // Load fullname after successful validation
        std::ifstream file("members.csv");
        std::string line, user, pass, name;
        getline(file, line);  // Skip header
        while (getline(file, line)) {
            std::istringstream iss(line);
            getline(iss, user, ',');
            getline(iss, pass, ',');
            getline(iss, name, ',');
            if (user == username && pass == password) {
                fullname = name;  // Set fullname
                break;
            }
        }
        file.close();

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

    /*std::ifstream file("carpool.csv");
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
    file.close();*/

    if (!isMemberAuthenticated) {
        std::cout << "Access denied. Please log in first.\n";
        return;
    }

    int memberCredits = 0;  // Member's available credits
    int memberRating = 0;   // Member's rating score
    std::string fullName;   // Member's full name

    // Load the member's current credit, rating, and full name from members.csv
    std::ifstream memberFile("members.csv");
    std::string memberLine;
    std::getline(memberFile, memberLine); // Skip the header line
    while (std::getline(memberFile, memberLine)) {
        std::istringstream memberSS(memberLine);
        std::vector<std::string> memberDetails;
        std::string memberDetail;
        while (std::getline(memberSS, memberDetail, ',')) {
            memberDetails.push_back(memberDetail);
        }
        if (memberDetails[0] == this->username) {
            memberCredits = std::stoi(memberDetails[7]); // Index 7 for credits
            memberRating = std::stoi(memberDetails[8]); // Index 8 for rating
            fullName = memberDetails[2]; // Index 2 for full name
            break;
        }
    }
    memberFile.close();

    // Read carpool.csv and filter eligible carpools
    std::ifstream carpoolFile("carpool.csv");
    std::string carpoolLine;
    std::vector<std::string> eligibleCarpools;
    std::vector<std::string> carpoolRawData; // To store raw carpool data for booking
    std::getline(carpoolFile, carpoolLine); // Skip header
    while (std::getline(carpoolFile, carpoolLine)) {
        std::istringstream carpoolSS(carpoolLine);
        std::vector<std::string> carpoolDetails;
        std::string carpoolDetail;
        while (std::getline(carpoolSS, carpoolDetail, ',')) {
            carpoolDetails.push_back(carpoolDetail);
        }
        if (carpoolDetails.size() > 12) {
            int availableSeats = std::stoi(carpoolDetails[7]);
            int currentBookedSeats = std::stoi(carpoolDetails[12]);
            int requiredCredits = std::stoi(carpoolDetails[8]);
            int minimumRating = std::stoi(carpoolDetails[10]);

            if (memberCredits >= requiredCredits && memberRating >= minimumRating && currentBookedSeats < availableSeats) {
                std::ostringstream displayLine;
                displayLine << "Route: " << carpoolDetails[0] << " to " << carpoolDetails[1]
                            << ", Departure: " << carpoolDetails[2] << " on " << carpoolDetails[3]
                            << ", Vehicle: " << carpoolDetails[4] << " (" << carpoolDetails[5] << ", " << carpoolDetails[6] << ")"
                            << ", Seats Available: " << (availableSeats - currentBookedSeats)
                            << ", Price per Seat: $" << carpoolDetails[8]
                            << ", Driver: " << carpoolDetails[11];
                eligibleCarpools.push_back(displayLine.str());
                carpoolRawData.push_back(carpoolLine); // Save raw data for potential booking
            }
        }
    }
    carpoolFile.close();

    // Display eligible carpools and let user choose
    if (eligibleCarpools.empty()) {
        std::cout << "No eligible carpools available based on your credits, rating, or seat availability.\n";
        return;
    }

    for (size_t i = 0; i < eligibleCarpools.size(); i++) {
        std::cout << i + 1 << ". " << eligibleCarpools[i] << "\n";
    }

    std::cout << "Enter the number of the carpool you want to book (0 to cancel): ";
    int choice;
    std::cin >> choice;
    if (choice > 0 && choice <= eligibleCarpools.size()) {
        std::string selectedCarpool = carpoolRawData[choice - 1]; // Retrieve the raw carpool data
        std::ofstream bookingFile("bookingRequests.csv", std::ios::app); // Append to booking file
        bookingFile << selectedCarpool << "," << fullName << ",Pending\n"; // Append full name and pending status
        bookingFile.close();
        std::cout << "Booking request created successfully. Status: Pending.\n";
    } else if (choice != 0) {
        std::cout << "Invalid choice. Booking cancelled.\n";
    }
}

void Member::manageBookings() {
    if (!isMemberAuthenticated) {
        std::cout << "Access denied. Please log in first.\n";
        return;
    }

    std::ifstream bookingsFile("bookingRequests.csv");
    if (!bookingsFile.is_open()) {
        std::cout << "Failed to open booking requests file.\n";
        return;
    }

    std::string line;
    std::getline(bookingsFile, line); // Skip the header
    std::vector<std::string> bookingLines; // Store all lines from the file
    std::vector<std::string> userBookings; // To display to the user
    bookingLines.push_back(line); // Add header to new list to be rewritten

    int bookingIndex = 1;
    while (std::getline(bookingsFile, line)) {
        std::istringstream ss(line);
        std::vector<std::string> bookingDetails;
        std::string detail;
        while (getline(ss, detail, ',')) {
            bookingDetails.push_back(detail);
        }

        if (bookingDetails[13] == fullname) {
            std::ostringstream bookingInfo;
            bookingInfo << "Booking " << bookingIndex << ": "
                        << "Date: " << bookingDetails[3] // date
                        << ", Time: " << bookingDetails[2] // departure time
                        << ", Departure: " << bookingDetails[0] // departure location
                        << ", Destination: " << bookingDetails[1] // destination location
                        << ", Driver: " << bookingDetails[11] // driver's name
                        << ", Status: " << bookingDetails[14]; // booking status
            userBookings.push_back(bookingInfo.str());
        }
        // Add all lines for now, removal is handled later
        bookingLines.push_back(line);
        bookingIndex++;
    }
    bookingsFile.close();

    if (userBookings.empty()) {
        std::cout << "You have no active bookings.\n";
        return;
    }

    std::cout << "Active bookings:\n---------------\n";
    for (const auto& booking : userBookings) {
        std::cout << booking << "\n";
    }

    // Options for the user
    int choice;
    std::cout << "\nOptions:\n";
    std::cout << "1. Unlist a booking\n";
    std::cout << "2. Back to menu\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (choice == 1) {
        int bookingNumber;
        std::cout << "Enter the booking number to unlist: ";
        std::cin >> bookingNumber;
        if (bookingNumber > 0 && bookingNumber <= userBookings.size()) {
            std::string selectedLine = bookingLines[bookingNumber]; // Adjust index for zero-based vector
            std::istringstream iss(selectedLine);
            std::vector<std::string> details;
            std::string detail;
            while (getline(iss, detail, ',')) {
                details.push_back(detail);
            }
            if (details[14] == "pending") {
                bookingLines.erase(bookingLines.begin() + bookingNumber); // Remove the selected line
                // Rewrite the file without the removed line
                std::ofstream outFile("bookingRequests.csv");
                for (const auto& l : bookingLines) {
                    outFile << l << "\n";
                }
                outFile.close();
                std::cout << "Booking unlisted successfully.\n";
            } else {
                std::cout << "Selected booking cannot be unlisted because it is not pending.\n";
            }
        }
    } else if (choice == 2) {
        return; // Return to main menu
    }
}



void Member::listCarpool() {
    // Implementation to list a new carpool as a driver
    if (!isMemberAuthenticated) {
        std::cout << "Access denied. Please log in first.\n";
        return;
    }

    std::string driverName; // To hold the full name of the driver

    // Fetch the driver's full name from members.csv using the authenticated username
    std::ifstream memberFile("members.csv");
    std::string line;
    std::getline(memberFile, line); // Skip the header line
    while (std::getline(memberFile, line)) {
        std::vector<std::string> fields;
        std::istringstream ss(line);
        std::string field;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        if (fields[0] == username) {
            driverName = fields[2]; // Assuming the full name is at index 2
            break;
        }
    }
    memberFile.close();

    std::string departureLocation, destinationLocation, departureTime, date, vehicleModel, vehicleColor, plateNumber;
    int availableSeats, driverRating, minimumPassengerRating;
    double contributionPerPassenger;

    std::cout << "Enter departure location: ";
    std::getline(std::cin, departureLocation);
    std::cout << "Enter destination location: ";
    std::getline(std::cin, destinationLocation);
    std::cout << "Enter departure time: ";
    std::getline(std::cin, departureTime);
    std::cout << "Enter date: ";
    std::getline(std::cin, date);
    std::cout << "Enter vehicle model: ";
    std::getline(std::cin, vehicleModel);
    std::cout << "Enter vehicle color: ";
    std::getline(std::cin, vehicleColor);
    std::cout << "Enter plate number: ";
    std::getline(std::cin, plateNumber);
    std::cout << "Enter number of available seats: ";
    std::cin >> availableSeats;
    std::cout << "Enter contribution amount per passenger in credit points: ";
    std::cin >> contributionPerPassenger;
    std::cout << "Enter your driver rating (1-5): ";
    std::cin >> driverRating;
    std::cout << "Set a minimum passenger rating for this carpool (1-5): ";
    std::cin >> minimumPassengerRating;
    std::cin.ignore(); // Clear the buffer after reading numbers

    // Append the new carpool data to the file, initializing booked seats to 0
    std::ofstream outFile("carpool.csv", std::ios::app);
    outFile << departureLocation << "," << destinationLocation << "," << departureTime << ","
            << date << "," << vehicleModel << "," << vehicleColor << "," << plateNumber << ","
            << availableSeats << "," << contributionPerPassenger << "," << driverRating << ","
            << minimumPassengerRating << "," << driverName << ",0\n";
    outFile.close();

    std::cout << "Carpool listing created successfully!\n";
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

    std::cout << "Starting the purchase process...\n";

    std::string inputPassword;
    std::cout << "Please enter your password for verification: ";
    std::cin >> inputPassword;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer after input

    if (inputPassword != password) {
        std::cout << "Password verification failed. Purchase aborted.\n";
        return;
    }

    int purchaseAmount;
    std::cout << "Enter the amount of credits to purchase ($1 = 1 credit): ";
    std::cin >> purchaseAmount;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer

    if (purchaseAmount <= 0) {
        std::cout << "Invalid amount. Purchase aborted.\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    bool updated = false;

    std::ifstream inFile("members.csv");
    if (!inFile.is_open()) {
        std::cerr << "Failed to open members file for reading.\n";
        return;
    }

    getline(inFile, line);  // Read and discard the header
    lines.push_back(line);  // Add the header back to the lines vector

    while (getline(inFile, line)) {
        std::vector<std::string> userDetails;
        std::stringstream ss(line);
        std::string detail;

        while (getline(ss, detail, ',')) {
            userDetails.push_back(detail);
        }

        if (userDetails[0] == username) {
            std::cout << "Updating credits for user: " << username << "\n";

            int currentCredits = std::stoi(userDetails[7]);  // Credits are at index 7
            currentCredits += purchaseAmount;
            userDetails[7] = std::to_string(currentCredits);
            std::stringstream updatedLine;
            for (size_t i = 0; i < userDetails.size(); i++) {
                updatedLine << userDetails[i];
                if (i < userDetails.size() - 1) updatedLine << ",";
            }
            line = updatedLine.str();
            updated = true;
        }
        lines.push_back(line);
    }
    inFile.close();

    std::ofstream outFile("members.csv", std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open members file for writing.\n";
        return;
    }

    for (const auto& eachLine : lines) {
        outFile << eachLine << "\n";
    }
    outFile.close();

    if (updated) {
        std::cout << "Purchase successful! " << purchaseAmount << " credits added to your account.\n";
    } else {
        std::cout << "User not found or update failed.\n";
    }
}
