#include "Admin.h"
#include <iostream>
#include <ifstream>

using namespace std;

Admin::Admin(const std::string& username, const std::string& password)
    : adminUsername(username), adminPassword(password) {}

void Admin::viewAdminInfo() const {
  cout << "Admin username: " << adminUsername << endl;  
  cout << "Admin password: " << adminPassword << endl;
}

void Admin::viewUserInfo(string username) const {
    
    ifstream readStream;
    
    string usernameData;
    string fullname;
    int phonenum;
    string idtype;
    int id;
    int credit;
    
    readStream.open("userInfo.dat", std::ios::in);
    if (!readStream) cout << "Fail to access user info data."
    ;

    while (getline(readStream, usernameData, ' ') {
        if (username == usernameData) {
            
            readStream.ignore(18, ' ');
            getline(readStream, fullname, '/');

            readStream >> phonenum >> idtype >> id >> credit;

            cout << "Name: " << fullname << '\n';
            cout << "Phone number: " << phonenum << '\n';
            cout << idtype << " ID: " << id << '\n';
            cout << "Credit: " << credit << '\n';
        }
        
    
}

