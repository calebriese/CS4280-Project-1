#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <string>
#include <map>
using namespace std;

enum TokenID {identifierToken, numberToken, keywordToken, operatorToken, EOFToken};

typedef struct token
{
    TokenID tokenID;
    string tokenInstance;
    int lineNumber;
}Token;

const map<string,string> operatorMap = {
        {"=","EqualToken"},
        {"=>","GreaterThanEqualToken"},
        {"=<","LessThanEqualToken"},
        {"==","EqualityToken"},
        {":","ColonToken"},
        {":=","ColonEqualToken"},
        {"+","AdditionToken"},
        {"-","SubtractionToken"},
        {"*","MultiplicationToken"},
        {"/","DivisionToken"},
        {"%","ModuloToken"},
        {".","DecimalToken"},
        {"(","OpenParenthesisToken"},
        {")","CloseParenthesisToken"},
        {",","CommaToken"},
        {"{","OpenBraceToken"},
        {"}","CloseBraceToken"},
        {";","SemicolonToken"},
        {"[","OpenBracketToken"},
        {"]","CloseBracketToken"},
        {"<","lessThanToken"},
        {">","greaterThanToken"}
};
///If things are starting to break then remove the last two >< tokens from this ^
const map<string,string> keywordMap = {
        {"begin","BeginToken"},
        {"end","EndToken"},
        {"loop","LoopToken"},
        {"whole","WholeToken"},
        {"void","VoidToken"},
        {"exit","ExitToken"},
        {"getter","GetterToken"},
        {"outter","OutterToken"},
        {"main","MainToken"},
        {"if","IfToken"},
        {"then","ThenToken"},
        {"assign","AssignToken"},
        {"data","DataToken"},
        {"proc","ProcToken"}
};

const string tokenNames[5] = {"Identfier", "Number", "Keyword", "Operator", "EOF"};

#endif