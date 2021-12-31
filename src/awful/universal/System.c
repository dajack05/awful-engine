#include <awful/System.h>
#include <stdio.h>
#include <time.h>

#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)

u64 SystemTime() { return clock() / CLOCKS_PER_MS; }