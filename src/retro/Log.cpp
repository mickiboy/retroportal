#include "impl/ANSI/LogImpl_ANSI.h"

namespace retro
{
    std::shared_ptr<Log::Impl> Log::impl;

    void Log::init()
    {
        impl = std::make_shared<LogImpl_ANSI>();

        debug("Initialized logging");
    }

    void Log::shutdown()
    {
        debug("Shutting logging down");

        impl.reset();
    }

    void Log::debug(const std::string& message)
    {
        log(LogType::Debug, message);
    }

    void Log::warning(const std::string& message)
    {
        log(LogType::Warning, message);
    }

    void Log::error(const std::string& message)
    {
        log(LogType::Error, message);
    }

    void Log::log(LogType type, const std::string& message)
    {
        if (impl) {
            impl->log(type, message);
        }
    }
}
