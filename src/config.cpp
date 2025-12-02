#include "config.h"

#include "gui/installer/video.h"
#include "gui/installer/audio.h"
#include "gui/installer/image.h"

#include <fstream>
#include <cstring>
#include <cstdint>
#include <vector>

std::string Config::Install_Location = "C:\\Program Files\\WFECT";

bool Config::Write() {
    std::ofstream out("data.wfect", std::ios::binary);
    if (!out) return false;

    out.write("WFECT", 5);
    out.write(Install_Location.c_str(), Install_Location.size() + 1);
    for (const auto& [extension, enabled] : GUI::Installer::Video::Filetypes)
        if (enabled)    
            out.write(extension.c_str(), extension.size() + 1);
    for (const auto& [extension, enabled] : GUI::Installer::Audio::Filetypes)
        if (enabled)
            out.write(extension.c_str(), extension.size() + 1);
    for (const auto& [extension, enabled] : GUI::Installer::Image::Filetypes)
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
    for (auto &p : GUI::Installer::Image::Filetypes)
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

        auto itI = GUI::Installer::Image::Filetypes.find(extension);
        if (itI != GUI::Installer::Image::Filetypes.end()) {
            itI->second = true;
            continue;
        }
    }

    if (in.fail() && !in.eof())
        return false;

    return true;
}