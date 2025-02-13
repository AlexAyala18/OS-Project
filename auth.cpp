#include "auth.h"

bool authenticateUser(const std::string& username, const std::string& password) {
    return (username == "12345" && password == "12345");
}