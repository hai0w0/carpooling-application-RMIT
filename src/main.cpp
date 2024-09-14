#include <iostream>
#include "Guest.h"
#include "Admin.h"
#include "Member.h"
#include "Carpool.h"
using namespace std;

void showWelcomeScreen() {
    cout << "EEET2482/EEET2653/COSC2082/COSC2721 Group Assignment" << endl;
    cout << "CARPOOLING APPLICATION" << endl;
    cout << "Instructor: Dr. Ling Huo Chong, Dr. Jeff Nijsse" << endl;
    cout << "Group: Group No." << endl;
    cout << "s4041605, Tran Dinh Hai" << endl;
    cout << "s3996843, Nguyen Phu Minh Quang" << endl;
    cout << "s4045608, Tran Quoc Hung" << endl;
    cout << "s4021259, Tran Van Dat" << endl;
    cout << endl;
    cout << "Use the app as:" << endl;
    cout << "1. Guest" << endl;
    cout << "2. Member" << endl;
    cout << "3. Admin" << endl;
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    // Loop to allow repeated usage until the user decides to exit
    while (true) {
        // Show the welcome screen
        showWelcomeScreen();

        // Read user choice with input validation
        if (!(cin >> choice)) {
            cin.clear(); // Clear error flag
            cout << "Please enter a valid number." << endl;
            continue;
        }

        // Process user choice
        switch (choice) {
            case 1: {
                cout << "You have selected Guest mode." << endl;
                Guest guest;
                bool continueGuestSession = true;
    
                while (continueGuestSession) {
                    cout << "\nPlease choose an option:" << endl;
                    cout << "1. Sign Up" << endl;
                    cout << "2. View Carpool Listings" << endl;
                    cout << "3. Exit" << endl;
                    cout << "Enter your choice: ";
        
                    int guestChoice;
                    cin >> guestChoice;
        
                    switch (guestChoice) {
                        case 1:
                            cout << "Guest Signup:\n";
                            guest.signup();
                            break;
                        case 2:
                            cout << "Viewing carpool listings as a guest:\n";
                            guest.viewCarpoolListings();
                            break;
                        case 3:
                            cout << "Exiting Guest mode...\n";
                            continueGuestSession = false; // Exit the guest session
                            break;
                        default:
                            cout << "Invalid choice, please try again." << endl;
                            break;
                    }
                }
                break;
            }

            case 2: {
                cout << "You have selected Member mode." << endl;
                Member member;
                member.loadMemberData();
                bool MembercontinueSession = true;
                bool MemberisLoggedIn = false;

                while (!MemberisLoggedIn) {
                    string Member_username, Member_password;
                    cout << "Enter username: ";
                    cin >> Member_username;
                    cout << "Enter password: ";
                    cin >> Member_password;
                    if (member.login(Member_username, Member_password)) {
                        cout << "Logged in successfully.\n";
                        MemberisLoggedIn = true; // Set the login flag to true
                    } else {
                        cout << "Login failed. Please try again.\n";
                    }
                }

                while (MembercontinueSession && MemberisLoggedIn) {
                    cout << "\nPlease choose an option:" << endl;
                    cout << "1. View your Profile Information" << endl;
                    cout << "2. Manage your Carpool Booking" << endl;
                    cout << "3. Book Carpool (Become a passenger)" << endl;
                    cout << "4. List Carpool (Become a driver)" << endl;
                    cout << "5. Manage your Passenger' requests" << endl;
                    cout << "6. Confirm Carpool Ride" << endl;
                    cout << "7. Rating" << endl;
                    cout << "8. Purchase Credit" << endl;
                    cout << "9. Unlist Carpool" << endl;
                    cout << "10. Exit" << endl;
                    cout << "Enter your choice: ";
                    int memberChoice;
                    cin >> memberChoice;

                    switch (memberChoice) {
                        case 1:
                            cout << "You have chosen to view profile information\n";
                            member.viewProfile();
                            cout << "Finish view profile";
                            break;
                        case 2:
                            cout << "\nManage Bookings for Passenger functionality is chosen.\n";
                            member.manageBookings();
                            break;
                        case 3:
                            // Implement Book Carpool functionality
                            cout << "Book Carpool functionality is chosen.\n";
                            member.bookCarpool();
                            break;
                        case 4:
                            // Implement List Carpool functionality
                            cout << "List Carpool functionality is chosen.\n";
                            member.listCarpool();
                            break;
                        case 5:
                            // Implement Manage Passenger Requests functionality
                            cout << "Manage Passenger Requests is chosen.\n";
                            member.manageRequests();
                            break;
                        case 6:
                            // Implement Cancellation functionality
                            cout << "Confirm carpool Ride is chosen.\n";
                            member.confirmCarpoolRides();
                            break;
                        case 7:
                            // Implement Rating functionality
                            cout << "Rating functionality not implemented yet.\n";
                            break;
                        case 8:
                            cout << "You have chosen the Purchase Credit option. Each credit is worth $1." << endl;
                            member.purchaseCredits();
                            break;
                        case 9:
                            cout << "You have chosen the Unlist Carppol option." << endl;
                            member.unlistCarpool();
                            break;
                        case 10:
                            cout << "Exiting Member mode...\n";
                            MembercontinueSession = false; // Exit the member session
                            break;
                        default:
                            cout << "Invalid choice, please try again." << endl;
                            break;
                    }
                }
                break; // This break is for the case 2 of the main switch
            }

            case 3: {
                cout << "You have selected Admin mode." << endl;
                Admin admin;
                admin.loadAdminData(); // Assuming this method sets up admin credentials
                bool continueSession = true;
                bool isLoggedIn = false; // Flag to check if the admin is logged in

                // Prompt for login before showing admin menu
                while (!isLoggedIn) {
                    string Admin_username, Admin_password;
                    cout << "Enter username: ";
                    cin >> Admin_username;
                    cout << "Enter password: ";
                    cin >> Admin_password;
                    if (admin.login(Admin_username, Admin_password)) {
                        cout << "Logged in successfully.\n";
                        isLoggedIn = true; // Set the login flag to true
                    } else {
                        cout << "Login failed. Please try again.\n";
                    }
                }

                // Continue with the admin menu after successful login
                while (continueSession && isLoggedIn) {
                    cout << "\nPlease choose an option:" << endl;
                    cout << "1. View All User Information" << endl;
                    cout << "2. View All Carpool Information" << endl;
                    cout << "3. Exit" << endl;
                    cout << "Enter your choice: ";
                    int adminChoice;
                    cin >> adminChoice;

                    switch (adminChoice) {
                        case 1:
                            admin.viewAllUsers();
                            break;
                        case 2:
                            admin.viewAllCarpools();
                            break;
                        case 3:
                            cout << "Exiting Admin mode...\n";
                            continueSession = false; // Exit the admin session
                            break;
                        default:
                            cout << "Invalid choice, please try again." << endl;
                            break;
                    }
                }
                break;
            }
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }

        // Ask if user wants to continue or exit
        cout << "\nDo you want to continue (Yes/No)? ";
        string answer;
        cin >> answer;
        if (answer == "No" || answer == "no") {
            break;  // Exit the loop and the program
        }
    }

    return 0;
}