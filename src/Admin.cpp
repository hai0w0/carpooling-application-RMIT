#include "Admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
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
    cout << "Displaying all users:\n";
    ifstream file("members.csv");
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void Admin::viewAllCarpools() const {
    if (!isAuthenticated) {
        cout << "Access denied. Please log in first.\n";
        return;
    }
    cout << "Displaying all carpool listings:\n";
    ifstream file("carpool.csv");
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

bool Admin::validateCredentials(const string& username, const string& password) const {
    return this->username == username && this->password == password;
}
