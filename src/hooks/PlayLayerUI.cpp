#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "../MacroEngine.hpp"

using namespace geode::prelude;

class $modify(MacroPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontRunActions) {
        if (!PlayLayer::init(level, useReplay, dontRunActions)) return false;

        auto& engine = MacroEngine::get();

        // Check if the macro bot is actually active right now
        if (engine.isRecording || engine.isPlaying) {
            auto winSize = CCDirector::sharedDirector()->getWinSize();

            // 1. Create the RobTop clapboard sprite from the game's sprite cache
            auto clapboardSprite = CCSprite::createWithSpriteFrameName("GJ_videoBtn_001.png");
            if (clapboardSprite) {
                // Position it neatly in the top-right corner of the gameplay interface
                clapboardSprite->setPosition({ winSize.width - 25.0f, winSize.height - 25.0f });
                clapboardSprite->setScale(0.6f);
                clapboardSprite->setTag(9988); // Assign a unique tag to find or remove it later

                // 2. Tint it dynamically: Red for recording, Green for playing back
                if (engine.isRecording) {
                    clapboardSprite->setColor({ 255, 80, 80 }); // Soft Red
                    
                    // Add a subtle pulsing animation if recording
                    auto pulseOut = CCScaleTo::create(0.5f, 0.65f);
                    auto pulseIn = CCScaleTo::create(0.5f, 0.55f);
                    auto sequence = CCSequence::create(pulseOut, pulseIn, nullptr);
                    clapboardSprite->runAction(CCRepeatForever::create(sequence));
                } else if (engine.isPlaying) {
                    clapboardSprite->setColor({ 80, 255, 80 }); // Soft Green
                }

                // 3. Attach it to the UI layer so it stays pinned over the camera movements
                if (this->m_uiLayer) {
                    this->m_uiLayer->addChild(clapboardSprite, 100);
                }
            }
        }

        return true;
    }
};