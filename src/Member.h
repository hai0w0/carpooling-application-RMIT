#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <map>

// Declaration of the Member class
class Member {
private:
    bool isMemberAuthenticated; // Flag to check if the member is currently authenticated
    std::string username; // Stores the username of the member
    std::string password; // Stores the password of the member
    std::string fullname; // Stores the full name of the member
    
    // A map to store member credentials, with the username as the key and a pair (password, fullname) as the value
    std::map<std::string, std::pair<std::string, std::string>> memberCredentials;

    // Private method to validate the username and password during login
    bool validateCredentials(const std::string& username, const std::string& password) const;
     

public:
    Member(); // Default constructor

    void loadMemberData(); // Loads member data from a data source
    void searchActiveCarpool(); // Allows members to search for active carpool listings
    bool login(const std::string& username, const std::string& password); // Log in for member with a username and password
    void viewProfile() const; // Displays the member's profile information
    void editProfile(); // Allows the member to edit their profile information
    void bookCarpool(); // Enables a member to book a carpool
    void listCarpool(); // Allows a member to list a new carpool
    void unlistCarpool(); // Provides functionality for a member to unlist an existing carpool
    void manageRequests(); // Manages incoming requests for carpools listed by the member
    void confirmCarpoolRides(); // Confirms the rides for a booked carpool
    void rating(); // Manages the rating system for carpools
    void purchaseCredits(); // Enables a member to purchase credits for booking carpools
    void manageBookings(); // Manages all bookings made by the member
    void transferCredits(const std::string& fromUser, const std::string& toUser, int amount); // Transfers credits from one user to another
    std::string getUserName() const; // Transfers credits from one user to another
    int getCredits() const; // Returns the current credit balance of the member
};

#endif