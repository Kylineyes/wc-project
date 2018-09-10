#ifndef WORK_H
#define WORK_H
#include <iostream>
#include <fstream>
#include <string>
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

    bool readFile(string fileName);

    static bool isUTF8;
    static bool calcChar;
    static bool calcWord;
    static bool calcLine;
    static bool xMode;
    static bool recursive;
    static bool detail;
private:
    char *res;
    int charNum;
    int wordNum;
    int lineNum;
    int blankLineNum;
    int codeLineNum;
    int commentLineNum;


};
#endif // WORK_H
