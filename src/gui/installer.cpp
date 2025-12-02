#include "installer.h"

#include "imgui.h"

#include "installer/image.h"
#include "installer/general.h"
#include "installer/video.h"
#include "installer/audio.h"

#include "../registry.h"
#include "../config.h"

#include <windows.h>
#include <urlmon.h>
#include <codecvt>
#include <locale>
#include <filesystem>

#pragma comment(lib, "urlmon.lib")

std::wstring GetExecutablePathW()
{
    wchar_t buffer[MAX_PATH];
    DWORD length = GetModuleFileNameW(NULL, buffer, MAX_PATH);
    if (length == 0 || length == MAX_PATH)
        return {};
    return std::wstring(buffer, length);
}

void RegEdit(std::map<std::string, bool>& Filetypes, std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>& conv, std::wstring& exe_path, bool* installNeeded) {
    for (const auto& [extension, enabled] : Filetypes) {
        if (enabled) {
            *installNeeded = true;

            const std::wstring base = L"SystemFileAssociations\\." + conv.from_bytes(extension) + L"\\shell\\wfect";

            if (!WindowsRegistry::SetRegString(HKEY_CLASSES_ROOT, base, L"MUIVerb", L"Convert to...")) return;
            if (!WindowsRegistry::SetRegString(HKEY_CLASSES_ROOT, base, L"SubCommands", L"")) return;

            for (const auto& [sub_extension, sub_enabled] : Filetypes) {
                if (sub_enabled && extension != sub_extension) {
                    if (!WindowsRegistry::SetRegString(HKEY_CLASSES_ROOT, base + L"\\shell\\" + conv.from_bytes(sub_extension), L"", conv.from_bytes(sub_extension))) return;
                    if (!WindowsRegistry::SetRegString(HKEY_CLASSES_ROOT, base + L"\\shell\\" + conv.from_bytes(sub_extension) + L"\\command", L"", exe_path + L" \"%1\" \"" + conv.from_bytes(sub_extension) + L"\"")) return;
                }
            }
        }
    }
}

void InstallFile(LPCSTR file) {
    std::filesystem::path install_location(Config::Install_Location);

    std::filesystem::create_directories(install_location);

    std::string base_url = "https://github.com/GlitchedDeveloper/Windows-File-Explorer-Conversion-Tool/raw/refs/heads/main/external/";
    std::string source_url = base_url + file;
    
    if (!std::filesystem::exists(install_location / file)) {
        std::filesystem::create_directories((install_location / file).parent_path());
        std::string destination_path_str = (install_location / file).string();

        URLDownloadToFileA(
            NULL, 
            source_url.c_str(), 
            destination_path_str.c_str(), 
            0, 
            NULL
        );
    }
}

void GUI::Installer::Render() {
    if (ImGui::BeginTabBar("InstallerTabBar")) {
        General::Render();
        Image::Render();
        Video::Render();
        Audio::Render();
        ImGui::EndTabBar();
    }
    
    float cursorPosY = ImGui::GetCursorPosY();
    if (ImGui::Button("Install")) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;

        std::wstring exe_path = GetExecutablePathW();
        exe_path = L"\"" + exe_path + L"\"";

        bool FFMPEG = false;
        bool nconvert = false;

        RegEdit(Video::Filetypes, conv, exe_path, &FFMPEG);
        RegEdit(Audio::Filetypes, conv, exe_path, &FFMPEG);
        RegEdit(Image::Filetypes, conv, exe_path, &nconvert);

        if (FFMPEG) {
            InstallFile("ffmpeg.exe");
        }
        if (nconvert) {
            InstallFile("nconvert/nconvert.exe");
            InstallFile("nconvert/vcomp120.dll");
            InstallFile("nconvert/plugins/aom.dll");
            InstallFile("nconvert/plugins/dav1d.dll");
            InstallFile("nconvert/plugins/heif.dll");
            InstallFile("nconvert/plugins/libJPEGXL.dll");
            InstallFile("nconvert/plugins/libde265.dll");
            InstallFile("nconvert/plugins/libsharpyuv.dll");
            InstallFile("nconvert/plugins/libwebp.dll");
            InstallFile("nconvert/plugins/libwebpdecoder.dll");
            InstallFile("nconvert/plugins/libwebpdemux.dll");
            InstallFile("nconvert/plugins/libwebpmux.dll");
            InstallFile("nconvert/plugins/libx265.dll");
            InstallFile("nconvert/plugins/openjp2.dll");
        }
    }

    {
        float textWidth = ImGui::CalcTextSize("Uninstall", nullptr, true).x;
        ImVec2 padding = ImGui::GetStyle().FramePadding;
        float windowWidth = ImGui::GetContentRegionAvail().x;
        ImGui::SetCursorPosX(windowWidth - padding.x - textWidth);
        ImGui::SetCursorPosY(cursorPosY);
    }

    if (ImGui::Button("Uninstall")) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
        for (const auto& [extension, enabled] : Video::Filetypes) {
            std::wstring extw = conv.from_bytes(extension);
            std::wstring base = L"SystemFileAssociations\\." + extw + L"\\shell\\wfect";
            WindowsRegistry::DeleteRegKey(HKEY_CLASSES_ROOT, base);
        }
        for (const auto& [extension, enabled] : Audio::Filetypes) {
            std::wstring extw = conv.from_bytes(extension);
            std::wstring base = L"SystemFileAssociations\\." + extw + L"\\shell\\wfect";
            WindowsRegistry::DeleteRegKey(HKEY_CLASSES_ROOT, base);
        }
    }
}