#include "Admin.h"
#include <iostream>

using namespace std;

Admin::Admin(const std::string& username, const std::string& password)
    : adminUsername(username), adminPassword(password) {}

void Admin::viewAdminInfo() const {
  cout << "Admin username: " << adminUsername << endl;  
  cout << "Admin password: " << adminPassword << endl;
}

void Admin::viewUserInfo() const {
    
}

