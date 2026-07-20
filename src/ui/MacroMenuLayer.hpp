#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include "../MacroEngine.hpp"

using namespace geode::prelude;

class MacroMenuLayer : public Popup<std::string const&> {
protected:
    TextInput* m_fileInput = nullptr;
    CCMenuItemToggler* m_recordToggle = nullptr;
    CCMenuItemToggler* m_playToggle = nullptr;

    bool setup(std::string const& value) override;
    void onRecord(CCObject* sender);
    void onPlay(CCObject* sender);
    void onLoad(CCObject* sender);
    void onSave(CCObject* sender);

public:
    static MacroMenuLayer* create(std::string const& title = "Universal Macro Bot");
};