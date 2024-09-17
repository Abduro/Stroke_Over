/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Nov-2019 at 6:37:16a, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack shared drawing library complementary colors pairs implementation file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack color library on 10-Oct-2021 at 2:01:31.3813618 pm, UTC+7, Novosibirsk, Sunday
*/
#include "color.compl.h"

using namespace ex_ui::color;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace color { namespace _impl {

	static CComplClrs CCmpClrs_Objs[] = {
	       CComplClrs(H2C(0x161C25), CLR_NONE     , H2C(0xF3A950), _T("Black & Orange")    ,       _T("The orange provides a dose of optimism, while the black is a professional and grounded counterpart.")),
	       CComplClrs(H2C(0x1C1A1A), CLR_NONE     , H2C(0xEB4D37), _T("Black & Red"   )    ,       _T("Daring and surprisingly inviting, color combination dominates and instills a sense of power and energy.")),
	       CComplClrs(H2C(0x333333), H2C(0xBA0000), H2C(0xE9E9E9), _T("Black, White & Red"),       _T("Black and white are one of the most popular, yet classic, colour schemes.")),
	       CComplClrs(H2C(0x2F2D29), CLR_NONE     , H2C(0xF9D342), _T("Black & Yellow")    ,       _T("The bright yellow and almost-black shade of grey have an air of mystery and intrigue.")),
	       CComplClrs(H2C(0x4830D4), CLR_NONE     , H2C(0xCBF380), _T("Blue & Green"  )    ,       _T("Blue and green are often associated with tranquility, but this electric blue and lime green exude energy and youthfulness.")),
	       CComplClrs(H2C(0x080A52), CLR_NONE     , H2C(0xEB2188), _T("Blue & Pink"   )    ,       _T("The vibrant pink radiates against the blue and works well for industries like beauty and blogging.")),
	       CComplClrs(H2C(0x273773), CLR_NONE     , H2C(0x8BD7BD), _T("Blue & Turquoise"  ),       _T("The colors are from the same color family, but are different enough to create a striking duo, with the turquoise used sparingly.")),
	       CComplClrs(H2C(0x90AFEC), CLR_NONE     , H2C(0xFEFEFE), _T("Blue & White"  )    ,       _T("This peaceful sky blue and white combo is a definite crowd pleaser, communicating feelings of trust and tranquility.")),
	       CComplClrs(H2C(0x34434D), CLR_NONE     , H2C(0xC75400), _T("Charcoal & Burnt Orange"),  _T("The best thing about charcoal and burnt orange combination is that it is gender neutral.")),
	       CComplClrs(H2C(0x585E5D), CLR_NONE     , H2C(0xF5CA0C), _T("Grey & Yellow" )    ,       _T("This colour combination is mostly attributed to the monochromatic feel that grey projects, and the contrasting vibrancy of yellow.")),
	       CComplClrs(H2C(0x858988), CLR_NONE     , H2C(0xA82B32), _T("Neutral Grey & Red"),       _T("Red is one of the best colours to use to break the monotony of neutral colours and spice things a notch or two.")),
	       CComplClrs(H2C(0x141A46), CLR_NONE     , H2C(0xFA935B), _T("Orange & Blue" )    ,       _T("This complementary color duo is a classic yet powerful pairing and is popular in the technology and banking sectors.")),
	       CComplClrs(H2C(0x4A274F), CLR_NONE     , H2C(0xFBA77D), _T("Orange & Purple")   ,       _T("This pairing of warm peach and eggplant purple is both elegant and unique.")),
	       CComplClrs(H2C(0x333333), CLR_NONE     , H2C(0xF27B70), _T("Peach & Black" )    ,       _T("This is a great colour combination for achieving a formal look.")),
	       CComplClrs(H2C(0x2F3C7D), CLR_NONE     , H2C(0xFEECEC), _T("Pink & Blue"   )    ,       _T("A delicate pink paired with navy blue gives off a playful yet trustworthy vibe.")),
	       CComplClrs(H2C(0x3D1560), CLR_NONE     , H2C(0xDE668B), _T("Purple & Pink" )    ,       _T("The bright pink adds a spark of energy, while the purple acts as a mature counterpart.")),
	       CComplClrs(H2C(0x3C1A5B), CLR_NONE     , H2C(0xFEF648), _T("Purple & Yellow")   ,       _T("Optimistic and energizing yellow with a rich purple to spark feelings of creativity.")),
	       CComplClrs(H2C(0x2B3252), H2C(0xEF5455), H2C(0xFAD644), _T("Red, Navy, & Yellow" ),     _T("The bright red complements the cheery yellow and regal navy, exuding power and confidence.")),
	       CComplClrs(H2C(0x5595A1), CLR_NONE     , H2C(0xFBEA74), _T("Turquoise & Marigold"),     _T("Turquoise and marigold are an excellent choice for colour combinations of getting extra pop.")),
	       CComplClrs(H2C(0x295F2D), CLR_NONE     , H2C(0xFFE67B), _T("Yellow & Green")    ,       _T("This youthful yellow brings life and energy to the otherwise calming green in this color combination.")),
	       CComplClrs(H2C(0xF86067), CLR_NONE     , H2C(0xFCEE77), _T("Yellow & Red"  )    ,       _T("The vibrant red and happy shade of yellow create a sense of energy and playfulness."))
	};

}}}
using namespace ex_ui::color::_impl;
/////////////////////////////////////////////////////////////////////////////

CComplClr:: CComplClr (void) : m_algo(_algo::e_simplistic) {}
CComplClr:: CComplClr (const CComplClr& _ref) : CComplClr() { *this = _ref; }
CComplClr:: CComplClr (const COLORREF _clr_src, const _algo e_algo) : CComplClr() { *this << e_algo << _clr_src; }
CComplClr::~CComplClr (void) {}

/////////////////////////////////////////////////////////////////////////////

TCmpClrAlgo CComplClr::Algo (void) const { return this->m_algo; }
bool        CComplClr::Algo (const _algo e_algo) {
	e_algo;
	bool b_changed = (this->Algo() != e_algo);

	if ( b_changed )
		this->m_algo = e_algo;

	return b_changed;
}

COLORREF  CComplClr::Get (void) const { return this->m_clr; }

HRESULT   CComplClr::Set (const COLORREF _from, const _algo e_how_to_make_it) {
	_from; e_how_to_make_it;
	HRESULT hr_ = S_OK;

	if (CLR_NONE == _from)
		return (hr_ = E_INVALIDARG);

	this->Algo(e_how_to_make_it);

	switch (e_how_to_make_it) {
	case _algo::e_simplistic: {
			// https://stackoverflow.com/questions/3054873/programmatically-find-complement-of-colors	              
			LONG r_ = 0xff & (_from >>  0);  r_ = 0xff - r_;
			LONG g_ = 0xff & (_from >>  8);  g_ = 0xff - g_;
			LONG b_ = 0xff & (_from >> 16);  b_ = 0xff - b_;
			LONG a_ = 0xff & (_from >> 24);

			this->m_clr = r_ + (g_ << 8) + (b_ << 16) + (a_ << 24);

		} break;
	default:
		hr_ = __DwordToHresult(ERROR_UNSUPPORTED_TYPE);
	}

	return  hr_;
}

/////////////////////////////////////////////////////////////////////////////

CComplClr&  CComplClr::operator = (const CComplClr& _ref) { this->m_clr = _ref.Get(); *this << _ref.Algo(); return *this; }
CComplClr&  CComplClr::operator <<(const _algo e_algo)  { this->Algo(e_algo); return *this; }
CComplClr&  CComplClr::operator <<(const COLORREF _clr) { this->Set(_clr, this->Algo()); return *this; }

/////////////////////////////////////////////////////////////////////////////

CComplClrs:: CComplClrs (void) { m_clr[0] = m_clr[1] = m_clr[2] = CLR_NONE; }
CComplClrs:: CComplClrs (const COLORREF _dark, const COLORREF _mid, const COLORREF _lt, LPCTSTR _lp_sz_nm, LPCTSTR _lp_sz_ds) {
	m_clr[0] = _dark; m_clr[1] = _mid; m_clr[2] = _lt; m_name = _lp_sz_nm; m_desc = _lp_sz_ds;
}
CComplClrs::~CComplClrs(void) {}

/////////////////////////////////////////////////////////////////////////////

const DWORD& CComplClrs::Dark  (void) const { return m_clr[0]; }
      DWORD& CComplClrs::Dark  (void)       { return m_clr[0]; }
const DWORD& CComplClrs::Light (void) const { return m_clr[2]; }
      DWORD& CComplClrs::Light (void)       { return m_clr[2]; }
const DWORD& CComplClrs::Middle(void) const { return m_clr[1]; }
      DWORD& CComplClrs::Middle(void)       { return m_clr[1]; }

/////////////////////////////////////////////////////////////////////////////

const bool   CComplClrs::Is (void) const { return (m_clr[0] != CLR_NONE || m_clr[1] != CLR_NONE || m_clr[2] != CLR_NONE); }

/////////////////////////////////////////////////////////////////////////////
const
CAtlString&  CComplClrs::Desc  (void) const { return m_desc;   }
CAtlString&  CComplClrs::Desc  (void)       { return m_desc;   }
const
CAtlString&  CComplClrs::Name  (void) const { return m_name;   }
CAtlString&  CComplClrs::Name  (void)       { return m_name;   }

/////////////////////////////////////////////////////////////////////////////

CComplClrs_Enum:: CComplClrs_Enum(void) {
	try {
		for (size_t i_ = 0; i_ < _countof(CCmpClrs_Objs); i_++) {
			m_clrs.push_back(CCmpClrs_Objs[i_]);
		}
	}
	catch (const ::std::bad_alloc&) {}
}
CComplClrs_Enum::~CComplClrs_Enum(void) {}

/////////////////////////////////////////////////////////////////////////////

const CComplClrs& CComplClrs_Enum::Item(const size_t _ndx) const {
	if (this->Size() == 0 || _ndx > this->Size() - 1) {
		static CComplClrs na_clr;
		return na_clr;
	}
	else
		return m_clrs[_ndx];
}
const TComplClrs& CComplClrs_Enum::Raw (void) const { return m_clrs; }
const size_t      CComplClrs_Enum::Size(void) const { return m_clrs.size(); }

/////////////////////////////////////////////////////////////////////////////

const CComplClrs& CComplClrs_Enum:: operator[](const size_t _ndx) const { return this->Item(_ndx); }