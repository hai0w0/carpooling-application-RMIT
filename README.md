# Carpooling Application - Group Project README

## Overview
This C++ console-based application facilitates ride-sharing among users in Viet Nam. It supports user registration, profile management, carpool listings, bookings, and a rating system. Designed and developed for the EEET2482/EEET2653 Software Engineering Design and COSC2082/COSC2721 Advanced Programming Techniques course at RMIT, Semester 2, 2024.

## Instructors
- Dr. Ling Huo Chong
- Dr. Jeff Nijsse

## Group Members
- s4041605, Tran Dinh Hai
- s3996843, Nguyen Phu Minh Quang
- s4045608, Tran Quoc Hung
- s4021259, Tran Van Dat

## Technical Setup and Execution

### Configuration file
Ensure you have a `.vscode` directory in your project's root. See the Configuration.txt for more details.

### Prerequisites
- G++ Compiler
- VSCode (recommended) with C/C++ extensions installed

### Build and Run
Open VSCode and navigate to the Terminal.
Compile the code by running: g++ main.cpp Guest.cpp Admin.cpp Member.cpp -o output/main
Run the executable with: ./output/main

### Verifying Output
After running the executable, you should see the following prompt:
====================================================
              CARPOOLING APPLICATION
                   ______--------___
                  /|             / |
       o___________|_\__________/__|
      ]|___     |  |=   ||  =|___  |"
      //   \\    |  |____||_///   \\|"
     |  X  |\--------------/|  X  |\
      \___/                  \___/
====================================================
EEET2482/EEET2653/COSC2082/COSC2721 Group Assignment
Instructor: Dr. Ling Huo Chong, Dr. Jeff Nijsse
Group: Group No.9
s4041605, Tran Dinh Hai
s3996843, Nguyen Phu Minh Quang
s4045608, Tran Quoc Hung
s4021259, Tran Van Dat
=========================================

Use the app as:
1. Guest
2. Member
3. Admin
4. Exit

Enter your choice:

#### License
This project is licensed under the MIT License - see the LICENSE file for details.