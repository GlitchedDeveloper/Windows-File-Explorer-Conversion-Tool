#include "images.h"

#include "imgui.h"

void GUI::Installer::Images::Render() {
	if (ImGui::BeginTabItem("Images")) {
		ImGui::Text("Placeholder");
		ImGui::EndTabItem();
	}
}