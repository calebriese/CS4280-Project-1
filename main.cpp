#include <iostream>
#include <string>
#include <cstring>
#include "testScanner.h"
using namespace std;

int main(int argc, char *argv[])
{
    fstream file;
    //gets the input and sees if a file was provided or not
    if (argc == 2)//file was provided
    {
        cout << "Reading input from file\n";
        string inputFile = argv[1];
        char * lastIndex = argv[1] + strlen(argv[1]);
        while (lastIndex > argv[1])
        {
            if (*lastIndex == '.')//there is an extension
            {
                break;
            }
            --lastIndex;
            if (lastIndex == argv[1])//not an extension
            {
                inputFile.append(".fs");
                break;
            }
        }
        file.open(inputFile);
    }
    else if (argc == 1)//read from the keyboard
    {
        string inputString;
        char *tmpname = strdup("/tmp/calebTMPFile");
        mkstemp(tmpname);
        file.open(tmpname);
        bool notBlank = true;
        cout << "Reading from the keyboard until blank line is entered\n";
        while (notBlank)
        {
            cout << "\nInput: ";
            getline(cin, inputString);
            file << inputString << endl;
            if (inputString.empty())
            {
                notBlank = false;
            }
        }
    }
    else
    {
        fprintf(stderr, "Incorrect Usage: Too many arguments provided.\n");
        return 1;
    }

    TestScanner testScanner;//call the testscanner and pass it the file
    testScanner.test(file);

    return 0;
}
