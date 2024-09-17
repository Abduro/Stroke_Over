#ifndef _EBO_TEST_$2$_H_INCLUDED
#define _EBO_TEST_$2$_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Aug-2024 at 21:58:37.6725041, UTC+7, Novosibirsk, Monday;
	This is Ebo pack system COM service base wrapper library unit test declaration file; 
*/
#include "_log.h"
#include "shared.string.h"
#include "sys.error.h"
#include "com.sec.base.h"
#include "com.svc.base.h"
#include "com.svc.props.h"

#pragma comment(lib, "sys.shared_v15.lib")   // is already included in shared lib ebo_test_$$$ test project;
#pragma comment(lib, "sys.err.core_v15.lib") // system error handling wrapper lib;
#pragma comment(lib, "sys.com.core_v15.lib") // this one must be tested by this unit test project;

#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);

#endif/*_EBO_TEST_$2$_H_INCLUDED*/