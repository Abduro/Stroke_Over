#ifndef _COLOR_DEFS_H_INCLUDED
#define _COLOR_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Mar-2024 at 15:13:53.0751887, UTC+7, Omsk, Saturday; [Thai timezone is kept]
	This is Ebo pack UIX color library generic definition declaration file; 
*/
#include <algorithm>  // https://en.cppreference.com/w/cpp/algorithm/swap ;
#include <cstddef>    // https://en.cppreference.com/w/cpp/language/types ;
#include <limits>

#if defined(_DEBUG)
#include "shared.preproc.h"
#include "shared.string.h"
#endif

namespace ex_ui { namespace color {
	// https://stackoverflow.com/questions/2745074/fast-ceiling-of-an-integer-division-in-c-c/2745086#2745086 ;

	/*
		https://en.wikipedia.org/wiki/Percentage ;
		https://dictionary.cambridge.org/dictionary/english/pct ;
		The limits:
		(a) no negative value is accepted; (done)
		(b) no fraction value is accepted; for example, 99.(9)% ; (done)
	*/

	// https://www.acronymfinder.com/Fraction-(F).html ;
	// perhaps using a template for declaring this class would be better, but for good readability making more overload methods is also acceptable ;)
	class CPercent_F {
	public:
		enum _std_range : uint8_t {
			e_max = 100,
			e_min = 0  ,
		};
		static const uint8_t n_max_digits = 6; // maximum number of digits in fractional part that is taking into account when comparison is made;
	public:
		 CPercent_F (const CPercent_F&);

		 CPercent_F (const float _value = 0.0f); // is used as default constructor if necessary;
		 CPercent_F (const int32_t _value);
		 
		 CPercent_F (CPercent_F&&) = delete;
		~CPercent_F (void) = default;

	public:
		float Get (void) const ;
		bool  Set (const float);       // returns true in case of data changes; a simplified comparison function is used (up to 6 digits in fractions are taken into account);
		bool  Set (const int32_t);     // sets percent as intiger data type value; it is automatically converted to float >> xxxx.00f;
		// https://en.cppreference.com/w/cpp/numeric/math/round ;
		int32_t GetAsInt (bool _no_round = false) const; // for data type conversion ::std::round() is applied; if input flag is false, the round func is not applied;

		bool  Is_equal (const float  , const uint8_t _n_digits = CPercent_F::n_max_digits) const;
		bool  Is_equal (const int32_t, const uint8_t _n_digits = CPercent_F::n_max_digits) const;

#if defined(_DEBUG)
		enum e_print {
			e_as_is  = 0, // outputs out the percent value as float number, i.e. as is;
			e_as_int = 1, // outputs the percentage value as an integer, which can be rounded up or down;
		};
		CString  Print (const e_print = e_print::e_as_is) const;
#endif
	public:
		CPercent_F&  operator = (const CPercent_F&);
		CPercent_F&  operator = (CPercent_F&&) = delete ;

		CPercent_F&  operator <<(const float   _f_value);
		CPercent_F&  operator <<(const int32_t _n_value);

		CPercent_F&  operator+= (const CPercent_F&);
		CPercent_F&  operator-= (const CPercent_F&);

		CPercent_F&  operator+= (const float _f_inc) ;
		CPercent_F&  operator-= (const float _f_dec) ;

		CPercent_F&  operator+= (const int32_t _n_inc);
		CPercent_F&  operator-= (const int32_t _n_dec);

		operator float (void) const;
		operator int32_t (void) const;

	private:
		float m_value;
	};

}}

typedef ex_ui::color::CPercent_F TPct_Flt;

namespace ex_ui { namespace color { namespace rgb {

	typedef uint8_t clr_value;  // color light intensity ;
	static const
	ex_ui::color::rgb::clr_value value_max = ((::std::numeric_limits<ex_ui::color::rgb::clr_value>::max)());

	typedef uint32_t clr_type;  // a mix of primary colors, each of them has own color light intensity;
	static const                // maximum acceptable value of RGB color channels; channels mostly relate to composing of digital image;
	ex_ui::color::rgb::clr_type clr_max = ((::std::numeric_limits<ex_ui::color::rgb::clr_type>::max)());
	/*
		https://stackoverflow.com/questions/2765164/inline-vs-inline-vs-inline-vs-forceinline ;
		__inline leads to: error LNK2019: unresolved external symbol when building unit test executable library;
	*/
	/*__inline*/ clr_value get_a_value (const clr_type); // extracts alpha transparency;
	/*__inline*/ clr_value get_b_value (const clr_type); // extracts blue  color value;
	/*__inline*/ clr_value get_g_value (const clr_type); // extracts green color value;
	/*__inline*/ clr_value get_r_value (const clr_type); // extracts red   color value;

	// this is stupid(!), but otherwise: error C2803: 'operator ==' must have at least one formal parameter of class type ;
	// thus, color type class is declared:
	class CType {
	public:
		 CType(const clr_type = 0);
		 CType(const CType&);
		 CType(CType&&);
		~CType(void);

	public:
		clr_type Get (void) const ;
		bool     Set (clr_type _type); // returns true in case of changing the value of internal type;

		bool EqualTo (const clr_type) const;

#if defined(_DEBUG)
		CString  Print(void) const;
#endif

	public:
		CType&  operator = (const CType&);
		CType&  operator = (CType&&);        // does not use classes' field value swap, just makes a copying;
		CType&  operator <<(clr_type);

		bool operator == (const CType&) const;
		bool operator != (const CType&) const;

		bool operator == (clr_type) const;
		bool operator != (clr_type) const;

		operator clr_type(void) const;

	private:
		clr_type m_type;
	};
}}}

typedef ex_ui::color::rgb::CType TRgbType;

typedef ex_ui::color::rgb::clr_value rgb_value; // similar to a color channel either red, green or blue; alpha channel can also have this value type;
#define rgb_val_max (ex_ui::color::rgb::value_max)

typedef ex_ui::color::rgb::clr_type  rgb_color; // it looks like COLORREF that is defined for GDI API;
#define rgb_clr_max (ex_ui::color::rgb::clr_max)

#define rgb_clr_none rgb_clr_max // this is the value for indicating non-existance a color, as CLR_NONE in GDI definitions;

#define _r_g_b(r,g,b) ((rgb_color)(uint8_t(r) | ((uint16_t(uint8_t(g))) << 8) | (uint32_t(uint8_t(b)) << 16))) // just substitutes RGB by data types with new names;
#define _r_g_b_a(r,g,b,a) (_r_g_b(r,g,b) | ((uint32_t(a))<<24) )                                               // just playing with data type names or definitions ;

#define HexToRgb(_hex) (_r_g_b( (uint32_t(_hex)>>16), (uint16_t(_hex)>>8), uint8_t(_hex)))
#if (0)
bool operator == (const TRgbType& _lhv, const TRgbType& _rhv);
bool operator != (const TRgbType& _lhv, const TRgbType& _rhv);

bool operator == (const TRgbType& _lhv, const rgb_color _rhv);
bool operator != (const TRgbType& _lhv, const rgb_color _rhv);

bool operator == (const rgb_color _lhv, const TRgbType& _rhv);
bool operator != (const rgb_color _lhv, const TRgbType& _rhv);
#endif

bool Is_equal (const rgb_color _lhs, const rgb_color _rhs, const bool _b_compare_alpha = true) ;

namespace ex_ui { namespace color { namespace hsl {

}}}

#endif/*_COLOR_DEFS_H_INCLUDED*/