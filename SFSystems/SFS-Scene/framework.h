#pragma once

#define WIN32_LEAN_AND_MEAN             // Wyklucz rzadko używane rzeczy z nagłówków systemu Windows
// Pliki nagłówkowe systemu Windows
#define NOMINMAX
#include <windows.h>

#ifdef SFSSCENE_EXPORTS
#define SFS_S_API __declspec(dllexport)
#else
#define SFS_S_API __declspec(dllimport)
#endif
