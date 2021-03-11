#include "scanner.h"
#include <iostream>
#include <string>

void Scanner::filter(string &currentLine)//the filter
{
    lineNumber++;
    currentLine = removeComments(currentLine);
}

string Scanner::removeComments(string currentLine)//removes comments from the line before the driver looks at it
{
    //finds position of first/second $$ if they exist
    size_t firstFound = currentLine.find("$$");
    size_t secondFound = currentLine.find("$$", firstFound + 1);


    if (firstFound != string::npos && secondFound == string::npos)//One comment found in the line
    {
        commenting = !commenting;
        if (commenting)
        {
            currentLine = currentLine.substr(0, firstFound);
        }
        else
        {
            currentLine.erase(0, firstFound + 2);
        }
    }
    else if (secondFound != string::npos) //Two comments found in the line
    {
        commenting = !commenting;
        if (commenting)//this one started the comment
        {
            int difference = (secondFound - firstFound);
            currentLine.erase(firstFound, difference + 2);
            currentLine.insert(firstFound, " ");//puts a space in place of the comment
            commenting = !commenting;
            currentLine = removeComments(currentLine);
        }
        else
        {
            currentLine.erase(0, firstFound + 2);//the first one ended the comment so erase from 0 to firstOne
            currentLine = removeComments(currentLine);
        }
    }
    else //No comments found in the line
    {
        if (commenting)
        {
            currentLine = "";
        }
    }

    return currentLine;
}

bool Scanner::driver(string input, Token &tk)//the driver, finds the tokens in the line and returns one
{
    tk.lineNumber = lineNumber;
    int category, nextState, state = S0;
    string currentWordAsIs;
    char nextChar = ' ';
    bool notFinished = true;

    while (notFinished)//while more characters left or token is returned
    {
        if (nextCharIndex < input.length())
        {
            nextChar = input[nextCharIndex];
        }
        else
        {
            nextChar = ' ';
        }
        category = findCategory(nextChar); //gets the category
        nextState = FSATable[state][category]; //gets the state

        if (nextState > 1000)//final state
        {
            tk.tokenInstance = "";
            switch (nextState)
            {
                case IDENTIFIER:
                    if (keywordMap.count(currentWordAsIs))
                    {
                        tk.tokenID = keywordToken;
                        tk.tokenInstance.append("(");
                        tk.tokenInstance.append(keywordMap.at(currentWordAsIs));
                        tk.tokenInstance.append(")");
                    }
                    else
                    {
                        tk.tokenID = identifierToken;
                    }
                    break;

                case INTEGER:
                    tk.tokenID = numberToken;
                    break;

                case OPERATOR:
                    tk.tokenID = operatorToken;

                    string checkMeForDouble = currentWordAsIs + nextChar;
                    if (operatorMap.count(checkMeForDouble))//handles two character operators
                    {
                        currentWordAsIs = checkMeForDouble;
                        nextCharIndex++;
                    }
                    tk.tokenInstance.append("(");
                    tk.tokenInstance.append(operatorMap.at(currentWordAsIs));
                    tk.tokenInstance.append(")");
                    break;
            }
            tk.tokenInstance.append(", Instance: " + currentWordAsIs);
            return true;
        }
        else if (nextState == ERROR)
        {
            cout << "SCANNER ERROR: Invalid Character at Line " << lineNumber << ": " << nextChar << endl;
            exit(1);
        }

        state = nextState;
        nextCharIndex++;
        if (!isspace(nextChar) && findCategory(nextChar) != 5 && currentWordAsIs.length() < 8)//adds character to a holder
        {
            currentWordAsIs.push_back(nextChar);
        }
        if (nextCharIndex > input.length())
        {
            notFinished = false;
        }
    }
    nextCharIndex = 0;
    return false;
}

int Scanner::findCategory(char ch)
{
    string charToString = {ch};
    if (isspace(ch))
    {
        return WS;
    }
    else if (isalpha(ch) || ch == '_')
    {
        return LETTER;
    }
    else if (isdigit(ch))
    {
        return DIGIT;
    }
    else if (operatorMap.count(charToString))
    {
        return VALID_OPERATOR;
    }
    else
    {
        return INVALID;
    }
}