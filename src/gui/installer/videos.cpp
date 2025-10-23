#include "videos.h"

#include "imgui.h"

void GUI::Installer::Videos::Render() {
	static bool mp4, mp3, mov, wmv, avi, mkv, flv, webm, mpg, mpeg, _3gp, _3g2;

	if (ImGui::BeginTabItem("Videos")) {
		ImGui::Text("Placeholder");
		ImGui::Checkbox("mp4", &mp4);
		ImGui::Checkbox("mp3", &mp3);
		ImGui::Checkbox("mov", &mov);
		ImGui::Checkbox("wmv", &wmv);
		ImGui::Checkbox("avi", &avi);
		ImGui::Checkbox("mkv", &mkv);
		ImGui::Checkbox("flv", &flv);
		ImGui::Checkbox("webm", &webm);
		ImGui::Checkbox("mpg", &mpg);
		ImGui::Checkbox("mpeg", &mpeg);
		ImGui::Checkbox("3gp", &_3gp);
		ImGui::Checkbox("3g2", &_3g2);






		if (ImGui::CollapsingHeader("More Options")) {




		}
		ImGui::EndTabItem();
	}
}