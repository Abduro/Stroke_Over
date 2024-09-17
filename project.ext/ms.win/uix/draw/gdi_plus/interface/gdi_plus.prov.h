#ifndef __PLATINUMSHAREDGDIPROVIDER_H_INCLUDED
#define __PLATINUMSHAREDGDIPROVIDER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 4-Nov-2007 at 9:57pm, GMT+3, Rostov-on-Don, Sunday;
	This is Sfx Pack owner-drawn related classe(s) declaration file.
	-----------------------------------------------------------------------------
	Adopted to Platinum project on 23-Mar-2014 at 8:45:09pm, GMT+4, Saint-Petersburg, Sunday; (https://platinumpayroll.co.nz)
	Adopted to File Guardian project on 28-May-2018 at 11:07:04p, UTC+7, Phuket, Rawai, Monday; (https://thefileguardian.com/)
	Adopted to Geometry Curve project on 17-Feb-2024 at 12:14:18.6040620, UTC+7, Novosibirsk, Saturday;
*/
#include <atlbase.h>
#include <atlwin.h>
#include <commctrl.h>

#pragma warning(disable: 4458)  // declaration of 'abcd' hides class member (GDI+)

#include "shared.gen.han.h"
#include "shared.sys.err.h"
#include "gdi.plus.defs.h"

namespace ex_ui { namespace draw {

	using shared::common::CGlobalAlloca;

	class CGdiPlusLib_Guard {
	protected:
		volatile bool m_auto_mode;
	public:
		 CGdiPlusLib_Guard(const bool _b_auto_mode = true); // capturing and releasing are automatic;
		~CGdiPlusLib_Guard(void);
	public:
		HRESULT   Capture(void);
		HRESULT   Release(void);
		bool      Secured(void) const;
	private:
		CGdiPlusLib_Guard(const CGdiPlusLib_Guard&);
		CGdiPlusLib_Guard& operator= (const CGdiPlusLib_Guard&);
	};

	class CGdiPlusPng_Loader
	{
	public:
		static HRESULT     CreateImages (const LPVOID pRawData, const DWORD _data_sz, Gdiplus::Bitmap*&);
		static HRESULT     CreateImages (const LPVOID pRawData, const DWORD _data_sz, HIMAGELIST& hImageList);
	public:
		static HRESULT     CreateImages (const ATL::_U_STRINGorID RID, const HMODULE hModule, HIMAGELIST& hImageList);
		static HRESULT     LoadResource (const ATL::_U_STRINGorID RID, const HMODULE hModule, Gdiplus::Bitmap*&);
		static HRESULT     LoadResource (const ATL::_U_STRINGorID RID, const HMODULE hModule, HBITMAP&);
	public:
		static HRESULT     CreateImages (const HBITMAP&, HIMAGELIST&); // bitmap handle provided must be destroyed by a caller;
		static HRESULT     CreateImages (const HBITMAP&, HIMAGELIST& , const SIZE& _sz_frame);
		static HMODULE     CurrentModule(void);
	};

	class CGdiPlusPng_Loader_lite {
	public:
		 CGdiPlusPng_Loader_lite(void);
		~CGdiPlusPng_Loader_lite(void);
	public:
		HRESULT     LoadImage(const ATL::_U_STRINGorID RID, Gdiplus::Bitmap*&);
		HRESULT     LoadImage(const ATL::_U_STRINGorID RID, HBITMAP&);
		HRESULT     LoadImage(const ATL::_U_STRINGorID RID, const HMODULE hModule, Gdiplus::Bitmap*&);
	};
#if (0)
#include "uix.gdi.z_buf.h"
	#define _c_clr const COLORREF
	class CGdiPlus_Helper { // TODO: must be re-viewed or deprecated;
	public:
		 CGdiPlus_Helper(void);
		~CGdiPlus_Helper(void);
	public:
		HRESULT     DrawImage(const HDC _h_dc, const RECT& _rc_area, Gdiplus::Bitmap* const);
		HRESULT     Gradient (
		               const HDC& _h_dc, const RECT& _rc_area, _c_clr _from, _c_clr _upto, const bool _b_horz = true
		            ); // no alpha channel at this time;
	};

#endif

}}

typedef ex_ui::draw::CGdiPlusLib_Guard       TGdiPlsGuard;
typedef ex_ui::draw::CGdiPlusPng_Loader      TPngLoader  ;
typedef ex_ui::draw::CGdiPlusPng_Loader_lite TPngLoaderLite;
#if (0)
typedef ex_ui::draw::CGdiPlus_Helper         TGdiPlsHelper ;
#endif
#endif/*__PLATINUMSHAREDGDIPROVIDER_H_INCLUDED*/