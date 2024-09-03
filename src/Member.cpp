#include "Member.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Constructor definition
Member::Member() : creditPoints(0) {}

// Method definitions
bool validateUser(std::string& inputUsername, const std::string& inputPassword) {
  string foundUsername, foundPassword;
  
  fstream fs;
  fs.open("members.csv", ios::in);

  while (fin >> temp) {
    string column;
    getline(fs, column);

    stringstream ss(column);
    string currUsername, currPassword;
    getline(ss, currUsername, ',');

    if (currUsername == inputUsername) {
      strcpy(foundUsername, currUsername);
      getline(ss, currPassword, ',');
      break;
    } else { continue;
           }
  }

  if (foundUsername.empty) { return false;
  }

  return (currPassword == inputPassword)? true : false
  
}
