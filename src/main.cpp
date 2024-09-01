#include <iostream>
#include "Guest.h"
#include "Admin.h"
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
                // Implement Member mode functionality
                //1.Login (Quang)
                //2.View Profile (Dat)
                //3.Book car to my list (dat xe de di)
                //4.Add car to my listing (cho thue xe)
                //5.View requests for car (xem nguoi muon di xe cua minh)
                //6.Cancellation (6.1 My booking; 6.2 My Listing) 
                //7.Rating (7.1 Rate Passenger; 7.2 Rate Driver) (Hung)
                //8.Purchase Credit. (Hai)
                //9.Exit (Hai)
                break;
            }



            case 3: {
                cout << "You have selected Admin mode." << endl;
                Admin admin;
                admin.loadAdminData(); // Assuming this method sets up admin credentials
                bool continueSession = true;

                while (continueSession){
                    cout << "\nPlease choose an option:" << endl;
                    cout << "1. Login" << endl;
                    cout << "2. View All User Information" << endl;
                    cout << "3. View All Carpool Information" << endl;
                    cout << "4. Exit" << endl;
                    cout << "Enter your choice: ";
                    int adminChoice;
                    cin >> adminChoice;

                    switch(adminChoice){
                        case 1: {
                            // Scoping for local variables
                            string Admin_username, Admin_password;
                            cout << "Enter username: ";
                            cin >> Admin_username;
                            cout << "Enter password: ";
                            cin >> Admin_password;
                            if (admin.login(Admin_username, Admin_password)) {
                                cout << "Logged in successfully.\n";
                            } else {
                                cout << "Login failed.\n";
                            }
                            break;
                        }
                        case 2:
                            admin.viewAllUsers();
                            break;
                        case 3:
                            admin.viewAllCarpools();
                            break;
                        case 4:
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
