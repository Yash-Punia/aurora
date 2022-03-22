#pragma once

namespace aurora::managers
{
    class LogManager
    {
        public:
            LogManager() = default;
            ~LogManager() = default;

            void Initialize();
            void Shutdown();
    };
} // namespace aurora::manager