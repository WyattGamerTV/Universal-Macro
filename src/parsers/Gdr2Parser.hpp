#pragma once
#include "IReplayParser.hpp"

class Gdr2Parser : public IReplayParser {
public:
    bool load(const ghc::filesystem::path& path, std::vector<MacroFrame>& outFrames) override;
    bool save(const ghc::filesystem::path& path, const std::vector<MacroFrame>& inFrames) override;
};