#ifndef GUEST_H
#define GUEST_H

#include <string>

class Guest {
public:
    Guest(); // Default constructor to initialize a Guest object
    void signup(); // Method to handle guest signup
    void viewCarpoolListings(); // Method to display carpool listings available
    
private:
    // Private variables for sign up
    std::string username;
    std::string password;
    std::string fullName;
    std::string phoneNumber;
    std::string email;
    std::string idType;
    std::string idNumber;
    int creditPoints;
    int rating;

    // Private methods for validating various pieces of information during signup
    bool isUsernameTaken(const std::string& username);
    bool isPhoneNumberTaken(const std::string& phoneNumber);
    bool isEmailTaken(const std::string& email);
    bool isIdNumberTaken(const std::string& idNumber);
    bool isValidPassword(const std::string& password);
    bool isValidFullName(const std::string& name);
    bool isValidEmail(const std::string& email);
    bool isValidIdType(int idTypeOption);
    bool isValidPhoneNumber(const std::string& number);
    void saveToFile() const; // Method to save guest information to a file
};

#endif