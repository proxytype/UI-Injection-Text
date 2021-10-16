// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include "detours.h"

typedef BOOL(WINAPI* realSetDlgItemTextW)(
    HWND    hDlg,
    int     nIDDlgItem,
    LPCWSTR lpString

    );

realSetDlgItemTextW originalRealSetDlgItemTextW = (realSetDlgItemTextW)GetProcAddress(GetModuleHandleA("User32.dll"), "SetDlgItemTextW");

BOOL WINAPI _SetDlgItemTextW(
    HWND    hDlg,
    int     nIDDlgItem,
    LPCWSTR lpString) {

    LPCWSTR d = L"----";

    return originalRealSetDlgItemTextW(hDlg, nIDDlgItem, d);

}

void attachDetour() {

    DetourRestoreAfterWith();
    DetourTransactionBegin();

    DetourUpdateThread(GetCurrentThread());

    DetourAttach((PVOID*)&originalRealSetDlgItemTextW, _SetDlgItemTextW);

    DetourTransactionCommit();
}

void deAttachDetour() {

    DetourTransactionBegin();

    DetourUpdateThread(GetCurrentThread());

    DetourDetach((PVOID*)&originalRealSetDlgItemTextW, _SetDlgItemTextW);

    DetourTransactionCommit();
}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        attachDetour();
        break;
    case DLL_PROCESS_DETACH:
        deAttachDetour();
        break;
    }
    return TRUE;
}


