#ifndef WSTRINGTOOL_H
#define WSTRINGTOOL_H

#include <wchar.h>
#include <string>
#include <windows.h>
using namespace std;
class WStringTool
{
public:
    WStringTool() = delete;
    ~WStringTool() = default;
    static string GbkToUtf8(const std::string& strGbk);
    static string Utf8ToGbk(const std::string& strUtf8);
    static wstring UTF8ToUnicode(const char* str);
    static char *UnicodeToUTF8(const wchar_t* str);
    static wstring GbkToUnicode(const char* strGbk);
    static string UnicodeToGbk (const std::wstring& strUnicode);
};

#endif // WSTRINGTOOL_H
