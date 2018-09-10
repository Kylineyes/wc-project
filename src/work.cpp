#include "work.h"

Work::Work()
{
    charNum = 0;
    wordNum = 0;
    lineNum = 0;
    blankLineNum = 0;
    codeLineNum = 0;
    commentLineNum = 0;
    res = NULL;
}

Work::~Work()
{
    delete res;
}


bool Work::readFile(string fileName)
{
    ifstream fin;
    fin.open(fileName, ios::binary);
    if(fin.is_open() == false)
        return false;
    fin.seekg(0, ios::end);
    int len = static_cast<int>(fin.tellg()) + 1;
    fin.seekg(0, ios::beg);
    res = new char[len + 1];
    fin.read(res, len);
    res[len] = '\0';
    //cout << res << endl;
    return true;
}


bool Work::isUTF8 = false;
bool Work::calcChar = false;
bool Work::calcWord = false;
bool Work::calcLine = false;
bool Work::xMode = false;
bool Work::recursive = false;
bool Work::detail = false;
