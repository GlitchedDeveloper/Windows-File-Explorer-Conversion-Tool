#include "installer.h"

#include "imgui.h"

#include "installer/images.h"
#include "installer/general.h"
#include "installer/videos.h"

void GUI::Installer::Render() {
    if (ImGui::BeginTabBar("InstallerTabBar")) {
        General::Render();
        Images::Render();
        Videos::Render();
        ImGui::EndTabBar();
    }
    
    float cursorPosY = ImGui::GetCursorPosY();
    if (ImGui::Button("Install")) {
    }

    {
        float textWidth = ImGui::CalcTextSize("Uninstall", nullptr, true).x;
        ImVec2 padding = ImGui::GetStyle().FramePadding;
        float windowWidth = ImGui::GetContentRegionAvail().x;
        ImGui::SetCursorPosX(windowWidth - padding.x - textWidth);
        ImGui::SetCursorPosY(cursorPosY);
    }

    if (ImGui::Button("Uninstall")) {

    }
}