#pragma once

#include <map>
#include <string>

namespace GUI::Installer::Image {
	extern std::map<std::string, bool> Filetypes;
	void Render();
}