#include "MacroMenuLayer.hpp"
#include "../parsers/ParserRegistry.hpp"

MacroMenuLayer* MacroMenuLayer::create(std::string const& title) {
    auto ret = new MacroMenuLayer();
    if (ret && ret->initAnchored(360.0f, 220.0f, title)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool MacroMenuLayer::setup(std::string const& value) {
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto& engine = MacroEngine::get();

    // 1. Text Input Field for File Path/Name
    m_fileInput = TextInput::create(240.0f, "macro_name.gdr2", "chatFont.fnt");
    m_fileInput->setPosition({ m_bgSprite->getContentSize().width / 2.0f, 140.0f });
    m_fileInput->setFilter("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.");
    m_mainLayer->addChild(m_fileInput);

    // 2. Control Buttons Container Menu
    auto controlsMenu = CCMenu::create();
    controlsMenu->setPosition({ m_bgSprite->getContentSize().width / 2.0f, 80.0f });
    m_mainLayer->addChild(controlsMenu);

    // Record Toggle Button Layout
    auto recordOnBtn = CCSprite::createWithSpriteFrameName("GJ_videoBtn_001.png");
    recordOnBtn->setColor({ 255, 100, 100 }); // Red tinted when recording
    auto recordOffBtn = CCSprite::createWithSpriteFrameName("GJ_videoBtn_001.png");
    
    m_recordToggle = CCMenuItemToggler::create(recordOffBtn, recordOnBtn, this, menu_selector(MacroMenuLayer::onRecord));
    m_recordToggle->setChecked(engine.isRecording);
    controlsMenu->addChild(m_recordToggle);

    // Playback Toggle Button Layout
    auto playOnBtn = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
    playOnBtn->setColor({ 100, 255, 100 }); // Green tinted when playing
    auto playOffBtn = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");

    m_playToggle = CCMenuItemToggler::create(playOffBtn, playOnBtn, this, menu_selector(MacroMenuLayer::onPlay));
    m_playToggle->setChecked(engine.isPlaying);
    m_playToggle->setPositionX(60.0f);
    controlsMenu->addChild(m_playToggle);

    // 3. File System Execution Buttons
    auto ioMenu = CCMenu::create();
    ioMenu->setPosition({ m_bgSprite->getContentSize().width / 2.0f, 35.0f });
    m_mainLayer->addChild(ioMenu);

    auto loadBtnSprite = ButtonSprite::create("Load", "goldFont.fnt", "GJ_button_01.png", 0.7f);
    auto loadBtn = CCMenuItemSpriteExtra::create(loadBtnSprite, this, menu_selector(MacroMenuLayer::onLoad));
    loadBtn->setPositionX(-50.0f);
    ioMenu->addChild(loadBtn);

    auto saveBtnSprite = ButtonSprite::create("Save", "goldFont.fnt", "GJ_button_02.png", 0.7f);
    auto saveBtn = CCMenuItemSpriteExtra::create(saveBtnSprite, this, menu_selector(MacroMenuLayer::onSave));
    saveBtn->setPositionX(50.0f);
    ioMenu->addChild(saveBtn);

    return true;
}

void MacroMenuLayer::onRecord(CCObject* sender) {
    auto& engine = MacroEngine::get();
    engine.isRecording = !m_recordToggle->isToggled();
    if (engine.isRecording) {
        engine.isPlaying = false;
        m_playToggle->setChecked(false);
        engine.clear(); // Clear memory buffer to record fresh clicks
    }
}

void MacroMenuLayer::onPlay(CCObject* sender) {
    auto& engine = MacroEngine::get();
    engine.isPlaying = !m_playToggle->isToggled();
    if (engine.isPlaying) {
        engine.isRecording = false;
        m_recordToggle->setChecked(false);
        engine.currentFrame = 0; // Reset runtime head pointer back to start
    }
}

void MacroMenuLayer::onLoad(CCObject* sender) {
    std::string filename = m_fileInput->getString();
    if (filename.empty()) return;

    auto path = Mod::get()->getSaveDir() / filename;
    auto parser = ParserRegistry::get().getParser(path);

    if (parser && parser->load(path, MacroEngine::get().activeMacro)) {
        FLAlertLayer::create("Success", "Macro parsed perfectly!", "OK")->show();
    } else {
        FLAlertLayer::create("Error", "Failed to parse macro format.", "OK")->show();
    }
}

void MacroMenuLayer::onSave(CCObject* sender) {
    std::string filename = m_fileInput->getString();
    if (filename.empty()) return;

    auto path = Mod::get()->getSaveDir() / filename;
    auto parser = ParserRegistry::get().getParser(path);

    if (parser && parser->save(path, MacroEngine::get().activeMacro)) {
        FLAlertLayer::create("Success", "Macro saved to data folder!", "OK")->show();
    } else {
        FLAlertLayer::create("Error", "Invalid layout file selection.", "OK")->show();
    }
}