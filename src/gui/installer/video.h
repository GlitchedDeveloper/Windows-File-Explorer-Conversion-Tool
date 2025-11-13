#pragma once

#include <map>
#include <string>

namespace GUI::Installer::Video {
	extern std::map<std::string, bool> Filetypes;
	void Render();
}