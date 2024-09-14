#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>

class Admin {
public:
    Admin();
    bool login(const std::string& username, const std::string& password);
    void viewAllUsers() const;
    void viewAllCarpools() const;
    void loadAdminData();

private:
    std::string username;
    std::string password;
    bool isAuthenticated;
    bool validateCredentials(const std::string& username, const std::string& password) const;
};

#endif
