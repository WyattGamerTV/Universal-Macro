#include <Geode/Geode.hpp>
#include "MacroEngine.hpp"
#include "parsers/ParserRegistry.hpp"

using namespace geode::prelude;

/**
 * Geode entry point. This function is automatically invoked by the loader
 * immediately after our universal macro bot binary has been safely loaded into memory.
 */
$execute {
    log::info("========================================");
    log::info(" Universal Macro Bot Initialized Successfully! ");
    log::info(" Developer: WyattGamerTV                ");
    log::info(" SDK Target: Geode v5.8.2               ");
    log::info("========================================");

    // Fetch the mod settings configuration
    auto defaultFormat = Mod::get()->getSettingValue<std::string>("default-format");
    log::info("Default macro export framework set to: .{}", defaultFormat);

    // Verify runtime communication capabilities with the rendering dependency
    if (Loader::get()->isModLoaded("eclipse.ffmpeg-api")) {
        log::info("Eclipse FFmpeg API dependency found. Rendering pipeline ready.");
    } else {
        log::warn("Eclipse FFmpeg API mod not detected. Video rendering features will be disabled.");
    }
}