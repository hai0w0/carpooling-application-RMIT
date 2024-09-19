#include <iostream>
#include <string>
#include <limits>
#include <thread>
#include <chrono>
#include <iomanip>
#include "Guest.h"
#include "Admin.h"
#include "Member.h"
#include "Carpool.h"
using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        // For Unix/Linux/macOS
        cout << "\033[2J\033[1;1H";
        cout.flush();
    #endif
    
    for (int i = 0; i < 50; ++i) {
        cout << endl;
    }
    cout << "\033[2J\033[1;1H";  
    cout.flush();
}

void showLoadingAnimation(const string& message, int duration) {
    string dots = "";
    for (int i = 0; i < duration; ++i) {
        clearScreen();
        cout << setw((80 - message.length() - 3) / 2) << " " << message << dots << endl;
        dots += ".";
        if (dots.length() > 3) dots = "";
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}



void showWelcomeScreen() {
    clearScreen();
    cout << "====================================================" << endl;
    cout << "              CARPOOLING APPLICATION" << endl;
    cout << "                   ______--------___\n";
    cout << "                  /|             / |\n";
    cout << "       o___________|_\\__________/__|\n";
    cout << "      ]|___     |  |=   ||  =|___  |\"\n";
    cout << "      //   \\\\    |  |____||_///   \\\\|\"\n";
    cout << "     |  X  |\\--------------/|  X  |\\\n";
    cout << "      \\___/                  \\___/\n";
    cout << "====================================================" << endl;
    cout << "EEET2482/EEET2653/COSC2082/COSC2721 Group Assignment" << endl;
    cout << "Instructor: Dr. Ling Huo Chong, Dr. Jeff Nijsse" << endl;
    cout << "Group: Group No.9" << endl;
    cout << "s4041605, Tran Dinh Hai" << endl;
    cout << "s3996843, Nguyen Phu Minh Quang" << endl;
    cout << "s4045608, Tran Quoc Hung" << endl;
    cout << "s4021259, Tran Van Dat" << endl;
    cout << "=========================================" << endl;
    cout << "\nUse the app as:" << endl;
    cout << "1. Guest" << endl;
    cout << "2. Member" << endl;
    cout << "3. Admin" << endl;
    cout << "4. Exit" << endl;
    cout << "\nEnter your choice: ";
}

int getValidChoice(int max) {
    int choice;
    while (!(cin >> choice) || choice < 1 || choice > max) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number between 1 and " << max << ": ";
    }
    return choice;
}

void guestMode() {
    Guest guest;
    bool continueGuestSession = true;

    while (continueGuestSession) {
        clearScreen();
        cout << "========== Guest Mode ==========" << endl;
        cout << "1. Sign Up" << endl;
        cout << "2. View Carpool Listings" << endl;
        cout << "3. Return to Main Menu" << endl;
        cout << "Enter your choice: ";

        int guestChoice = getValidChoice(3);

        switch (guestChoice) {
            case 1:
                clearScreen();
                cout << "===== Guest Signup =====" << endl;
                guest.signup();
                break;
            case 2:
                clearScreen();
                cout << "===== Carpool Listings =====" << endl;
                guest.viewCarpoolListings();
                break;
            case 3:
                continueGuestSession = false;
                break;
        }

        if (continueGuestSession) {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}

void memberMode() {
    Member member;
    member.loadMemberData();
    bool continueSession = true;
    bool isLoggedIn = false;

    while (!isLoggedIn) {
        clearScreen();
        cout << "========== Member Login ==========\n";
        cout << "Enter username: ";
        string username, password;
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (member.login(username, password)) {
            showLoadingAnimation("Logging in", 3);
            clearScreen();
            cout << "Welcome, " << member.getUserName() << "!\n";
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            isLoggedIn = true;
        } else {
            cout << "Login failed. Press Enter to try again...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    while (continueSession && isLoggedIn) {
        clearScreen();
        cout << "========== Main Menu ==========\n";
        cout << "1. View Profile\n";
        cout << "2. Be a Passenger\n";
        cout << "3. Be a Driver\n";
        cout << "4. Rating\n";
        cout << "5. Purchase Credit\n";
        cout << "6. Logout\n";
        cout << "Enter your choice: ";

        int memberChoice = getValidChoice(6);

        switch (memberChoice) {
            case 1: {
                clearScreen();
                member.viewProfile();
                cout << "1. Edit Profile\n";
                cout << "2. Return to Main Menu\n";
                cout << "Enter your choice: ";
                int editChoice = getValidChoice(2);
                if (editChoice == 1) {
                    cout << endl;
                    member.editProfile();
                }
                break;
            }
            case 2: {
                bool passengerSession = true;
                while (passengerSession) {
                    clearScreen();
                    cout << "===== Be a Passenger =====\n";
                    cout << "1. Manage Bookings\n";
                    cout << "2. Book Carpool\n";
                    cout << "3. Return to Main Menu\n";
                    cout << "Enter your choice: ";
                    int passengerChoice = getValidChoice(3);
                    switch (passengerChoice) {
                        case 1:
                            clearScreen();
                            member.manageBookings();
                            break;
                        case 2:
                            clearScreen();
                            cout << "===== Book Carpool =====\n";
                            member.bookCarpool();
                            break;
                        case 3:
                            passengerSession = false;
                            break;
                    }
                    if (passengerChoice != 3) {
                        cout << "\nPress Enter to return to the Passenger Menu...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();
                    }
                }
                break;
            }
            case 3: {
                bool driverSession = true;
                while (driverSession) {
                    clearScreen();
                    cout << "===== Be a Driver =====\n";
                    cout << "1. List Carpool\n";
                    cout << "2. Unlist Carpool\n";
                    cout << "3. Manage Passenger Requests\n";
                    cout << "4. Confirm Carpool Rides\n";
                    cout << "5. Return to Main Menu\n";
                    cout << "Enter your choice: ";
                    int driverChoice = getValidChoice(5);

                    switch (driverChoice) {
                        case 1:
                            clearScreen();
                            cout << "===== List Carpool =====\n";
                            member.listCarpool();
                            break;
                        case 2:
                            clearScreen();
                            cout << "===== Unlist Carpool =====\n";
                            member.unlistCarpool();
                            break;
                        case 3:
                            clearScreen();
                            cout << "===== Manage Passenger Requests =====\n";
                            member.manageRequests();
                            break;
                        case 4:
                            clearScreen();
                            cout << "===== Confirm Carpools =====\n";
                            member.confirmCarpoolRides();
                            break;
                        case 5:
                            driverSession = false;
                            break;
                    }

                    if (driverChoice != 3) {
                        cout << "\nPress Enter to return to the Driver Menu...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();
                    }
                }
                break;
            }
            case 4:
                clearScreen();
                cout << "===== Rating =====\n";
                member.rating();
                break;
            case 5:
                clearScreen();
                cout << "===== Purchase Credit =====\n";
                member.purchaseCredits();
                break;
            case 6:
                continueSession = false;
                break;
        }

        if (continueSession && memberChoice != 6) {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}

void adminMode() {
    Admin admin;
    admin.loadAdminData();
    bool continueSession = true;
    bool isLoggedIn = false;

    while (!isLoggedIn) {
        clearScreen();
        cout << "========== Admin Login ==========" << endl;
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (admin.login(username, password)) {
            showLoadingAnimation("Logging in", 3);
            clearScreen();
            cout << "Welcome, Admin!" << endl;
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            isLoggedIn = true;
        } else {
            cout << "Login failed. Press Enter to try again...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    while (continueSession && isLoggedIn) {
        clearScreen();
        cout << "========== Admin Menu ==========" << endl;
        cout << "1. View All User Information" << endl;
        cout << "2. View All Carpool Information" << endl;
        cout << "3. Logout" << endl;
        cout << "Enter your choice: ";

        int adminChoice = getValidChoice(3);

        switch (adminChoice) {
            case 1:
                clearScreen();
                cout << "===== All User Information =====" << endl;
                admin.viewAllUsers();
                break;
            case 2:
                clearScreen();
                cout << "===== All Carpool Information =====" << endl;
                admin.viewAllCarpools();
                break;
            case 3:
                continueSession = false;
                break;
        }

        if (continueSession) {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}

int main() {
    while (true) {
        showWelcomeScreen();
        int choice = getValidChoice(4);

        switch (choice) {
            case 1:
                guestMode();
                break;
            case 2:
                memberMode();
                break;
            case 3:
                adminMode();
                break;
            case 4:
                cout << "Thank you for using the Carpooling Application. Goodbye!" << endl;
                return 0;
        }
    }

    return 0;
}