#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>

class Admin {
public:
    Admin();  // Constructor declaration.
    bool login(const std::string& username, const std::string& password);  // Attempts to log in an admin.
    void viewAllUsers() const;  // Displays all user data.
    void viewAllCarpools() const;  // Displays all carpool listings.
    void loadAdminData();  // Loads admin data from a file.

private:
    std::string username;  // Stores the admin's username.
    std::string password;  // Stores the admin's password.
    bool isAuthenticated;  // Indicates whether the admin is currently authenticated.
    bool validateCredentials(const std::string& username, const std::string& password) const;  // Validates credentials.
};

#endif



