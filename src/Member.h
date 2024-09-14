#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <map>

class Member {
private:
    bool isMemberAuthenticated;
    std::string username;
    std::string password;
    std::string fullname;
    std::map<std::string, std::pair<std::string, std::string>> memberCredentials;
    bool validateCredentials(const std::string& username, const std::string& password) const;

public:
    Member();
    void loadMemberData();
    void searchActiveCarpool();
    bool login(const std::string& username, const std::string& password);
    void viewProfile() const;
    void editProfile();
    void bookCarpool();
    void listCarpool();
    void unlistCarpool();
    void manageRequests();
    void confirmCarpoolRides();
    void rating();
    void purchaseCredits();
    void manageBookings();
    void transferCredits(const std::string& fromUser, const std::string& toUser, int amount);
};

#endif