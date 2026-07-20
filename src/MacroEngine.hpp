#pragma once
#include <vector>
#include <cstdint>

struct MacroFrame {
    uint32_t frame;
    bool player2;
    bool holds;      // true = press, false = release
    double xPos;     // Physics positional data for corrections
    double yPos;
};

class MacroEngine {
private:
    MacroEngine() = default;

public:
    static MacroEngine& get() {
        static MacroEngine instance;
        return instance;
    }

    std::vector<MacroFrame> activeMacro;
    bool isRecording = false;
    bool isPlaying = false;
    uint32_t currentFrame = 0;
    size_t playbackIndex = 0;

    void clear() {
        activeMacro.clear();
        currentFrame = 0;
        playbackIndex = 0;
    }

    void recordInput(bool player2, bool holds, double x, double y) {
        activeMacro.push_back({currentFrame, player2, holds, x, y});
    }
};