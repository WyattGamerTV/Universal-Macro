#pragma once
#include "IReplayParser.hpp"
#include <memory>
#include <string>
#include <map>

class ParserRegistry {
public:
    static ParserRegistry& get() {
        static ParserRegistry instance;
        return instance;
    }

    // Finds the matching parser object from your massive format list
    std::shared_ptr<IReplayParser> getParser(const ghc::filesystem::path& path);
};