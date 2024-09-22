#ifndef _EBO_TEST_$5$_H_INCLUDED
#define _EBO_TEST_$5$_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Sep-2024 at 00:42:27.165, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack shared gdi+ render unit test interface declaration file; 
*/
#include "_log.h"

#include "sys.error.h"

#include "gdi_plus.defs.h"
#include "gdi_plus.prov.h"

#pragma comment(lib, "sys.shared_v15.lib")   // this is the base;
#pragma comment(lib, "sys.err.core_v15.lib") // for using error object;
#pragma comment(lib, "gdi.plus_v15.lib")     // this one must be tested by this unit test project;
#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);

#endif/*_EBO_TEST_$5$_H_INCLUDED*/