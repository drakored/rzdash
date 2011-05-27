#ifndef WIN32_H
#define WIN32_H


#ifdef WIN32
#include <windows.h>
#define usleep Sleep // we replace usleep by Sleep for Windows builds.
#define SLEEP 100 // usleep uses nanoseconds, Windows's Sleep uses microsecons, therefore we need to divide it by 1000.
#else
#define SLEEP 100000 // 100ms, or 100000ns
#endif


#endif // WIN32_H
