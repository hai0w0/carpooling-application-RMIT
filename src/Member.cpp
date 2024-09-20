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

// Constructor for the Member class, initializing isAuthenticated to false
Member::Member() : isMemberAuthenticated(false) {}

// Loads member data from a CSV file into a map.
void Member::loadMemberData() {
    ifstream file("members.csv");
    string line;
    getline(file, line); // Discard the header line
    while (getline(file, line)) {
        istringstream iss(line);
        string username, password;

        // Extract username and password
        getline(iss, username, ',');
        getline(iss, password, ',');
        memberCredentials[username] = {username, password};
    }
    file.close();
}

// Validates whether the provided username and password match the stored credentials.
bool Member::validateCredentials(const string& username, const string& password) const {
    auto it = memberCredentials.find(username); // Attempt to find the username in the memberCredentials map.

    // Check if the iterator does not point to the end of the map, which means the username was found.
    // Then, check if the associated password matches the one provided.
    // The second element of the map's value pair (username, password pair) is checked against the provided password.
    return it != memberCredentials.end() && it->second.second == password;
}

string Member::getUserName() const {
    return username; // Get the member's username
}

// Handles the member login process by validating credentials and retrieving additional member data.
bool Member::login(const string& inputUsername, const string& inputPassword) {

    // Check if the provided username and password are valid using the validateCredentials method.
    if (validateCredentials(inputUsername, inputPassword)) {
        isMemberAuthenticated = true; // Set the authentication flag to true upon successful validation.

        // Store the authenticated username and password for the current session.
        username = inputUsername;
        password = inputPassword;
        ifstream file("members.csv");
        string line, user, pass, name;
        getline(file, line); // Skip the header

        // Iterate through the file line by line to find the corresponding member record.
        while (getline(file, line)) {
            istringstream iss(line); // Use a string stream to parse each line.
            // Extract the username, password, and full name fields from the current line.
            getline(iss, user, ',');
            getline(iss, pass, ',');
            getline(iss, name, ',');

            // If the current line matches the authenticated username and password, extract the full name.
            if (user == username && pass == password) {
                fullname = name;  
                break; // Break out of the loop since we found the matching record.
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

// Function to view the profile of an authenticated member.
void Member::viewProfile() const {
    if (!isMemberAuthenticated) { // Check if the member is authenticated.
        cout << "Access denied. Please log in first.\n";
        return;
    }

    // Open the "members.csv" file to read profile data.
    ifstream file("members.csv");
    if (!file.is_open()) {
        cerr << "Error: Failed to open profile data file.\n";
        return;
    }

    string line;
    bool found = false;
    getline(file, line); // Skip the header line
    while (getline(file, line)) {
        istringstream ss(line);
        vector<string> userDetails;
        string detail;

        // Parse the current line into components based on commas.
        while (getline(ss, detail, ',')) {
            userDetails.push_back(detail);
        }

        // Check if the current line's username matches the authenticated user's username.
        if (userDetails.size() >= 7 && userDetails[0] == username) {
            found = true;

            // Display the profile information.
            cout << "\n=============== Your Profile Information ===============\n";
            cout << left << setw(20) << "Username:" << userDetails[0] << "\n";
            cout << left << setw(20) << "Full Name:" << userDetails[2] << "\n";
            cout << left << setw(20) << "Phone Number:" << userDetails[3] << "\n";
            cout << left << setw(20) << "Email:" << userDetails[4] << "\n";
            cout << left << setw(20) << "ID Type:" << userDetails[5] << "\n";
            cout << left << setw(20) << "ID Number:" << userDetails[6] << "\n";
            cout << left << setw(20) << "Credit Points:" << userDetails[7] << "\n";
            cout << left << setw(20) << "Rating:" << userDetails[8] << "\n";
            cout << "========================================================\n";
            break; // Exit the loop after finding and displaying the profile.
        }
    }

    file.close();

    // If no profile is found for the username, display an error message.
    if (!found) {
        cerr << "Error: User profile not found in the database.\n";
    }
}

// Define editing profile details function
void Member::editProfile() {
    if (!isMemberAuthenticated) { // Check if the member is authenticated
        cout << "Access denied. Please log in first.\n";
        return;
    }

    vector<string> lines; // Container to hold lines read from the file
    string line;
    bool found = false; // Flag to indicate if the user is found in the file

    ifstream inFile("members.csv"); // Open the members.csv file
    if (!inFile.is_open()) {
        cout << "Failed to open members file.\n";
        return; // Exit the function if file cannot be opened
    }

    // Read lines from the file and store them in the vector
    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    // Iterate through each line to find the user's details
    for (auto& line : lines) {
        istringstream iss(line);
        vector<string> userDetails;
        string detail;
        // Split the line into individual details
        while (getline(iss, detail, ',')) {
            userDetails.push_back(detail);
        }
        // Check if matches the member's username
        if (userDetails[0] == username) { 
            found = true;
             // Display options for updating the profile
            cout << "Select an option to update:\n";
            cout << "1. Password\n";
            cout << "2. Phone Number\n";
            cout << "3. Email\n";
            cout << "0. Cancel\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;
            cin.ignore(); // Ignore the newline after the integer input

            switch (choice) { // Process the choice made by the user
                case 1:
                    cout << "Enter new password: ";
                    getline(cin, userDetails[1]);
                    cout << "Password has been updated successfully. Please restart app to use new password.\n";
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

    // If the user was found and the profile was updated, rewrite the file with updated data
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

// Handles the process of booking a carpool for the authenticated member
void Member::bookCarpool() {
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }

    int memberCredits = 0;
    int memberRating = 0;
    string fullName;
    ifstream memberFile("members.csv"); // Load member details from the CSV file
    string memberLine;
    getline(memberFile, memberLine);
    while (getline(memberFile, memberLine)) {
        istringstream memberSS(memberLine);
        vector<string> memberDetails;
        string memberDetail;
        // Parse the member details from each line
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

    // Load eligible carpools from the carpool CSV file
    vector<vector<string>> eligibleCarpools;
    ifstream carpoolFile("carpool.csv");
    string carpoolLine;
    getline(carpoolFile, carpoolLine); 
    while (getline(carpoolFile, carpoolLine)) {
        istringstream carpoolSS(carpoolLine);
        vector<string> carpoolDetails;
        string carpoolDetail;
        // Parse the carpool details from each line
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
    // Function to display available carpools
    auto displayCarpools = [](const vector<vector<string>>& carpools) {
        for (size_t i = 0; i < carpools.size(); i++) {
            const auto& carpool = carpools[i];
            cout << i + 1 << ". Route: " << carpool[0] << " to " << carpool[1]
                 << ", Departure: " << carpool[2] << " on " << carpool[3]
                 << ", Vehicle: " << carpool[4] << " (" << carpool[5] << ", " << carpool[6] << ")"
                 << ", Seats Available: " << (stoi(carpool[7]) - stoi(carpool[12]))
                 << ", Price per Seat: $" << carpool[8]
                 << ", Driver Rating: " << carpool[9]
                 << ", Driver: " << carpool[11] << "\n";
        }
    };
    // Function to filter carpools based on user criteria
    auto getFilteredCarpools = [&](const vector<vector<string>>& carpools,
                                   const string& departure, const string& destination,
                                   int maxPrice, int minDriverRating) {
        vector<vector<string>> filtered;
        for (const auto& carpool : carpools) {
            if ((!departure.empty() && carpool[0] != departure) ||
                (!destination.empty() && carpool[1] != destination) ||
                (maxPrice > 0 && stoi(carpool[8]) > maxPrice) ||
                (minDriverRating > 0 && stoi(carpool[9]) < minDriverRating)) {
                continue; // Skip carpools that do not meet the criteria
            }
            filtered.push_back(carpool); // Add the carpool to the filtered list
        }
        return filtered;
    };

    // Interactive loop for carpool booking options
    while (true) {
        if (eligibleCarpools.empty()) {
            cout << "No eligible carpools available.\n";
            return;
        }
        cout << "Available carpools that you can request:\n";
        displayCarpools(eligibleCarpools); // Display the eligible carpools

        cout << "\nOptions:\n";
        cout << "1. Book a carpool\n";
        cout << "2. Filter carpools\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        // Handle User choice
        int choice; 
        while (!(cin >> choice) || choice < 1 || choice > 3) {
            cout << "Invalid input. Please enter a number between 1 and 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            cout << "Enter the number of the carpool you want to book (0 to cancel): ";
            int bookingChoice;
            while (!(cin >> bookingChoice) || bookingChoice < 0 || bookingChoice > static_cast<int>(eligibleCarpools.size())) {
                cout << "Invalid input. Please enter a number between 0 and " << eligibleCarpools.size() << ": ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (bookingChoice == 0) {
                cout << "Booking cancelled.\n";
                continue;
            }

            // Proceed with booking request
            const auto& selectedCarpool = eligibleCarpools[bookingChoice - 1];
            ofstream bookingFile("bookingRequests.csv", ios::app); // Open booking file for appending
            for (size_t i = 0; i < selectedCarpool.size(); ++i) {
                bookingFile << selectedCarpool[i];
                if (i < selectedCarpool.size() - 1) bookingFile << ",";
            }
            bookingFile << "," << fullName << ",Pending\n"; // Append the user's name and Booking status
            bookingFile.close();
            cout << "Booking request created successfully. Status: Pending.\n";
            return;
        } else if (choice == 2) {
            // Handle filtering of carpools
            string departure, destination;
            int maxPrice, minDriverRating;

            // Helper function to validate and get location input
            auto getValidLocation = [](const string& prompt, const vector<string>& validLocations) -> string {
                string input;
                do {
                    cout << prompt;
                    getline(cin, input);
                    bool isValid = any_of(validLocations.begin(), validLocations.end(), [&](const string& validLocation) {
                        return input == validLocation;
                    });
                    if (!isValid && !input.empty()) {
                        cout << "Invalid location. Please enter one of the allowed cities (Hanoi, Danang, Hue, Ho Chi Minh City) or leave blank for no filter.\n";
                    } else {
                        return input; // Return the valid input
                    }
                } while (true);
            };

            vector<string> validLocations = {"Hanoi", "Danang", "Hue", "Ho Chi Minh City", "hanoi", "danang", "hue", "ho chi minh city"};
            departure = getValidLocation("Enter departure location (Hanoi, Danang, Hue, Ho Chi Minh City)(or leave blank for no filter): ", validLocations);
            destination = getValidLocation("Enter destination location (Hanoi, Danang, Hue, Ho Chi Minh City)(or leave blank for no filter): ", validLocations);

            if (!departure.empty() && !destination.empty() && departure == destination) {
                cout << "Error: Departure and destination locations cannot be the same.\n";
                continue; // Restart the loop for another action
            }

            cout << "Enter maximum price per seat that you want to pay (0 for no limit): ";
            while (!(cin >> maxPrice) || maxPrice < 0) {
                cout << "Invalid input. Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter minimum Driver's rating (0 for no limit): ";
            while (!(cin >> minDriverRating) || minDriverRating < 0 || minDriverRating > 5) {
                cout << "Invalid input. Please enter a number between 0 and 5: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            auto filteredCarpools = getFilteredCarpools(eligibleCarpools, departure, destination, maxPrice, minDriverRating);
            if (!filteredCarpools.empty()) {
                eligibleCarpools = filteredCarpools;
                cout << "\nFiltered carpools:\n";
                displayCarpools(eligibleCarpools);
            } else {
                cout << "No carpools match your filters.\n";
            }
        } else if (choice == 3) {
            return;
        }
    }
}

void Member::manageBookings() {
    // Check if the member is authenticated
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }

    // Open the bookings file
    ifstream bookingsFile("bookingRequests.csv");
    if (!bookingsFile.is_open()) {
        cout << "Failed to open booking requests file.\n";
        return;
    }

    // Read the file contents
    string line;
    getline(bookingsFile, line); // Skip header line
    vector<string> bookingLines;
    vector<string> userBookings;

    // Store all booking lines in a vector
    while (getline(bookingsFile, line)) {
        bookingLines.push_back(line);
    }
    bookingsFile.close();

    // Process bookings and display user's pending bookings
    int displayedIndex = 1;
    vector<int> mappingIndex;
    for (int i = 0; i < bookingLines.size(); i++) {
        istringstream ss(bookingLines[i]);
        vector<string> bookingDetails;
        string detail;
        while (getline(ss, detail, ',')) {
            bookingDetails.push_back(detail);
        }

        // Check if the booking belongs to the current user and is pending
        if (bookingDetails[13] == fullname && bookingDetails[14] == "Pending") {
            ostringstream bookingInfo;
            bookingInfo << "Booking " << displayedIndex << ": "
                        << "Date: " << bookingDetails[3]
                        << ", Time: " << bookingDetails[2]
                        << ", Departure: " << bookingDetails[0]
                        << ", Destination: " << bookingDetails[1]
                        << ", Driver: " << bookingDetails[11]
                        << ", Status: " << bookingDetails[14];
            userBookings.push_back(bookingInfo.str());
            mappingIndex.push_back(i);
            displayedIndex++;
        }
    }

    // Display options and handle user input
    int choice;
    do {
        // Check if user has any active bookings
        if (userBookings.empty()) {
            cout << "You have no active bookings. Try booking a carpool now!\n";
            break;
        }

        // Display active bookings
        cout << "This is your current active bookings:\n---------------\n";
        for (const auto& booking : userBookings) {
            cout << booking << "\n";
        }

        // Display menu options
        cout << "\nOptions:\n";
        cout << "1. Unlist a booking\n";
        cout << "2. Back to menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Handle user choice
        if (choice == 1) {
            int bookingNumber;
            cout << "Enter the booking number to unlist: ";
            cin >> bookingNumber;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Process unlisting request
            if (bookingNumber > 0 && bookingNumber <= mappingIndex.size()) {
                int actualIndex = mappingIndex[bookingNumber - 1];
                bookingLines.erase(bookingLines.begin() + actualIndex);

                // Update the bookings file
                ofstream outFile("bookingRequests.csv");
                for (const auto& l : bookingLines) {
                    outFile << l << "\n";
                }
                outFile.close();
                cout << "Booking unlisted successfully.\n";
                break;
            } else if (bookingNumber == 0){
                cout << "Unlist Booking is cancelled.\n";
                break;
            }else{
                cout << "Invalid booking number entered.\n";
            }
        }
    } while (choice != 2);
}


void Member::listCarpool() {
    // Check if the member is authenticated
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }

    // Declare variables for carpool listing details
    string departureLocation, destinationLocation, departureTime, departureDate;
    string vehicleModel, vehicleColor, plateNumber;
    int availableSeats, contributionPerPassenger, minimumPassengerRating;
    int driverRating = 0;
    string fullName;

    // Fetch driver's rating and full name from members.csv
    ifstream memberFile("members.csv");
    string memberLine;
    getline(memberFile, memberLine); // Skip header line
    while (getline(memberFile, memberLine)) {
        istringstream memberSS(memberLine);
        vector<string> memberDetails;
        string memberDetail;
        while (getline(memberSS, memberDetail, ',')) {
            memberDetails.push_back(memberDetail);
        }
        if (memberDetails[0] == this->username) {
            driverRating = stoi(memberDetails[8]);
            fullName = memberDetails[2];
            break;
        }
    }
    memberFile.close();

    // Check if driver's rating is sufficient to list a carpool
    if (driverRating == -1) {
        cout << "Your rating needs to be 1 or higher to list a carpool. Please complete some rides as a passenger first.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Lambda function to get valid location input
    auto getValidLocation = [](const string& prompt, const vector<string>& validLocations) -> string {
        string input;
        do {
            cout << prompt;
            getline(cin, input);
            bool isValid = any_of(validLocations.begin(), validLocations.end(), [&](const string& validLocation) {
                return input == validLocation;
            });
            if (!isValid) {
                cout << "Invalid location. Please enter one of the allowed cities (Hanoi, Danang, Hue, Ho Chi Minh City).\n";
            } else {
                return input;
            }
        } while (true);
    };

    // Get departure and destination locations
    vector<string> validLocations = {"Hanoi", "Danang", "Hue", "Ho Chi Minh City"};
    departureLocation = getValidLocation("Enter departure location, correctly spelling the cities (Hanoi, Danang, Hue, Ho Chi Minh City): ", validLocations);
    destinationLocation = getValidLocation("Enter destination location, correctly spelling the cities (Hanoi, Danang, Hue, Ho Chi Minh City): ", validLocations);

    // Check if departure and destination are different
    if (departureLocation == destinationLocation) {
        cout << "Error: Departure and destination locations cannot be the same.\n";
        return;
    }

    // Lambda function to get valid time input
    auto getValidTime = []() -> string {
        string input;
        while (true) {
            cout << "Enter departure time (e.g., 9:00 AM): ";
            getline(cin, input);
            istringstream ss(input);
            int hours, minutes;
            char colon, ampm[3];
            if (ss >> hours >> colon >> minutes >> ampm &&
                colon == ':' && hours >= 1 && hours <= 12 && minutes >= 0 && minutes <= 59 &&
                (strcmp(ampm, "AM") == 0 || strcmp(ampm, "PM") == 0)) {
                return input;
            }
            cout << "Invalid time format. Please use HH:MM AM/PM format.\n";
        }
    };
    departureTime = getValidTime();

    // Lambda function to get valid date input
    auto getValidDate = []() -> string {
        string input;
        while (true) {
            cout << "Enter departure date (YYYY-MM-DD) (In the year of 2024 only): ";
            getline(cin, input);
            istringstream ss(input);
            int year, month, day;
            char dash1, dash2;
            if (ss >> year >> dash1 >> month >> dash2 >> day &&
                dash1 == '-' && dash2 == '-' &&
                year >= 2024 && month >= 1 && month <= 12 && day >= 1 && day <= 31) {
                return input;
            }
            cout << "Invalid date format. Please use YYYY-MM-DD format.\n";
        }
    };
    departureDate = getValidDate();

    // Get vehicle details
    cout << "Enter vehicle model: ";
    getline(cin, vehicleModel);

    cout << "Enter vehicle color: ";
    getline(cin, vehicleColor);

    cout << "Enter plate number: ";
    getline(cin, plateNumber);

    // Lambda function to get valid numeric input
    auto getValidNumber = [](const string& prompt, int min, int max) -> int {
        int value;
        while (true) {
            cout << prompt;
            if (cin >> value && value >= min && value <= max) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    };

    // Get carpool details
    availableSeats = getValidNumber("Enter number of available seats (1-10): ", 1, 50);
    contributionPerPassenger = getValidNumber("Enter contribution per passenger (1-100): ", 1, 100);
    minimumPassengerRating = getValidNumber("Enter minimumPassengerRating (-1-5) (-1 if you allow new members to request your carpool): ", -1, 5);

    // Save carpool listing to carpool.csv
    ofstream outFile("carpool.csv", ios::app);
    outFile << departureLocation << ',' << destinationLocation << ',' << departureTime << ','
            << departureDate << ',' << vehicleModel << ',' << vehicleColor << ',' << plateNumber << ','
            << availableSeats << ',' << contributionPerPassenger << ',' << driverRating << ','
            << minimumPassengerRating << ',' << fullName << ',' << "0" << '\n';
    outFile.close();

    cout << "Carpool listing created successfully!\n";
}


void Member::unlistCarpool() {
    // Check if the member is authenticated
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }
    
    vector<string> carpools;
    vector<int> driverCarpoolIndices;
    ifstream carpoolFile("carpool.csv");
    string line;
    getline(carpoolFile, line); 
    carpools.push_back(line); // Store header line
    int index = 1;
    
    // Read and process carpool listings
    while (getline(carpoolFile, line)) {
        istringstream iss(line);
        vector<string> details;
        string detail;
        while (getline(iss, detail, ',')) {
            details.push_back(detail);
        }
        
        carpools.push_back(line);
        
        // Display carpools listed by the current user
        if (details[11] == fullname) { 
            cout << index << ". " 
                      << "From: " << details[0] << ", To: " << details[1]
                      << ", Date: " << details[3] << ", Time: " << details[2] << "\n";
            driverCarpoolIndices.push_back(carpools.size() - 1);
            index++;
        }
    }
    carpoolFile.close();
    
    // Check if the user has any active carpool listings
    if (driverCarpoolIndices.empty()) {
        cout << "You have no active carpool listings.\n";
        return;
    }
    
    // Get user's choice for unlisting
    int choice;
    cout << "Enter the number of the carpool you want to unlist (0 to cancel): ";
    cin >> choice;
    
    // Validate user's choice
    if (choice < 1 || choice > driverCarpoolIndices.size()) {
        cout << "Invalid choice. Unlisting cancelled.\n";
        return;
    }
    
    // Get the selected carpool
    int selectedIndex = driverCarpoolIndices[choice - 1];
    string selectedCarpool = carpools[selectedIndex];
    
    // Check for accepted requests
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
    
    // Prevent unlisting if there are accepted requests
    if (hasAcceptedRequests) {
        cout << "Cannot unlist this carpool as it has accepted requests.\n";
        return;
    }
    
    // Remove the selected carpool from the list
    carpools.erase(carpools.begin() + selectedIndex);
    
    // Update the carpool.csv file
    ofstream outFile("carpool.csv");
    for (const auto& carpool : carpools) {
        outFile << carpool << "\n";
    }
    outFile.close();
    
    cout << "Carpool successfully unlisted.\n";
}


void Member::manageRequests() {
    // Check if the member is authenticated
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }

    vector<string> bookings;
    ifstream file("bookingRequests.csv");
    if (!file.is_open()) {
        cout << "Failed to open booking requests file.\n";
        return;
    }

    // Read all booking requests into memory
    string line;
    while (getline(file, line)) {
        bookings.push_back(line);
    }
    file.close();

    // Lambda function to display active booking requests
    auto DisplayBookings = [&]() {
        cout << "Active booking requests:\n";
        cout << "------------------------\n";
        int displayIndex = 1;
        vector<int> indexMap;
        for (int i = 0; i < bookings.size(); i++) {
            istringstream ss(bookings[i]);
            vector<string> details;
            string token;
            while (getline(ss, token, ',')) {
                details.push_back(token);
            }
            // Display only pending requests for the current member
            if (details[11] == fullname && (details[14] == "pending" || details[14] == "Pending")) {
                cout << "Booking " << displayIndex++ << ": "
                     << "Passenger: " << details[13]
                     << ", Date: " << details[3]
                     << ", Time: " << details[2]
                     << ", Departure: " << details[0]
                     << ", Destination: " << details[1]
                     << ", Status: " << details[14] << '\n';
                indexMap.push_back(i);
            }
        }
        if (displayIndex == 1) {
            cout << "You have no active booking requests.\n";
        }
        return indexMap;
    };

    // Main loop for managing requests
    while (true) {
        vector<int> indexMap = DisplayBookings();

        cout << "Options:\n";
        cout << "1. Accept a booking\n";
        cout << "2. Reject a booking\n";
        cout << "3. Back to menu\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1 || choice == 2) {
            cout << "Enter the booking number to modify: ";
            int bookingNumber;
            cin >> bookingNumber;

            // Validate booking number
            if (bookingNumber < 1 || bookingNumber > indexMap.size()) {
                cout << "Invalid booking number. Please try again.\n";
                continue;
            }

            // Update the status of the selected booking
            int actualIndex = indexMap[bookingNumber - 1];
            string& selectedBooking = bookings[actualIndex];
            size_t lastComma = selectedBooking.rfind(',');
            selectedBooking.replace(lastComma + 1, string::npos, choice == 1 ? "Accepted" : "Rejected");

            // Write changes back to the file
            ofstream outFile("bookingRequests.csv");
            for (const auto& line : bookings) {
                outFile << line << "\n";
            }
            outFile.close();

            cout << "Booking has been " << (choice == 1 ? "accepted" : "rejected") << ".\n";
            system("cls");
        } else if (choice == 3) {
            break;
        }
    }
}

void Member::confirmCarpoolRides() {
    // Check if the member is authenticated
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }

    // Open and read the bookings file
    ifstream bookingsFile("bookingRequests.csv");
    if (!bookingsFile.is_open()) {
        cout << "Failed to open booking requests file.\n";
        return;
    }
    string line;
    getline(bookingsFile, line); // Read header
    map<string, vector<string>> carpoolGroups;
    vector<string> allBookings;
    allBookings.push_back(line); // Store header
    
    // Process each booking
    while (getline(bookingsFile, line)) {
        istringstream ss(line);
        vector<string> bookingDetails;
        string detail;
        while (getline(ss, detail, ',')) {
            bookingDetails.push_back(detail);
        }

        // Group accepted bookings by trip details
        if (bookingDetails[11] == fullname && bookingDetails[14] == "Accepted") {
            string tripKey = bookingDetails[0] + "|" + bookingDetails[1] + "|" + bookingDetails[2] + "|" + bookingDetails[3];
            carpoolGroups[tripKey].push_back(line);
        }
        allBookings.push_back(line);
    }
    bookingsFile.close();

    // Check if there are any accepted rides to confirm
    if (carpoolGroups.empty()) {
        cout << "No accepted carpool rides to confirm.\n";
        return;
    }

    // Display accepted carpool rides
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
        // Process completed ride
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

        // Update booking statuses
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

        // Write updated bookings back to file
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

        // Update carpool.csv
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

            // Write updated carpool details back to file
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
    vector<string> lines;  // To store all lines from members.csv
    string line;  // Temporary string to hold each line read from the file
    
    // Open the members.csv file for reading
    ifstream inFile("members.csv");
    if (!inFile.is_open()) {
        // If file can't be opened, display an error message and return
        cout << "Failed to open members.csv for reading.\n";
        return;
    }
    
    // Read each line from the file and store it in the 'lines' vector
    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();  // Close the file after reading
    
    // Flags to track whether both users are found
    bool fromUserFound = false, toUserFound = false;
    
    // Loop through each line in the vector
    for (auto& line : lines) {
        istringstream iss(line);  // String stream to parse the line
        vector<string> userDetails;  // Vector to hold details of a single user
        string detail;  // Temporary string to hold each value (separated by commas)
        
        // Split the line by commas and push each part into userDetails
        while (getline(iss, detail, ',')) {
            userDetails.push_back(detail);
        }
        
        // Check if the line contains enough details (assuming index 7 is credits)
        if (userDetails.size() > 7) {
            // Check if this line corresponds to the 'fromUser'
            if (userDetails[2] == fromUser) {
                int currentCredits = stoi(userDetails[7]);  // Convert string to integer
                userDetails[7] = to_string(currentCredits - amount);  // Deduct amount
                fromUserFound = true;  // Mark that 'fromUser' was found
            } 
            // Check if this line corresponds to the 'toUser'
            else if (userDetails[2] == toUser) {
                int currentCredits = stoi(userDetails[7]);  // Convert string to integer
                userDetails[7] = to_string(currentCredits + amount);  // Add amount
                toUserFound = true;  // Mark that 'toUser' was found
            }
            
            // If either user was updated, reassemble the line with updated details
            if (fromUserFound || toUserFound) {
                ostringstream oss;  // Output string stream to rebuild the line
                for (size_t i = 0; i < userDetails.size(); ++i) {
                    if (i > 0) oss << ",";  // Add commas between details
                    oss << userDetails[i];  // Add each user detail back to the line
                }
                line = oss.str();  // Update the line with the modified details
            }
        }
        
        // If both users are found, stop searching
        if (fromUserFound && toUserFound) break;
    }
    
    // If either user was not found, display an error and exit
    if (!fromUserFound || !toUserFound) {
        cout << "Error: One or both users not found.\n";
        return;
    }
    
    // Open the members.csv file for writing (overwrite mode)
    ofstream outFile("members.csv");
    if (!outFile.is_open()) {
        // If the file can't be opened, display an error message and return
        cout << "Failed to open members.csv for writing.\n";
        return;
    }
    
    // Write each updated line back to the file
    for (const auto& updatedLine : lines) {
        outFile << updatedLine << "\n";
    }
    outFile.close();  // Close the file after writing
    
    // Inform the user that the transfer was successful
    cout << "Credits transferred successfully.\n";
}


void Member::rating() {
    // Check if the user is authenticated
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }

    vector<vector<string>> completedRides;  // To store completed rides that haven't been rated
    map<string, bool> ratedRides;  // Map to track already rated rides

    // Open file to check for already rated rides
    ifstream ratedFile("ratedRides.csv");
    string ratedLine;
    // Read each line from the file and mark it as rated
    while (getline(ratedFile, ratedLine)) {
        ratedRides[ratedLine] = true;
    }
    ratedFile.close();

    // Open booking requests file to find completed rides
    ifstream bookingsFile("bookingRequests.csv");
    string line;
    getline(bookingsFile, line); // Skip the header line
    // Read each booking request to find completed rides involving the authenticated user
    while (getline(bookingsFile, line)) {
        istringstream ss(line);
        vector<string> bookingDetails;
        string detail;
        while (getline(ss, detail, ',')) {
            bookingDetails.push_back(detail);
        }
        // Check if the ride is marked as "Completed" and if the user is involved
        if (bookingDetails[14] == "Completed" && 
            (bookingDetails[11] == fullname || bookingDetails[13] == fullname)) {
            // Construct a unique identifier for the ride to avoid double rating
            string rideIdentifier = fullname + "," + bookingDetails[0] + "," + bookingDetails[1] + "," + bookingDetails[3] + "," + bookingDetails[2] + "," + (bookingDetails[11] == fullname ? bookingDetails[13] : bookingDetails[11]);
            if (ratedRides.find(rideIdentifier) == ratedRides.end()) {
                completedRides.push_back(bookingDetails);
            }
        }
    }
    bookingsFile.close();

    // If no new rides are available to rate
    if (completedRides.empty()) {
        cout << "No new completed rides to rate.\n";
        return;
    }

    // Display the list of completed rides available for rating
    cout << "Completed rides available for rating:\n";
    for (size_t i = 0; i < completedRides.size(); ++i) {
        // Identify the other user involved in the ride
        string otherUser = (completedRides[i][11] == fullname) ? completedRides[i][13] : completedRides[i][11];
        // Determine if the user is rating a driver or a passenger
        string roleBeingRated = (completedRides[i][11] == fullname) ? "Passenger" : "Driver";
        // Display the ride information
        cout << i + 1 << ". " << completedRides[i][0] << " to " << completedRides[i][1]
             << " on " << completedRides[i][3] << " at " << completedRides[i][2]
             << " with " << otherUser << " as " << roleBeingRated << "\n";
    }

    // Prompt user to select a ride to rate
    int choice;
    cout << "Select a person to rate (0 to cancel): ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Validate user input
    if (choice < 1 || choice > static_cast<int>(completedRides.size())) {
        cout << "Rating is cancelled.\n";
        return;
    }

    // Extract details of the selected ride
    const auto& selectedRide = completedRides[choice - 1];
    string ratedUser = (selectedRide[11] == fullname) ? selectedRide[13] : selectedRide[11];
    string raterRole = (selectedRide[11] == fullname) ? "Driver" : "Passenger";

    // Prompt user for rating and review
    int ratingScore;
    string review;
    cout << "Rate " << ratedUser << " (1-5): ";
    cin >> ratingScore;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Validate rating score
    if (ratingScore < 1 || ratingScore > 5) {
        cout << "Invalid rating. Must be between 1 and 5.\n";
        return;
    }
    // Optional review input
    cout << "Leave a review (optional): ";
    getline(cin, review);

    // Read members.csv and update the rating of the rated user
    vector<string> memberLines;
    ifstream membersFile("members.csv");
    getline(membersFile, line);  // Read header
    memberLines.push_back(line);
    // Read each member's data
    while (getline(membersFile, line)) {
        istringstream ss(line);
        vector<string> memberDetails;
        string detail;
        while (getline(ss, detail, ',')) {
            memberDetails.push_back(detail);
        }
        // If the rated user is found, update their rating
        if (memberDetails[2] == ratedUser) {
            int currentRating = stoi(memberDetails[8]);
            int newRating = (currentRating + ratingScore) / 2;  // Average the new rating
            memberDetails[8] = to_string(newRating);
            ostringstream updatedMember;
            // Reassemble the member line
            for (size_t i = 0; i < memberDetails.size(); ++i) {
                updatedMember << memberDetails[i];
                if (i < memberDetails.size() - 1) updatedMember << ",";
            }
            memberLines.push_back(updatedMember.str());
        } else {
            memberLines.push_back(line);  // Keep the original line if no update
        }
    }
    membersFile.close();

    // Write the updated members.csv file
    ofstream outMembersFile("members.csv");
    for (const auto& memberLine : memberLines) {
        outMembersFile << memberLine << "\n";
    }
    outMembersFile.close();

    // Log the rating in the ratings.csv file
    ofstream ratingsFile("ratings.csv", ios::app);
    ratingsFile << raterRole << "," << fullname << "," << ratedUser << "," 
                << ratingScore << "," << review << "\n";
    ratingsFile.close();

    // Mark the ride as rated by adding it to ratedRides.csv
    ofstream ratedRidesFile("ratedRides.csv", ios::app);
    ratedRidesFile << fullname << "," << selectedRide[0] << "," << selectedRide[1] << "," 
                   << selectedRide[3] << "," << selectedRide[2] << "," << ratedUser << "\n";
    ratedRidesFile.close();

    cout << "Rating submitted successfully.\n";
}


void Member::purchaseCredits() {
    // Check if the user is authenticated
    if (!isMemberAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }

    cout << "Starting the purchase process...\n";

    // Prompt user to enter password for verification
    string inputPassword;
    cout << "Please enter your password for verification (New password will not work until you restart the app!): ";
    cin >> inputPassword;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer

    // Verify if the entered password matches the stored password
    if (inputPassword != password) {
        cout << "Password verification failed. Purchase aborted.\n";
        return;
    }

    // Ask for the number of credits the user wants to purchase
    int purchaseAmount;
    cout << "Enter the amount of credits to purchase ($1 = 1 credit): ";
    cin >> purchaseAmount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer

    // Validate that the purchase amount is a positive number
    if (purchaseAmount <= 0) {
        cout << "Invalid amount. Purchase aborted.\n";
        return;
    }

    vector<string> lines;  // Vector to hold all lines from the members.csv file
    string line;  // Temporary string to hold each line read from the file
    bool updated = false;  // Flag to check if the user's credits were updated

    // Open the members.csv file for reading
    ifstream inFile("members.csv");
    if (!inFile.is_open()) {
        cerr << "Failed to open members file for reading.\n";
        return;
    }

    getline(inFile, line);  // Read and store the header line
    lines.push_back(line);  // Keep the header line in the vector

    // Read each line and check if it corresponds to the authenticated user
    while (getline(inFile, line)) {
        vector<string> userDetails;
        stringstream ss(line);
        string detail;

        // Split the line by commas and push each detail into the vector
        while (getline(ss, detail, ',')) {
            userDetails.push_back(detail);
        }

        // If the current line is the authenticated user's record
        if (userDetails[0] == username) {
            cout << "Updating credits for user: " << username << "\n";

            // Update the user's credits by adding the purchase amount
            int currentCredits = stoi(userDetails[7]);
            currentCredits += purchaseAmount;
            userDetails[7] = to_string(currentCredits);

            // Reassemble the line with the updated credits
            stringstream updatedLine;
            for (size_t i = 0; i < userDetails.size(); i++) {
                updatedLine << userDetails[i];
                if (i < userDetails.size() - 1) updatedLine << ",";
            }
            line = updatedLine.str();  // Replace the line with the updated version
            updated = true;  // Mark that the user was updated
        }
        lines.push_back(line);  // Add the (possibly updated) line to the vector
    }
    inFile.close();  // Close the input file

    // Open the members.csv file for writing (overwrite mode)
    ofstream outFile("members.csv", ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Failed to open members file for writing.\n";
        return;
    }

    // Write each line from the vector back to the file
    for (const auto& eachLine : lines) {
        outFile << eachLine << "\n";
    }
    outFile.close();  // Close the output file

    // Notify the user if the purchase was successful or if the update failed
    if (updated) {
        cout << "Purchase successful! " << purchaseAmount << " credits added to your account.\n";
    } else {
        cout << "User not found or update failed.\n";
    }
}
