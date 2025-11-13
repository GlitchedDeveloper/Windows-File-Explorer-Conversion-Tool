#include "audio.h"

#include "imgui.h"

#include "../../config.h"

std::map<std::string, bool> GUI::Installer::Audio::Filetypes = {
    {"mp3", false},
    {"wav", false},
    {"aac", false},
    {"flac", false},
    {"ogg", false},
    {"wma", false},
    {"m4a", false},
    {"alac", false},
    {"ac3", false},
    {"opus", false},
    {"amr", false},
    {"aiff", false},
    {"caf", false},
    {"mp2", false},
    {"dsd", false},
    {"pcm", false},
    {"au", false}
};

void GUI::Installer::Audio::Render() {
	if (ImGui::BeginTabItem("Audio")) {
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