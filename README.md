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


The program starts and displays a login prompt.
The user types their username and password:
Password characters are hidden with *.
Press TAB to switch between username and password fields.
Press BACKSPACE to delete characters.
The user presses ENTER to submit.
If correct, a loading animation appears (Loading...).
If incorrect, an "Invalid Credentials!" message appears.
The program exits after login.

For our process, we used an enumeration for our ProcessState function
so that our process state cannot take any other values except
NEW, READY, RUNNING, WAITING, and TERMINATED. We also
set our system memory as a constant int variable so that the value
cannot be changed. In our process class, we had a constructor initialize 
our process values, and defined in our class how our process functioned. 
Essentially, our process would first test to see if there is enough available 
system memory for the process to execute, which if there is, it executes 
the READY state and displays the current process information such as proccess
number, state, time remaining, etc. Then, it would transition to the running state, and
then decrement the remaining time by 1, and this would repeat until
the remaining time equals 0, which then the process would terminate and
the next one would begin.

