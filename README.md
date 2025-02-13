# Title: Operating System Project
The team members in this project are Joseph Rodriguez and Alexander Ayala. This multi-part semester long project
will see us implement a simplified operating system using C++. The first part of the project revolves around
setting up a basic authentification system, which will serve as the foundation of the operating system. Eventually, we will
have to create more complex components of the operating system, including an interactive graphical user interface.

Instructions: 
1. auth.h (Header File)
Declares the authenticateUser function.
2. auth.cpp (Authentication Logic)
Implements authenticateUser() to check username and password.
Uses hardcoded credentials ("12345" and "12345").
3. main.cpp (Main Logic)
Handles user input and authentication.
Implements:
drawUI() → Displays username/password input fields.
showLoadingAnimation() → Displays a "Loading..." animation

How To....
The program starts and displays a login prompt.
The user types their username and password:
Password characters are hidden with *.
Press TAB to switch between username and password fields.
Press BACKSPACE to delete characters.
The user presses ENTER to submit.
If correct, a loading animation appears (Loading...).
If incorrect, an "Invalid Credentials!" message appears.
The program exits after login.



