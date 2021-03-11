#include "testScanner.h"
#include "scanner.h"
#include <cstdio>

void TestScanner::test(fstream &file)//this is the testing function
{
    file.clear();
    file.seekg(0);//sets file to beginning
    if (file.is_open())
    {
        Scanner myScanner;
        string input;
        int lineNum = 0;
        while (getline(file, input))//gets lines while there are some
        {
            lineNum++;
            myScanner.filter(input);//gets rid of comments and counts line numbers
            while (myScanner.driver(input, myToken))//while there are tokens left in the line
            {
                cout << "Line:" << myToken.lineNumber << ", Token: " << tokenNames[myToken.tokenID] << myToken.tokenInstance << endl;
            }
        }
        myToken.lineNumber = lineNum;
        myToken.tokenID = EOFToken;
        myToken.tokenInstance = "EOF";// simulate EOF token
        cout << "Line:" << myToken.lineNumber << ", Token: " << tokenNames[myToken.tokenID] << " Instance: "<< myToken.tokenInstance << endl;
        file.close();
        remove("temporaryFile.txt");
    }
    else
    {
        cout << "Error opening the file";
    }
}
