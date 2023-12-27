#include <iostream>
#include <string>
#include <fstream>
#include <QStringList>
#include "scanner.hpp"
using namespace std;
int currentChar = 0;
bool ErrorScanner=false;
/*All Tiny language reserved words stored for further use*/
string Reserved_Words[] = { "if","then","else","end","repeat","until","read","write" };

/*The State machine states to be traversed on*/
enum Allstates { START, COMMENT, NUMBER, ID, ASSIGN, SYMBOL, ERROR, END };

/*The RESERVED words types*/
enum Allreserved { IF, THEN, ELSE, ENDWORD, REPEAT, UNTIL, READ, WRITE};

/*The special symbols types*/
enum Alltypes { SEMICOLON, LESSTHAN, EQUAL, PLUS, MINUS, MULT, DIV, OPENBRACKET, CLOSEDBRACKET };
Allstates current_state = START;//global variable to store the current state

/*Utility functions to check for type of current character*/
bool is_letter(char c) {
    if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z')
        return true;
    else
        return false;
}

/*Tokens to be return to parser*/
bool is_digit(char c) {
    if (c >= '0' && c <= '9')
        return true;
    else
        return false;
}

bool is_symbol(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '(' || c == ')' || c == ';')
        return true;
    else
        return false;
}

int reserved_type(string str){
    if(str == "if"){
        return IF;
    }
    else if(str == "then"){
        return THEN;
    }
    else if(str == "else"){
        return ELSE;
    }
    else if(str == "end"){
        return ENDWORD;
    }
    else if(str == "repeat"){
        return REPEAT;
    }
    else if(str == "until"){
        return UNTIL;
    }
    else if(str == "read"){

        return READ;
    }
    else if(str == "write"){
        return WRITE;
    }
    return 100;
}

int symbol_type(char c) {
    if (c == ';') {
        return SEMICOLON;
    }
    else if (c == '<') {
        return LESSTHAN;
    }
    else if (c == '=') {
        return EQUAL;
    }
    else if (c == '+') {
        return PLUS;
    }
    else if (c == '-') {
        return MINUS;
    }
    else if (c == '*') {
        return MULT;
    }
    else if (c == '/') {
        return DIV;
    }
    else if (c == '(') {
        return OPENBRACKET;
    }
    else if (c == ')') {
        return CLOSEDBRACKET;
    }
    return 100;
}

bool is_space(char c) {
    if (c == '\t' || c == ' ' || c == '\n')
        return true;
    else
        return false;
}

Token getToken(string Code) {
    ErrorScanner=false;
    Token token;

    bool is_Reserved = false;
    int reservedType = 0;
    int symbolType = 0;
    string type;
    /*State machine implementation and transitions are based on current character*/
    while (current_state != END ) {
        switch (current_state) {
        case START:
            if (is_digit(Code[currentChar])) {
                token.Type = "NUMBER";
                current_state = NUMBER;
            }
            else if (is_space(Code[currentChar])) {
                currentChar++;
                if (currentChar == Code.length())
                    current_state = END;
                else
                    current_state = START;
            }
            else if (Code[currentChar] == ':') {
                token.Type = "ASSIGN";
                current_state = ASSIGN;
            }
            else if (is_letter(Code[currentChar])) {

                current_state = ID;
            }
            else if (Code[currentChar] == '{') {
                token.Type = "COMMENT";
                currentChar++;
                current_state = COMMENT;
            }
            else if (is_symbol(Code[currentChar])) {
                token.Type = "Symbol";
                current_state = SYMBOL;

            }
            else current_state = ERROR;

            break;

        case NUMBER:
            while (is_digit(Code[currentChar])) {
                token.Value += Code[currentChar];
                currentChar++;
            }
            cout << token.Value << ", " << "NUMBER" << endl;
            //token.Value = "";
            if (currentChar == Code.length())
                current_state = END;
            else
                current_state = START;

            return token;
            break;


        case ID:
            while (is_letter(Code[currentChar]) && !is_space(Code[currentChar])) {
                token.Value += Code[currentChar];
                currentChar++;
            }
            for (int currentChar = 0; currentChar < 8; currentChar++)
            {
                if (Reserved_Words[currentChar] == token.Value)
                    is_Reserved = true;
            }
            if (is_Reserved){
                reservedType = reserved_type(token.Value);
                switch (reservedType) {
                case IF:
                    token.Type = "IF";
                    break;
                case THEN:
                    token.Type = "THEN";
                    break;
                case ENDWORD:
                    token.Type = "END";
                    break;
                case REPEAT:
                    token.Type = "REPEAT";
                    break;
                case UNTIL:
                    token.Type = "UNTIL";
                    break;
                case READ:
                    token.Type = "READ";
                    break;
                case WRITE:
                    token.Type = "WRITE";
                    break;
                case ELSE:
                    token.Type = "ELSE";
                    break;
            }
            cout << token.Value << ", " << token.Type << endl;
            }
            else{
                cout << token.Value << ", " << "IDENTIFIER" << endl;
                token.Type = "IDENTIFIER";
            }
            //token.Value = "";
            is_Reserved = false;
            if (currentChar == Code.length())
                current_state = END;
            else
                current_state = START;

            return token;
            break;


        case COMMENT:
            if (current_state == COMMENT) {
                while (Code[currentChar] != '}') {
                    currentChar++;
                }
                currentChar++;
                if (currentChar == Code.length())
                    current_state = END;
                else
                    current_state = START;
            }

            break;

        case ASSIGN:
            if (Code[currentChar] == ':') {
                if(Code[currentChar+1]=='=')
                {
                currentChar += 2;
                token.Type="ASSIGN";
                token.Value=":=";
                cout << ":=" << ", " << "ASSIGN" << endl;
                /*return to start case to handle next character state*/
                current_state = START;
                }
            }
            else {
                if (currentChar == Code.length())
                    current_state = END;
                else
                    current_state = START;
            }
            return token;
            break;
        case SYMBOL:
            symbolType = symbol_type(Code[currentChar]);
            switch (symbolType) {
            case SEMICOLON:
                token.Type = "SEMICOLON";
                break;
            case LESSTHAN:
                token.Type = "LESSTHAN";
                break;
            case EQUAL:
                token.Type = "EQUAL";
                break;
            case PLUS:
                token.Type = "PLUS";
                break;
            case MINUS:
                token.Type = "MINUS";
                break;
            case MULT:
                token.Type = "MULT";
                break;
            case DIV:
                token.Type = "DIV";
                break;
            case OPENBRACKET:
                token.Type = "OPENBRACKET";
                break;
            case CLOSEDBRACKET:
                token.Type = "CLOSEDBRACKET";
                break;
            }
            token.Value=Code[currentChar];
            cout << Code[currentChar] << ", " << token.Type << endl;
            currentChar++;
            if (currentChar == Code.length())
                current_state = END;
            else
                current_state = START;

            return token;
            break;

        case ERROR:
            cout<<"ERROR"<<endl;
            ErrorScanner=true;
            current_state = END;
            break;
        case END:
            break;
        //default:
            //current_state = ERROR;
            //break;


        }
    }
}


vector<Token> getTokenList(string input){
    vector<Token> tokens;
    Token token;
    int index = 0;
    currentChar = 0;
    current_state = START;

    // Convert the input string to a QString object
    QString qinput = QString::fromStdString(input);

    while((index < (input.length()))&&!ErrorScanner ){
        cout<<input.substr(index,input.length());
        string i=input.substr(index,input.length());
        cout<<i;
        token=getToken(input);
        tokens.push_back(token);
        index=currentChar+1;
    }
    cout<<"finished";
    cout<<tokens.size();
    return tokens;
}


// Define the qt function caller extractTokens
vector<Token> extractTokens(string input) {
    // Create an empty vector of Tokens
    vector<Token> tokens;

    // Remove all spaces in the input string
    input.erase(remove(input.begin(), input.end(), ' '), input.end());

    // Convert the input string to a QString object
    QString qinput = QString::fromStdString(input);

    // Split the QString object by newline characters
    QStringList lines = qinput.split("\n");

    // Loop through each line
    for (QString line : lines) {
        // Split the line by colon characters
        QStringList parts = line.split(",");

        // Check if the line has exactly two parts
        if (parts.size() == 2) {
            // Create a new Token with the value and type from the parts
            Token token;
            token.Value = parts[0].toStdString();
            token.Type = parts[1].toStdString();

            // Append the Token to the vector
            tokens.push_back(token);
        }
    }

    // Return the vector of Tokens
    return tokens;
}
