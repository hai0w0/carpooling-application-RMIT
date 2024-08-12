// include/User.h
#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;
    std::string fullName;
    std::string phoneNumber;
    std::string email;
    std::string idType;
    std::string idNumber;
    int creditPoints;
    bool isAdmin;
    bool isVerified;

public:
    User();
    User(const std::string& username, const std::string& password, const std::string& fullName,
         const std::string& phoneNumber, const std::string& email, const std::string& idType,
         const std::string& idNumber, int creditPoints = 10, bool isAdmin = false, bool isVerified = false);

    // Getters and setters
    std::string getUsername() const;
    void setUsername(const std::string& username);

    std::string getPassword() const;
    void setPassword(const std::string& password);

    // Add other getters and setters as needed

    void registerUser();
    void updateProfile();
    void changePassword();
    // Add other methods as needed
};

#endif // USER_H
