#ifndef _COLOR_GDI_PLUS_H_INCLUDED
#define _COLOR_GDI_PLUS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 4-Nov-2007 at 9:57pm, GMT+3, Rostov-on-Don, Sunday;
	This is Sfx package owner-drawn colour related classe(s) declaration; [volunteer project];
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 2-May-2020 at 1:36:19p, UTC+7, Novosibirsk, Saturday;
	Adopted to Ebo Pack color project on 11-Oct-2021 at 10:57:57.5820828 pm, UTC+7, Novosibirsk, Monday;
*/
#include <iterator>
#include <gdiplus.h>
#include "shared.gen.sys.err.h"
#include "color.alpha.h"
#include "color.compl.h"

#ifndef _Opaque
#define _Opaque (0xff)
#endif

#ifndef _SemiTrans
#define _SemiTrans  (0x7F)      // 50% opacity
#endif

#ifndef GetAValue
#define GetAValue(_clr)	( 0 == LOBYTE((_clr)>>24) ? 255 : LOBYTE((_clr)>>24) )
#endif

namespace ex_ui { namespace color {

	using shared::sys_core::CError;

	class CDebugPrint {
	public:
		 CDebugPrint  (void);
		 CDebugPrint  (const CDebugPrint&);
		~CDebugPrint  (void);
	public:
		CString  Print(const COLORREF) const;
	public:
		CDebugPrint&   operator = (const CDebugPrint&);
		CString        operator <<(const COLORREF) const ; // Print() is called;
	};

	typedef Gdiplus::Color TColor;
	// https://en.wikipedia.org/wiki/RGB_color_space ;
	// ToDo: this color is used for introducing a layer of abstraction, perhaps public inherits from gdi-plus color would be better;
	// such a class name is for making a difference between 'color' (that is met often) and 'colour',
	// otherwise it's not essential what kind of English is applied: UK or US;
	class CColour {
	protected:
		TColor m_clr;

	public:
		 CColour(void);
	explicit CColour(const CColour&);
	explicit CColour(const COLORREF clr, const BYTE alpha = _Opaque);
	explicit CColour(const TColor& );
		~CColour(void);

	public:
		BYTE     Alpha  (void) const;
		VOID     Alpha  (const BYTE b_value = _SemiTrans);
		VOID     Create (const COLORREF clr, const BYTE _alpha = _Opaque); // actually, 4th byte of COLORREF may be used for alpha channel;
		const
		TColor&  Data   (void) const;
		VOID     Empty  (void)      ;
		bool     Is     (void) const; // returns true if m_clr is not CLR_NONE;
#if defined(_DEBUG)
		CStringW Print  (void) const;
#endif
		COLORREF Rgb    (void) const;
		VOID     Rgb    (const COLORREF);

	public:
		operator const TColor& (void) const;
		operator const TColor* (void) const;
		operator const COLORREF(void) const;

	public:
		CColour& operator = (const CColour&);
		CColour& operator = (const TColor &);
		CColour& operator <<(const BYTE _alpha);
		CColour& operator <<(const COLORREF);

	public:
		bool operator == (const CColour&) const;
		bool operator != (const CColour&) const;
		bool operator == (COLORREF) const;
		bool operator != (COLORREF) const;
	};

	class CColour_Ex : public CColour {
	                  typedef CColour TBase;
	public:
		 CColour_Ex(void);
		 CColour_Ex(const CColour&);
		 CColour_Ex(const CColour_Ex&);
		 CColour_Ex(const COLORREF clr, const BYTE alpha = _Opaque);
		~CColour_Ex(void);

	public:
		HRESULT  Darken (const __int8 btValue);  // TColorQuad is also makes this option;
		HRESULT  Lighten(const __int8 btValue);  // TColorQuad is also makes this option;

	public:
		CColour_Ex& operator+= (const __int8 btValue);  // makes color light;
		CColour_Ex& operator-= (const __int8 btValue);  // makes color dark ;
		CColour_Ex& operator = (const CColour&);        // regular color object is assigned;
		CColour_Ex& operator = (const CColour_Ex&);
	};
}}

typedef ex_ui::color::CColour     TColour;
typedef ex_ui::color::CColour_Ex  TColourEx;

typedef ex_ui::color::CDebugPrint TDbgPrint;

#endif/*_COLOR_GDI_PLUS_H_INCLUDED*/