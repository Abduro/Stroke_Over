#ifndef _SHAREDLITESYSTEMERROR_H_INCLUDED
#define _SHAREDLITESYSTEMERROR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Jan-2010 at 6:50:29pm, GMT+3, Rostov-on-Don, Thursday;
	This is Row27 project data model error class declaration file.
	-----------------------------------------------------------------------------
	Adopted to Pulspay project on 15-May-2012 at 9:39:48pm, GMT+3, Rostov-on-Don, Tuesday;
	Adopted to Platinum project on 19-Mar-2014 at 7:02:24am, GMT+4, Taganrog, Wednesday;
	Adopted to VS v15 on 16-May-2018 at 5:28:25p, UTC+7, Phuket, Rawai, Monday;
	-----------------------------------------------------------------------------
	Adopted to FakeGPS driver project on 13-Dec-2019 at 10:19:37a, UTC+7, Novosibirsk, Friday;
*/
#include <comdef.h> // https://learn.microsoft.com/en-us/cpp/cpp/com-error-class ;
#include <map>

#include "shared.preproc.h" // playing with some preprocessor definitions;
#include "shared.string.h"  // it is just the string of some extended version;

#include "sys.sync_obj.h"   // included for trying to make error object available to work in multithreaded environment;
#include "sys.err.codes.h"  // for converting winapi system error codes to handle result;

/*
	error C7525: inline variables require at least '/std:c++17'
	this error is removed by following setting the attribute of this project:
	...
	<Compile>
		<LanguageStandard>stdcpplatest</LanguageStandard>
	</Compile>
	...
*/

namespace shared { namespace sys_core {

	struct CLang {
		DWORD  dwPrimary;  // primary language Id
		DWORD  dwSecond;   // sub-language Id

		CLang(void) : dwPrimary(LANG_NEUTRAL), dwSecond(SUBLANG_DEFAULT) {}
		CLang(const DWORD _primary, const DWORD _second) : dwPrimary(_primary), dwSecond(_second) {}

		DWORD  Id (void) const { return MAKELANGID(dwPrimary, dwSecond); }
	};

	typedef const CLang& TLangRef;

	class CErr_Base {
	protected:
		DWORD         m_code   ;
		HRESULT       m_result ;
		CLang         m_lang   ;
		CSyncObject   m_lock   ;

	public:
		CErr_Base(void);
		CErr_Base(const DWORD  dwError, const CLang&);
		CErr_Base(const HRESULT hError, const CLang&);
#if defined(_DEBUG)
	public:
		CString Print (void) const;
#endif

	public:
		CErr_Base& operator= (const DWORD   _code)    ;    // sets error result from win 32 error code;
		CErr_Base& operator= (const HRESULT _hres)    ;    // sets error result; S_OK is acceptable;
		CErr_Base& operator= (TLangRef) ;

	public:
		operator DWORD    (void) const;   // gets error state Win API code;
		operator HRESULT  (void) const;   // gets error state of execution result;
		operator TLangRef (void) const;   // gets error description language;
		operator TSyncRef (void)      ;   // gets synchronize object referecnce;
	};
#if (0)
	class CErr_Source {
	public:
		 CErr_Source (void);
		 CErr_Source (const CErr_Source&);
		 CErr_Source (LPCTSTR _lp_sz_cls, LPCTSTR _lp_sz_method, LPCTSTR _lp_sz_name_sp);
		~CErr_Source (void);

	public: // properties;
		LPCTSTR  Class (void) const;
		CString& Class (void)      ;
		LPCTSTR  Method(void) const;
		CString& Method(void)      ;
		LPCTSTR  NameSp(void) const;
		CString& NameSp(void)      ;

	public:
		CString  Get (LPCTSTR _lp_sz_format = _T("Class = %s; Func = %s;")) const;
		bool     Set (LPCTSTR _lp_sz_cls, LPCTSTR _lp_sz_method, LPCTSTR _lp_sz_name_sp);

	public:
		CErr_Source& operator = (const CErr_Source&);

	private:
		CString  m_class ;  // name of source class; 
		CString  m_method;  // name of a method being called;
		CString  m_space ;  // name space full path; mostly used for global functions that is defined outside of structure or class; 
	};
#endif
	class CErr_State : public CErr_Base {
	                  typedef CErr_Base TBase;
	protected:
		CString    m_buffer; // error details' buffer;

	public:
		 CErr_State (void);
		 CErr_State (const CErr_State&);
		~CErr_State (void);

	public:
		LPCTSTR Get (void) const;        // gets error state details;
		VOID    Set (const bool _reset); // if _reset is true, error state is OLE_E_BLANK; otherwise, the state is set to false (i.e. S_OK);
		VOID    Set (const DWORD   _err_code);
		VOID    Set (const DWORD   _err_code, LPCTSTR _lp_sz_desc, ...); // sets the object state manually;
		VOID    Set (const DWORD   _err_code, const UINT resId); // sets the object state manually, description is loaded from string resource specified by identifier
		VOID    Set (const HRESULT _err_code); // sets error code and updates error description;
		VOID    Set (const HRESULT _err_code, LPCTSTR _lp_sz_desc, ...); // sets the object state manually;
		VOID    Set (const HRESULT _err_code, const UINT resId); // sets the object state manually, description is loaded from string resource specified by identifier
		VOID    Set (LPCTSTR  _sz_desc)     ; // sets a state description;
		VOID    Set (LPCTSTR  _sz_desc, ...); // sets a state description from pattern and multiple arguments;

#if defined(_DEBUG)
		CString Print (void) const;       // not thread-safe;
#endif

	public:
		operator bool     (void) const;   // returns TRUE when state indicates a ***failure*** (i.e. is not S_OK);
		operator LPCTSTR  (void) const;   // gets error state details;

	public:
		CErr_State&   operator= (const bool _reset); // if _reset is true, error state is a failure ; otherwise, the state is false (i.e. S_OK);
		CErr_State&   operator= (const CErr_State&);
		CErr_State&   operator= (LPCTSTR  _sz_desc);

		bool operator == (HRESULT) const; // compares the input result with this state object result value; [not thread safe]
		bool operator != (HRESULT) const; // compares the input result with this state object result value; [not thread safe]
	};

	bool operator==(const bool _lhs, const CErr_State& _rhs);
	bool operator!=(const bool _lhs, const CErr_State& _rhs);
	bool operator==(const CErr_State& _lhs, const bool _rhs);
	bool operator!=(const CErr_State& _lhs, const bool _rhs);

	typedef const CErr_State  TErr_State;

	class CError {
	public:
		 CError(void);
		 CError(const CError&);
		~CError(void);

	public:
		virtual
		HRESULT       Result(const HRESULT _new); // sets new error state result and returns a previous one;
	public:
		LPCTSTR       Class (void) const ;                               // gets the error source class name;
		VOID          Class (LPCTSTR)    ;                               // sets the error source class name;
		VOID          Class (LPCTSTR _lp_class, const bool bFormatted);  // sets the error source class name;
		VOID          Clear (void)       ;        // sets the error object to success state, i.e. no error state;
		DWORD         Code  (void) const ;        // gets Win API error code;
		VOID          Code  (const DWORD);        // sets Win API error code;
		LPCTSTR       Desc  (void) const ;        // gets the current description;
		bool          Is    (void) const ;        // returns true if the object is in error state, otherwise, false, i.e. no error;
		TLangRef&     Lang  (void) const ;        // gets language identifier;
		HRESULT       Last  (void)       ;        // updates error state by getting last error code by ::GetLastError() function;
		LPCTSTR       Method(void) const ;        // gets module name that produces the error, if any
		VOID          Method(LPCTSTR)    ;        // sets module name that produces the error
		VOID          Reset (void)       ;        // re-sets the error object to blank state (OLE_E_BLANK)
		HRESULT       Result(void) const ;        // gets the current result code
		DWORD         Show  (const HWND  = ::GetActiveWindow()) const;
		CErr_State&   State (void)       ;
		TErr_State&   State (void) const ;
#if defined(_DEBUG)
		enum e_print {
		     e_all  = 0, // prints all parts of the error including: error base, error state, error context;
		     e_base = 1, // prints error base content: win32 code, h_result, description;
		     e_ctx  = 2, // prints the context in which the error is working;
		     e_reqs = 3, // prints error code, result, description, class and method names;
		};
		CString Print (const e_print = e_print::e_all) const;
#endif

	public:
		CError& operator= (const _com_error&);    // sets error info from COM error object;
		CError& operator= (const CError&)    ;    // sets error info from other error object;
		CError& operator= (const DWORD _code);    // sets error result from win 32 error code;
		CError& operator= (const HRESULT _hr);    // sets error result; S_OK is acceptable;
		CError& operator= (LPCTSTR _lp_desc );    // sets error description;

	public:
		CError& operator<<(const HRESULT _hr);    // sets error result; intended for using in routines for error initial state set;
		CError& operator<<(const CString& _method); // sets method name the error occurs in; 
		CError& operator>>(const CString& _class) ; // sets class name that is the source of the error;
		CError& operator<<(LPCTSTR _p_method);    // sets error method;
		CError& operator>>(LPCTSTR _p_class );    // sets error source; intended for using in routines for error initial state set;

	public:
		operator const bool  (void) const    ;    // returns true if error object is ***IN*** error state, otherwise false;
		operator HRESULT     (void) const    ;    // returns error result;
		operator LPCTSTR     (void) const    ;    // returns error description;
		operator CErr_State& (void)          ;    // returns error state (rw) ;
		operator TErr_State& (void) const    ;    // returns error state (ra) ;
	
	protected:
		mutable
		CErr_State    m_state ;   // error state;
		CString       m_class ;   // a class name; this class owns the error object;
		CString       m_method;   // a method name; method name indicates what context an execution runs in;
	};

	bool operator==(const bool _lhs, const CError& _rhs);
	bool operator!=(const bool _lhs, const CError& _rhs);
	bool operator==(const CError& _lhs, const bool _rhs);
	bool operator!=(const CError& _lhs, const bool _rhs);
#if (1)
	class CErr_Format {
	protected:
		const
		CError&   m_error_ref;

	public:
		 CErr_Format (const CError&);
		~CErr_Format (void);

	public:
		CString   Do  (LPCTSTR _lp_sz_sep = NULL) const; // gets formatted string: {code|@sep|description|@sep|module|@sep|source};
		CString   Do_2(LPCTSTR _lp_sz_sep = NULL) const; // gets formatted string: {code|@sep|description|@sep|module};
		CString   Do_4(LPCTSTR _lp_sz_sep = NULL) const; // gets formatted string: {code|@sep|description};
		CString   Do_6(LPCTSTR _lp_sz_pattern   ) const; // pattern: $(x) - hresult; $(c) - code; $(d) - desc; $(m) - module; $(s) - source;
		                                                 // for example, output to console:
		                                                 // This is error:\n\tcode=%d$(c)\n\tdesc=%s$(d)\n\tmodule=%s$(m)\n\tsrc=%s$(s);
	};
#endif
}}
typedef const shared::sys_core::CError&  TErrorRef;

#endif/*_SHAREDLITESYSTEMERROR_H_INCLUDED*/