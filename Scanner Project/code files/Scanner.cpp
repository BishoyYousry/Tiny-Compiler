#include"scanner.h"


bool Is_Speccial_character_Or_space(char x);
bool Store_Speccial_character_Or_space(char x);
bool IsReservedWord(string x);
bool IsNum(string x);
bool IsIdentifier(string x);
bool IsError(string x);

vector<token> Tokens_storage;

/*********************************** Main_Functions ***************************/
void Scanning(string InputPath)
{
    string FilePath = InputPath;
    ifstream InputFile(FilePath);
    string in;
    if (!InputFile.is_open()) {
        cout << "error" << endl;
    }
    while (getline(InputFile, in))
    {
        string x;
        for (int i = 0; i < in.length(); i++)
        {
            if (in[i] == ':' && in[i + 1] == '=')
            {
                token y = { ":=" , "ASSIGN" };
                Tokens_storage.push_back(y);
                i++;
            }
            else if (Is_Speccial_character_Or_space(in[i]))
            {
                Store_Speccial_character_Or_space(in[i]);
                x.clear();
            }
            else if ((Is_Speccial_character_Or_space(in[i + 1])) || (i == (in.length() - 1)))
            {
                x.push_back(in[i]);
                if (IsReservedWord(x))    {}
                else if (IsNum(x))        {}
                else if (IsIdentifier(x)) {}
                else if (IsError(x))      {}
                x.clear();
            }
            else
            {
                x.push_back(in[i]);
            }
        }
    }
    InputFile.close();
    showTokens(Tokens_storage);
}

void showTokens(vector <token> y)
{
    ofstream myfile;
    myfile.open("Scanner_Output.txt");
    for (auto it = y.begin(); it != y.end(); it++)
    {
        myfile << "(" << it->data << ", " << it-> type << ")" << "\n";
    }
    myfile.close();
}

/***********************************Helper_Functions***************************/
bool Is_Speccial_character_Or_space(char x)
{
    char SpecialCharacter[10] = { ';', '=', '<', '(', ')', '/', '*','+', '-', ' ' };
    for (int i = 0; i < 10; i++)
    {
        if (x == SpecialCharacter[i])
            return true;
    }
    return false;
}

bool Store_Speccial_character_Or_space(char x)
{
    token y;
    y.data = x;
    switch (x)
    {
    case ';':
        y.type = "SEMICOLON";
        break;

    case '=':
        y.type = "EQUAL";
        break;

    case '<':
        y.type = "LESSTHAN";
        break;

    case '(':
        y.type = "OPENBRACKET";
        break;

    case ')':
        y.type = "CLOSEBRACKET";
        break;

    case '/':
        y.type = "DIV";
        break;

    case '*':
        y.type = "MUL";
        break;

    case '+':
        y.type = "PLUS";
        break;

    case '-':
        y.type = "MINUS";
        break;

    case ' ':
        y.type = "SPACE";
        break;

    default:
        break;
    }
    Tokens_storage.push_back(y);
    return true;
}

bool IsReservedWord(string x)
{
    string ReservedWord[8] = { "if", "then", "else", "end", "repeat", "until", "read","write" };
    string TokenType[8] = { "IF", "THEN", "ELSE", "END", "REPEAT", "UNTIL", "READ","WRITE" };
    token y;

    for (int i = 0; i < 8; i++)
    {
        if (x == ReservedWord[i])
        {
            y.data = ReservedWord[i];
            y.type = TokenType[i];
            Tokens_storage.push_back(y);
            return true;
        }
    }
    return false;
}

bool IsNum(string x)
{
    for (int i = 0; i < x.length(); i++)
    {
        if (!isdigit(x[i]))
        {
            return false;
        }
    }
    token y = { x,"NUMBER" };
    Tokens_storage.push_back(y);
    return true;
}

bool IsIdentifier(string x)
{
    for (int i = 0; i < x.length(); i++)
    {
        if (!isalpha(x[i]))
        {
            return false;
        }
    }
    token y = { x,"IDENTIFIER" };
    Tokens_storage.push_back(y);
    return true;
}

bool IsError(string x)
{
    for (int i = 0; i < x.length(); i++)
    {
        if ((!isalpha(x[i])) && (!isdigit(x[i])) && (!Is_Speccial_character_Or_space(x[i])))
        {
            token y = { x,"ERROR" };
            Tokens_storage.push_back(y);
            return true;
        }
    }
    return false;
}