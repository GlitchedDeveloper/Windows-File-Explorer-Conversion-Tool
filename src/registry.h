#pragma once

#include <windows.h>
#include <shlobj.h>
#include <iostream>
#include <string>

namespace WindowsRegistry {
    bool SetRegString(HKEY root, const std::wstring &subkey, const std::wstring &name, const std::wstring &value);
    bool DeleteRegKey(HKEY root, const std::wstring &subkey);
};