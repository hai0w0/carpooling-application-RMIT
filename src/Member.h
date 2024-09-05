#ifndef MEMBER_H
#define MEMBER_H

#include <string>

class Member {
public:
    Member();
    void loadMemberData(); // Load member data from a file
    bool login(const std::string& username, const std::string& password);
    void viewProfile() const;
    void manageBookings();
    void bookCarpool();
    void listCarpool();
    void manageRequests();
    void handleCancellation();
    void Rating();
    void purchaseCredits();

private:
    std::string username;
    std::string password;
    bool isAuthenticated;
    // Additional attributes for the member's profile

    bool validateCredentials(const std::string& username, const std::string& password) const;
};

#endif // MEMBER_H
