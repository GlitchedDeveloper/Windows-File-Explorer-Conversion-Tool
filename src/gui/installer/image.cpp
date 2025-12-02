#include "image.h"

#include "imgui.h"

#include "../../config.h"

std::map<std::string, bool> GUI::Installer::Image::Filetypes = {
    {"png", false},
    {"jpg", false},
    {"jpeg", false},
    {"bmp", false},
    {"gif", false},
    {"tiff", false},
    {"tif", false},
    {"webp", false},
    {"heic", false},
    {"heif", false},
    {"avif", false},
    {"ico", false},
    {"svg", false}
};

void GUI::Installer::Image::Render() {
	if (ImGui::BeginTabItem("Image")) {
		ImVec2 avail = ImGui::GetContentRegionAvail();
		float buttonHeight = ImGui::GetFrameHeightWithSpacing();
		float childHeight = avail.y - buttonHeight;

		if (ImGui::BeginChild("Scrollarea", ImVec2(0, childHeight), false, ImGuiWindowFlags_AlwaysUseWindowPadding)) {
			if (ImGui::Button("Enable All"))
				for (auto& [extension, enabled] : Filetypes) {
					enabled = true;
					Config::Write();
				}
			ImGui::SameLine();
			if (ImGui::Button("Disable All"))
				for (auto& [extension, enabled] : Filetypes) {
					enabled = false;
					Config::Write();
				}

			for (auto& [extension, enabled] : Filetypes) {
				if (ImGui::Checkbox(extension.c_str(), &enabled))
					Config::Write();
			}
			ImGui::EndChild();
		}


		ImGui::EndTabItem();
	}
}