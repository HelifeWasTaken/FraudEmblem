#pragma once

#define KAT_NAME    "Kat"
#define KAT_VERSION "0.1"

#ifdef CMAKE_BUILD_TYPE
#define KAT_BUILD_TYPE CMAKE_BUILD_TYPE
#else
#define KAT_BUILD_TYPE "Unknown"
#endif

#if defined(_WIN32) || defined(_WIN64)
#define KAT_WINDOWS    1
#define KAT_API        __declspec(dllexport)
#define KAT_API_IMPORT __declspec(dllimport)
#define KAT_OS         "Windows"
#elif defined(__linux__) || defined(__unix__)
#define KAT_UNIX 1
#define KAT_API  __attribute__((visibility("default")))
#define KAT_API_IMPORT
#define KAT_OS "Unix"
#elif defined(__APPLE__)
#define KAT_MACOS 1
#define KAT_API   __attribute__((visibility("default")))
#define KAT_API_IMPORT
#define KAT_OS "MacOS"
#endif

#if defined(KAT_UNIX) || defined(KAT_MACOS)
#define KAT_POSIX 1
#endif

#if !defined(KAT_WINDOWS) && !defined(KAT_POSIX)
#error "Unsupported platform"
#endif

#define KAT_VERSION_FULL                                                  \
    KAT_NAME " v" KAT_VERSION " (" KAT_BUILD_TYPE               \
                  ") " KAT_OS
