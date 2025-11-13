#pragma once

#include <map>
#include <string>

namespace GUI::Installer::Audio {
	extern std::map<std::string, bool> Filetypes;
	void Render();
}