#ifndef _SYSERRFORMAT_H_INCLUDED
#define _SYSERRFORMAT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 8-Sep-2019 at 7:01:14a, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack shared lite library system error format interface declaration file.
	-----------------------------------------------------------------------------
	Adopted to Geometry Curve project on 17-Feb-2024 at 07:12:16.9170139, UTC+7, Novosibirsk, Saturday;
*/
#include "shared.string.h"
#include "sys.error.h"

namespace shared { namespace sys_core { namespace _impl {

	class CErr_Details {
	private:
		CString m_temp;   // a template for extracting arguments from list;
		CString m_desc;
		CLang   m_lang;

	public:
		 CErr_Details (void) ;
		~CErr_Details (void) ;

	public:
		LPCTSTR args     (LPCTSTR _lp_sz_pat, const va_list& _err_args);
		VOID    clear    (void);        // does not clear argument template;
		VOID    normalize(void);
		DWORD   size     (void) const;

	public:
		CErr_Details& operator << (const CLang&   _err_lang);
		CErr_Details& operator << (const DWORD    _err_code);
		CErr_Details& operator << (const HRESULT  _err_code);
		CErr_Details& operator << (const va_list& _err_args);
		CErr_Details& operator << (LPCTSTR  _lp_sz_template);

	public:
		operator  LPCTSTR (void) const;
	};

	class CErr_Pattern {
	public:
		enum _tp : USHORT {
			e_line  = 0x0,   // this is a pattern for status bar or other type of UI controls;
			e_box   = 0x1,   // this is a pattern for message box;
			e_state = 0x2,   // this is a pattern for error state in one line;
		};
	private:
		_tp  m_active;
	public:
		 CErr_Pattern (void);
		~CErr_Pattern (void);
	public:
		CAtlStringW Get (const _tp _e_type) const; // TODO: needs to return statically defined pattern;

	public:
		CErr_Pattern& operator << (const _tp _e_type);
	public:
		operator const _tp (void) const;
		operator CString   (void) const;
	};

	class CErr_Fmt {
	private:
		CString      m_sep;  // line separator is any;
		CString      m_fmt;  // a buffer of formatted string;
		CErr_Pattern m_pat;
	public:
		 CErr_Fmt (void);
		~CErr_Fmt (void);
	
	public:
		LPCTSTR   Format (TErrorRef);
		LPCTSTR   Format (TErr_State&);

	public:
		CErr_Fmt& operator << (const CErr_Pattern&  ) ;
		CErr_Fmt& operator << (LPCTSTR _lp_sz_sep   ) ;
		CErr_Fmt& operator << (TErrorRef  _error_ref) ;
		CErr_Fmt& operator << (TErr_State& _state   ) ;

	public:
		operator LPCTSTR (void) const;
	};

	class CErr_Msg {
	public:
		 CErr_Msg (void);
		~CErr_Msg (void);

	public:
		LPCTSTR     Na (void) const;
		LPCTSTR     NotFound(void) const;
	};
}}}

#endif/*_SYSERRFORMAT_H_INCLUDED*/