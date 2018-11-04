#include <iostream>
#include <windows.h>
#include <string.h>
#include <stdio.h>

//#define MASK TEXT("*.*")
#define BufferSize 256
#define MASK "*.*"


using namespace std;

HANDLE CreateFile1(HANDLE hfile,LPCSTR PATH)
{
    hfile = CreateFile(PATH,
                       GENERIC_READ | GENERIC_WRITE,//dwDesiredAccess
                       FILE_SHARE_WRITE | FILE_SHARE_READ,//dwShareMode NULL - no one program can open your file
                       NULL,//lpSecurity
                       OPEN_ALWAYS,//dwCreationDisposition
                       FILE_ATTRIBUTE_NORMAL,
                       NULL
                       );
    return hfile;
}


BOOL CreateDirectory1(LPCSTR PATH)
{
    CreateDirectory(PATH,
                    NULL
                        );
}


void Search(char *Dir, char *Mask)
{
    char buf[1000]={0};
    sprintf(buf, "%s\\%s\r", Dir, Mask);

    WIN32_FIND_DATA FindFileData;
    HANDLE hf;
    hf=FindFirstFile(buf, &FindFileData);

    if (hf!=INVALID_HANDLE_VALUE)
    {
        do
        {
            sprintf(buf, "%s\\%s\r", Dir, FindFileData.cFileName);
            cout<<buf<<"\r\n";

            if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if (strcmp(FindFileData.cFileName,"..")!=0 && strcmp(FindFileData.cFileName,".")!=0)
                {
                    Search(buf, Mask);
                }
            }
        }
        while (FindNextFile(hf,&FindFileData)!=0);
        FindClose(hf);
    }

}


void Search1(char * Dir, char * mask,HANDLE hfile)
{
    char buf[256] = {0};
    sprintf(buf,"%s\\%s\r",Dir,mask);

    WIN32_FIND_DATA wind;
    HANDLE search = FindFirstFile(buf,&wind);

    if(search != INVALID_HANDLE_VALUE)
    {
        do{
            sprintf(buf,"%s\\%s\r",Dir,wind.cFileName);
            cout<<buf<<endl;
            if(wind.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    if (strcmp(wind.cFileName,"..")!=0 && strcmp(wind.cFileName,".")!=0)
                        {
                            DWORD id = 0;
                            WriteFile(hfile,&buf,strlen(buf),&id,NULL);
                            Search1(buf, mask, hfile);
                        }
                }

        }
        while(FindNextFile(search,&wind)!=0);
        FindClose(search);

    }
}



void ShowDirectory(LPCSTR path,LPCSTR name)
{
    WIN32_FIND_DATA wind;
    SetCurrentDirectory(path);

    char buf[BufferSize];
    HANDLE search1 = FindFirstFile(TEXT("*.*"),&wind);

    if(search1 != INVALID_HANDLE_VALUE)
    {
        do
        {
            GetCurrentDirectory(sizeof(buf),buf);
            if(wind.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    if (strcmp(wind.cFileName,"..")!=0 && strcmp(wind.cFileName,".")!=0)
                        {
                            //cout<<"Your Result: "<<endl;
                            //cout<<wind.cFileName<<endl;
                            if(strcmp(name,wind.cFileName) == 0)
                                cout<<"Your Directory Name: "<<wind.cFileName<<endl;
                            else
                                cout<<"Wrong DIRECTORY"<<endl;
                        }
                }
            else
            {
                if(strcmp(name,wind.cFileName) == 0)
                    cout<<"Your FILE Name: "<<wind.cFileName<<endl;
                else
                    cout<<"Wrong FILE"<<endl;

            }
           // SetCurrentDirectory(path);
        }
        while(FindNextFile(search1,&wind)!=0);
        FindClose(search1);
    }
    else
        cout<<"HJK";

}


void ReadF(HANDLE hfile, HANDLE hfile24)
{
    BOOL read;
    DWORD buffsize = GetFileSize(hfile,NULL);
    char group[100] = {"\nAdd information:\nGroup: FB-62. Name: Gennady_Shybaiev\r"};
    //TCHAR *buf = new char[buffsize];
    TCHAR buf[256];
    DWORD BytesRead;
    DWORD BytesWrite;

    do
        {
            printf("%s\r",buf);
            read = ReadFile(hfile,buf,buffsize,&BytesRead,NULL);
            if(read == false)
            {
                cout<<"FASLE ";
                break;
            }

            if(BytesRead == 0)//if nothing was readed
            {
                cout<<"BytesRead == NULL"<<endl;
                break;
            }
        }
    while(BytesRead != 0);
    printf("%s\r",buf);
    strcat(buf,group);
    cout<<buf<<endl;

    WriteFile(hfile24,buf,strlen(buf),&BytesWrite,NULL);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{

    HANDLE hfile,hdir,hfile23,hfile24;

    DWORD bufCount,bufTemp;
    BOOL Fwrite,w,Rfile,Cdirectory;
    char str[] = "My first text...";
    char buffer[BufferSize] = {0};
    DWORD BytesToWrite = strlen(str);
    DWORD BytesForRead = strlen(str);
    DWORD lpBytesWritten = 0;
    DWORD lpBytesRead = 0;
    DWORD nIn,nOt;

    LPCSTR PATH = "C:\\Users\\Gennady\\Desktop\\WinApi\\LAB2.txt";
    LPCSTR PATH23 = "C:\\Users\\Gennady\\Desktop\\WinApi\\FILE21\\FILE22\\FILE23\\FILE23.txt";
    LPCSTR PATH24 = "C:\\Users\\Gennady\\Desktop\\WinApi\\FILE21\\FILE22\\FILE23\\FILE24.txt";

    LPCSTR DIR_PATH = "C:\\Users\\Gennady\\Desktop\\WinApi\\FILE11";
    LPSTR DIR_PATH43 = "C:\\Users\\Gennady\\Desktop\\WinApi\\";
    LPCSTR DIR_PATH1 = "C:\\Users\\Gennady\\Desktop\\WinApi\\FILE11\\FILE12";
    LPCSTR DIR_PATH2 = "C:\\Users\\Gennady\\Desktop\\WinApi\\FILE11\\FILE12\\FILE13";
    LPCSTR DIR_PATH21 = "C:\\Users\\Gennady\\Desktop\\WinApi\\FILE21";
    LPCSTR DIR_PATH22 = "C:\\Users\\Gennady\\Desktop\\WinApi\\FILE21\\FILE22";
    LPCSTR DIR_PATH23 = "C:\\Users\\Gennady\\Desktop\\WinApi\\FILE21\\FILE22\\FILE23";



    hfile = CreateFile(PATH,
                        GENERIC_WRITE | GENERIC_READ,//dwDesiredAccess
                        FILE_SHARE_WRITE | FILE_SHARE_READ,//dwShareMode NULL - no one program can open your file
                        NULL,//lpSecurity
                        OPEN_ALWAYS,//dwCreationDisposition
                        FILE_ATTRIBUTE_NORMAL,
                        NULL
                        );
    hfile23 = CreateFile(PATH23,
                        GENERIC_WRITE | GENERIC_READ,//dwDesiredAccess
                        FILE_SHARE_WRITE | FILE_SHARE_READ,//dwShareMode NULL - no one program can open your file
                        NULL,//lpSecurity
                        OPEN_ALWAYS,//dwCreationDisposition
                        FILE_ATTRIBUTE_NORMAL,
                        NULL
                        );

    hfile24 = CreateFile(PATH24,
                        GENERIC_WRITE,//dwDesiredAccess
                        FILE_SHARE_WRITE | FILE_SHARE_READ,//dwShareMode NULL - no one program can open your file
                        NULL,//lpSecurity
                        OPEN_ALWAYS,//dwCreationDisposition
                        FILE_ATTRIBUTE_NORMAL,
                        NULL
                        );

    if(hfile==NULL)
    {
        cout<<"Your CreateFile HANDLE hfile CANNOT be created! "<<endl;
    }

    if(hfile23==NULL)
    {
        cout<<"Your CreateFile HANDLE hfile23 CANNOT be created! "<<endl;
    }

    if(hfile24==NULL)
    {
        cout<<"Your CreateFile HANDLE hfile24 CANNOT be created! "<<endl;
    }

    //CREATE DIRECTORY SYSTEM:
    //CreateFile1(hfile,PATH);
    CreateDirectory1(DIR_PATH);
    CreateDirectory1(DIR_PATH1);
    CreateDirectory1(DIR_PATH2);
    CreateDirectory1(DIR_PATH21);
    CreateDirectory1(DIR_PATH22);
    CreateDirectory1(DIR_PATH23);

    Fwrite = WriteFile(hfile23,//File HANDLE
                       str,//string to write
                       BytesToWrite,//how many bytes do you want o write?
                       &lpBytesWritten,//number of written bytes
                       NULL//for OVERLAPPED
                       );

    if(Fwrite == false)
    {
        cout<<"Your WriteFile BOOL CANNOT be created! \r"<<GetLastError()<<endl;

    }
    else
    {
        cout<<"Your TEXT was written\r"<<endl;
    }


    //Search in WinApi directory
    Search1(TEXT("C:\\Users\\Gennady\\Desktop\\WinApi\r"),TEXT("*.*\r"),hfile);
    //CopyFile(PATH,PATH23,FALSE);

    //Find FILE or DIRECTORY
    ShowDirectory(TEXT("C:\\Users\\Gennady\\Desktop\\WinApi\r"), TEXT("LAB2.txt\r"));

    ReadF(hfile,hfile24);


    //important because your program will close
    CloseHandle(hfile);//BUT for FileFirstFile we must use FindClose();
    CloseHandle(hfile23);
    CloseHandle(hfile24);
    system("pause");


    return 0;
}
