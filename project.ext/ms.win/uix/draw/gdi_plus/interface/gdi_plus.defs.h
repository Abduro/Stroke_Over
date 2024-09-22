#ifndef _GDI_PLUS_DEFS_INCLUDED
#define _GDI_PLUS_DEFS_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Jan-2010 at 11:26:44pm, GMT+3, Rostov-on-Don, Saturday;
	This is Sfx Pack drawing service provider class declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 11-Aug-2018 at 4:14:00p, UTC+7, Novosibirsk, Saturday;
	Adopted to Geometry Curve project on 17-Feb-2024 at 10:51:26.3687197, UTC+7, Novosibirsk, Saturday;
*/
#include <atlbase.h> // *important*::this header must be included first, otherwise gdi+ headers generate compile error!
#include <map>       // for enumerating possible errors of gdi+ internal state;

// https://stackoverflow.com/questions/27126860/how-to-turn-on-gdi-1-1-instead-of-1-0-in-mfc-project/27128349
#define __manifest_gdiplus_dependency                                        \
    "\"/manifestdependency:type='Win32' "                                    \
    "name='Microsoft.Windows.GdiPlus' version='1.1.0.0' "                    \
    "processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\""

#pragma comment(linker, __manifest_gdiplus_dependency )
#ifdef  GDIPVER
#undef  GDIPVER
#endif
#define GDIPVER 0x0110

/*
	Manifest file must include the dependency of GDI+ version like this:
	<assemblyIdentity
		type="win32"
		name="Microsoft.Windows.Common-Controls" version="6.0.0.0"
		processorArchitecture="*"
		publicKeyToken="6595b64144ccf1df"
		language="*"
	/>
	or linker instruction like this (in one line):
	#pragma comment(linker,
	"\"/manifestdependency:type='Win32' "
	"name='Microsoft.Windows.GdiPlus' version='1.1.0.0' "
	"processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\""
	)
*/

#pragma warning(disable: 4458)  // declaration of 'abcd' hides class member (GDI+)
#include <gdiplus.h>
#include <gdiplusheaders.h>
#include <gdiplusgraphics.h>

#pragma comment(lib, "gdiplus.lib")

#include "sys.error.h"

namespace ex_ui { namespace draw { namespace gdi_pls {

	typedef Gdiplus::Bitmap TBitmap;
	typedef Gdiplus::Status TStatus;

	using TError = shared::sys_core::CError;
	using t_stat = TStatus;
	/*
		what is your name? a shorter name...
		Lilu... (c) 5th Element, (43:35);

		ToDo::not sure the enumeration below would be useful; it requires a review;
		The review is made: the enumeration below inherits the original gdi+ one, but can have additional elements for extending gdi+ status states;
	*/
	enum  e_status : uint32_t {
		e_no_err      = t_stat::Ok                       ,
		e_generic     = t_stat::GenericError             ,
		e_inv_arg     = t_stat::InvalidParameter         ,
		e_no_memory   = t_stat::OutOfMemory              ,
		e_obj_busy    = t_stat::ObjectBusy               ,
		e_out_buff    = t_stat::InsufficientBuffer       ,
		e_not_impl    = t_stat::NotImplemented           ,
		e_win_err     = t_stat::Win32Error               ,
		e_inv_state   = t_stat::WrongState               ,
		e_aborted     = t_stat::Aborted                  ,
		e_no_file     = t_stat::FileNotFound             ,
		e_overflow    = t_stat::ValueOverflow            ,
		e_no_access   = t_stat::AccessDenied             ,
		e_unk_image   = t_stat::UnknownImageFormat       ,
		e_no_family   = t_stat::FontFamilyNotFound       ,
		e_no_style    = t_stat::FontStyleNotFound        ,
		e_not_ttf     = t_stat::NotTrueTypeFont          ,
		e_unsup_ver   = t_stat::UnsupportedGdiplusVersion,
		e_not_init    = t_stat::GdiplusNotInitialized    ,
		e_no_prop     = t_stat::PropertyNotFound         ,
		e_unsup_prop  = t_stat::PropertyNotSupported     ,
		e_inited      = e_unsup_prop + 1                 , // this is the status of the object being in initialized state;
		e_uninited    = e_unsup_prop + 2                 , // this is the status of extension mode, that is set after calling release/unload method; 
	};

	/*
		system error handling is not efficient for catching GDI+ errors due to this library produces its own internal errors
		that are partially somehow related to WinAPI but in the most cases they aren't;

		the main purpose of the GDI+ error adapter is to expose some description of the error state of the library;
		such approach does not require an inheritance from shared::sys_core::CError; 
	*/
	// ToDo: this class and the adapter of sys error use different enums, must be re-viewed;
	class CErr_Assoc {
	public:
		 CErr_Assoc (const t_stat = t_stat::Ok, const err_code = TErrCodes::no_error, const bool b_is_sys = false);
		 CErr_Assoc (const CErr_Assoc&);
		 CErr_Assoc (CErr_Assoc&&) = delete;
		~CErr_Assoc (void) ;

	public: // accessr(s) and mutator(s);

		err_code   Code (void) const;
		const bool Code (const err_code);

		bool Is_sys (void) const;
		void Is_sys (const bool);

		t_stat Status (void) const;
		bool   Status (const t_stat);

	public:
		bool   Set (const t_stat, const err_code, const bool b_is_sys); // returns true if one of the attributes is changed;

#if defined(_DEBUG)
		enum e_print {
			e_all = 0,
			e_req = 1,
		};
		CString   Print (const e_print = e_print::e_req) const;
#endif
	public:
		CErr_Assoc& operator = (const CErr_Assoc&);
		CErr_Assoc& operator = (CErr_Assoc&&) = delete;
		CErr_Assoc& operator <<(const err_code);
		CErr_Assoc& operator <<(const bool _is_sys);
		CErr_Assoc& operator <<(const t_stat);

	private:
		t_stat    m_status  ;
		err_code  m_err_code;   // this is associated system error handling error result;
		bool      m_b_sys;      // this is a flag that indicates that system information is accessible through ::FormatMessage();
	};

	// https://docs.microsoft.com/en-us/windows/win32/api/gdiplustypes/ne-gdiplustypes-status;

	class CErr_Adapter {
	public:
		 CErr_Adapter (const e_status = e_status::e_no_err, _pc_sz _p_desc = nullptr);
		 CErr_Adapter (const CErr_Adapter&);
		 CErr_Adapter (CErr_Adapter&&) = delete;
		~CErr_Adapter (void);

	public: // attribute(s) and mutator(s);
		_pc_sz    Desc (void) const;         // gets status description;
		bool      Desc (_pc_sz)    ;         // sets status description; returns true in case of changing value;

		e_status  Status (void) const;       // gets status value;
		bool      Status (const e_status);   // sets status value; returns true in case of changing the status value;
		const
		CErr_Assoc&  Sys_err (void) const;   // returns a reference to the object associated with the system error; (r-o);
		CErr_Assoc&  Sys_err (void)      ;   // returns a reference to the object associated with the system error; (r-w);

	public: // method(s);
		bool      Set (const e_status, _pc_sz _p_desc) ; // sets error adapter data in one call; returs true if at least one of the attributes is changed;
#if defined(_DEBUG)
		enum e_print {
			e_all = 0,  // outputs this class name, status value and its description; a status association to the system error is also included;
			e_val = 1,  // outputs this class status value and its description;
		};
		CString   Print (const e_print = e_print::e_all) const;
#endif
	public:
		CErr_Adapter& operator = (const CErr_Adapter&);
		CErr_Adapter& operator = (CErr_Adapter&&) = delete;

		CErr_Adapter& operator <<(_pc_sz _p_desc);
		CErr_Adapter& operator <<(const e_status);

		CErr_Adapter& operator <<(const CErr_Assoc&);

	private:
		e_status   m_status;
		CString    m_desc  ;
		CErr_Assoc m_assoc ;
	};

#if (0)
	class CErr_Adapter {
	public:
		 CErr_Adapter (void);
		 CErr_Adapter (const TStatus, _pc_sz _p_desc, const err_code, const bool _b_is_sys);
		 CErr_Adapter (const CErr_Adapter&);
		 CErr_Adapter (CErr_Adapter&&) = delete;
		 CErr_Adapter (const TStatus);
		~CErr_Adapter (void) ;

	public:
		err_code Code   (void) const;                    // gets error code; there is no set() of code due to it can be done through setting status value only;
		_pc_sz   Desc   (void) const;                    // gets the status description;
		bool     Desc   (_pc_sz)    ;                    // sets the status description; returns true in case of change, otherwise, false that indicates no change;
		bool     Is_sys (void) const;
#if defined(_DEBUG)
		CString  Print  (void) const;
#endif
		err_code Set (const TStatus, _pc_sz _p_desc, const err_code, const bool _b_is_sys);    // sets the current value of the status and its description;

		TStatus  Status (void) const;                    // gets the status code;
		bool     Status (const TStatus);                 // sets the status code;

	public:
		CErr_Adapter& operator = (const CErr_Adapter&);  // just making a copy;
		CErr_Adapter& operator = (CErr_Adapter&&) = delete;
		CErr_Adapter& operator <<(const  TStatus);       // sets the status code; if the code is predefined the error discription is updated;
		CErr_Adapter& operator <<(_pc_sz _p_desc);       // sets a description of the error status;
		CErr_Adapter& operator <<(const err_code);       // sets associated system error code;
		CErr_Adapter& operator <<(const bool _b_sys);    // sets a flag of an avalablility getting details from GetLastErros();

		CErr_Adapter& operator >>(TError&);              // takes an input error object and sets hresult error code with description to this object;

		operator err_code (void) const;
		operator TStatus  (void) const;

	protected:
		err_code  m_code;      // this is associated system api error code for this status;
		CString   m_desc;      // status description;
		bool      m_is_sys;    // indicates an accessability of getting details from the win api;
		TStatus   m_status;    // the status value;
	};
#endif
}}}

using TStatus = ex_ui::draw::gdi_pls::TStatus;

typedef ex_ui::draw::gdi_pls::CErr_Assoc   TErrAssoc;
typedef ex_ui::draw::gdi_pls::CErr_Adapter TErrAdapt;

typedef ::std::map<uint32_t, TErrAdapt>  TRawStatus; // the key that is based on gdi+ status enumeration is intentionally replaced by plain data type;

namespace ex_ui { namespace draw { namespace gdi_pls {

	class CErr_Adapt_enum {
	public:
		 CErr_Adapt_enum (const bool _b_auto = true);       // if b_auto is true, the Set() is called up;
		 CErr_Adapt_enum (const CErr_Adapt_enum&) = delete;
		 CErr_Adapt_enum (CErr_Adapt_enum&&) = delete;
		~CErr_Adapt_enum (void);

	public:
		const TErrAdapt&  Get (const uint32_t _code) const; // returns a reference to an object specified by status code; if not found >> fake object; not-thread-safe;
		const TRawStatus& Raw (void) const;                 // returns a reference to the collection of all gdi+ status;
		
		err_code Set (void);           // fills this enumerarion by the set of predefined gdi+ status;

	public: static
		CErr_Adapt_enum&  Ref (void) ; // this is the singleton of this enumeration object;

	private:
		CErr_Adapt_enum& operator = (const CErr_Adapt_enum&) = delete;
		CErr_Adapt_enum& operator = (CErr_Adapt_enum&&) = delete;

	private:
		TRawStatus m_raw_stats;
	};
}}}

typedef ex_ui::draw::gdi_pls::CErr_Adapt_enum TErrAdapt_enum;

namespace ex_ui { namespace draw { namespace defs {
	interface IExclusion {
		virtual   HRESULT   Add  (const RECT&)       { return E_NOTIMPL; }
		virtual   HRESULT   Apply(const HDC  ) const { return E_NOTIMPL; }
		virtual   HRESULT   Clear(void)              { return E_NOTIMPL; }
		virtual   ULONG     Count(void)        const { return 0; }
		virtual   RECT&     Get  (const ULONG _ndx)  { _ndx; static RECT rc_empty = {0}; return rc_empty; }
	};
	interface IRenderer_Base {
		virtual   IExclusion& Excluded(void);
	};
	/*
		This interface is used as a pointer to parent window draw functionality;
		Safity of assignment must be protected by critical section inside a receiver implementation;
		But that is not enough taking into account that interface pointer being assigned may possibly point to destroyed object later;
		the only protection here is an assignment of an interface that is implemented ***exactly*** by parent window;
	*/
	interface IRenderer : public IRenderer_Base
	{
		/*
			This function maybe useful for direct call from child control to owner/parent function of filling the background;
			maybe parent object implementation can identify a calling window by extracting window handle from DC provided for calculating required shifts;
			but at the same time, it is much easier (at least it seems to be so) to provide a rectangle being calculated by child control;
			child control knows who its parent, and to use appropriate shift(s) while calculating a rectangle; but it is not truth always;
		*/
		virtual   HRESULT  DrawBackground(const HDC hSurface, const RECT& rcDrawArea) {hSurface; rcDrawArea; return E_NOTIMPL;}
		virtual   HRESULT  DrawParentBackground(const HWND hChild, const HDC hSurface, RECT& rcUpdated) PURE;
	};
}}}

#endif/*_GDI_PLUS_DEFS_INCLUDED*/