#ifndef WORK_H
#define WORK_H
#include <iostream>
#include <fstream>
#include <string>
#include "wstringtool.h"
//using namespace std;
//using std::string = string;
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
    friend ostream& operator << (ostream& out, const Work& o)
    {
        return out;
    }

    void output();

    bool readFile(string fileName);
    string parse();

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
    char *res;
    int charNum;
    int wordNum;
    int lineNum;
    int blankLineNum;
    int codeLineNum;
    int annotationLineNum;


};
#endif // WORK_H
