#include <iostream>
#include "Guest.h"

int main() {
    // Create a Guest object
    Guest guest;

    // Simulate guest actions
    std::cout << "Guest Signup:\n";
    guest.signup();

    std::cout << "\nViewing carpool listings as a guest:\n";
    guest.viewCarpoolListings();

    return 0;
}
