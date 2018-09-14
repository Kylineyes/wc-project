#include <iostream>
#include <vector>
#include <io.h>
#include <direct.h>
#include <queue>
#include "src/getopt.h"
#include "wstringtool.h"
#include "src/work.h"
using namespace std;

void getFiles(LPCWSTR folderPath, LPCWSTR para, vector<wstring>& target)
{
    HANDLE hFile;
    WIN32_FIND_DATA pNextInfo;
    wstring folderPathStr = folderPath;
    wstring paraStr = para;
    wstring matchStr = folderPathStr + paraStr;
    hFile = FindFirstFileW(matchStr.c_str(),&pNextInfo);
    if(hFile == INVALID_HANDLE_VALUE)
    {
        return;
    }
    target.push_back(folderPathStr + wstring(pNextInfo.cFileName));
    int count = 1;
    while(FindNextFile(hFile,&pNextInfo))
    {
        if(pNextInfo.cFileName[0] == '.')
           continue;
        target.push_back(folderPathStr + wstring(pNextInfo.cFileName));
    }
}

void traverseSubFolder(string& para, vector<wstring>& target)
{
    char* thisPath = _getcwd(NULL, 1024);

    queue<string> folderQue;

    folderQue.push(thisPath);
    wstring pathStr = WStringTool::GbkToUnicode(para.c_str());
    string path;

    _finddata_t fileInfo;
    while(!folderQue.empty())
    {
        path = folderQue.front();
        folderQue.pop();

        //cout << path << endl;
        //wstring searchFolder = WStringTool::GbkToUnicode((path + "\\" + para).c_str());
        wstring folderPathStr = WStringTool::GbkToUnicode(path.c_str()) + WStringTool::GbkToUnicode("\\");
        getFiles(folderPathStr.c_str(), pathStr.c_str(), target);

        string newPath = path + "\\*";
        intptr_t handle = _findfirst(newPath.c_str(), &fileInfo);
        do{
            if(strcmp(fileInfo.name, ".") == 0
                || strcmp(fileInfo.name, "..") == 0)
                continue;
            if(fileInfo.attrib & _A_SUBDIR) {
                folderQue.push( path + "\\" + fileInfo.name );
            }
        }while(_findnext(handle, &fileInfo) == 0);
    }

    delete[] thisPath;
}

int error(string msg)
{
    cout << msg << endl;
    exit(1);
}
int main(int argc, char* argv[])
{

    vector<wstring> files;
    vector<string> match;
    char par[] = "-cwlsax";
    bool recursive =false;
    while(true)
    {
        int c = getopt(argc, argv, par);
        if(c == -1)
            break;
        switch (c) {
        case 'c':Work::calcChar = true;
            break;
        case 'w':Work::calcWord = true;
            break;
        case 'l':Work::calcLine = true;
            break;
        case 's':recursive = true;
            break;
        case 'a':Work::detail = true;
            break;
        case 1:
            //files.push_back(WStringTool::GbkToUnicode(optarg));
            match.push_back(optarg);
        default:
            break;
        }
    }

    if(recursive) {
        for(auto& e : match)
            traverseSubFolder(e, files);
    } else {
        char* thisPath = _getcwd(NULL, 1024);
        wstring thisPathW = WStringTool::GbkToUnicode(thisPath) + WStringTool::GbkToUnicode("\\");
        for(auto& e : match) {
            wstring paraStr = WStringTool::GbkToUnicode(e.c_str());
            getFiles(thisPathW.c_str(), paraStr.c_str(), files);
        }
        delete[] thisPath;
    }

    Work work;
    for(auto& file : files) {
        work.readFile(file.c_str());
        work.parse();
        work.formatOutput();
    }
    return 0;
}
