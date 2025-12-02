#include "window.h"

#include "imgui.h"

#include "debug.h"
#include "installer.h"

GUIType GUI::Window::CurrentGUI = GUIType::Installer;

void GUI::Window::Render() {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5.0f, 5.0f));
    ImGui::Begin("Window", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoDecoration);
    ImGui::PopStyleVar(3);

    switch (CurrentGUI) {
    case GUIType::Debug:
        GUI::Debug::Render();
        break;
    case GUIType::Installer:
        GUI::Installer::Render();
        break;
    default:
        break;
    }

    ImGui::End();
}