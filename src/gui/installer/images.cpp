#include "images.h"

#include "imgui.h"

void GUI::Installer::Images::Render() {
	static bool jpeg, png, bmp, gif, tiff, svg, webp, pdf;

	if (ImGui::BeginTabItem("Images")) {
		ImVec2 avail = ImGui::GetContentRegionAvail();
		float buttonHeight = ImGui::GetFrameHeightWithSpacing();
		float childHeight = avail.y - buttonHeight;
		if (ImGui::BeginChild("Scrollarea", ImVec2(0, childHeight), false, ImGuiWindowFlags_AlwaysUseWindowPadding)) {

			ImGui::Checkbox("jpeg", &jpeg);
			ImGui::Checkbox("png", &png);
			ImGui::Checkbox("bmp", &bmp);
			ImGui::Checkbox("gif", &gif);
			ImGui::Checkbox("tiff", &tiff);
			ImGui::Checkbox("svg", &svg);
			ImGui::Checkbox("webp", &webp);
			ImGui::Checkbox("pdf", &pdf);

			ImGui::EndChild();
		}

		ImGui::EndTabItem();
	}
}
