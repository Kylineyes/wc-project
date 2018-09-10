#include "wstringtool.h"

string WStringTool::GbkToUtf8(const string &strGbk)//传入的strGbk是GBK编码
{
    //gbk转unicode
    int len = MultiByteToWideChar(CP_ACP, 0, strGbk.c_str(), -1, NULL, 0);
    wchar_t *strUnicode = new wchar_t[len];
    wmemset(strUnicode, 0, len);
    MultiByteToWideChar(CP_ACP, 0, strGbk.c_str(), -1, strUnicode, len);

    //unicode转UTF-8
    len = WideCharToMultiByte(CP_UTF8, 0, strUnicode, -1, NULL, 0, NULL, NULL);
    char * strUtf8 = new char[len];
    WideCharToMultiByte(CP_UTF8, 0, strUnicode, -1, strUtf8, len, NULL, NULL);

    std::string strTemp(strUtf8);//此时的strTemp是UTF-8编码
    delete[]strUnicode;
    delete[]strUtf8;
    strUnicode = NULL;
    strUtf8 = NULL;
    return strTemp;
}

string WStringTool::Utf8ToGbk(const string &strUtf8)//传入的strUtf8是UTF-8编码
{
    //UTF-8转unicode
    int len = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, NULL, 0);
    wchar_t * strUnicode = new wchar_t[len];//len = 2
    wmemset(strUnicode, 0, len);
    MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, strUnicode, len);

    //unicode转gbk
    len = WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, NULL, 0, NULL, NULL);
    char *strGbk = new char[len];//len=3 本来为2，但是char*后面自动加上了\0
    memset(strGbk, 0, len);
    WideCharToMultiByte(CP_ACP,0, strUnicode, -1, strGbk, len, NULL, NULL);

    std::string strTemp(strGbk);//此时的strTemp是GBK编码
    delete[]strUnicode;
    delete[]strGbk;
    strUnicode = NULL;
    strGbk = NULL;
    return strTemp;
}

wstring WStringTool::UTF8ToUnicode(const char *str)
{
    int textlen ;
    wchar_t * result;
    textlen = MultiByteToWideChar( CP_UTF8, 0, str,-1, NULL,0 );
    result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t));
    memset(result,0,(textlen+1)*sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0,str,-1,(LPWSTR)result,textlen );
    std::wstring strTemp(result);
    return strTemp;
}

char *WStringTool::UnicodeToUTF8(const wchar_t *str)
{
    char* result;
    int textlen;
    textlen = WideCharToMultiByte( CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL );
    result =(char *)malloc((textlen+1)*sizeof(char));
    memset(result, 0, sizeof(char) * ( textlen + 1 ) );
    WideCharToMultiByte( CP_UTF8, 0, str, -1, result, textlen, NULL, NULL );
    return result;
}

wstring WStringTool::GbkToUnicode(const char* strGbk)//返回值是wstring
{
    int len = MultiByteToWideChar(CP_ACP, 0, strGbk, -1, NULL, 0);
    wchar_t *strUnicode = new wchar_t[len];
    wmemset(strUnicode, 0, len);
    MultiByteToWideChar(CP_ACP, 0, strGbk, -1, strUnicode, len);

    std::wstring strTemp(strUnicode);//此时的strTemp是Unicode编码
    delete[]strUnicode;
    strUnicode = NULL;
    return strTemp;
}

string WStringTool::UnicodeToGbk(const wstring &strUnicode)//参数是wstring
{
    int len = WideCharToMultiByte(CP_ACP, 0, strUnicode.c_str(), -1, NULL, 0, NULL, NULL);
    char *strGbk = new char[len];//len=3 本来为2，但是char*后面自动加上了\0
    memset(strGbk, 0, len);
    WideCharToMultiByte(CP_ACP,0,strUnicode.c_str(), -1, strGbk, len, NULL, NULL);

    std::string strTemp(strGbk);//此时的strTemp是GBK编码
    delete[]strGbk;
    strGbk = NULL;
    return strTemp;
}
