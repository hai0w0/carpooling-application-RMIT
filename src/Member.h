/*#ifndef MEMBER_H
#define MEMBER_H

#include <string>

class Member {
private:
    std::string username;
    std::string password;
    std::string fullName;
    std::string phoneNumber;
    std::string email;
    std::string idType;
    std::string idNumber;
    int creditPoints;
    double ratingScore;
    std::string status; // "Passenger" or "Driver"

    bool isValidPassword(const std::string& password);
    bool isValidPhoneNumber(const std::string& phoneNumber);
    bool isValidEmail(const std::string& email);

public:
    Member();

    bool validateUser(const std::string& inputUsername, const std::string& inputPassword);
    void viewProfile();
    void editProfile();
    void bookCar();
    void driveCar();
    void viewCarpool();
    void manageCarList();
    void manageRequests();
    void purchaseCredit();
    void rateUser(double rating);
};

#endif // MEMBER_H*/
#ifndef MEMBER_H
#define MEMBER_H

/*#include "../../utils/Review.h"
#include "../../utils/time/Period.h"
#include "../house/House.h"
#include "Account.h"
#include "OccupantReview.h"*/
#include <iostream>
#include <vector>

namespace utils {
    namespace time {
        class Period;
    }
}

namespace house {
    class House;
    class HouseRequest;
}

namespace account {
    class OccupantReview;

    class Member : public Account {
      private:
        unsigned credits;
        double rating_score;
        std::string memberID;
        std::string first_name;
        std::string last_name;
        std::string phone_number;
        house::House *house;
        std::vector<OccupantReview *> reviews;
        std::vector<house::HouseRequest*> requests;

      public:
        Member();
        Member(
            const std::string &memberID,
            const std::string &username,
            const std::string &password,
            const std::string &first_name,
            const std::string &last_name,
            const std::string &phone_number,
            unsigned int credits = 500,
            double rating_score = 10
        );

        unsigned int get_credits() const;
        void setCredits(unsigned int credit);

        const std::string &get_first_name() const;
        const std::string &get_last_name() const;
        const std::string &get_phone_number() const;
        const std::string &get_id() const;
        house::House *getHouse() const;
        double getRatingScore() const;
        void setRatingScore(double ratingScore);

        void from_map(std::map<std::string, std::string> map) override;
        std::map<std::string, std::string> to_map() override;
    };

} // account

#endif//RMIT2022C_EEET2482_LODGING_APP_SRC_ENTITIES_ACCOUNT_MEMBER_H_


    unsigned int Member::get_credits() const {
        return credits;
    }

    const std::string &Member::get_first_name() const {
        return first_name;
    }

    const std::string &Member::get_last_name() const {
        return last_name;
    }

    const std::string &Member::get_phone_number() const {
        return phone_number;
    }

    const std::string &Member::get_id() const {
        return this->memberID;
    }

    double Member::getRatingScore() const {
        return rating_score;
    }

    void Member::setRatingScore(double ratingScore) {
        rating_score = ratingScore;
    }

    void Member::from_map(std::map<std::string, std::string> map) {
        Account::from_map(map);
        this->memberID = map["member_id"];
        this->first_name = map["first_name"];
        this->last_name = map["last_name"];
        this->phone_number = map["phone_number"];
        this->credits = std::stoul(map["credits"]);
        this->rating_score = std::stod(map["rating_score"]);
    }

    std::map<std::string, std::string> Member::to_map() {
        std::map<std::string, std::string> map = Account::to_map();
        map.emplace("member_id", this->memberID);
        map.emplace("first_name", this->first_name);
        map.emplace("last_name", this->last_name);
        map.emplace("phone_number", this->phone_number);
        map.emplace("credits", std::to_string(this->credits));
        map.emplace("rating_score", std::to_string(this->rating_score));
        return map;
    }

}// namespace account
