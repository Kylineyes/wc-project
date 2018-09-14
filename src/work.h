#ifndef WORK_H
#define WORK_H
#include <iostream>
#include <fstream>
#include <string>
#include "wstringtool.h"
using ostream = std::ostream;
using string = std::string;
using wstring = std::wstring;
using ifstream = std::ifstream;
using ios = std::ios;

class Work
{
public:
    Work();
    ~Work();

    bool readFile(const wchar_t* fileName);
    void parse();
    void formatOutput();

    static bool isUTF8;
    static bool calcChar;
    static bool calcWord;
    static bool calcLine;
    static bool xMode;
    static bool detail;

private:
    bool isAlpha(wchar_t wc);
    bool isDigit(wchar_t wc);
    bool isSpace(wchar_t wc);
    bool isSymbol(wchar_t wc);
    void init();
    wstring fileName;
    char *res;
    int charNum;
    int wordNum;
    int lineNum;
    int blankLineNum;
    int codeLineNum;
    int annotationLineNum;


};
#endif // WORK_H
