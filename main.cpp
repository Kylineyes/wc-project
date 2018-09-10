#include <iostream>
#include "src/getopt.h"
#include "wstringtool.h"
#include "src/work.h"
using namespace std;

int error(string msg)
{
    cout << msg << endl;
    exit(1);
}
int main(int argc, char* argv[])
{
    string targetFile;
    char par[] = "-cwlsax";
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
        case 's':Work::recursive = true;
            break;
        case 'a':Work::detail = true;
            break;
        case 1:
            targetFile = optarg;
        default:
            break;
        }
    }
    if(targetFile.empty())
        error("filename's parameter is not accepted!");

    Work tes;
    tes.readFile(targetFile);
    return 0;
}
