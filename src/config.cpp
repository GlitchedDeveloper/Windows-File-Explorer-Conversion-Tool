#include "config.h"

#include "gui/installer/video.h"
#include "gui/installer/audio.h"

#include <fstream>
#include <cstring>
#include <cstdint>
#include <vector>

bool Config::Write() {
    std::ofstream out("data.wfect", std::ios::binary);
    if (!out) return false;

    out.write("WFECT", 5);
    for (const auto& [extension, enabled] : GUI::Installer::Video::Filetypes)
        if (enabled)    
            out.write(extension.c_str(), extension.size() + 1);
    for (const auto& [extension, enabled] : GUI::Installer::Audio::Filetypes)
        if (enabled)
            out.write(extension.c_str(), extension.size() + 1);
    return out.good();
}

bool Config::Read() {
    std::ifstream in("data.wfect", std::ios::binary);
    if (!in) return false;

    char header[6] = {};
    in.read(header, 5);
    if (in.gcount() != 5 || std::strncmp(header, "WFECT", 5) != 0)
        return false;

    for (auto &p : GUI::Installer::Video::Filetypes)
        p.second = false;
    for (auto &p : GUI::Installer::Audio::Filetypes)
        p.second = false;

    std::string extension;
    while (std::getline(in, extension, '\0')) {
        if (extension.empty())
            continue;

        auto itV = GUI::Installer::Video::Filetypes.find(extension);
        if (itV != GUI::Installer::Video::Filetypes.end()) {
            itV->second = true;
            continue;
        }

        auto itA = GUI::Installer::Audio::Filetypes.find(extension);
        if (itA != GUI::Installer::Audio::Filetypes.end()) {
            itA->second = true;
            continue;
        }
    }

    if (in.fail() && !in.eof())
        return false;

    return true;
}