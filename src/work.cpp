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

void Work::output()
{
    cout << "charNum: " << charNum << endl;
    cout << "wordNum: " << wordNum << endl;
    cout << "lineNum: " << lineNum << endl;
    cout << "blankLineNum: " << blankLineNum << endl;
    cout << "codeLineNum: " << codeLineNum << endl;
    cout << "annotationLineNum: " << annotationLineNum << endl;
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
    res = new char[len];
    fin.read(res, len);
    res[len-1] = '\0'; // before is 0xCD
    return true;
}

string Work::parse()
{
    //isUTF8 = true;
    //cout << isUTF8 << endl;
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
    bool isInMultiAnnotation = false;
    bool preIsStar = false;
    bool checkAlpha = false;
    auto iter = content.begin();
    while(iter != content.end())
    {
        if(*iter == '\r') { // remove '\r'
            ++iter;
            continue;
        }
        cout << "~" << *iter << "|" << (char)*iter << "~" << endl;
        ++charNum; // always
        if(*iter == '\n') {

            ++lineNum;

            if(checkAlpha) {
                ++wordNum;
            }

            if(isInMultiAnnotation) {
                ++annotationLineNum;
            } else if(!hasShowCodeChar && isInSingleAnnotation) {
                ++annotationLineNum;
            } else if(!hasShowVisualChar) {
                ++blankLineNum;
                cout << "wtf" << endl;
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
            //isInMultiAnnotation
            preIsStar = false;
            checkAlpha = false;

        } else if(isAlpha(*iter) || isDigit(*iter) || *iter == '_') {

            if(!isInMultiAnnotation && !isInSingleAnnotation) {
                hasShowVisualChar = true;
                hasShowCodeChar = true;
            }
            preIsSpaceChar = false;
            //hasShowSingleQuotaion = false;
            //hasShowDoubleQuotaion = false;
            preIsSlash = false;
            //isInSingleAnnotation = false;
            //isInMultiAnnotation
            preIsStar = false;
            checkAlpha = true;

        } else if(isSpace(*iter)) {

            if(checkAlpha) {
                ++wordNum;
            }

            preIsSpaceChar = true;
            preIsSlash = false;
            //isInSingleAnnotation = false;
            //isInMultiAnnotation
            preIsStar = false;
            checkAlpha = false;

        } else if(*iter == '/') {
            if(checkAlpha) {
                ++wordNum;
            }
            if(!isInSingleAnnotation) {
                if(preIsSlash) {
                    isInSingleAnnotation = true;
                } else if(preIsStar && isInMultiAnnotation) {
                    isInMultiAnnotation = false;
                    ++annotationLineNum;
                } else {
                    hasShowVisualChar = true;
                }
            }


            preIsSpaceChar = false;
            preIsStar = false;
            preIsSlash = true;
            checkAlpha = false;

        } else if(*iter == '*') {
            if(checkAlpha) {
                ++wordNum;
            }

            if(!isInSingleAnnotation) {
                if(preIsSlash) {
                    isInMultiAnnotation = true;
                }
            }

            preIsSpaceChar = false;
            preIsSlash = false;
            preIsStar = true;
            checkAlpha = false;

        } else if(isSymbol(*iter)) {
            if(checkAlpha) {
                ++wordNum;
            }
            if(!isInMultiAnnotation && !isInSingleAnnotation) {
                hasShowVisualChar = true;
            }
            preIsSpaceChar = false;
            preIsSlash = false;
            preIsStar = false;
            checkAlpha = false;

        } else {
            ++wordNum;
            cout << "!" << *iter << "!";

            preIsSpaceChar = false;
            preIsSlash = false;
            preIsStar = false;
            checkAlpha = false;
        }

        ++iter;
    }


    return "done";
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
