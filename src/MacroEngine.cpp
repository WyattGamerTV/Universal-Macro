#include "MacroEngine.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

void MacroEngine::recordInput(bool player2, bool holds, double x, double y) {
    activeMacro.push_back({currentFrame, player2, holds, x, y});
}

void MacroEngine::playbackUpdate(class PlayerObject* player1, class PlayerObject* player2) {
    // Keep running through actions that match our current precise frame
    static size_t playbackIndex = 0;
    
    // Reset index if we restarted the level
    if (currentFrame == 0) {
        playbackIndex = 0;
    }

    while (playbackIndex < activeMacro.size() && activeMacro[playbackIndex].frame == currentFrame) {
        const auto& action = activeMacro[playbackIndex];
        
        // Target the correct player object based on frame data
        PlayerObject* targetPlayer = action.player2 ? player2 : player1;
        
        if (targetPlayer) {
            // Force the action on the game engine side
            if (action.holds) {
                targetPlayer->pushButton(PlayerButton::Jump);
            } else {
                targetPlayer->releaseButton(PlayerButton::Jump);
            }

            // Apply light positional correction if coordinates exist
            if (action.xPos != 0.0 || action.yPos != 0.0) {
                targetPlayer->m_position = { static_cast<float>(action.xPos), static_cast<float>(action.yPos) };
            }
        }
        
        playbackIndex++;
    }
}