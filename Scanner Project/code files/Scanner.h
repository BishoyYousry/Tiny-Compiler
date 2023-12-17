#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

struct token
{
    string data;
    string type;
}; 

extern vector<token> Tokens_storage;

string ReadFile(string);
void Scanning(string);
void showTokens(vector<token>);
string getToken(string);

#endif
