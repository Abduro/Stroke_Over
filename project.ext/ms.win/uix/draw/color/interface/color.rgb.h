#ifndef __SFXSOACLIENTDRAWINGSERVICECOLOURQUAD_H_
#define __SFXSOACLIENTDRAWINGSERVICECOLOURQUAD_H_
/*
	Created by Tech_dog (ebontrop@gmail.com) on 8-Mar-2012 at 9:59:04pm, GMT+3, Rostov-on-Don, Thursday;
	This is SfxSOA Client Drawing Service Colour Quad class declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 2-May-2020 at 8:53:42p, UTC+7, Novosibirsk, Saturday;
	Adopted to Ebo Pack color project on 10-Oct-2021 at 4:28:57.0784593 am, UTC+7, Novosibirsk, Sunday;
*/
#include "color._defs.h"
#include "color.alpha.h"

namespace ex_ui { namespace color { namespace rgb {

	using TPercent = TPct_Flt;
	// perhaps it would be better to consider RGBQUAD as the base for this class:
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-rgbquad ;
	class CQuad {
	public:
		enum channel : uint32_t { // strictly speaking, alpha value is not an rgb color channel, but just a transparency value;
			r = 0, g = 1, b = 2, a = 3, _count = a + 1 
		};
	public:
		 CQuad (clr_value _r = 0, clr_value _g = 0, clr_value _b = 0, clr_value _a = 0); // initiates color to "absolute" black emptiness by default;
		 CQuad (clr_type  _color);                   // no separate assigning alpha value, it is supposed that input color already has the required one;
		 CQuad (clr_type  _color, clr_value _alpha); // this and above ctors set valid flag to true;
		 CQuad (const CQuad&);
		 CQuad (CQuad&&);
		~CQuad (void);

	public: // accessor(s);
		__inline clr_value A (void) const;  // gets alpha channel value;
		__inline clr_value B (void) const;  // gets blue color channel value;
		__inline clr_value G (void) const;  // gets green color channel value;
		__inline clr_value R (void) const;  // gets red color channel value;

		__inline clr_value Get (channel) const; // gets specified channel of the primary color;

	public: // mutetor(s);
		__inline bool A (clr_value); // sets alpha channel value; returns true if the value is changed;
		__inline bool B (clr_value); // sets blue  color channel value; returns true if the value is changed;
		__inline bool G (clr_value); // sets green color channel value; returns true if the value is changed;
		__inline bool R (clr_value); // sets red   color channel value; returns true if the value is changed;

		__inline bool Set (channel, clr_value);                                      // sets specified channel of a color quad to given input value;
		__inline bool Set (rgb_color _color , bool _valid = true);                   // sets color quad's value including alpha;
		__inline bool Set (rgb_color _color , clr_value _alpha, bool _valid = true); // sets color channel' value with alpha value; returns true if it's changed;
		__inline bool Set (clr_value _r, clr_value _g, clr_value _b, clr_value _a);  // sets color quad by input primary colors separately, plus alpha;

	public: // convertor(s)
		clr_type ToRgb  (void) const;          // classic or plain color reference that actually does not care about transparency;
		clr_type ToRgbA (void) const;          // this is complete color value that has alpha channel set to some level;

	public:
		bool   Is_equal_to (const rgb_color) const;
		/*
			the color cannot be identified or recognized as invalid by the value of the primary color channels,
			because the data type of the channel value is uint8_t or unsigned char,
			and this data type can only contain a value in the desired range of values [0..255];
		*/
#if (0)
		bool  Is (void) const; // returns true if the quad does not equal to color max value; *important*: alpha value is also taken into account;
#else
		const bool  Is (void) const;
		      bool& Is (void)      ;           // may be used for direct setting validity of this quad color value to true|false;
#endif
		void  Reset  (void);                   // zeros value of all color channels and sets to invalid state;

#ifdef _DEBUG
		enum e_print {
			e_all    = 0, // prints class name, rgba values and valid flag value;
			e_req    = 1, // pronts rgba values and valid flag  value;
			e_no_pfx = 2, // removes 'cls' prefix from the out string;
		};
		CString Print (const e_print = e_print::e_req) const;
#endif

	public:
		CQuad&  operator = (const CQuad&);
		CQuad&  operator = (CQuad&&);
		CQuad&  operator <<(bool _valid);      // sets a validity of this quad object;
		CQuad&  operator <<(rgb_color _color); // assigning plain color value; transparency value or alpha is set to opaque; it's made for compatibility with GDI;
		CQuad&  operator <<(clr_value _alpha); // accepts a magic alpha;

		operator bool (void) const;
		operator rgb_color (void) const;

		bool operator == (rgb_color) const;    // compares for equality the rgb color values  ; valid flags are not taken into account;
		bool operator != (rgb_color) const;    // compares for inequality the rgb color values; valid flags are not taken into account;

		bool operator == (const CQuad&) const; // uses the above equality operator by providing the input object rgb color; validity flags are not checked(!);
		bool operator != (const CQuad&) const; // uses the above inequality operator by providing the input object rgb color; validity flags are not checked(!);

	protected:
		bool      m_valid;                  // false by default; This value is not calculated, it is simply set for cases when an object needs to mark its color as invalid;
		clr_value m_value[channel::_count]; // using an array can provide better code compactness, but at the same time it is not so much readable;
	};

	/*
		https://en.wikipedia.org/wiki/Colorfulness ;
		https://en.wikipedia.org/wiki/Chromium ;
		https://stackoverflow.com/questions/596216/formula-to-determine-perceived-brightness-of-rgb-color ;
		https://en.wikipedia.org/wiki/Chromaticity ; relates to 'chroma' definition ;

		This class is for some rgb color transformation, i.e. to make it dark or light;
	*/

	class CColor : public CQuad {
	              typedef CQuad TBase;
	public:
		CColor (void);
		CColor (clr_type _color);                      // alpha channel is used as it is;
		CColor (clr_type _color , clr_value _alpha);   // alpha channel is specified separately;

	public: // transform(s);
		float Chroma (void) const;             // gets color intensity value (aka chromacity) from this quad color channels; (must be clarified)

		bool  Darken (const TPercent&);        // darkens a color quad by specified percent value in [0...100] range; returns true if succeeds;
		bool  Darken (const uint8_t _percent); // darkens a color quad by specified percent value in [0...100] range; returns true if succeeds;

		bool  Differ (const clr_type _src, const int8_t _percent); // differs rgb value of input color by percent given in [-100...+100] range;

		bool  Lighten(const TPercent& );       // lightens a color by specified percent value in [0...100]; returns true if succeeds;
		bool  Lighten(const uint8_t _percent); // lightens a color by specified percent value in [0...100]; returns true if succeeds;

#ifdef _DEBUG
		using e_print = TBase::e_print;
		CString Print (const e_print = e_print::e_req) const;
#endif
	};
	// https://stackoverflow.com/questions/14375156/how-to-convert-a-rgb-color-value-to-an-hexadecimal-value-in-c >> just as an example;
	// just the converter for color data representation;
	class CHex {
	public:
		 CHex (clr_type = 0);
		 CHex (const CHex& );
		 CHex (CHex&&) = delete;
		~CHex (void);

	public:
		const
		CQuad& Color (void) const;
		CQuad& Color (void) ;

	public:
#if defined (_DEBUG)
		enum e_print {
			 e_all = 0,
			 e_val = 1,
		};
		static CString Print (const clr_type);
		static CString Print (const CQuad&, const e_print = e_print::e_val);
#endif
	public:
		CHex&  operator = (const CHex&);
		CHex&  operator = (CHex&&) = delete;
		CHex&  operator <<(const clr_type);
		CHex&  operator <<(const CQuad&);

	private:
		CQuad  m_color;
	};

}}}

typedef ex_ui::color::rgb::CQuad  TRgbQuad ;
typedef ex_ui::color::rgb::CColor TRgbColor;

#endif/*__SFXSOACLIENTDRAWINGSERVICECOLOURQUAD_H_*/