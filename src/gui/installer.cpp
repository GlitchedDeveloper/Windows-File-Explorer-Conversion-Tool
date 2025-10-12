#include "installer.h"

#include "imgui.h"

#include "installer/images.h"
#include "installer/general.h"

void GUI::Installer::Render() {
	if (ImGui::BeginTabBar("InstallerTabBar")) {
		General::Render();
		Images::Render();
		ImGui::EndTabBar();
	}
}