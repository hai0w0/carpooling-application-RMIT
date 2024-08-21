#ifndef ADMIN_H
#define ADMIN_H

#include <string>

class Admin {
public:
    Admin(); // Constructor declaration

    void signup();
    void viewCarpoolListings();

private:
    std::string username;
    std::string password;

    bool isValidPassword(const std::string& password);
};

#endif // ADMIN_H
