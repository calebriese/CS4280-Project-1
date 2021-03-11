#ifndef TESTSCANNER_H
#define TESTSCANNER_H
#include <iostream>
#include <string>
#include "token.h"
#include <fstream>
using namespace std;

class TestScanner
{
    Token myToken;
    public:
    void test(fstream &file);
};
#endif