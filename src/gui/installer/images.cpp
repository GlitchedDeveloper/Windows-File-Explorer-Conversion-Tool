#include "images.h"

#include "imgui.h"

void GUI::Installer::Images::Render() {
	static bool jpeg, png, bmp, gif, tiff, svg, webp, pdf;

	if (ImGui::BeginTabItem("Images")) {
		ImGui::Text("Supported Image Types:");
		ImGui::Separator();

		ImGui::Checkbox("JPEG", &jpeg);
		ImGui::Checkbox("PNG", &png);
		ImGui::Checkbox("BMP", &bmp);
		ImGui::Checkbox("GIF", &gif);
		ImGui::Checkbox("TIFF", &tiff);
		ImGui::Checkbox("SVG", &svg);
		ImGui::Checkbox("WEBP", &webp);
		ImGui::Checkbox("PDF", &pdf);

		ImGui::EndTabItem();
	}
}
