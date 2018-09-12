#include "work.h"

Work::Work()
{
    charNum = 0;
    wordNum = 0;
    lineNum = 0;
    blankLineNum = 0;
    codeLineNum = 0;
    annotationLineNum = 0;
    res = nullptr;
}

Work::~Work()
{
    delete res;
}

//void Work::output()
//{
//    cout << "charNum: " << charNum << endl;
//    cout << "wordNum: " << wordNum << endl;
//    cout << "lineNum: " << lineNum << endl;
//    cout << "blankLineNum: " << blankLineNum << endl;
//    cout << "codeLineNum: " << codeLineNum << endl;
//    cout << "annotationLineNum: " << annotationLineNum << endl;
//}


bool Work::readFile(string fileName)
{
    ifstream fin;
    fin.open(fileName, ios::binary);
    if(fin.is_open() == false)
        return false;
    fin.seekg(0, ios::end);
    int len = static_cast<int>(fin.tellg()) + 1;
    fin.seekg(0, ios::beg);
    res = new char[len];
    fin.read(res, len);
    res[len-1] = '\0'; // before is 0xCD
    return true;
}

void Work::formatOutput()
{
    if(Work::calcChar) {
        wcout << "The number of char is " << charNum << endl;
    }
    if(Work::calcWord) {
        wcout << "The number of word is " << wordNum << endl;
    }
    if(Work::calcLine) {
        wcout << "The number of line is " << lineNum << endl;
    }
    if(Work::detail) {
        wcout << "The number of blank-line is " << blankLineNum << endl;
        wcout << "The number of code-line is " << codeLineNum << endl;
        wcout << "The number of annotation-line is " << annotationLineNum << endl;
    }
}

void Work::parse()
{
    wstring content = (isUTF8)
            ? WStringTool::UTF8ToUnicode(res + 3) // remove BOM
            : WStringTool::GbkToUnicode(res);
    bool hasShowVisualChar = false;
    bool hasShowCodeChar = false;
    bool preIsSpaceChar = true;
    bool hasShowSingleQuotaion = false;
    bool hasShowDoubleQuotaion = false;
    bool preIsSlash = false;
    bool isInSingleAnnotation = false;
    bool checkAlpha = false;
    auto iter = content.begin();
    while(iter != content.end())
    {
        if(*iter == '\r') { // remove '\r'
            ++iter;
            continue;
        }
        ++charNum; // always
        if(*iter == '\n') {

            ++lineNum;

            if(checkAlpha) {
                ++wordNum;
            }

            if(!hasShowCodeChar && isInSingleAnnotation) {
                ++annotationLineNum;
            } else if(!hasShowVisualChar) {
                ++blankLineNum;
            } else {
                ++codeLineNum;
            }

            hasShowVisualChar = false;
            hasShowCodeChar = false;
            preIsSpaceChar = true;
            hasShowSingleQuotaion = false;
            hasShowDoubleQuotaion = false;
            preIsSlash = false;
            isInSingleAnnotation = false;
            checkAlpha = false;

        } else if(isAlpha(*iter) || isDigit(*iter) || *iter == '_') {

            if(!isInSingleAnnotation) {
                hasShowVisualChar = true;
                hasShowCodeChar = true;
            }
            preIsSpaceChar = false;
            preIsSlash = false;
            checkAlpha = true;

        } else if(isSpace(*iter)) {

            if(checkAlpha) {
                ++wordNum;
            }

            preIsSpaceChar = true;
            preIsSlash = false;
            checkAlpha = false;

        } else if(*iter == '/') {
            if(checkAlpha) {
                ++wordNum;
            }
            if(!isInSingleAnnotation && preIsSlash) {
                    isInSingleAnnotation = true;
            }

            preIsSpaceChar = false;
            preIsSlash = true;
            checkAlpha = false;

        }else if(isSymbol(*iter)) {
            if(checkAlpha) {
                ++wordNum;
            }
            if(!isInSingleAnnotation) {
                hasShowVisualChar = true;
            }
            preIsSpaceChar = false;
            preIsSlash = false;
            checkAlpha = false;

        } else {
            ++wordNum;

            preIsSpaceChar = false;
            preIsSlash = false;
            checkAlpha = false;
        }

        ++iter;
    }

    ++lineNum;

    if(checkAlpha) {
        ++wordNum;
    }

    if(!hasShowCodeChar && isInSingleAnnotation) {
        ++annotationLineNum;
    } else if(!hasShowVisualChar) {
        ++blankLineNum;
    } else {
        ++codeLineNum;
    }

}

bool Work::isAlpha(wchar_t wc)
{
    if(('a' <= wc && wc <= 'z') || ('A' <= wc && wc <= 'Z'))
        return true;
    return false;
}

bool Work::isDigit(wchar_t wc)
{
    if('0' <= wc && wc <= '9')
        return true;
    return false;
}

bool Work::isSpace(wchar_t wc)
{
    if(wc == ' ' || wc == '\t')
        return true;
    return false;
}

bool Work::isSymbol(wchar_t wc)
{

    switch(wc){
    case '!':case '@':case '#':case '$':
    case '%':case '^':case '&':case '*':
    case '(':case ')':case '-':case '=':
    case '+':case '{':case '[':case ']':
    case '}':case ':':case ';':case '\'':
    case '\"':case '\\':case '|':case ',':
    case '<':case '.':case '>':case '/':
    case '?':case '`':case '~':case '_':
        return true;
    }
    return false;
}



bool Work::isUTF8 = false;
bool Work::calcChar = false;
bool Work::calcWord = false;
bool Work::calcLine = false;
bool Work::xMode = false;
bool Work::detail = false;
