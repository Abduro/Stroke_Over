#ifndef _SHAREDUIXGENHSL_H_INCLUDED
#define _SHAREDUIXGENHSL_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) 26-Aug-2010 at 4:52:07pm, GMT+3, Rostov-on-Don, Thursday;
	This is UIX shared draw library generic HSL/RGB (hue-saturation-lightness) conversion interface declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 26-Sep-2018 at 5:34:48a, UTC+7, Novosibirsk, Wednesday;
	Adopted to Ebo Pack color project on 10-Oct-2021 at 5:23:45.7340975 am, UTC+7, Novosibirsk, Sunday;
*/
#include <vector>
#include "color.quad.h" // ToDo: color.quad.h and color.hsl.h have cyclic references to each other; it requires to be reviewed;

/////////////////////////////////////////////////////////////////////////////
#define HLS(h,l,s) ((HLSCOLOR)(((BYTE)(h)|((WORD)((BYTE)(l))<<8))|(((DWORD)(BYTE)(s))<<16)))
/////////////////////////////////////////////////////////////////////////////
#define HLS_H(hls) ((BYTE)(hls))
#define HLS_L(hls) ((BYTE)(((WORD)(hls)) >> 8))
#define HLS_S(hls) ((BYTE)((hls)>>16))
/////////////////////////////////////////////////////////////////////////////
typedef DWORD HLSCOLOR;

namespace ex_ui { namespace color {
	// http://colorizer.org/
	class C_hls {
	private:
		HLSCOLOR m_hls; // is composed by hue + luminocity + saturation;

	public:
		 C_hls (void);
		 C_hls (const C_hls&);
		 C_hls (const BYTE _h, const BYTE _l, const BYTE _s);
		 C_hls (const COLORREF _rgb);
		~C_hls (void);

	public:
		BYTE       Get_H(void) const;   // gets hue value;
		BYTE       Get_L(void) const;   // gets luminosity value;
		BYTE       Get_S(void) const;   // gets saturation value;
		const bool Is   (void) const;   // what is a criterion: it eqauls to zero or to something else; the first one is chosen for now;
		HLSCOLOR   ToHLS(const BYTE _h, const BYTE _l, const BYTE _s); // creates HLS value from hue, luminocity and saturation values;
		HLSCOLOR   ToHLS(const COLORREF _rgb);
		HLSCOLOR   ToHLS(const COLORREF _rgb, __int8 percent_L, __int8 percent_S); // creates HLS value from RGB, luminocity % and saturation %;
		COLORREF   ToRGB(void) const;   // it is very discussible what is returned: it may be black whole or CLR_NONE; returns the latter one;

	public:
		C_hls& operator = (const C_hls&);
		C_hls& operator <<(const COLORREF _rgb);

	public:
		operator bool     (void) const; // returns true in case when HLS value is not zero and decomposed RGB is not CLR_NONE;
		operator COLORREF (void) const;
	};

	// TODO: take into account a compatibility with Adobe Photoshop 'Hue/Saturation Adjustment' command;
	// https://en.wikipedia.org/wiki/HSL_and_HSV
	class C_hsl {
	private:
		FLOAT     m_h;      // hue value;
		FLOAT     m_s;      // saturation value;
		FLOAT     m_l;      // lightness value;

	public:
		 C_hsl (void);
		 C_hsl (const C_hsl&);
		 C_hsl (const FLOAT _hue, const FLOAT _light, const FLOAT _saturation);
		 C_hsl (const COLORREF _rgb);
		~C_hsl (void);

	public:
		FLOAT      _h(void) const  ;   // gets hue value;
		HRESULT    _h(const FLOAT) ;   // sets hue value;
		FLOAT      _l(void) const  ;   // gets lightness value;
		HRESULT    _l(const FLOAT) ;   // sets lightness value;
		FLOAT      _s(void) const  ;   // gets saturation value;
		HRESULT    _s(const FLOAT) ;   // sets saturation value;

	public:
		void       Clear  (void)      ;
		bool       IsValid(void) const;
		COLORREF   To_rgb (void) const;

	public:
		C_hsl& operator = (const C_hsl&  );
		C_hsl& operator <<(const COLORREF);  // assumes all components of HSL are clear before setting to new values;

	public:
		operator const COLORREF(void) const;

	public:
		static bool H_is_valid(const FLOAT _val);
		static bool L_is_valid(const FLOAT _val);
		static bool S_is_valid(const FLOAT _val);
	};
	// This class does not make any relations between RGB, hue, chroma and lightness values yet;
	// This class is used as an element or an object for representing colors' set in, for example, web design;
	class C_hsl_clr {
	private:
		COLORREF     m_rgb;     // color RGB value;
		USHORT       m_hue;     // hue value in degree; 0 - 360;
		UCHAR        m_chr;     // a saturation in percent, i.e. chroma;
		UCHAR        m_lgt;     // a lightness percentage;
		CString      m_cga;     // cga(colour graphics adapter) name/number or alias;
		CString      m_web;     // color friendly name for web;

	public:
		 C_hsl_clr (void);
		 C_hsl_clr (const C_hsl_clr&);
		~C_hsl_clr (void);

	public:
		LPCTSTR      Cga   (void) const  ;
		VOID         Cga   (LPCTSTR)     ;
		UCHAR        Chrome(void) const  ;
		HRESULT      Chrome(const UCHAR) ;
		USHORT       Hue   (void) const  ;
		HRESULT      Hue   (const USHORT);
		UCHAR        Light (void) const  ;
		HRESULT      Light (const UCHAR) ;
		COLORREF     Rgb   (void) const  ;
		HRESULT      Rgb   (const COLORREF);
		LPCTSTR      Web   (void) const  ;
		VOID         Web   (LPCTSTR)     ;

	public:
		C_hsl_clr&  operator = (const C_hsl_clr&);
		C_hsl_clr&  operator <<(const COLORREF  ); // applies RGB value provided; using alpha channel is not considered yet;

	public:
		operator const COLORREF(void) const;

	public:
		static float Chrome(const COLORREF _rgb);
	};

	typedef ::std::vector<C_hsl_clr>  T_hsl_clr_set;

	class C_hsl_clr_set {
	public:
		enum _r : UINT {
			na = 0xFFFF
		};
	private:
		T_hsl_clr_set   m_set;

	public:
		 C_hsl_clr_set(void);
		~C_hsl_clr_set(void);

	public:
		HRESULT     Append(const C_hsl_clr&);
		VOID        Clear (void);
		UINT        Count (void) const;
		const
		C_hsl_clr&  Colour(const INT _ndx) const;  // provides read-only access to HSL colour element by given index; no checking available range;
	};

	class C_hsl_clr_std : public C_hsl_clr_set {
	                     typedef C_hsl_clr_set T_base;
	public:
		C_hsl_clr_std(void);
	};
}}

typedef ex_ui::color::C_hls      THlsColor;
typedef ex_ui::color::C_hsl      THslColor;
typedef ex_ui::color::C_hsl_clr  THslColor_Ex;

#endif/* _SHAREDUIXGENHSL_H_INCLUDED*/