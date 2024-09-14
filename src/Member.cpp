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
using namespace std;

Member::Member() : isMemberAuthenticated(false) {}

void Member::loadMemberData() {
    ifstream file("members.csv");
    string line;
    getline(file, line); 
    while (getline(file, line)) {
        istringstream iss(line);
        string username, password;
        getline(iss, username, ',');
        getline(iss, password, ',');
        memberCredentials[username] = {username, password};
    }
    file.close();
}

bool Member::validateCredentials(const string& username, const string& password) const {
    auto it = memberCredentials.find(username);
    return it != memberCredentials.end() && it->second.second == password;
}

bool Member::login(const string& inputUsername, const string& inputPassword) {
    if (validateCredentials(inputUsername, inputPassword)) {
        isMemberAuthenticated = true;
        username = inputUsername;
        password = inputPassword;
        ifstream file("members.csv");
        string line, user, pass, name;
        getline(file, line);  
        while (getline(file, line)) {
            istringstream iss(line);
            getline(iss, user, ',');
            getline(iss, pass, ',');
            getline(iss, name, ',');
            if (user == username && pass == password) {
                fullname = name;  
                break;
            }
        }
        file.close();

        cout << "Login successful.\n";
        return true;
    } else {
        cout << "Login failed.\n";
        return false;
    }
}


void Member::viewProfile() const {
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }

    ifstream file("members.csv");
    if (!file.is_open()) {
        cerr << "Error: Failed to open profile data file.\n";
        return;
    }

    string line;
    bool found = false;
    getline(file, line);
    while (getline(file, line)) {
        istringstream ss(line);
        vector<string> userDetails;
        string detail;

        while (getline(ss, detail, ',')) {
            userDetails.push_back(detail);
        }

        if (userDetails.size() >= 7 && userDetails[0] == username) {
            found = true;
            cout << "\n=============== Your Profile Information ===============\n";
            cout << left << setw(20) << "Username:" << userDetails[0] << "\n";
            cout << left << setw(20) << "Full Name:" << userDetails[2] << "\n";
            cout << left << setw(20) << "Phone Number:" << userDetails[3] << "\n";
            cout << left << setw(20) << "Email:" << userDetails[4] << "\n";
            cout << left << setw(20) << "ID Type:" << userDetails[5] << "\n";
            cout << left << setw(20) << "ID Number:" << userDetails[6] << "\n";
            cout << left << setw(20) << "Credit Points:" << userDetails[7] << "\n";
            cout << "========================================================\n";
            break;
        }
    }

    file.close();

    if (!found) {
        cerr << "Error: User profile not found in the database.\n";
    }
}

void Member::editProfile() {
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }

    vector<string> lines;
    string line;
    bool found = false;

    ifstream inFile("members.csv");
    if (!inFile.is_open()) {
        cout << "Failed to open members file.\n";
        return;
    }

    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    for (auto& line : lines) {
        istringstream iss(line);
        vector<string> userDetails;
        string detail;
        while (getline(iss, detail, ',')) {
            userDetails.push_back(detail);
        }

        if (userDetails[0] == username) { 
            found = true;
            cout << "Select an option to update:\n";
            cout << "1. Password\n";
            cout << "2. Phone Number\n";
            cout << "3. Email\n";
            cout << "0. Cancel\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;
            cin.ignore(); 

            switch (choice) {
                case 1:
                    cout << "Enter new password: ";
                    getline(cin, userDetails[1]);
                    cout << "Password has been updated successfully.\n";
                    break;
                case 2:
                    cout << "Enter new phone number: ";
                    getline(cin, userDetails[3]);
                    cout << "Phone number has been updated successfully.\n";
                    break;
                case 3:
                    cout << "Enter new email: ";
                    getline(cin, userDetails[4]);
                    cout << "Email has been updated successfully.\n";
                    break;
                case 0:
                    cout << "Update cancelled.\n";
                    return;
                default:
                    cout << "Invalid choice. No changes made.\n";
                    return;
            }
            ostringstream oss;
            for (const auto& item : userDetails) {
                if (&item != &userDetails[0]) oss << ",";
                oss << item;
            }
            line = oss.str();
            break;
        }
    }

    if (!found) {
        cout << "User not found.\n";
        return;
    }

    ofstream outFile("members.csv");
    if (!outFile.is_open()) {
        cout << "Failed to open members file for writing.\n";
        return;
    }

    for (const auto& updatedLine : lines) {
        outFile << updatedLine << "\n";
    }
    outFile.close();

    cout << "Profile updated successfully.\n";
}


void Member::bookCarpool() {
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }

    int memberCredits = 0;
    int memberRating = 0;
    string fullName;
    ifstream memberFile("members.csv");
    string memberLine;
    getline(memberFile, memberLine);
    while (getline(memberFile, memberLine)) {
        istringstream memberSS(memberLine);
        vector<string> memberDetails;
        string memberDetail;
        while (getline(memberSS, memberDetail, ',')) {
            memberDetails.push_back(memberDetail);
        }
        if (memberDetails[0] == this->username) {
            memberCredits = stoi(memberDetails[7]);
            memberRating = stoi(memberDetails[8]);
            fullName = memberDetails[2];
            break;
        }
    }
    memberFile.close();
    vector<vector<string>> eligibleCarpools;
    ifstream carpoolFile("carpool.csv");
    string carpoolLine;
    getline(carpoolFile, carpoolLine); 
    while (getline(carpoolFile, carpoolLine)) {
        istringstream carpoolSS(carpoolLine);
        vector<string> carpoolDetails;
        string carpoolDetail;
        while (getline(carpoolSS, carpoolDetail, ',')) {
            carpoolDetails.push_back(carpoolDetail);
        }
        if (carpoolDetails.size() > 12) {
            int availableSeats = stoi(carpoolDetails[7]);
            int currentBookedSeats = stoi(carpoolDetails[12]);
            int requiredCredits = stoi(carpoolDetails[8]);
            int minimumRating = stoi(carpoolDetails[10]);

            if (memberCredits >= requiredCredits && memberRating >= minimumRating && currentBookedSeats < availableSeats) {
                eligibleCarpools.push_back(carpoolDetails);
            }
        }
    }
    carpoolFile.close();

    auto displayCarpools = [](const vector<vector<string>>& carpools) {
        for (size_t i = 0; i < carpools.size(); i++) {
            const auto& carpool = carpools[i];
            cout << i + 1 << ". Route: " << carpool[0] << " to " << carpool[1]
                      << ", Departure: " << carpool[2] << " on " << carpool[3]
                      << ", Vehicle: " << carpool[4] << " (" << carpool[5] << ", " << carpool[6] << ")"
                      << ", Seats Available: " << (stoi(carpool[7]) - stoi(carpool[12]))
                      << ", Price per Seat: $" << carpool[8]
                      << ", Driver: " << carpool[11] << "\n";
        }
    };

    while (true) {
        if (eligibleCarpools.empty()) {
            cout << "No eligible carpools available.\n";
            return;
        }

        cout << "\nAvailable carpools:\n";
        displayCarpools(eligibleCarpools);

        cout << "\nOptions:\n";
        cout << "1. Book a carpool\n";
        cout << "2. Filter carpools\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            cout << "Enter the number of the carpool you want to book: ";
            int bookingChoice;
            cin >> bookingChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (bookingChoice > 0 && bookingChoice <= static_cast<int>(eligibleCarpools.size())) {
                const auto& selectedCarpool = eligibleCarpools[bookingChoice - 1];
                ofstream bookingFile("bookingRequests.csv", ios::app);
                for (size_t i = 0; i < selectedCarpool.size(); ++i) {
                    bookingFile << selectedCarpool[i];
                    if (i < selectedCarpool.size() - 1) bookingFile << ",";
                }
                bookingFile << "," << fullName << ",Pending\n";
                bookingFile.close();
                cout << "Booking request created successfully. Status: Pending.\n";
                return;
            } else {
                cout << "Invalid choice. Please try again.\n";
            }
        } else if (choice == 2) {
            string departure, destination;
            int maxPrice;

            cout << "Enter departure location (leave blank for no filter): ";
            getline(cin, departure);

            cout << "Enter destination location (leave blank for no filter): ";
            getline(cin, destination);

            cout << "Enter maximum price per seat (0 for no limit): ";
            cin >> maxPrice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            auto filteredCarpools = eligibleCarpools;
            filteredCarpools.erase(
                remove_if(filteredCarpools.begin(), filteredCarpools.end(),
                    [&](const vector<string>& carpool) {
                        return (!departure.empty() && carpool[0] != departure) ||
                               (!destination.empty() && carpool[1] != destination) ||
                               (maxPrice > 0 && stoi(carpool[8]) > maxPrice);
                    }),
                filteredCarpools.end()
            );

            eligibleCarpools = filteredCarpools;
            cout << "\nFiltered carpools:\n";
            displayCarpools(eligibleCarpools);
        } else if (choice == 3) {
            return;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Member::manageBookings() {
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }

    ifstream bookingsFile("bookingRequests.csv");
    if (!bookingsFile.is_open()) {
        cout << "Failed to open booking requests file.\n";
        return;
    }

    string line;
    getline(bookingsFile, line);
    vector<string> bookingLines; 
    vector<string> userBookings; 
    bookingLines.push_back(line); 

    int bookingIndex = 1;
    while (getline(bookingsFile, line)) {
        istringstream ss(line);
        vector<string> bookingDetails;
        string detail;
        while (getline(ss, detail, ',')) {
            bookingDetails.push_back(detail);
        }

        if (bookingDetails[13] == fullname) {
            ostringstream bookingInfo;
            bookingInfo << "Booking " << bookingIndex << ": "
                        << "Date: " << bookingDetails[3]
                        << ", Time: " << bookingDetails[2] 
                        << ", Departure: " << bookingDetails[0] 
                        << ", Destination: " << bookingDetails[1] 
                        << ", Driver: " << bookingDetails[11] 
                        << ", Status: " << bookingDetails[14]; 
            userBookings.push_back(bookingInfo.str());
        }
        bookingLines.push_back(line);
        bookingIndex++;
    }
    bookingsFile.close();

    if (userBookings.empty()) {
        cout << "You have no active bookings.\n";
        return;
    }
    cout << "Active bookings:\n---------------\n";
    for (const auto& booking : userBookings) {
        cout << booking << "\n";
    }
    int choice;
    cout << "\nOptions:\n";
    cout << "1. Unlist a booking\n";
    cout << "2. Back to menu\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        int bookingNumber;
        cout << "Enter the booking number to unlist: ";
        cin >> bookingNumber;
        if (bookingNumber > 0 && bookingNumber <= userBookings.size()) {
            string selectedLine = bookingLines[bookingNumber];
            istringstream iss(selectedLine);
            vector<string> details;
            string detail;
            while (getline(iss, detail, ',')) {
                details.push_back(detail);
            }
            if (details[14] == "pending") {
                bookingLines.erase(bookingLines.begin() + bookingNumber);
                ofstream outFile("bookingRequests.csv");
                for (const auto& l : bookingLines) {
                    outFile << l << "\n";
                }
                outFile.close();
                cout << "Booking unlisted successfully.\n";
            } else {
                cout << "Selected booking cannot be unlisted because it is not pending.\n";
            }
        }
    } else if (choice == 2) {
        return;
    }
}

void Member::listCarpool() {
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }
    string driverName;
    ifstream memberFile("members.csv");
    string line;
    getline(memberFile, line); 
    while (getline(memberFile, line)) {
        vector<string> fields;
        istringstream ss(line);
        string field;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        if (fields[0] == username) {
            driverName = fields[2];
            break;
        }
    }
    memberFile.close();
    string departureLocation, destinationLocation, departureTime, date, vehicleModel, vehicleColor, plateNumber;
    int availableSeats, driverRating, minimumPassengerRating;
    double contributionPerPassenger;
    cout << "Enter departure location: ";
    getline(cin, departureLocation);
    cout << "Enter destination location: ";
    getline(cin, destinationLocation);
    cout << "Enter departure time: ";
    getline(cin, departureTime);
    cout << "Enter date: ";
    getline(cin, date);
    cout << "Enter vehicle model: ";
    getline(cin, vehicleModel);
    cout << "Enter vehicle color: ";
    getline(cin, vehicleColor);
    cout << "Enter plate number: ";
    getline(cin, plateNumber);
    cout << "Enter number of available seats: ";
    cin >> availableSeats;
    cout << "Enter contribution amount per passenger in credit points: ";
    cin >> contributionPerPassenger;
    cout << "Enter your driver rating (1-5): ";
    cin >> driverRating;
    cout << "Set a minimum passenger rating for this carpool (1-5): ";
    cin >> minimumPassengerRating;
    cin.ignore(); 
    ofstream outFile("carpool.csv", ios::app);
    outFile << departureLocation << "," << destinationLocation << "," << departureTime << ","
            << date << "," << vehicleModel << "," << vehicleColor << "," << plateNumber << ","
            << availableSeats << "," << contributionPerPassenger << "," << driverRating << ","
            << minimumPassengerRating << "," << driverName << ",0\n";
    outFile.close();
    cout << "Carpool listing created successfully!\n";
}

void Member::unlistCarpool() {
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }
    vector<string> carpools;
    vector<int> driverCarpoolIndices;
    ifstream carpoolFile("carpool.csv");
    string line;
    getline(carpoolFile, line); 
    carpools.push_back(line); 
    int index = 1;
    while (getline(carpoolFile, line)) {
        istringstream iss(line);
        vector<string> details;
        string detail;
        while (getline(iss, detail, ',')) {
            details.push_back(detail);
        }
        
        carpools.push_back(line);
        
        if (details[11] == fullname) { 
            cout << index << ". " 
                      << "From: " << details[0] << ", To: " << details[1]
                      << ", Date: " << details[3] << ", Time: " << details[2] << "\n";
            driverCarpoolIndices.push_back(carpools.size() - 1);
            index++;
        }
    }
    carpoolFile.close();
    
    if (driverCarpoolIndices.empty()) {
        cout << "You have no active carpool listings.\n";
        return;
    }
    
    int choice;
    cout << "Enter the number of the carpool you want to unlist (0 to cancel): ";
    cin >> choice;
    
    if (choice < 1 || choice > driverCarpoolIndices.size()) {
        cout << "Invalid choice. Unlisting cancelled.\n";
        return;
    }
    
    int selectedIndex = driverCarpoolIndices[choice - 1];
    string selectedCarpool = carpools[selectedIndex];
    ifstream bookingFile("bookingRequests.csv");
    bool hasAcceptedRequests = false;
    while (getline(bookingFile, line)) {
        if (line.find(selectedCarpool.substr(0, selectedCarpool.find_last_of(','))) != string::npos &&
            line.find("Accepted") != string::npos) {
            hasAcceptedRequests = true;
            break;
        }
    }
    bookingFile.close();
    
    if (hasAcceptedRequests) {
        cout << "Cannot unlist this carpool as it has accepted requests.\n";
        return;
    }
    
    carpools.erase(carpools.begin() + selectedIndex);
    
    ofstream outFile("carpool.csv");
    for (const auto& carpool : carpools) {
        outFile << carpool << "\n";
    }
    outFile.close();
    
    cout << "Carpool successfully unlisted.\n";
}

void Member::manageRequests() {
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }
    while (true) { 
        ifstream bookingsFile("bookingRequests.csv");
        if (!bookingsFile.is_open()) {
            cout << "Failed to open booking requests file.\n";
            return;
        }
        string line;
        getline(bookingsFile, line); 
        vector<string> userBookings; 

        int bookingIndex = 1;
        while (getline(bookingsFile, line)) {
            istringstream ss(line);
            vector<string> bookingDetails;
            string detail;
            while (getline(ss, detail, ',')) {
                bookingDetails.push_back(detail);
            }
            if (bookingDetails[11] == fullname && bookingDetails[14] != "Rejected" || bookingDetails[11] == fullname && bookingDetails[14] != "Completed") {
                ostringstream bookingInfo;
                bookingInfo << "Booking " << bookingIndex++ << ": "
                            << "Passenger: " << bookingDetails[13]
                            << ", Date: " << bookingDetails[3] 
                            << ", Time: " << bookingDetails[2] 
                            << ", Departure: " << bookingDetails[0] 
                            << ", Destination: " << bookingDetails[1] 
                            << ", Status: " << bookingDetails[14]; 
                userBookings.push_back(bookingInfo.str());
            }
        }
        bookingsFile.close();

        if (userBookings.empty()) {
            cout << "You have no active booking requests.\n";
            return; 
        }
        cout << "Active booking requests:\n------------------------\n";
        for (const auto& booking : userBookings) {
            cout << booking << "\n";
        }
        int choice;
        cout << "\nOptions:\n";
        cout << "1. Accept a booking\n";
        cout << "2. Reject a booking\n";
        cout << "3. Back to menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1 || choice == 2) {
            int bookingNumber;
            cout << "Enter the booking number to modify: ";
            cin >> bookingNumber;
            if (bookingNumber > 0 && bookingNumber <= userBookings.size()) {
                istringstream iss(userBookings[bookingNumber - 1]);
                vector<string> details;
                string detail;
                while (getline(iss, detail, ',')) {
                    details.push_back(detail);
                }
                if (choice == 1 && details[14] == "pending") {
                    details[14] = "Accepted";
                } else if (choice == 2) {
                    details[14] = "Rejected";
                }
                cout << "Booking has been " << (choice == 1 ? "accepted" : "rejected") << ".\n";
            }
        } else if (choice == 3) {
            return;
        }
    }
}

void Member::confirmCarpoolRides() {
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }

    ifstream bookingsFile("bookingRequests.csv");
    if (!bookingsFile.is_open()) {
        cout << "Failed to open booking requests file.\n";
        return;
    }
    string line;
    getline(bookingsFile, line); 
    map<string, vector<string>> carpoolGroups;
    vector<string> allBookings;
    allBookings.push_back(line); 
    while (getline(bookingsFile, line)) {
        istringstream ss(line);
        vector<string> bookingDetails;
        string detail;
        while (getline(ss, detail, ',')) {
            bookingDetails.push_back(detail);
        }

        if (bookingDetails[11] == fullname && bookingDetails[14] == "Accepted") {
            string tripKey = bookingDetails[0] + "|" + bookingDetails[1] + "|" + bookingDetails[2] + "|" + bookingDetails[3];
            carpoolGroups[tripKey].push_back(line);
        }
        allBookings.push_back(line);
    }
    bookingsFile.close();

    if (carpoolGroups.empty()) {
        cout << "No accepted carpool rides to confirm.\n";
        return;
    }
    cout << "Accepted carpool rides:\n-----------------------\n";
    int index = 1;
    for (const auto& group : carpoolGroups) {
        istringstream keyDetails(group.first);
        vector<string> tripInfo;
        string info;
        while (getline(keyDetails, info, '|')) {
            tripInfo.push_back(info);
        }
        cout << index++ << ". Trip from " << tripInfo[0] << " to " << tripInfo[1]
                  << " at " << tripInfo[2] << " on " << tripInfo[3] << "\n";
        cout << "   Passengers: " << group.second.size() << "\n";
    }

    // Allow driver to select a ride to confirm completion
    cout << "Select a ride to confirm (0 to cancel): ";
    int choice;
    cin >> choice;
    if (choice == 0 || choice > carpoolGroups.size()) return;

    auto it = carpoolGroups.begin();
    advance(it, choice - 1);

    cout << "Is the trip completed? (yes/no): ";
    string confirmation;
    cin >> confirmation;

    if (confirmation == "yes") {
        int totalContribution = 0;
        for (const auto& bookingLine : it->second) {
            istringstream ss(bookingLine);
            vector<string> bookingDetails;
            string detail;
            while (getline(ss, detail, ',')) {
                bookingDetails.push_back(detail);
            }
            string passengerName = bookingDetails[13];
            int contribution = stoi(bookingDetails[8]);
            totalContribution += contribution;
            transferCredits(passengerName, fullname, contribution);
        }
        
        cout << "Carpool ride confirmed as completed. " << totalContribution << " credits have been transferred.\n";
        for (auto& booking : allBookings) {
            istringstream ss(booking);
            vector<string> bookingDetails;
            string detail;
            while (getline(ss, detail, ',')) {
                bookingDetails.push_back(detail);
            }
            if (bookingDetails[11] == fullname && 
                bookingDetails[0] == it->second[0].substr(0, it->second[0].find(',')) &&
                bookingDetails[14] == "Accepted") {
                bookingDetails[14] = "Completed";
                ostringstream updatedBooking;
                for (size_t i = 0; i < bookingDetails.size(); ++i) {
                    updatedBooking << bookingDetails[i];
                    if (i < bookingDetails.size() - 1) updatedBooking << ",";
                }
                booking = updatedBooking.str();
            }
        }
        ofstream outFile("bookingRequests.csv");
        if (outFile.is_open()) {
            for (const auto& booking : allBookings) {
                outFile << booking << "\n";
            }
            outFile.close();
            cout << "Booking statuses updated successfully.\n";
        } else {
            cout << "Failed to update booking statuses in the file.\n";
        }
        vector<string> carpoolLines;
        ifstream carpoolFile("carpool.csv");
        if (carpoolFile.is_open()) {
            string carpoolLine;
            while (getline(carpoolFile, carpoolLine)) {
                istringstream ss(carpoolLine);
                vector<string> carpoolDetails;
                string detail;
                while (getline(ss, detail, ',')) {
                    carpoolDetails.push_back(detail);
                }
                if (carpoolDetails.size() > 11 && 
                    carpoolDetails[0] == it->second[0].substr(0, it->second[0].find(',')) &&
                    carpoolDetails[11] == fullname) { 
                    carpoolDetails[12] = "0";  // Set current booked seats to 0
                    ostringstream updatedCarpool;
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

            ofstream carpoolOutFile("carpool.csv");
            if (carpoolOutFile.is_open()) {
                for (const auto& carpoolLine : carpoolLines) {
                    carpoolOutFile << carpoolLine << "\n";
                }
                carpoolOutFile.close();
                cout << "Carpool details updated successfully.\n";
            } else {
                cout << "Failed to update carpool details in the file.\n";
            }
        } else {
            cout << "Failed to open carpool.csv for reading.\n";
        }
    } else {
        cout << "Carpool ride not confirmed as completed.\n";
    }
}

void Member::transferCredits(const string& fromUser, const string& toUser, int amount) {
    vector<string> lines;
    string line;
    ifstream inFile("members.csv");
    if (!inFile.is_open()) {
        cout << "Failed to open members.csv for reading.\n";
        return;
    }
    
    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();
    
    bool fromUserFound = false, toUserFound = false;
    for (auto& line : lines) {
        istringstream iss(line);
        vector<string> userDetails;
        string detail;
        while (getline(iss, detail, ',')) {
            userDetails.push_back(detail);
        }
        
        if (userDetails.size() > 7) {
            if (userDetails[2] == fromUser) {
                int currentCredits = stoi(userDetails[7]);
                userDetails[7] = to_string(currentCredits - amount);
                fromUserFound = true;
            } else if (userDetails[2] == toUser) {
                int currentCredits = stoi(userDetails[7]);
                userDetails[7] = to_string(currentCredits + amount);
                toUserFound = true;
            }
            
            if (fromUserFound || toUserFound) {
                ostringstream oss;
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
        cout << "Error: One or both users not found.\n";
        return;
    }
    ofstream outFile("members.csv");
    if (!outFile.is_open()) {
        cout << "Failed to open members.csv for writing.\n";
        return;
    }
    
    for (const auto& updatedLine : lines) {
        outFile << updatedLine << "\n";
    }
    outFile.close();
    
    cout << "Credits transferred successfully.\n";
}

void Member::rating() {
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }
    vector<vector<string>> completedRides;
    ifstream bookingsFile("bookingRequests.csv");
    string line;
    getline(bookingsFile, line); // Skip header
    while (getline(bookingsFile, line)) {
        istringstream ss(line);
        vector<string> bookingDetails;
        string detail;
        while (getline(ss, detail, ',')) {
            bookingDetails.push_back(detail);
        }
        if (bookingDetails[14] == "Completed" && 
            (bookingDetails[11] == fullname || bookingDetails[13] == fullname)) {
            completedRides.push_back(bookingDetails);
        }
    }
    bookingsFile.close();

    if (completedRides.empty()) {
        cout << "No completed rides to rate.\n";
        return;
    }
    cout << "Completed rides:\n";
    for (size_t i = 0; i < completedRides.size(); ++i) {
        cout << i + 1 << ". " << completedRides[i][0] << " to " << completedRides[i][1]
                  << " on " << completedRides[i][3] << " at " << completedRides[i][2] << "\n";
    }
    int choice;
    cout << "Select a ride to rate (0 to cancel): ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (choice < 1 || choice > static_cast<int>(completedRides.size())) {
        cout << "Invalid choice. Rating cancelled.\n";
        return;
    }

    const auto& selectedRide = completedRides[choice - 1];
    string ratedUser = (selectedRide[11] == fullname) ? selectedRide[13] : selectedRide[11];
    string raterRole = (selectedRide[11] == fullname) ? "Driver" : "Passenger";

    // Get rating and review
    int ratingScore;
    string review;
    cout << "Rate " << ratedUser << " (1-5): ";
    cin >> ratingScore;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (ratingScore < 1 || ratingScore > 5) {
        cout << "Invalid rating. Must be between 1 and 5.\n";
        return;
    }
    cout << "Leave a review (optional): ";
    getline(cin, review);
    vector<string> memberLines;
    ifstream membersFile("members.csv");
    getline(membersFile, line); 
    memberLines.push_back(line);
    while (getline(membersFile, line)) {
        istringstream ss(line);
        vector<string> memberDetails;
        string detail;
        while (getline(ss, detail, ',')) {
            memberDetails.push_back(detail);
        }
        if (memberDetails[2] == ratedUser) {
            int currentRating = stoi(memberDetails[8]);
            int newRating = (currentRating + ratingScore) / 2; 
            memberDetails[8] = to_string(newRating);
            ostringstream updatedMember;
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
    ofstream outMembersFile("members.csv");
    for (const auto& memberLine : memberLines) {
        outMembersFile << memberLine << "\n";
    }
    outMembersFile.close();
    ofstream ratingsFile("ratings.csv", ios::app);
    ratingsFile << raterRole << "," << fullname << "," << ratedUser << "," 
                << ratingScore << "," << review << "\n";
    ratingsFile.close();

    cout << "Rating submitted successfully.\n";
}

void Member::purchaseCredits() {
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }

    cout << "Starting the purchase process...\n";

    string inputPassword;
    cout << "Please enter your password for verification: ";
    cin >> inputPassword;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  

    if (inputPassword != password) {
        cout << "Password verification failed. Purchase aborted.\n";
        return;
    }

    int purchaseAmount;
    cout << "Enter the amount of credits to purchase ($1 = 1 credit): ";
    cin >> purchaseAmount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  

    if (purchaseAmount <= 0) {
        cout << "Invalid amount. Purchase aborted.\n";
        return;
    }

    vector<string> lines;
    string line;
    bool updated = false;

    ifstream inFile("members.csv");
    if (!inFile.is_open()) {
        cerr << "Failed to open members file for reading.\n";
        return;
    }

    getline(inFile, line);  
    lines.push_back(line);  

    while (getline(inFile, line)) {
        vector<string> userDetails;
        stringstream ss(line);
        string detail;

        while (getline(ss, detail, ',')) {
            userDetails.push_back(detail);
        }

        if (userDetails[0] == username) {
            cout << "Updating credits for user: " << username << "\n";

            int currentCredits = stoi(userDetails[7]);
            currentCredits += purchaseAmount;
            userDetails[7] = to_string(currentCredits);
            stringstream updatedLine;
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

    ofstream outFile("members.csv", ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Failed to open members file for writing.\n";
        return;
    }

    for (const auto& eachLine : lines) {
        outFile << eachLine << "\n";
    }
    outFile.close();

    if (updated) {
        cout << "Purchase successful! " << purchaseAmount << " credits added to your account.\n";
    } else {
        cout << "User not found or update failed.\n";
    }
}
