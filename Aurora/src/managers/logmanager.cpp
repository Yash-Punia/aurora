#include "managers/logmanager.h"

#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <memory>

namespace aurora::managers
{
    void LogManager::Initialize()
    {
        //Make a memory sink and log to console
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        //Set pattern for the console sink that'll parse internally {Year-Month-Date Hour-Minute-Seconds.Milliseconds Message}
        consoleSink->set_pattern("%^[%Y-%m-%d %H:%M:%S.%e] %v%$");

        //To support multiple sinks, maintaining vector of sink pointers
        std::vector<spdlog::sink_ptr> sinks { consoleSink };

        //Logger to log into various loggers with different sinks
        auto logger = std::make_shared<spdlog::logger>(AURORA_DEFAULT_LOGGER_NAME, sinks.begin(), sinks.end());

        //Gets each and every log possible with trace being the lowest level
        logger->set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace); //Flush out everything to stdout or file on different situations {flushing on each trace}
        spdlog::register_logger(logger); //Maintains global registry so that logger can be accessed from everywhere
    }

    void LogManager::Shutdown()
    {
        spdlog::shutdown();
    }
} // namespace aurora::managers