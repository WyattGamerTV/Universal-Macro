#include "Gdr2Parser.hpp"
#include <fstream>
#include <Geode/Geode.hpp>

bool Gdr2Parser::load(const ghc::filesystem::path& path, std::vector<MacroFrame>& outFrames) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) return false;

    // Read magic identifier header string "GDR2"
    char header[4];
    file.read(header, 4);
    if (std::string(header, 4) != "GDR2") return false;

    // Read the total number of frames stored in this binary file
    uint32_t totalFrames = 0;
    file.read(reinterpret_cast<char*>(&totalFrames), sizeof(totalFrames));

    outFrames.reserve(totalFrames);

    // Stream the binary structures straight into the macro vector buffer
    for (uint32_t i = 0; i < totalFrames; ++i) {
        MacroFrame frame;
        file.read(reinterpret_cast<char*>(&frame.frame), sizeof(frame.frame));
        file.read(reinterpret_cast<char*>(&frame.player2), sizeof(frame.player2));
        file.read(reinterpret_cast<char*>(&frame.holds), sizeof(frame.holds));
        file.read(reinterpret_cast<char*>(&frame.xPos), sizeof(frame.xPos));
        file.read(reinterpret_cast<char*>(&frame.yPos), sizeof(frame.yPos));
        outFrames.push_back(frame);
    }
    return true;
}

bool Gdr2Parser::save(const ghc::filesystem::path& path, const std::vector<MacroFrame>& inFrames) {
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) return false;

    // Write binary identifier string signature
    file.write("GDR2", 4);

    uint32_t totalFrames = static_cast<uint32_t>(inFrames.size());
    file.write(reinterpret_cast<const char*>(&totalFrames), sizeof(totalFrames));

    // Sequentially write frame byte alignments out to disk
    for (const auto& frame : inFrames) {
        file.write(reinterpret_cast<const char*>(&frame.frame), sizeof(frame.frame));
        file.write(reinterpret_cast<const char*>(&frame.player2), sizeof(frame.player2));
        file.write(reinterpret_cast<const char*>(&frame.holds), sizeof(frame.holds));
        file.write(reinterpret_cast<const char*>(&frame.xPos), sizeof(frame.xPos));
        file.write(reinterpret_cast<const char*>(&frame.yPos), sizeof(frame.yPos));
    }
    return true;
}