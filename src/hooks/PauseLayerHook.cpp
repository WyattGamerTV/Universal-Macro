#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include "../ui/MacroMenuLayer.hpp"

using namespace geode::prelude;

class $modify(MacroPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        // Locating the standard side-button configuration panel inside the pause overlay
        auto menu = this->getChildByID("right-button-menu");
        if (!menu) menu = this->getChildByID("left-button-menu"); // Fallback check

        if (menu) {
            // Re-use our custom clapboard visual for the UI launch selector button
            auto sprite = CCSprite::createWithSpriteFrameName("GJ_videoBtn_001.png");
            sprite->setScale(0.75f);

            auto button = CCMenuItemSpriteExtra::create(
                sprite,
                this,
                menu_selector(MacroPauseLayer::onOpenMacroMenu)
            );

            menu->addChild(button);
            menu->updateLayout(); // Forces Geode to neatly auto-space the new button
        }
    }

    void onOpenMacroMenu(CCObject* sender) {
        MacroMenuLayer::create()->show();
    }
};