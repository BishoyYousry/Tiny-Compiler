#include "parser.hpp"
#include <vector>
#include <iostream>

int main()
{
    std::vector<Token>v;
    v.push_back({ NUMBER, "12" });
    v.push_back({ IDENTIFIER, "IDENTIFIER" });
    v.push_back({ SEMICOLON, ";" });
    v.push_back({ READ, "read" });
    v.push_back({ IDENTIFIER, "numTwo"});
    v.push_back({ SEMICOLON, "sdhcbsdmkjadcnkmnvk" });
    v.push_back({ IF, "iff" });
    v.push_back({ IDENTIFIER, "numOne" });
    Parser parser;
    for (int i = 0; i < v.size(); i++)
    {
        parser.tokens.push_back(&v[i]);    
    }
    parser.program();
    for (auto element:parser.errors)
    {
        std::cout << element << "\t";
    }
    return 0;
}