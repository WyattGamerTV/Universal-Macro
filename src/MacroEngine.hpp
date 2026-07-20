#pragma once
#include <vector>
#include <string>
#include <cstdint>

// Unified internal frame structure
struct MacroFrame {
    uint32_t frame;
    bool player2;
    bool holds;      // true for press, false for release
    double xPos;     // For physics correction if the format supports it
    double yPos;
};

// Main state controller
class MacroEngine {
public:
    static MacroEngine& get() {
        static MacroEngine instance;
        return instance;
    }

    std::vector<MacroFrame> activeMacro;
    bool isRecording = false;
    bool isPlaying = false;
    uint32_t currentFrame = 0;

    void clear() { activeMacro.clear(); currentFrame = 0; }
    void recordInput(bool player2, bool holds, double x, double y);
    void playbackUpdate(class PlayerObject* player1, class PlayerObject* player2);
};