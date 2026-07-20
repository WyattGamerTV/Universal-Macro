#include "MhrJsonParser.hpp"
#include <fstream>
#include <Geode/Geode.hpp>

bool MhrJsonParser::load(const ghc::filesystem::path& path, std::vector<MacroFrame>& outFrames) {
    std::ifstream file(path);
    if (!file.is_open()) return false;

    std::string err;
    auto json = matjson::parse(file, err);
    if (!err.empty()) return false;

    // Mega Hack Replay structure wraps frames inside an "inputs" array block
    if (json.contains("inputs") && json["inputs"].is_array()) {
        for (auto& item : json["inputs"].as_array()) {
            MacroFrame frame;
            frame.frame = item["frame"].as_int();
            frame.player2 = item.contains("p2") ? item["p2"].as_bool() : false;
            frame.holds = item["down"].as_bool(); // MHR standard names clicks as "down"
            frame.xPos = item.contains("x") ? item["x"].as_double() : 0.0;
            frame.yPos = item.contains("y") ? item["y"].as_double() : 0.0;
            outFrames.push_back(frame);
        }
        return true;
    }
    return false;
}

bool MhrJsonParser::save(const ghc::filesystem::path& path, const std::vector<MacroFrame>& inFrames) {
    std::ofstream file(path);
    if (!file.is_open()) return false;

    matjson::Value root = matjson::Object();
    matjson::Value inputs = matjson::Array();

    for (const auto& frame : inFrames) {
        matjson::Value obj = matjson::Object();
        obj["frame"] = static_cast<int>(frame.frame);
        obj["p2"] = frame.player2;
        obj["down"] = frame.holds;
        obj["x"] = frame.xPos;
        obj["y"] = frame.yPos;
        inputs.push_back(obj);
    }

    root["inputs"] = inputs;
    file << root.dump(matjson::NO_INDENTATION); // Flatten layout output to maximize processing speed
    return true;
}