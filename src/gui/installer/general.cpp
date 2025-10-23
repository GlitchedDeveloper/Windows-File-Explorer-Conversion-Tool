#include "general.h"

#include "imgui.h"

void GUI::Installer::General::Render() {
	static char install_location[256];

	if (ImGui::BeginTabItem("General")) {
		ImGui::Text("Placeholder");
		ImGui::Text("Install Location");
		ImGui::SameLine();
		ImGui::InputText("###InstallLocation", install_location, sizeof(install_location));
		ImGui::SameLine();
		ImGui::Button("Choose Folder");
		ImGui::EndTabItem();
	}
}