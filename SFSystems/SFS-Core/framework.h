#pragma once

#define WIN32_LEAN_AND_MEAN   
#define NOMINMAX
#include <windows.h>

#ifdef SFSUI_EXPORTS
#define SFS_C_API __declspec(dllexport)
#else
#define SFS_C_API __declspec(dllimport)
#endif

