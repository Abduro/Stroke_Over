#ifndef _GDI_PLUS_DEFS_INCLUDED
#define _GDI_PLUS_DEFS_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Jan-2010 at 11:26:44pm, GMT+3, Rostov-on-Don, Saturday;
	This is Sfx Pack drawing service provider class declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 11-Aug-2018 at 4:14:00p, UTC+7, Novosibirsk, Saturday;
	Adopted to Geometry Curve project on 17-Feb-2024 at 10:51:26.3687197, UTC+7, Novosibirsk, Saturday;
*/
#include <atlbase.h> // *important*::this header must be included first, otherwise GDI+ headers generate compile error!

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

#include <atlapp.h>
#include <atlgdi.h>

#define __HRESULT_FROM_LASTERROR()   HRESULT_FROM_WIN32(::GetLastError())
#define __H(rc__)    (rc__.bottom - rc__.top)
#define __W(rc__)    (rc__.right - rc__.left)

#define HexToRgb(_hex)  ( RGB( LOBYTE((_hex)>>16),LOBYTE((_hex)>>8),LOBYTE((_hex))) )
#define H2C(_hex) HexToRgb(_hex)

namespace ex_ui { namespace draw {

	typedef Gdiplus::Bitmap TBitmap;
	typedef Gdiplus::Status TStatus;

	// system error not used as a parent class here yet; this approach must be reviewed;
	// https://docs.microsoft.com/en-us/windows/win32/api/gdiplustypes/ne-gdiplustypes-status
	class CErr_drw {
	protected:
		HRESULT  m_result;
		TStatus  m_status;

	public:
		 CErr_drw (void);
		 CErr_drw (const CErr_drw&);
		 CErr_drw (TStatus);
		~CErr_drw (void);

	public:
		HRESULT Get (void) const;
		HRESULT Set (const TStatus);

	public:
		operator HRESULT (void) const;
		operator TStatus (void) const;

	public:
		CErr_drw& operator = (const CErr_drw&);
		CErr_drw& operator <<(const TStatus);
	};

namespace defs {
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

typedef ex_ui::draw::CErr_drw TErr_drw;

#endif/*_GDI_PLUS_DEFS_INCLUDED*/