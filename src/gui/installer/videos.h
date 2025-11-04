#pragma once

#include <map>
#include <string>

namespace GUI::Installer::Videos {
	extern std::map<std::string, bool> Filetypes;
	void Render();
}