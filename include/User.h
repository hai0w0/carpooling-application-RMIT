#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
  User(); // Constructor declaration

  void register(std::string& username, std::string& password, std::string& fullname,
                int& phoneNum, std::string& email, 
                std::string& idType, int& idNum);

  bool login(std::string username, std::string password);

  void editProfile(std:string& fullname, int& phoneNum, std::string& email, 
                  std::string& idType, int& idNum);

  void changePassword(std::string oldPassword, std::string newPassword);


private:
  std::string username;
  std::string password;
  std::string fullname;

  int phoneNum;
  std::string email;

  std::string idType;
  int idNum;

  int credit;
  float rating; //(?)
    

  //bool isValidPassword(const std::string& password);
};

#endif // ADMIN_H
