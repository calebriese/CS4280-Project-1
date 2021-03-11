#ifndef SCANNER_H
#define SCANNER_H
#include <string>
#include "token.h"
using namespace std;

class Scanner
{
public:
    int nextCharIndex = 0;
    int lineNumber = 0;
    bool commenting = false;


    enum TransitionTable {WS = 0, LETTER = 1, DIGIT = 2, VALID_OPERATOR = 3, INVALID = 5};

    enum TableStates{ ERROR = -1, S0 = 0, S1 = 1, S2 = 2, S3 = 3, IDENTIFIER = 1001, INTEGER = 1002, OPERATOR = 1003, EOF_STATE = 1004 };

    int FSATable[4][6] = { {S0,         S1,       S2,       S3,         EOF_STATE,  ERROR},
                           {IDENTIFIER, S1,       S1,       IDENTIFIER, IDENTIFIER, IDENTIFIER},
                           {INTEGER,    INTEGER,  S2,       INTEGER,    INTEGER,    INTEGER},
                           {OPERATOR,   OPERATOR, OPERATOR, OPERATOR,   OPERATOR,   OPERATOR}};




    void filter(string &currentLine);//preprocessor filter skips comments, counts line numbers, maybe maps characters to column #, error on invalid character
    string removeComments(string currentLine);
    bool driver(string input, Token &tk);
    int findCategory(char ch);
};
#endif