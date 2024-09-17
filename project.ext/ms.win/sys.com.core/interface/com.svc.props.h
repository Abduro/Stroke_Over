#ifndef _COM_SVC_PROPS_H_INCLUDED
#define _COM_SVC_PROPS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Aug-2024 at 20:31:54.9977308, UTC+7, Novosibirsk, Sunday;
	This is Stroke Over project shared variant-struct-based property interface declaration file;
*/
#include <comdef.h>  // _com_error class declaration;
#include <comutil.h> // _variant_t class declaration;

#include "shared.preproc.h"
#include "shared.string.h"
#include "sys.error.h"

namespace shared { namespace sys_core { namespace com {
	// https://learn.microsoft.com/en-us/cpp/atl/data-types-classes          >> a currency class looks to be useful;
	// https://learn.microsoft.com/en-us/cpp/atl/reference/ccomvariant-class >> must have VT_BSTR type for making a copy, that is not appropriate;

	using shared::sys_core::CError  ;
	using TError   = const  CError& ;

	using _prop_id = long;

	// https://learn.microsoft.com/en-us/windows/win32/winauto/variant-structure ;
	// https://learn.microsoft.com/en-us/windows/win32/api/oaidl/ns-oaidl-variant;

	// https://learn.microsoft.com/en-us/windows/win32/learnwin32/error-handling-in-com >> _variant_t may raise a com_error when an operation failed;

	class CProperty { // this class is very similar in implementation to shared::sys_core::seh::CNode, but given that these classes are
	                  // intended to be used in very different areas, some code duplication persists, a common parent class is not created;
	                  // ToDo: using this class as named flag which has specific value looks like not good idea;
	public:
		 CProperty (_prop_id = 0);
		 CProperty (const _variant_t&);
		 CProperty (const CProperty&);
		 CProperty (CProperty&&);
		~CProperty (void);

	public:
		err_code    Clear (void) ;             // clears the value by setting to empty type (VT_EMPTY);

		_prop_id    Id (void) const;           // gets property identifier value;
		bool        Id (_prop_id)  ;           // sets property identifier value; returns true in case of identifier value change;

		const
		_variant_t& Get (void) const;          // gets a reference to value that is currently set for this property;
		err_code    Set (const _variant_t&);   // sets the value of this property; possible exception may be raised, but it will be catched;

		const
		_variant_t& Value (void) const;        // this is the same property as get();
		err_code    Value (const _variant_t&); // this is the same property as set();

#if defined(_DEBUG)
		CString    Print (void) const;
#endif
	public:
		CProperty& operator = (const CProperty&);
		CProperty& operator = (CProperty&&);
		CProperty& operator <<(const _prop_id);           // sets the property identifier;
		CProperty& operator <<(const _variant_t& _value); // calls the property set();
		const
		CProperty& operator >>(_variant_t& _out) const;   // calls the property get();

	protected:
		_prop_id   m_id;
		_variant_t m_value; // https://learn.microsoft.com/en-us/cpp/cpp/variant-t-class ;
		                    // https://learn.microsoft.com/en-us/windows/win32/api/oaidl/ns-oaidl-variant ;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/propidlbase/ns-propidlbase-propvariant ;
	// https://learn.microsoft.com/en-us/windows/win32/api/propidl/nn-propidl-ipropertystorage ;
}}}

#endif/*_COM_SVC_PROPS_H_INCLUDED*/