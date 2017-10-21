#pragma once

#include <retro/Log.h>

namespace retro
{
    class LogImpl_ANSI : public Log::Impl
    {
    public:
        LogImpl_ANSI();
        virtual ~LogImpl_ANSI() = default;

        void log(LogType type, const std::string& message) override;
    };
}
