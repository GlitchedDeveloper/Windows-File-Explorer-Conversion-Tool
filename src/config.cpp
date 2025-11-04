#include "config.h"

#include "gui/installer/videos.h"

#include <fstream>
#include <cstring>
#include <cstdint>
#include <vector>

bool Config::Write() {
    std::ofstream out("data.wfect", std::ios::binary);
    if (!out) return false;

    out.write("WFECT", 5);
    int enabled_offset = 0;

    out.write(reinterpret_cast<const char*>(&enabled_offset), sizeof(enabled_offset));
    for (const auto& [extension, enabled] : GUI::Installer::Videos::Filetypes)
        out.write(extension.c_str(), extension.size() + 1);

    enabled_offset = static_cast<int>(out.tellp());

    uint8_t byte = 0;
    int bit_index = 0;
    for (const auto& [ext, enabled] : GUI::Installer::Videos::Filetypes) {
        if (enabled)
            byte |= (1 << bit_index);
        bit_index++;
        if (bit_index == 8) {
            out.put(static_cast<char>(byte));
            byte = 0;
            bit_index = 0;
        }
    }
    if (bit_index > 0)
        out.put(static_cast<char>(byte));

    out.seekp(5);
    out.write(reinterpret_cast<const char*>(&enabled_offset), sizeof(enabled_offset));
    return out.good();
}

bool Config::Read() {
    std::ifstream in("data.wfect", std::ios::binary);
    if (!in) return false;

    char header[6] = {};
    in.read(header, 5);
    if (std::strncmp(header, "WFECT", 5) != 0)
        return false;

    int enabled_offset = 0;
    in.read(reinterpret_cast<char*>(&enabled_offset), sizeof(enabled_offset));

    std::vector<std::pair<std::string, bool>> data;

    while (in.tellg() < enabled_offset && in) {
        std::string extension;
        std::getline(in, extension, '\0');
        if (!extension.empty())
            data.push_back({extension, false});
    }

    uint8_t byte = 0;
    int bit_index = 0;
    for (auto& [extension, enabled] : data) {
        if (bit_index == 0) {
            if (!in.read(reinterpret_cast<char*>(&byte), 1))
                break;
        }
        enabled = (byte >> bit_index) & 1;
        bit_index = (bit_index + 1) % 8;
    }
    
    for (auto& [extension, enabled] : data) {
        if (GUI::Installer::Videos::Filetypes.find(extension) != GUI::Installer::Videos::Filetypes.end())
            GUI::Installer::Videos::Filetypes[extension] = enabled;
    }

    return true;
}