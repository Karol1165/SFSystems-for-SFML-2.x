#pragma once

#define WIN32_LEAN_AND_MEAN            
#define NOMINMAX
#include <windows.h>

#ifdef _DEBUG
#include <iostream>
#endif

#include "../SFS-Core/Base.hpp"
#include "../SFS-Core/Data.hpp"

#ifdef SFSSCENE_EXPORTS
#define SFS_S_API __declspec(dllexport)
#else
#define SFS_S_API __declspec(dllimport)
#endif
