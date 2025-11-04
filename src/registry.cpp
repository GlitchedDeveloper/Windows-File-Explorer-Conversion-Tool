#include "registry.h"

#include <fstream>

bool WindowsRegistry::SetRegString(HKEY root, const std::wstring &subkey, const std::wstring &name, const std::wstring &value)
{
    HKEY hKey = NULL;
    LONG r = RegCreateKeyExW(root, subkey.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
    if (r != ERROR_SUCCESS) {
        std::wcerr << L"RegCreateKeyEx failed for " << subkey << L" : " << r << L"\n";
        return false;
    }
    r = RegSetValueExW(hKey, name.empty() ? NULL : name.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE*>(value.c_str()), static_cast<DWORD>((value.size()+1) * sizeof(wchar_t)));
    RegCloseKey(hKey);
    if (r != ERROR_SUCCESS) {
        std::wcerr << L"RegSetValueEx failed for " << subkey << L"\\" << name << L" : " << r << L"\n";
        return false;
    }
    return true;
}

static bool DeleteKeyRecursiveManual(HKEY root, const std::wstring &subkey)
{
    HKEY hKey = NULL;
    LONG r = RegOpenKeyExW(root, subkey.c_str(), 0, KEY_READ | KEY_WRITE, &hKey);
    if (r != ERROR_SUCCESS) {
        if (r == ERROR_FILE_NOT_FOUND) return true;
        std::wcerr << L"RegOpenKeyEx (recursive) failed for " << subkey << L" : " << r << L"\n";
        return false;
    }

    DWORD index = 0;
    wchar_t nameBuf[512];
    FILETIME ft;
    while (true) {
        DWORD nameLen = _countof(nameBuf);
        LONG rr = RegEnumKeyExW(hKey, index, nameBuf, &nameLen, NULL, NULL, NULL, &ft);
        if (rr == ERROR_NO_MORE_ITEMS) break;
        if (rr != ERROR_SUCCESS) {
            std::wcerr << L"RegEnumKeyEx failed for " << subkey << L" : " << rr << L"\n";
            RegCloseKey(hKey);
            return false;
        }
        std::wstring child = subkey + L"\\" + std::wstring(nameBuf, nameLen);
        if (!DeleteKeyRecursiveManual(root, child)) {
            RegCloseKey(hKey);
            return false;
        }
    }

    RegCloseKey(hKey);

    LONG del = RegDeleteKeyW(root, subkey.c_str());
    if (del != ERROR_SUCCESS) {
        std::wcerr << L"RegDeleteKey failed for " << subkey << L" : " << del << L"\n";
        return false;
    }
    return true;
}

bool WindowsRegistry::DeleteRegKey(HKEY root, const std::wstring &subkey)
{
    HMODULE adv = GetModuleHandleW(L"Advapi32.dll");
    if (adv) {
        using FnRegDeleteTreeW = LONG (WINAPI*)(HKEY, LPCWSTR);
        FnRegDeleteTreeW pDel = reinterpret_cast<FnRegDeleteTreeW>(GetProcAddress(adv, "RegDeleteTreeW"));
        if (pDel) {
            LONG r = pDel(root, subkey.c_str());
            if (r == ERROR_SUCCESS || r == ERROR_FILE_NOT_FOUND) return true;
            std::wcerr << L"RegDeleteTreeW failed for " << subkey << L" : " << r << L"\n";
        }
    }

    return DeleteKeyRecursiveManual(root, subkey);
}