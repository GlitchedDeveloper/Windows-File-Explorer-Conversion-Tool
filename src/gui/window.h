#pragma once

enum GUIType {
	Debug,
	Installer
};

namespace GUI::Window {
	extern GUIType CurrentGUI;
	void Render();
}