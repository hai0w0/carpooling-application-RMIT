#include <iostream>
#include "Guest.h"
using namespace std;
int main() {
    // Create a Guest object
    Guest guest;

    // Simulate guest actions
    cout << "Guest Signup:\n";
    guest.signup();

    cout << "\nViewing carpool listings as a guest:\n";
    guest.viewCarpoolListings();

    return 0;
}

