// Executable size report utility.
// Aras Pranckevicius, http://aras-p.info/projSizer.html
// Based on code by Fabian "ryg" Giesen, http://farbrausch.com/~fg/
// Public domain.

#pragma once
#include <vector>
#include <cstring>
#include <string>
#include <cassert>

#pragma warning(disable:4018)
#pragma warning(disable:4267)
#pragma warning(disable:4244)

typedef signed int sInt;
typedef char sChar;
typedef float sF32;
typedef double sF64;
typedef unsigned int sU32;
typedef bool sBool;

inline void sCopyString( sChar* a, size_t a_len, const sChar* b, int b_len )
{
	if (strncpy_s( a, a_len, b, b_len ) != 0) {
		abort();
	}
}

