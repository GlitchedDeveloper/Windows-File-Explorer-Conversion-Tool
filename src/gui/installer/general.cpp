#include "general.h"

#include "imgui.h"

void GUI::Installer::General::Render() {
	static char install_location[256];
	if (ImGui::BeginTabItem("General")) {
		ImVec2 avail = ImGui::GetContentRegionAvail();
		float buttonHeight = ImGui::GetFrameHeightWithSpacing();
		float childHeight = avail.y - buttonHeight;
		if (ImGui::BeginChild("Scrollarea", ImVec2(0, childHeight), false, ImGuiWindowFlags_AlwaysUseWindowPadding)) {

			ImGui::Text("Install Location");
			ImGui::SameLine();
			ImGui::InputText("###InstallLocation", install_location, sizeof(install_location));
			ImGui::SameLine();
			ImGui::Button("Choose Folder");

			ImGui::EndChild();
		}

		ImGui::EndTabItem();
	}

}