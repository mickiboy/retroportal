#include <iomanip>
#include <sstream>
#include "impl/ANSI/LogImpl_ANSI.h"

namespace retro
{
    std::shared_ptr<Log::Impl> Log::impl;
    std::chrono::high_resolution_clock::time_point Log::startTime;

    void Log::init()
    {
        using namespace std::chrono;

        impl = std::make_shared<LogImpl_ANSI>();
        startTime = high_resolution_clock::now();

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
        using namespace std::chrono;

        if (impl) {
            auto currentTime = high_resolution_clock::now();
            auto timeSpan = currentTime - startTime;
            auto ns = timeSpan.count();
            auto m = duration_cast<minutes>(timeSpan).count();
            auto h = duration_cast<hours>(timeSpan).count();

            std::ostringstream ss;
            ss << std::setfill('0')
                << std::setw(1) << h << ':'
                << std::setw(2) << m << ':'
                << std::setw(2) << (ns % 1000000000000) / 1000000000 << '.'
                << std::setw(3) << (ns % 1000000000) / 1000000;

            impl->log(type, ss.str(), message);
        }
    }
}
