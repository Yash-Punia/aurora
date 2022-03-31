#pragma once
#include "spdlog/spdlog.h"

#include <intrin.h>

#define AURORA_DEFAULT_LOGGER_NAME "auroralogger" 
#define AURORA_BREAK __debugBreak();

#ifndef AURORA_CONFIG_RELEASE
#define AURORA_TRACE(...)   if(spdlog::get(AURORA_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(AURORA_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__);}
#define AURORA_DEBUG(...)   if(spdlog::get(AURORA_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(AURORA_DEFAULT_LOGGER_NAME)->debug(__VA_ARGS__);}
#define AURORA_INFO(...)   if(spdlog::get(AURORA_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(AURORA_DEFAULT_LOGGER_NAME)->info(__VA_ARGS__);}
#define AURORA_WARN(...)   if(spdlog::get(AURORA_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(AURORA_DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__);}
#define AURORA_ERROR(...)   if(spdlog::get(AURORA_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(AURORA_DEFAULT_LOGGER_NAME)->error(__VA_ARGS__);}
#define AURORA_FATAL(...)   if(spdlog::get(AURORA_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(AURORA_DEFAULT_LOGGER_NAME)->critical(__VA_ARGS__);}
#define AURORA_ASSERT(x, msg)  if((x)) {} else { AURORA_FATAL("ASSERT - {}\n\t{}\n\tinfile: {}\n\ton line: {}", #x, msg, __FILE__, __LINE__); AURORA_BREAK}

// //Disable logging for different build if any
// #else

// #define AURORA_TRACE(...)   (void)0
// #define AURORA_DEBUG(...)   (void)0
// #define AURORA_INFO(...)    (void)0
// #define AURORA_WARN(...)    (void)0
// #define AURORA_ERROR(...)   (void)0
// #define AURORA_FATAL(...)   (void)0
#endif

