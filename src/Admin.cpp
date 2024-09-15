#include "Admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>  
using namespace std;

Admin::Admin() : isAuthenticated(false) {}
void Admin::loadAdminData() {
    ifstream file("admin.csv");
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string username, password;
        getline(iss, username, ',');
        getline(iss, password, ',');
        if (username != "username") { 
            this->username = username;
            this->password = password;
        }
    }
    file.close();
}

bool Admin::login(const string& enteredUsername, const string& enteredPassword) {
    ifstream file("admin.csv");
    string line, username, password;
    getline(file, line);

    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, username, ',');
        getline(iss, password, ',');
        if (enteredUsername == username && enteredPassword == password) {
            isAuthenticated = true;
            cout << "Login successful.\n";
            file.close();
            return true;
        }
    }

    cout << "Login failed. Please check your username and password.\n";
    file.close();
    return false;
}

void Admin::viewAllUsers() const {
    if (!isAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }
    cout << "\nDisplaying all users:\n";
    ifstream file("members.csv");
    string line;
    getline(file, line);

    cout << left 
         << setw(15) << "Username" 
         << setw(15) << "Full Name" 
         << setw(15) << "Phone" 
         << setw(30) << "Email" 
         << setw(15) << "ID Type" 
         << setw(15) << "ID Number" 
         << setw(10) << "Credits" 
         << setw(7) << "Rating" << endl;
    cout << string(120, '-') << endl;

    while (getline(file, line)) {
        istringstream iss(line);
        string username, password, fullName, phoneNumber, email, idType, idNumber, credits, rating;
        getline(iss, username, ',');
        getline(iss, password, ',');
        getline(iss, fullName, ',');
        getline(iss, phoneNumber, ',');
        getline(iss, email, ',');
        getline(iss, idType, ',');
        getline(iss, idNumber, ',');
        getline(iss, credits, ',');
        getline(iss, rating, ',');
        
        cout << left << setw(15) << username << setw(15) << fullName << setw(15) << phoneNumber 
             << setw(30) << email << setw(15) << idType << setw(15) << idNumber 
             << setw(10) << credits << setw(7) << rating << endl;
    }
    file.close();
}



void Admin::viewAllCarpools() const {
    if (!isAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }
    cout << "\nDisplaying all carpool listings:\n";
    ifstream file("carpool.csv");
    string line;
    getline(file, line);

    cout << left 
         << setw(15) << "Departure" 
         << setw(15) << "Destination" 
         << setw(10) << "Time" 
         << setw(10) << "Date" 
         << setw(15) << "Vehicle Model"
         << setw(10) << "Color"
         << setw(12) << "Plate Number"
         << setw(7) << "Seats"
         << setw(13) << "Contribution"
         << setw(7) << "Rating"
         << setw(15) << "Driver Name"
         << setw(12) << "Booked Seats" << endl;
    cout << string(140, '-') << endl;

    while (getline(file, line)) {
        istringstream iss(line);
        string departure, destination, time, date, vehicleModel, color, plateNumber, seats, contribution, rating, driverName, bookedSeats;
        getline(iss, departure, ',');
        getline(iss, destination, ',');
        getline(iss, time, ',');
        getline(iss, date, ',');
        getline(iss, vehicleModel, ',');
        getline(iss, color, ',');
        getline(iss, plateNumber, ',');
        getline(iss, seats, ',');
        getline(iss, contribution, ',');
        getline(iss, rating, ',');
        getline(iss, driverName, ',');
        getline(iss, bookedSeats, ',');

        cout << left 
             << setw(15) << departure 
             << setw(15) << destination 
             << setw(10) << time 
             << setw(10) << date 
             << setw(15) << vehicleModel
             << setw(10) << color
             << setw(12) << plateNumber
             << setw(7) << seats
             << setw(13) << contribution
             << setw(7) << rating
             << setw(15) << driverName
             << setw(12) << bookedSeats << endl;
    }
    file.close();
}


