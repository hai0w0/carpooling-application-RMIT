#include "Admin.h"
#include <iostream>
#include <fstream>
#include <sstream>

Admin::Admin() : isAuthenticated(false) {}

void Admin::loadAdminData() {
    std::ifstream file("admin.csv");
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

bool Admin::login(const std::string& username, const std::string& password) {
    if (validateCredentials(username, password)) {
        isAuthenticated = true;
        std::cout << "Login successful.\n";
        return true;
    } else {
        std::cout << "Login failed. Please check your username and password.\n";
        return false;
    }
}

void Admin::viewAllUsers() const {
    if (!isAuthenticated) {
        std::cout << "Access denied. Please log in first.\n";
        return;
    }
    std::cout << "Displaying all users:\n";
    std::ifstream file("members.csv");
    std::string line;
    while (getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}

void Admin::viewAllCarpools() const {
    if (!isAuthenticated) {
        std::cout << "Access denied. Please log in first.\n";
        return;
    }
    std::cout << "Displaying all carpool listings:\n";
    std::ifstream file("carpool.csv");
    std::string line;
    while (getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}

bool Admin::validateCredentials(const std::string& username, const std::string& password) const {
    // Assuming credentials were loaded
    return this->username == username && this->password == password;
}
