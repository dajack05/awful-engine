#ifndef H_GLOBAL
#define H_GLOBAL

// Is this windoze?
#if defined _WIN32
#define __WINDOZE__
#define OS "Win32/64"
#elif defined __APPLE__
#define __MACOS__
#define OS "MacOS"
#elif __linux__
#define __LINUX__
#define OS "Linux"
#else
#define OS "Unknown"
#endif

#endif