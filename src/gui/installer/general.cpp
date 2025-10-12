#include "general.h"

#include "imgui.h"

void GUI::Installer::General::Render() {
	if (ImGui::BeginTabItem("General")) {
		ImGui::Text("Placeholder");
		ImGui::EndTabItem();
	}
}