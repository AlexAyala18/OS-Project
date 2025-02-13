#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "auth.h"
#include <conio.h>

void drawUI(const std::string& username, const std::string& password, bool typingPassword) {
    system("cls"); // Clear console screen (Windows-specific)
    std::cout << "=============================" << std::endl;
    std::cout << "     Welcome to Basic OS     " << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "Enter Username: " << username << std::endl;
    std::cout << "Enter Password: " << (typingPassword ? std::string(password.length(), '*') : "") << std::endl;
    std::cout << "(Press ENTER to submit)" << std::endl;
}

void showLoadingAnimation() {
    system("cls"); // Clear screen
    std::string loadingText = "Loading";
    for (int i = 0; i < 3; ++i) {
        std::cout << loadingText;
        for (int j = 0; j <= i; ++j) {
            std::cout << ".";
        }
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        system("cls");
    }
    std::cout << "System Ready!" << std::endl;
}

int main() {
    std::string inputUsername = "";
    std::string inputPassword = "";
    bool typingPassword = false;
    char ch;

    drawUI(inputUsername, inputPassword, typingPassword);

    while (true) {
        ch = _getch();
        if (ch == 13) { // Enter key
            if (authenticateUser(inputUsername, inputPassword)) {
                showLoadingAnimation();
                std::cout << "\nLogin Successful!" << std::endl;
            }
            else {
                std::cout << "\nInvalid Credentials!" << std::endl;
            }
            break;
        }
        else if (ch == 8) { // Backspace key
            if (typingPassword && !inputPassword.empty()) inputPassword.pop_back();
            else if (!typingPassword && !inputUsername.empty()) inputUsername.pop_back();
        }
        else if (ch == 9) { // Tab key to switch input fields
            typingPassword = !typingPassword;
        }
        else if (ch >= 32 && ch <= 126) { // Printable characters
            if (typingPassword) inputPassword += ch;
            else inputUsername += ch;
        }
        drawUI(inputUsername, inputPassword, typingPassword);
    }

    return 0;
}
