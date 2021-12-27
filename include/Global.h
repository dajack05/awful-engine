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

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef char s8;
typedef short s16;
typedef int s32;
typedef long s64;

typedef u8 bool;
#define false 0
#define true 1

#endif