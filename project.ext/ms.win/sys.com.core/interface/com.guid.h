#ifndef _COM_GUID_H_INCLUDED
#define _COM_GUID_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Sep-2024 at 09:57:57.966, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack project system comp-obj-model generic guid interface declaration file;
*/
#include <guiddef.h>

#include "shared.preproc.h"
#include "shared.string.h"

#include "sys.error.h"

#ifndef __guid_null
#define __guid_null {0x00000000L, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} 
#endif

namespace shared { namespace sys_core { namespace com {

	using TString = TStringEx;

	// https://learn.microsoft.com/en-us/windows/win32/api/guiddef/ns-guiddef-guid ;
	// https://learn.microsoft.com/en-us/windows/win32/api/guiddef/nf-guiddef-isequalguid ;
#if (0)
	bool operator == (const GUID& _lhv, const GUID& _rhv); // already defined in guiddef.h;
	bool operator != (const GUID& _lhv, const GUID& _rhv); // already defined in guiddef.h;
#endif
	class CGuid {
	public:
		 CGuid (void);
		 CGuid (_pc_sz _p_guid);       // converts input text >> TString().Guid() >> CLSIDFromString();
		 CGuid (const CGuid&);
		 CGuid (const GUID& _guid);    // ToDo: perhaps it would be better approach of a constructor declaration >> CGuid(const GUID = __guid_null);
		 CGuid (CGuid&&) = delete;
		~CGuid (void);

	public:
		err_code Create (void) ;       // https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-cocreateguid ; 
		const
		GUID&  Get (void) const;
		bool   Set (const GUID&);      // returns true in case of this class attribute value has been changed;
		bool   Set (_pc_sz _guid);     // makes a conversion from text to the guid structure;

		bool   Is_equal(const GUID&) const;

#if defined(_DEBUG)
		CString Print (void) const;
#endif
	public:
		CGuid&  operator = (const CGuid&);
		CGuid&  operator = (CGuid&&) = delete;
		CGuid&  operator <<(const GUID&);
		CGuid&  operator <<(_pc_sz _p_guid);

#pragma warning(disable: 4227)
		operator const GUID  (void) const;
		operator const GUID& (void) const;
#pragma warning(default: 4227)

		bool operator == (const CGuid&) const ;
		bool operator != (const CGuid&) const ;

	public:
		static CGuid& Ref (void);     // get a reference to a singleton of this class;

	private:
		GUID  m_guid;
	};

}}}

#endif/*_COM_GUID_H_INCLUDED*/