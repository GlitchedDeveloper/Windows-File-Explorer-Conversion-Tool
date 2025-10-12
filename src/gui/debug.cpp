#include "debug.h"

#include "imgui.h"

#include "window.h"

void GUI::Debug::Render() {
    ImGui::Text("Select a GUI to test");
    if (ImGui::Button("Installer")) {
        GUI::Window::CurrentGUI = GUIType::Installer;
    }
}