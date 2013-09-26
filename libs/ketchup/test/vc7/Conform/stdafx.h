// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

// Change these values to use different versions
#define WINVER		0x0400
//#define _WIN32_WINNT	0x0400
#define _WIN32_IE	0x0400
#define _RICHEDIT_VER	0x0100

#include <pstade/vodka/drink.hpp>

#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <pstade/tomato/wtl/app.hpp>
#include <pstade/tomato/atl/win.hpp>

#include <pstade/gravy/auto_link.hpp>
