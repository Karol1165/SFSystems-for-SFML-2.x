#pragma once

#define WIN32_LEAN_AND_MEAN      
#define NOMINMAX
#include <windows.h>

#ifdef _DEBUG
#include<iostream>
#endif

#ifdef SFSUTILTIES_EXPORTS
#define SFS_U_API __declspec(dllexport)
#else
#define SFS_U_API __declspec(dllimport)
#endif
