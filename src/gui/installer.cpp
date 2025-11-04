#include "installer.h"

#include "imgui.h"

#include "installer/images.h"
#include "installer/general.h"
#include "installer/videos.h"

#include "../registry.h"

#include <codecvt>
#include <locale>

std::wstring GetExecutablePathW()
{
    wchar_t buffer[MAX_PATH];
    DWORD length = GetModuleFileNameW(NULL, buffer, MAX_PATH);
    if (length == 0 || length == MAX_PATH)
        return {};
    return std::wstring(buffer, length);
}

void GUI::Installer::Render() {
    if (ImGui::BeginTabBar("InstallerTabBar")) {
        General::Render();
        Images::Render();
        Videos::Render();
        ImGui::EndTabBar();
    }
    
    float cursorPosY = ImGui::GetCursorPosY();
    if (ImGui::Button("Install")) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;

        std::wstring exe_path = GetExecutablePathW();
        exe_path = L"\"" + exe_path + L"\"";

        for (const auto& [extension, enabled] : Videos::Filetypes) {
            if (enabled) {
                const std::wstring base = L"SystemFileAssociations\\." + conv.from_bytes(extension) + L"\\shell\\ConvertTo";

                if (!WindowsRegistry::SetRegString(HKEY_CLASSES_ROOT, base, L"MUIVerb", L"Convert to...")) return;
                if (!WindowsRegistry::SetRegString(HKEY_CLASSES_ROOT, base, L"SubCommands", L"")) return;

                for (const auto& [sub_extension, sub_enabled] : Videos::Filetypes) {
                    if (sub_enabled && extension != sub_extension) {
                        if (!WindowsRegistry::SetRegString(HKEY_CLASSES_ROOT, base + L"\\shell\\" + conv.from_bytes(sub_extension), L"", conv.from_bytes(sub_extension))) return;
                        if (!WindowsRegistry::SetRegString(HKEY_CLASSES_ROOT, base + L"\\shell\\" + conv.from_bytes(sub_extension) + L"\\command", L"", exe_path + L" \"%1\" \"" + conv.from_bytes(sub_extension) + L"\"")) return;
                    }
                }
            }
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
        for (const auto& [extension, enabled] : Videos::Filetypes) {
            std::wstring extw = conv.from_bytes(extension);
            std::wstring base = L"SystemFileAssociations\\." + extw + L"\\shell\\ConvertTo";
            WindowsRegistry::DeleteRegKey(HKEY_CLASSES_ROOT, base);
        }
    }
}