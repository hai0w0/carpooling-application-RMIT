#ifndef GUEST_H
#define GUEST_H

#include <string>

class Guest {
public:
    Guest(); // Constructor declaration

    void signup();
    void viewCarpoolListings();

private:
    std::string username;
    std::string password;
    std::string fullName;
    std::string phoneNumber;
    std::string email;
    std::string idType;
    std::string idNumber;
    int creditPoints;

    bool isValidPassword(const std::string& password);
};

#endif // GUEST_H
