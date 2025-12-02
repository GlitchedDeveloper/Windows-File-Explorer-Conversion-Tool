#pragma once

#include <string>

namespace Config {
	extern std::string Install_Location;
    bool Write();
    bool Read();
}