#pragma once

#if defined(_DEBUG) || !defined(NDEBUG) || defined(DEBUG)
#define BOUNT_DEBUG
#endif

#if defined(_MSC_VER)
#define BOUNT_MSVC_COMPILER
#define BOUNT_EXPORT __declspec(dllexport)
#define BOUNT_IMPORT __declspec(dllimport)
#elif defined(__clang__)
#define BOUNT_CLANG_COMPILER
#define BOUNT_EXPORT __attribute__((visibility("default")))
#define BOUNT_IMPORT
#elif defined(__GNUC__)
#define BOUNT_GCC_COMPILER
#define BOUNT_EXPORT __attribute__((visibility("default")))
#define BOUNT_IMPORT
#endif

#if defined(_WIN32)
#define BOUNT_WINDOWS_OS
#elif defined(__linux__)
#define BOUNT_LINUX_OS
#elif defined(__APPLE__)
#define BOUNT_MACOS_OS
#else
#error "Operating System is not supported."
#endif

#include "bount-types/types.hpp"
