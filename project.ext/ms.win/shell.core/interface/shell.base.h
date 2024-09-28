#ifndef _SHELL_BASE_H_INCLUDED
#define _SHELL_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Sep-2024 at 15:30:50.842, GMT+7, Novosibirsk, Wednesday;
	This is Ebo pack windows shell extension base interface declaration file;
*/
#include <shobjidl_core.h>
#include <combaseapi.h>
#include <guiddef.h>

#include "shared.string.h"
#include "sys.error.h"

#include "com.guid.h"
#include "com.unk.h"

namespace shell { namespace ext { namespace core {

	using TString = TStringEx;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;

	using CGuid    = shared::sys_core::com::CGuid;
	using CUnknown = shared::sys_core::com::CUnknown;

	// https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nn-shobjidl_core-ishellextinit ;
	static GUID this_guid = __guid_null;

	class CShellExtInit : public IShellExtInit, public CUnknown {
	public:
		 CShellExtInit (void);
		 CShellExtInit (const CShellExtInit&);
		 CShellExtInit (CShellExtInit&&) = delete;
		virtual ~CShellExtInit (void);

	public:
		TError&  Error (void) const;   // returns the last error object;

#if defined(_DEBUG)
		enum e_print {
			 e_all = 0, // prints detailed info of this class object: its name, valid state, the last error;
			 e_req = 1, // prints current init state only;
		};
		CString  Print (const e_print = e_print::e_all) const;
#endif
	public:
		CShellExtInit&  operator = (const CShellExtInit&);
		CShellExtInit&  operator = (CShellExtInit&&) = delete;

	private:
		CError   m_error;
	};

}}}

typedef shell::ext::core::CShellExtInit  TShellExtInit;

#endif/*_SHELL_BASE_H_INCLUDED*/