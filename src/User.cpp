// src/User.cpp
#include "User.h"
#include <iostream>

User::User() : username(""), password(""), fullName(""), phoneNumber(""), email(""),
               idType(""), idNumber(""), creditPoints(10), isAdmin(false), isVerified(false) {}

User::User(const std::string& username, const std::string& password, const std::string& fullName,
           const std::string& phoneNumber, const std::string& email, const std::string& idType,
           const std::string& idNumber, int creditPoints, bool isAdmin, bool isVerified)
    : username(username), password(password), fullName(fullName), phoneNumber(phoneNumber),
      email(email), idType(idType), idNumber(idNumber), creditPoints(creditPoints),
      isAdmin(isAdmin), isVerified(isVerified) {}

std::string User::getUsername() const {
    return username;
}

void User::setUsername(const std::string& username) {
    this->username = username;
}

std::string User::getPassword() const {
    return password;
}

void User::setPassword(const std::string& password) {
    this->password = password;
}

// Implement other methods as needed

void User::registerUser() {
    // Implementation for user registration
}

void User::updateProfile() {
    // Implementation for profile update
}

void User::changePassword() {
    // Implementation for password change
}
