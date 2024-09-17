#ifndef _COLOR_GRADIENT_H_INCLUDED
#define _COLOR_GRADIENT_H_INCLUDED
/*
	Created by Tech_doc (ebontrop@gmail.com) on 12-Oct-2021 at 1:16:28.2479704 am, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack color project gradient interface declaration file;
*/
#include "color.gdi_plus.h"
#include "color.compl.h"

namespace ex_ui { namespace color {

	// https://en.wikipedia.org/wiki/Gradient
	// https://en.wikipedia.org/wiki/Color_gradient
	// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-gradientfill
	// https://www.dictionary.com/browse/gradient
	class CGradient {
	protected:
		CColour   m_clr_0 ;          // the first color or the color which the gradient starts from;
		CColour   m_clr_1 ;          // the second color or the color which the gradient ends up;
		bool      m_b_vert;          // a direction of a gradient either vertical (default) or horizontal;

	public:
		 CGradient (void);
		 CGradient (const CColour& _from, const CColour& _to);
		 CGradient (const COLORREF _from, const COLORREF _to);
		 CGradient (const CGradient&);
		~CGradient (void);

	public:
		const bool  Is    (void) const; // returns true if one of the gradient colors is true;
		const bool  IsVert(void) const;
		      bool& IsVert(void)      ;
		const
		CColour& c0(void) const;     // gets first color (ro);
		CColour& c0(void)      ;     // gets first color (rw);
		const
		CColour& c1(void) const;     // gets second color (ro);
		CColour& c1(void)      ;     // gets second color (rw);

		const
		CColour& First (void) const;
		CColour& First (void)      ;
		const
		CColour& Second(void) const;
		CColour& Second(void)      ;
		HRESULT  Set   (const CComplClrs&); // takes into account the dark and light only;
		HRESULT  Set   (const CColour& _from, const CColour& _to);
		HRESULT  Set   (const COLORREF _from, const COLORREF _to);

	public:
		CGradient& operator = (const CGradient&);
		CGradient& operator <<(const bool _b_vert);
		CGradient& operator <<(const CComplClrs& );
	};
}}

typedef ::std::vector<ex_ui::color::CGradient> TGradients;

namespace ex_ui { namespace color {

	using shared::sys_core::CError;

	// https://stackoverflow.com/questions/31427117/difference-between-element-item-and-entry-when-it-comes-to-programming
	class CGradient_Strip {
	protected:
		TGradients     m_strip;
		mutable CError m_error;

	public:
		 CGradient_Strip (void);
		 CGradient_Strip (const CGradient_Strip&);
		~CGradient_Strip (void);

	public:
		HRESULT     Add   (const CGradient&);
		HRESULT     Clear (void) ;
		size_t      Count (void) const;
		TErrorRef   Error (void) const;
		const bool  Is    (void) const; // returns true if this strip is not empty and all gradient tiles are valid;
		const bool  IsVert(void) const; // returns true if *each* gradient element is vertical;
		      void  IsVert(const bool); // sets an orientation to all elements of this strip;
		const
		CGradient& Item(const size_t _ndx) const;
		CGradient& Item(const size_t _ndx);
		HRESULT  Remove(const size_t _ndx);
		const
		TGradients& Raw(void) const;

	public:
		CGradient_Strip& operator = (const CGradient_Strip&);
		CGradient_Strip& operator+= (const CGradient&);
		CGradient_Strip& operator-= (const size_t _ndx);
	};
}}

typedef ex_ui::color::CGradient        TGradient;
typedef ex_ui::color::CGradient_Strip  TGradientStrip;

#endif/*_COLOR_GRADIENT_H_INCLUDED*/