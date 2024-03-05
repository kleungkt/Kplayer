#include "qstatuscheck.h"
#include <Windows.h>
#include <QDebug>

HMODULE
(*MyLoadLibraryA)(
    _In_ LPCSTR lpLibFileName
) = NULL;

FARPROC
(*MyGetProcAddress)(
    _In_ HMODULE hModule,
    _In_ LPCSTR lpProcName
);

VOID (* myExitProcess)(UINT uExitCode);

static
class StaticData
{
public:
    StaticData()
    {
        MyLoadLibraryA = reinterpret_cast<HMODULE(*)(LPCSTR)>(LoadLibraryA);
        MyGetProcAddress = reinterpret_cast<FARPROC(*)(HMODULE, LPCSTR)>(GetProcAddress);
    }
} _;

QStatusCheck::QStatusCheck(QObject* parent) : QThread(parent)
{
    //             ExitProcess
    //             +-+-+-+-+-+
    //             BA987654321
    char data[] = "PnrlWlt_hqt";//"ExitProcess";
    //            Kernel32.dll
    //            +-+-+-+-+-+-
    //            CBA987654321
    char dll[] = "WZ|eme9-2ank";
    for(int i = 0; i < 11; i++)
    {
        //Restore ExitProcess
        if(i % 2 == 0)
        {
            data[i] -= (11 - i);
        }
        else
        {
            data[i] += (11 - i);
        }
    }
    for(int i = 0; i < 12; i++)
    {
        //Restore Kernel32.dll
        if(i % 2 == 0)
        {
            dll[i] -= (12 - i);
        }
        else
        {
            dll[i] += (12 - i);
        }
    }
    HMODULE hdll = MyLoadLibraryA(dll);
    myExitProcess = (VOID(*)(UINT))MyGetProcAddress(hdll, data);
}
extern bool LOGIN_STATUS;
void QStatusCheck::run()
{
    m_status = LOGIN_STATUS;
    if(m_status == false)
    {
        myExitProcess(0);
        //qDebug() << __FILE__ << __LINE__ << LOGIN_STATUS << m_status;
        abort();
        exit(0);
    }
}
