#pragma once

#include "headers.hpp"

extern bool ErrorScanner;
struct Token{
    std::string Type;
    std::string Value;
};

std::vector<Token> getTokenList(std::string input);
std::vector<Token> extractTokens(std::string input);
Token getToken(std:: string Code);
