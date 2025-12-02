#include "general.h"

#include "imgui.h"

#include "../../config.h"

void GUI::Installer::General::Render() {
	if (ImGui::BeginTabItem("General")) {
		ImVec2 avail = ImGui::GetContentRegionAvail();
		float buttonHeight = ImGui::GetFrameHeightWithSpacing();
		float childHeight = avail.y - buttonHeight;
		if (ImGui::BeginChild("Scrollarea", ImVec2(0, childHeight), false, ImGuiWindowFlags_AlwaysUseWindowPadding)) {

			ImGui::Text("Install Location");
			ImGui::SameLine();
			{
				char buf[260];
				strncpy(buf, Config::Install_Location.c_str(), sizeof(buf));
				buf[sizeof(buf) - 1] = '\0';
				if (ImGui::InputText("###InstallLocation", buf, sizeof(buf))) {
					Config::Install_Location = buf;
				}
			}
			ImGui::SameLine();
			ImGui::Button("Choose Folder");

			ImGui::EndChild();
		}

		ImGui::EndTabItem();
	}

}