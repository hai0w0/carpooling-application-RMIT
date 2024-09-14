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

void Member::editProfile() {
    if (!isMemberAuthenticated) {
        std::cout << "Access denied. Please log in first.\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    bool found = false;

    std::ifstream inFile("members.csv");
    if (!inFile.is_open()) {
        std::cout << "Failed to open members file.\n";
        return;
    }

    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    for (auto& line : lines) {
        std::istringstream iss(line);
        std::vector<std::string> userDetails;
        std::string detail;
        while (getline(iss, detail, ',')) {
            userDetails.push_back(detail);
        }

        if (userDetails[0] == username) { // Assuming username is the first element
            found = true;
            std::cout << "Select an option to update:\n";
            std::cout << "1. Password\n";
            std::cout << "2. Phone Number\n";
            std::cout << "3. Email\n";
            std::cout << "0. Cancel\n";
            std::cout << "Enter your choice: ";
            int choice;
            std::cin >> choice;
            std::cin.ignore(); // Clear the newline character left in the input buffer

            switch (choice) {
                case 1:
                    std::cout << "Enter new password: ";
                    getline(std::cin, userDetails[1]);
                    std::cout << "Password has been updated successfully.\n";
                    break;
                case 2:
                    std::cout << "Enter new phone number: ";
                    getline(std::cin, userDetails[3]);
                    std::cout << "Phone number has been updated successfully.\n";
                    break;
                case 3:
                    std::cout << "Enter new email: ";
                    getline(std::cin, userDetails[4]);
                    std::cout << "Email has been updated successfully.\n";
                    break;
                case 0:
                    std::cout << "Update cancelled.\n";
                    return;
                default:
                    std::cout << "Invalid choice. No changes made.\n";
                    return;
            }

            // Update the line with new details
            std::ostringstream oss;
            for (const auto& item : userDetails) {
                if (&item != &userDetails[0]) oss << ",";
                oss << item;
            }
            line = oss.str();
            break;
        }
    }

    if (!found) {
        std::cout << "User not found.\n";
        return;
    }

    std::ofstream outFile("members.csv");
    if (!outFile.is_open()) {
        std::cout << "Failed to open members file for writing.\n";
        return;
    }

    for (const auto& updatedLine : lines) {
        outFile << updatedLine << "\n";
    }
    outFile.close();

    std::cout << "Profile updated successfully.\n";
}


void Member::bookCarpool() {
    if (!isMemberAuthenticated) {
        std::cout << "Access denied. Please log in first.\n";
        return;
    }

    int memberCredits = 0;
    int memberRating = 0;
    std::string fullName;

    // Load member data
    std::ifstream memberFile("members.csv");
    std::string memberLine;
    std::getline(memberFile, memberLine); // Skip header
    while (std::getline(memberFile, memberLine)) {
        std::istringstream memberSS(memberLine);
        std::vector<std::string> memberDetails;
        std::string memberDetail;
        while (std::getline(memberSS, memberDetail, ',')) {
            memberDetails.push_back(memberDetail);
        }
        if (memberDetails[0] == this->username) {
            memberCredits = std::stoi(memberDetails[7]);
            memberRating = std::stoi(memberDetails[8]);
            fullName = memberDetails[2];
            break;
        }
    }
    memberFile.close();

    // Read and store all eligible carpools
    std::vector<std::vector<std::string>> eligibleCarpools;
    std::ifstream carpoolFile("carpool.csv");
    std::string carpoolLine;
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
                eligibleCarpools.push_back(carpoolDetails);
            }
        }
    }
    carpoolFile.close();

    auto displayCarpools = [](const std::vector<std::vector<std::string>>& carpools) {
        for (size_t i = 0; i < carpools.size(); i++) {
            const auto& carpool = carpools[i];
            std::cout << i + 1 << ". Route: " << carpool[0] << " to " << carpool[1]
                      << ", Departure: " << carpool[2] << " on " << carpool[3]
                      << ", Vehicle: " << carpool[4] << " (" << carpool[5] << ", " << carpool[6] << ")"
                      << ", Seats Available: " << (std::stoi(carpool[7]) - std::stoi(carpool[12]))
                      << ", Price per Seat: $" << carpool[8]
                      << ", Driver: " << carpool[11] << "\n";
        }
    };

    while (true) {
        if (eligibleCarpools.empty()) {
            std::cout << "No eligible carpools available.\n";
            return;
        }

        std::cout << "\nAvailable carpools:\n";
        displayCarpools(eligibleCarpools);

        std::cout << "\nOptions:\n";
        std::cout << "1. Book a carpool\n";
        std::cout << "2. Filter carpools\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            std::cout << "Enter the number of the carpool you want to book: ";
            int bookingChoice;
            std::cin >> bookingChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (bookingChoice > 0 && bookingChoice <= static_cast<int>(eligibleCarpools.size())) {
                const auto& selectedCarpool = eligibleCarpools[bookingChoice - 1];
                std::ofstream bookingFile("bookingRequests.csv", std::ios::app);
                for (size_t i = 0; i < selectedCarpool.size(); ++i) {
                    bookingFile << selectedCarpool[i];
                    if (i < selectedCarpool.size() - 1) bookingFile << ",";
                }
                bookingFile << "," << fullName << ",Pending\n";
                bookingFile.close();
                std::cout << "Booking request created successfully. Status: Pending.\n";
                return;
            } else {
                std::cout << "Invalid choice. Please try again.\n";
            }
        } else if (choice == 2) {
            std::string departure, destination;
            int maxPrice;

            std::cout << "Enter departure location (leave blank for no filter): ";
            std::getline(std::cin, departure);

            std::cout << "Enter destination location (leave blank for no filter): ";
            std::getline(std::cin, destination);

            std::cout << "Enter maximum price per seat (0 for no limit): ";
            std::cin >> maxPrice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            auto filteredCarpools = eligibleCarpools;
            filteredCarpools.erase(
                std::remove_if(filteredCarpools.begin(), filteredCarpools.end(),
                    [&](const std::vector<std::string>& carpool) {
                        return (!departure.empty() && carpool[0] != departure) ||
                               (!destination.empty() && carpool[1] != destination) ||
                               (maxPrice > 0 && std::stoi(carpool[8]) > maxPrice);
                    }),
                filteredCarpools.end()
            );

            eligibleCarpools = filteredCarpools;
            std::cout << "\nFiltered carpools:\n";
            displayCarpools(eligibleCarpools);
        } else if (choice == 3) {
            return;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
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

void Member::unlistCarpool() {
    if (!isMemberAuthenticated) {
        std::cout << "Access denied. Please log in first.\n";
        return;
    }

    std::vector<std::string> carpools;
    std::vector<int> driverCarpoolIndices;
    
    // Read carpool.csv
    std::ifstream carpoolFile("carpool.csv");
    std::string line;
    std::getline(carpoolFile, line); // Skip header
    carpools.push_back(line); // Add header to carpools vector
    
    int index = 1;
    while (std::getline(carpoolFile, line)) {
        std::istringstream iss(line);
        std::vector<std::string> details;
        std::string detail;
        while (std::getline(iss, detail, ',')) {
            details.push_back(detail);
        }
        
        carpools.push_back(line);
        
        if (details[11] == fullname) { // Assuming driver's name is at index 11
            std::cout << index << ". " 
                      << "From: " << details[0] << ", To: " << details[1]
                      << ", Date: " << details[3] << ", Time: " << details[2] << "\n";
            driverCarpoolIndices.push_back(carpools.size() - 1);
            index++;
        }
    }
    carpoolFile.close();
    
    if (driverCarpoolIndices.empty()) {
        std::cout << "You have no active carpool listings.\n";
        return;
    }
    
    int choice;
    std::cout << "Enter the number of the carpool you want to unlist (0 to cancel): ";
    std::cin >> choice;
    
    if (choice < 1 || choice > driverCarpoolIndices.size()) {
        std::cout << "Invalid choice. Unlisting cancelled.\n";
        return;
    }
    
    int selectedIndex = driverCarpoolIndices[choice - 1];
    std::string selectedCarpool = carpools[selectedIndex];
    
    // Check for accepted requests in bookingRequests.csv
    std::ifstream bookingFile("bookingRequests.csv");
    bool hasAcceptedRequests = false;
    while (std::getline(bookingFile, line)) {
        if (line.find(selectedCarpool.substr(0, selectedCarpool.find_last_of(','))) != std::string::npos &&
            line.find("Accepted") != std::string::npos) {
            hasAcceptedRequests = true;
            break;
        }
    }
    bookingFile.close();
    
    if (hasAcceptedRequests) {
        std::cout << "Cannot unlist this carpool as it has accepted requests.\n";
        return;
    }
    
    // Remove the selected carpool
    carpools.erase(carpools.begin() + selectedIndex);
    
    // Write back to carpool.csv
    std::ofstream outFile("carpool.csv");
    for (const auto& carpool : carpools) {
        outFile << carpool << "\n";
    }
    outFile.close();
    
    std::cout << "Carpool successfully unlisted.\n";
}

void Member::manageRequests() {
    if (!isMemberAuthenticated) {
        std::cout << "Access denied. Please log in first.\n";
        return;
    }

    while (true) {  // Continuously allow the user to manage bookings until they decide to exit
        std::ifstream bookingsFile("bookingRequests.csv");
        if (!bookingsFile.is_open()) {
            std::cout << "Failed to open booking requests file.\n";
            return;
        }

        std::string line;
        std::getline(bookingsFile, line); // Skip the header
        std::vector<std::string> userBookings; // To display to the user

        int bookingIndex = 1;
        while (std::getline(bookingsFile, line)) {
            std::istringstream ss(line);
            std::vector<std::string> bookingDetails;
            std::string detail;
            while (getline(ss, detail, ',')) {
                bookingDetails.push_back(detail);
            }

            // Only add bookings that are not rejected and belong to the driver to the view
            if (bookingDetails[11] == fullname && bookingDetails[14] != "Rejected" || bookingDetails[11] == fullname && bookingDetails[14] != "Completed") {
                std::ostringstream bookingInfo;
                bookingInfo << "Booking " << bookingIndex++ << ": "
                            << "Passenger: " << bookingDetails[13] // passenger name
                            << ", Date: " << bookingDetails[3] // date
                            << ", Time: " << bookingDetails[2] // departure time
                            << ", Departure: " << bookingDetails[0] // departure location
                            << ", Destination: " << bookingDetails[1] // destination location
                            << ", Status: " << bookingDetails[14]; // booking status
                userBookings.push_back(bookingInfo.str());
            }
        }
        bookingsFile.close();

        if (userBookings.empty()) {
            std::cout << "You have no active booking requests.\n";
            return; // If no bookings are active, return to the menu
        }

        std::cout << "Active booking requests:\n------------------------\n";
        for (const auto& booking : userBookings) {
            std::cout << booking << "\n";
        }

        // Options for the driver
        int choice;
        std::cout << "\nOptions:\n";
        std::cout << "1. Accept a booking\n";
        std::cout << "2. Reject a booking\n";
        std::cout << "3. Back to menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1 || choice == 2) {
            int bookingNumber;
            std::cout << "Enter the booking number to modify: ";
            std::cin >> bookingNumber;
            if (bookingNumber > 0 && bookingNumber <= userBookings.size()) {
                std::istringstream iss(userBookings[bookingNumber - 1]);
                std::vector<std::string> details;
                std::string detail;
                while (getline(iss, detail, ',')) {
                    details.push_back(detail);
                }
                // Process acceptance or rejection based on the choice
                if (choice == 1 && details[14] == "pending") {
                    // Accept the booking
                    details[14] = "Accepted";
                } else if (choice == 2) {
                    // Reject the booking
                    details[14] = "Rejected";
                }
                
                // Notify user of the outcome
                std::cout << "Booking has been " << (choice == 1 ? "accepted" : "rejected") << ".\n";
            }
        } else if (choice == 3) {
            return; // Exit the loop and return to the main menu
        }
    }
}


void Member::confirmCarpoolRides() {
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

    std::map<std::string, std::vector<std::string>> carpoolGroups;
    std::vector<std::string> allBookings;

    allBookings.push_back(line); // Add header to allBookings

    while (std::getline(bookingsFile, line)) {
        std::istringstream ss(line);
        std::vector<std::string> bookingDetails;
        std::string detail;
        while (getline(ss, detail, ',')) {
            bookingDetails.push_back(detail);
        }

        if (bookingDetails[11] == fullname && bookingDetails[14] == "Accepted") {
            std::string tripKey = bookingDetails[0] + "|" + bookingDetails[1] + "|" + bookingDetails[2] + "|" + bookingDetails[3];
            carpoolGroups[tripKey].push_back(line);
        }
        allBookings.push_back(line);
    }
    bookingsFile.close();

    if (carpoolGroups.empty()) {
        std::cout << "No accepted carpool rides to confirm.\n";
        return;
    }

    // Display available carpools
    std::cout << "Accepted carpool rides:\n-----------------------\n";
    int index = 1;
    for (const auto& group : carpoolGroups) {
        std::istringstream keyDetails(group.first);
        std::vector<std::string> tripInfo;
        std::string info;
        while (getline(keyDetails, info, '|')) {
            tripInfo.push_back(info);
        }
        std::cout << index++ << ". Trip from " << tripInfo[0] << " to " << tripInfo[1]
                  << " at " << tripInfo[2] << " on " << tripInfo[3] << "\n";
        std::cout << "   Passengers: " << group.second.size() << "\n";
    }

    // Allow driver to select a ride to confirm completion
    std::cout << "Select a ride to confirm (0 to cancel): ";
    int choice;
    std::cin >> choice;
    if (choice == 0 || choice > carpoolGroups.size()) return;

    auto it = carpoolGroups.begin();
    std::advance(it, choice - 1);

    std::cout << "Is the trip completed? (yes/no): ";
    std::string confirmation;
    std::cin >> confirmation;

    if (confirmation == "yes") {
        int totalContribution = 0;
        for (const auto& bookingLine : it->second) {
            std::istringstream ss(bookingLine);
            std::vector<std::string> bookingDetails;
            std::string detail;
            while (getline(ss, detail, ',')) {
                bookingDetails.push_back(detail);
            }
            std::string passengerName = bookingDetails[13];
            int contribution = std::stoi(bookingDetails[8]);
            totalContribution += contribution;
            transferCredits(passengerName, fullname, contribution);
        }
        
        std::cout << "Carpool ride confirmed as completed. " << totalContribution << " credits have been transferred.\n";
        
        // Update the status in allBookings to "Completed"
        for (auto& booking : allBookings) {
            std::istringstream ss(booking);
            std::vector<std::string> bookingDetails;
            std::string detail;
            while (getline(ss, detail, ',')) {
                bookingDetails.push_back(detail);
            }
            if (bookingDetails[11] == fullname && 
                bookingDetails[0] == it->second[0].substr(0, it->second[0].find(',')) &&
                bookingDetails[14] == "Accepted") {
                bookingDetails[14] = "Completed";
                std::ostringstream updatedBooking;
                for (size_t i = 0; i < bookingDetails.size(); ++i) {
                    updatedBooking << bookingDetails[i];
                    if (i < bookingDetails.size() - 1) updatedBooking << ",";
                }
                booking = updatedBooking.str();
            }
        }
        
        // Rewrite the bookingRequests.csv file with updated statuses
        std::ofstream outFile("bookingRequests.csv");
        if (outFile.is_open()) {
            for (const auto& booking : allBookings) {
                outFile << booking << "\n";
            }
            outFile.close();
            std::cout << "Booking statuses updated successfully.\n";
        } else {
            std::cout << "Failed to update booking statuses in the file.\n";
        }

        // Update carpool.csv to set available seats to 0
        std::vector<std::string> carpoolLines;
        std::ifstream carpoolFile("carpool.csv");
        if (carpoolFile.is_open()) {
            std::string carpoolLine;
            while (std::getline(carpoolFile, carpoolLine)) {
                std::istringstream ss(carpoolLine);
                std::vector<std::string> carpoolDetails;
                std::string detail;
                while (getline(ss, detail, ',')) {
                    carpoolDetails.push_back(detail);
                }
                if (carpoolDetails.size() > 11 && 
                    carpoolDetails[0] == it->second[0].substr(0, it->second[0].find(',')) &&
                    carpoolDetails[11] == fullname) { 
                    carpoolDetails[12] = "0";  // Set current booked seats to 0
                    std::ostringstream updatedCarpool;
                    for (size_t i = 0; i < carpoolDetails.size(); ++i) {
                        updatedCarpool << carpoolDetails[i];
                        if (i < carpoolDetails.size() - 1) updatedCarpool << ",";
                    }
                    carpoolLines.push_back(updatedCarpool.str());
                } else {
                    carpoolLines.push_back(carpoolLine);
                }
            }
            carpoolFile.close();

            std::ofstream carpoolOutFile("carpool.csv");
            if (carpoolOutFile.is_open()) {
                for (const auto& carpoolLine : carpoolLines) {
                    carpoolOutFile << carpoolLine << "\n";
                }
                carpoolOutFile.close();
                std::cout << "Carpool details updated successfully.\n";
            } else {
                std::cout << "Failed to update carpool details in the file.\n";
            }
        } else {
            std::cout << "Failed to open carpool.csv for reading.\n";
        }
    } else {
        std::cout << "Carpool ride not confirmed as completed.\n";
    }
}

void Member::transferCredits(const std::string& fromUser, const std::string& toUser, int amount) {
    std::vector<std::string> lines;
    std::string line;
    
    // Read the entire members.csv file
    std::ifstream inFile("members.csv");
    if (!inFile.is_open()) {
        std::cout << "Failed to open members.csv for reading.\n";
        return;
    }
    
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();
    
    bool fromUserFound = false, toUserFound = false;
    
    // Update credit amounts
    for (auto& line : lines) {
        std::istringstream iss(line);
        std::vector<std::string> userDetails;
        std::string detail;
        while (std::getline(iss, detail, ',')) {
            userDetails.push_back(detail);
        }
        
        if (userDetails.size() > 7) {
            if (userDetails[2] == fromUser) {
                int currentCredits = std::stoi(userDetails[7]);
                userDetails[7] = std::to_string(currentCredits - amount);
                fromUserFound = true;
            } else if (userDetails[2] == toUser) {
                int currentCredits = std::stoi(userDetails[7]);
                userDetails[7] = std::to_string(currentCredits + amount);
                toUserFound = true;
            }
            
            if (fromUserFound || toUserFound) {
                std::ostringstream oss;
                for (size_t i = 0; i < userDetails.size(); ++i) {
                    if (i > 0) oss << ",";
                    oss << userDetails[i];
                }
                line = oss.str();
            }
        }
        
        if (fromUserFound && toUserFound) break;
    }
    
    if (!fromUserFound || !toUserFound) {
        std::cout << "Error: One or both users not found.\n";
        return;
    }
    
    // Write the updated data back to members.csv
    std::ofstream outFile("members.csv");
    if (!outFile.is_open()) {
        std::cout << "Failed to open members.csv for writing.\n";
        return;
    }
    
    for (const auto& updatedLine : lines) {
        outFile << updatedLine << "\n";
    }
    outFile.close();
    
    std::cout << "Credits transferred successfully.\n";
}



void Member::rating() {
    if (!isMemberAuthenticated) {
        std::cout << "Access denied. Please log in first.\n";
        return;
    }

    // Load completed rides
    std::vector<std::vector<std::string>> completedRides;
    std::ifstream bookingsFile("bookingRequests.csv");
    std::string line;
    std::getline(bookingsFile, line); // Skip header
    while (std::getline(bookingsFile, line)) {
        std::istringstream ss(line);
        std::vector<std::string> bookingDetails;
        std::string detail;
        while (std::getline(ss, detail, ',')) {
            bookingDetails.push_back(detail);
        }
        if (bookingDetails[14] == "Completed" && 
            (bookingDetails[11] == fullname || bookingDetails[13] == fullname)) {
            completedRides.push_back(bookingDetails);
        }
    }
    bookingsFile.close();

    if (completedRides.empty()) {
        std::cout << "No completed rides to rate.\n";
        return;
    }

    // Display completed rides
    std::cout << "Completed rides:\n";
    for (size_t i = 0; i < completedRides.size(); ++i) {
        std::cout << i + 1 << ". " << completedRides[i][0] << " to " << completedRides[i][1]
                  << " on " << completedRides[i][3] << " at " << completedRides[i][2] << "\n";
    }

    // Select a ride to rate
    int choice;
    std::cout << "Select a ride to rate (0 to cancel): ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (choice < 1 || choice > static_cast<int>(completedRides.size())) {
        std::cout << "Invalid choice. Rating cancelled.\n";
        return;
    }

    const auto& selectedRide = completedRides[choice - 1];
    std::string ratedUser = (selectedRide[11] == fullname) ? selectedRide[13] : selectedRide[11];
    std::string raterRole = (selectedRide[11] == fullname) ? "Driver" : "Passenger";

    // Get rating and review
    int ratingScore;
    std::string review;
    std::cout << "Rate " << ratedUser << " (1-5): ";
    std::cin >> ratingScore;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (ratingScore < 1 || ratingScore > 5) {
        std::cout << "Invalid rating. Must be between 1 and 5.\n";
        return;
    }
    std::cout << "Leave a review (optional): ";
    std::getline(std::cin, review);

    // Update user's rating in members.csv
    std::vector<std::string> memberLines;
    std::ifstream membersFile("members.csv");
    std::getline(membersFile, line); // Read and store header
    memberLines.push_back(line);
    while (std::getline(membersFile, line)) {
        std::istringstream ss(line);
        std::vector<std::string> memberDetails;
        std::string detail;
        while (std::getline(ss, detail, ',')) {
            memberDetails.push_back(detail);
        }
        if (memberDetails[2] == ratedUser) {
            int currentRating = std::stoi(memberDetails[8]);
            int newRating = (currentRating + ratingScore) / 2; // Simple average
            memberDetails[8] = std::to_string(newRating);
            std::ostringstream updatedMember;
            for (size_t i = 0; i < memberDetails.size(); ++i) {
                updatedMember << memberDetails[i];
                if (i < memberDetails.size() - 1) updatedMember << ",";
            }
            memberLines.push_back(updatedMember.str());
        } else {
            memberLines.push_back(line);
        }
    }
    membersFile.close();

    // Write updated members data
    std::ofstream outMembersFile("members.csv");
    for (const auto& memberLine : memberLines) {
        outMembersFile << memberLine << "\n";
    }
    outMembersFile.close();

    // Store rating and review in a new file: ratings.csv
    std::ofstream ratingsFile("ratings.csv", std::ios::app);
    ratingsFile << raterRole << "," << fullname << "," << ratedUser << "," 
                << ratingScore << "," << review << "\n";
    ratingsFile.close();

    std::cout << "Rating submitted successfully.\n";
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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  

    if (inputPassword != password) {
        std::cout << "Password verification failed. Purchase aborted.\n";
        return;
    }

    int purchaseAmount;
    std::cout << "Enter the amount of credits to purchase ($1 = 1 credit): ";
    std::cin >> purchaseAmount;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  

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

    getline(inFile, line);  
    lines.push_back(line);  

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
