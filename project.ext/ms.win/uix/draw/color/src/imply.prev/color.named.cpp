/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Sep-2021 at 10:38:09.705 pm, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack UIX named color interface implementation file.
*/
#include "color.named.h"

using namespace ex_ui::color;

/////////////////////////////////////////////////////////////////////////////

CNamed:: CNamed (void) : m_clr(CLR_NONE) {}
CNamed:: CNamed (const CNamed& _ref) : CNamed() { *this = _ref; }
CNamed:: CNamed (const COLORREF _clr, LPCTSTR _lp_sz_name) : CNamed() { *this << _clr << _lp_sz_name; }
CNamed::~CNamed (void) {}

/////////////////////////////////////////////////////////////////////////////

COLORREF   CNamed::Color (void) const { return this->m_clr; }
HRESULT    CNamed::Color (const COLORREF _clr) {
	_clr;
	HRESULT hr_ = S_OK;

	if (CLR_NONE == _clr)
		return (hr_ = E_INVALIDARG);

	this->m_clr = _clr;

	return  hr_;
}

LPCTSTR    CNamed::Name (void) const { return this->m_name.GetString(); }
HRESULT    CNamed::Name (LPCTSTR _lp_sz_name) {
	_lp_sz_name;
	HRESULT hr_ = S_OK;

	CString cs_probe(_lp_sz_name);
	if (cs_probe.IsEmpty())
		return (hr_ = E_INVALIDARG);

	cs_probe.Trim();
	if (cs_probe.IsEmpty())
		return (hr_ = E_INVALIDARG);

	this->m_name = cs_probe;

	return  hr_;
}

/////////////////////////////////////////////////////////////////////////////

const bool CNamed::Is (void) const { return (CLR_NONE != this->m_clr && false == this->m_name.IsEmpty()); }

/////////////////////////////////////////////////////////////////////////////

CNamed&  CNamed::operator = (const CNamed& _ref) { *this << _ref.Color() << _ref.Name(); return *this; }
CNamed&  CNamed::operator <<(const COLORREF _clr) { this->Color(_clr); return *this; }
CNamed&  CNamed::operator <<(LPCTSTR _lp_sz_name) { this->Name(_lp_sz_name); return *this; }

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace color { namespace _impl {

	static TNamedClrRaw named_colors = {
	     { TNamedClrIds::e_AliceBlue           , TNamedColor(RGB(0xf0, 0xf8, 0xff), _T("AliceBlue")           ) },
	     { TNamedClrIds::e_AntiqueWhite        , TNamedColor(RGB(0xfa, 0xeb, 0xd7), _T("AntiqueWhite")        ) },
	     { TNamedClrIds::e_Aqua                , TNamedColor(RGB(0x00, 0xff, 0xff), _T("Aqua")                ) },
	     { TNamedClrIds::e_Aquamarine          , TNamedColor(RGB(0x7f, 0xff, 0xd4), _T("Aquamarine")          ) },
	     { TNamedClrIds::e_Azure               , TNamedColor(RGB(0xf0, 0xff, 0xff), _T("Azure")               ) },
	     { TNamedClrIds::e_Beige               , TNamedColor(RGB(0xf5, 0xf5, 0xdc), _T("Beige")               ) },
	     { TNamedClrIds::e_Bisque              , TNamedColor(RGB(0xff, 0xe4, 0xc4), _T("Bisque")              ) },
	     { TNamedClrIds::e_BeccaPurple         , TNamedColor(RGB(0x66, 0x33, 0x99), _T("BeccaPurple")         ) },
	     { TNamedClrIds::e_Black               , TNamedColor(RGB(0x00, 0x00, 0x00), _T("Black")               ) },
	     { TNamedClrIds::e_BlanchedAlmond      , TNamedColor(RGB(0xff, 0xeb, 0xcd), _T("BlanchedAlmond")      ) },
	     { TNamedClrIds::e_Blue                , TNamedColor(RGB(0x00, 0x00, 0xff), _T("Blue")                ) },
	     { TNamedClrIds::e_BlueViolet          , TNamedColor(RGB(0x8a, 0x2b, 0xe2), _T("BlueViolet")          ) },
	     { TNamedClrIds::e_Brown               , TNamedColor(RGB(0xa5, 0x2a, 0x2a), _T("Brown")               ) },
	     { TNamedClrIds::e_BurlyWood           , TNamedColor(RGB(0xde, 0xb8, 0x87), _T("BurlyWood")           ) },
	     { TNamedClrIds::e_Burlywood           , TNamedColor(RGB(0xde, 0xb8, 0x87), _T("Burlywood")           ) },
	     { TNamedClrIds::e_CadetBlue           , TNamedColor(RGB(0x5f, 0x9e, 0xa0), _T("CadetBlue")           ) },
	     { TNamedClrIds::e_Carnation           , TNamedColor(RGB(0xff, 0x5e, 0xd0), _T("Carnation")           ) },
	     { TNamedClrIds::e_Cayenne             , TNamedColor(RGB(0x8d, 0x00, 0x00), _T("Cayenne")             ) },
	     { TNamedClrIds::e_Chartreuse          , TNamedColor(RGB(0x7f, 0xff, 0x00), _T("Chartreuse")          ) },
	     { TNamedClrIds::e_Chocolate           , TNamedColor(RGB(0xd2, 0x69, 0x1e), _T("Chocolate")           ) },
	     { TNamedClrIds::e_Coral               , TNamedColor(RGB(0xff, 0x7f, 0x50), _T("Coral")               ) },
	     { TNamedClrIds::e_CornflowerBlue      , TNamedColor(RGB(0x64, 0x95, 0xed), _T("CornflowerBlue")      ) },
	     { TNamedClrIds::e_Cornsilk            , TNamedColor(RGB(0xff, 0xf8, 0xdc), _T("Cornsilk")            ) },
	     { TNamedClrIds::e_Crimson             , TNamedColor(RGB(0xdc, 0x14, 0x3c), _T("Crimson")             ) },
	     { TNamedClrIds::e_Cyan                , TNamedColor(RGB(0x00, 0xff, 0xff), _T("Cyan")                ) },
	     { TNamedClrIds::e_DeepPink            , TNamedColor(RGB(0xff, 0x14, 0x93), _T("DeepPink")            ) },
	     { TNamedClrIds::e_DeepSkyBlue         , TNamedColor(RGB(0x00, 0xbf, 0xbf), _T("DeepSkyBlue")         ) },
	     { TNamedClrIds::e_DimGray             , TNamedColor(RGB(0x69, 0x69, 0x69), _T("DimGray")             ) },
	     { TNamedClrIds::e_DimGrey             , TNamedColor(RGB(0x69, 0x69, 0x69), _T("DimGrey")             ) },
	     { TNamedClrIds::e_DodgerBlue          , TNamedColor(RGB(0x1e, 0x90, 0xff), _T("DodgerBlue")          ) },
	     { TNamedClrIds::e_Feldspar            , TNamedColor(RGB(0xd1, 0x92, 0x75), _T("Feldspar")            ) },
	     { TNamedClrIds::e_FireBrick           , TNamedColor(RGB(0xb2, 0x22, 0x22), _T("FireBrick")           ) },
	     { TNamedClrIds::e_Firebrick           , TNamedColor(RGB(0xb2, 0x22, 0x22), _T("Firebrick")           ) },
	     { TNamedClrIds::e_FloralWhite         , TNamedColor(RGB(0xff, 0xfa, 0xf0), _T("FloralWhite")         ) },
	     { TNamedClrIds::e_ForestGreen         , TNamedColor(RGB(0x22, 0x8b, 0x22), _T("ForestGreen")         ) },
	     { TNamedClrIds::e_Fuchsia             , TNamedColor(RGB(0xff, 0x00, 0xff), _T("Fuchsia")             ) },
	     { TNamedClrIds::e_Gainsboro           , TNamedColor(RGB(0xdc, 0xdc, 0xdc), _T("Gainsboro")           ) },
	     { TNamedClrIds::e_GhostWhite          , TNamedColor(RGB(0xf8, 0xf8, 0xff), _T("GhostWhite")          ) },
	     { TNamedClrIds::e_Gold                , TNamedColor(RGB(0xff, 0xd7, 0x00), _T("Gold")                ) },
	     { TNamedClrIds::e_GoldenRod           , TNamedColor(RGB(0xda, 0xa5, 0x20), _T("GoldenRod")           ) },
	     { TNamedClrIds::e_Goldenrod           , TNamedColor(RGB(0xda, 0xa5, 0x20), _T("Goldenrod")           ) },
	     { TNamedClrIds::e_Green               , TNamedColor(RGB(0x00, 0x80, 0x00), _T("Green")               ) },
	     { TNamedClrIds::e_GreenYellow         , TNamedColor(RGB(0xad, 0xff, 0x2f), _T("GreenYellow")         ) },
	     { TNamedClrIds::e_HoneyDew            , TNamedColor(RGB(0xf0, 0xff, 0xf0), _T("HoneyDew")            ) },
	     { TNamedClrIds::e_Honeydew            , TNamedColor(RGB(0xf0, 0xff, 0xf0), _T("Honeydew")            ) },
	     { TNamedClrIds::e_HotPink             , TNamedColor(RGB(0xff, 0x69, 0xb4), _T("HotPink")             ) },
	     { TNamedClrIds::e_IndianRed           , TNamedColor(RGB(0xcd, 0x5c, 0x5c), _T("IndianRed")           ) },
	     { TNamedClrIds::e_Indigo              , TNamedColor(RGB(0x4b, 0x00, 0x82), _T("Indigo")              ) },
	     { TNamedClrIds::e_Ivory               , TNamedColor(RGB(0xff, 0xff, 0xf0), _T("Ivory")               ) },
	     { TNamedClrIds::e_Khaki               , TNamedColor(RGB(0xf0, 0xe6, 0x8c), _T("Khaki")               ) },
	     { TNamedClrIds::e_Lavender            , TNamedColor(RGB(0xe6, 0xe6, 0xfa), _T("Lavender")            ) },
	     { TNamedClrIds::e_LavenderBlush       , TNamedColor(RGB(0xff, 0xf0, 0xf5), _T("LavenderBlush")       ) },
	     { TNamedClrIds::e_LawnGreen           , TNamedColor(RGB(0x7c, 0xfc, 0x00), _T("LawnGreen")           ) },
	     { TNamedClrIds::e_LemonChiffon        , TNamedColor(RGB(0xff, 0xfa, 0xcd), _T("LemonChiffon")        ) },
	     { TNamedClrIds::e_Lime                , TNamedColor(RGB(0x00, 0xff, 0x00), _T("Lime")                ) },
	     { TNamedClrIds::e_LimeGreen           , TNamedColor(RGB(0x32, 0xcd, 0x32), _T("LimeGreen")           ) },
	     { TNamedClrIds::e_Linen               , TNamedColor(RGB(0xfa, 0xf0, 0xe6), _T("Linen")               ) },
	     { TNamedClrIds::e_Magenta             , TNamedColor(RGB(0xff, 0x00, 0xff), _T("Magenta")             ) },
	     { TNamedClrIds::e_Maroon              , TNamedColor(RGB(0x80, 0x00, 0x00), _T("Maroon")              ) },
	     { TNamedClrIds::e_MidnightBlue        , TNamedColor(RGB(0x19, 0x19, 0x70), _T("MidnightBlue")        ) },
	     { TNamedClrIds::e_MintCream           , TNamedColor(RGB(0xf5, 0xff, 0xfa), _T("MintCream")           ) },
	     { TNamedClrIds::e_MistyRose           , TNamedColor(RGB(0xff, 0xe4, 0xe1), _T("MistyRose")           ) },
	     { TNamedClrIds::e_Moccasin            , TNamedColor(RGB(0xff, 0xe4, 0xb5), _T("Moccasin")            ) },
	     { TNamedClrIds::e_NavajoWhite         , TNamedColor(RGB(0xff, 0xde, 0xad), _T("NavajoWhite")         ) },
	     { TNamedClrIds::e_Navy                , TNamedColor(RGB(0x00, 0x00, 0x80), _T("Navy")                ) },
	     { TNamedClrIds::e_OldLace             , TNamedColor(RGB(0xfd, 0xf5, 0xe6), _T("OldLace")             ) },
	     { TNamedClrIds::e_Olive               , TNamedColor(RGB(0x80, 0x80, 0x00), _T("Olive")               ) },
	     { TNamedClrIds::e_OliveDrab           , TNamedColor(RGB(0x6b, 0x8e, 0x23), _T("OliveDrab")           ) },
	     { TNamedClrIds::e_Olivedrab           , TNamedColor(RGB(0x6b, 0x8e, 0x23), _T("Olivedrab")           ) },
	     { TNamedClrIds::e_Orange              , TNamedColor(RGB(0xff, 0xa5, 0x00), _T("Orange")              ) },
	     { TNamedClrIds::e_OrangeRed           , TNamedColor(RGB(0xff, 0x45, 0x00), _T("OrangeRed")           ) },
	     { TNamedClrIds::e_Orchid              , TNamedColor(RGB(0xda, 0x70, 0xd6), _T("Orchid")              ) },
	     { TNamedClrIds::e_PaleGoldenRod       , TNamedColor(RGB(0xee, 0xe8, 0xaa), _T("PaleGoldenRod")       ) },
	     { TNamedClrIds::e_PaleGoldenrod       , TNamedColor(RGB(0xee, 0xe8, 0xaa), _T("PaleGoldenrod")       ) },
	     { TNamedClrIds::e_PaleGreen           , TNamedColor(RGB(0x98, 0xfb, 0x98), _T("PaleGreen")           ) },
	     { TNamedClrIds::e_PaleTurquoise       , TNamedColor(RGB(0xaf, 0xee, 0xee), _T("PaleTurquoise")       ) },
	     { TNamedClrIds::e_PaleVioletRed       , TNamedColor(RGB(0xdb, 0x70, 0x93), _T("PaleVioletRed")       ) },
	     { TNamedClrIds::e_PapayaWhip          , TNamedColor(RGB(0xff, 0xef, 0xd5), _T("PapayaWhip")          ) },
	     { TNamedClrIds::e_PeachPuff           , TNamedColor(RGB(0xff, 0xda, 0xb9), _T("PeachPuff")           ) },
	     { TNamedClrIds::e_Peachpuff           , TNamedColor(RGB(0xff, 0xda, 0xb9), _T("Peachpuff")           ) },
	     { TNamedClrIds::e_Peru                , TNamedColor(RGB(0xcd, 0x85, 0x3f), _T("Peru")                ) },
	     { TNamedClrIds::e_Pink                , TNamedColor(RGB(0xff, 0xc0, 0xcb), _T("Pink")                ) },
	     { TNamedClrIds::e_Plum                , TNamedColor(RGB(0xdd, 0xa0, 0xdd), _T("Plum")                ) },
	     { TNamedClrIds::e_PowderBlue          , TNamedColor(RGB(0xb0, 0xe0, 0xe6), _T("PowderBlue")          ) },
	     { TNamedClrIds::e_Purple              , TNamedColor(RGB(0x80, 0x00, 0x80), _T("Purple")              ) },
	     { TNamedClrIds::e_RebeccaPurple       , TNamedColor(RGB(0x66, 0x33, 0x99), _T("RebeccaPurple")       ) },
	     { TNamedClrIds::e_Red                 , TNamedColor(RGB(0xff, 0x00, 0x00), _T("Red")                 ) },
	     { TNamedClrIds::e_RosyBrown           , TNamedColor(RGB(0xbc, 0x8f, 0x8f), _T("RosyBrown")           ) },
	     { TNamedClrIds::e_RoyalBlue           , TNamedColor(RGB(0x41, 0x69, 0xe1), _T("RoyalBlue")           ) },
	     { TNamedClrIds::e_SaddleBrown         , TNamedColor(RGB(0x8b, 0x45, 0x13), _T("SaddleBrown")         ) },
	     { TNamedClrIds::e_Salmon              , TNamedColor(RGB(0xfa, 0x80, 0x72), _T("Salmon")              ) },
	     { TNamedClrIds::e_SandyBrown          , TNamedColor(RGB(0xf4, 0xa4, 0x60), _T("SandyBrown")          ) },
	     { TNamedClrIds::e_SeaGreen            , TNamedColor(RGB(0x2e, 0x8b, 0x57), _T("SeaGreen")            ) },
	     { TNamedClrIds::e_SeaShell            , TNamedColor(RGB(0xff, 0xf5, 0xee), _T("SeaShell")            ) },
	     { TNamedClrIds::e_Seashell            , TNamedColor(RGB(0xff, 0xf5, 0xee), _T("Seashell")            ) },
	     { TNamedClrIds::e_Sienna              , TNamedColor(RGB(0xa0, 0x52, 0x2d), _T("Sienna")              ) },
	     { TNamedClrIds::e_Silver              , TNamedColor(RGB(0xc0, 0xc0, 0xc0), _T("Silver")              ) },
	     { TNamedClrIds::e_SkyBlue             , TNamedColor(RGB(0x87, 0xce, 0xeb), _T("SkyBlue")             ) },
	     { TNamedClrIds::e_SlateBlue           , TNamedColor(RGB(0x6a, 0x5a, 0xcd), _T("SlateBlue")           ) },
	     { TNamedClrIds::e_SlateGray           , TNamedColor(RGB(0x70, 0x80, 0x90), _T("SlateGray")           ) },
	     { TNamedClrIds::e_SlateGrey           , TNamedColor(RGB(0x70, 0x80, 0x90), _T("SlateGrey")           ) },
	     { TNamedClrIds::e_Snow                , TNamedColor(RGB(0xff, 0xfa, 0xfa), _T("Snow")                ) },
	     { TNamedClrIds::e_SpringGreen         , TNamedColor(RGB(0x00, 0xff, 0x7f), _T("SpringGreen")         ) },
	     { TNamedClrIds::e_SteelBlue           , TNamedColor(RGB(0x46, 0x82, 0xb4), _T("SteelBlue")           ) },
	     { TNamedClrIds::e_Tan                 , TNamedColor(RGB(0xd2, 0xb4, 0x8c), _T("Tan")                 ) },
	     { TNamedClrIds::e_Teal                , TNamedColor(RGB(0x00, 0x80, 0x80), _T("Teal")                ) },
	     { TNamedClrIds::e_Thistle             , TNamedColor(RGB(0xd8, 0xbf, 0xd8), _T("Thistle")             ) },
	     { TNamedClrIds::e_Tomato              , TNamedColor(RGB(0xff, 0x63, 0x47), _T("Tomato")              ) },
	     { TNamedClrIds::e_Turquoise           , TNamedColor(RGB(0x40, 0xe0, 0xd0), _T("Turquoise")           ) },
	     { TNamedClrIds::e_Violet              , TNamedColor(RGB(0xee, 0x82, 0xee), _T("Violet")              ) },
	     { TNamedClrIds::e_VioletRed           , TNamedColor(RGB(0xd0, 0x20, 0x90), _T("VioletRed")           ) },
	     { TNamedClrIds::e_Wheat               , TNamedColor(RGB(0xf5, 0xde, 0xb3), _T("Wheat")               ) },
	     { TNamedClrIds::e_White               , TNamedColor(RGB(0xff, 0xff, 0xff), _T("White")               ) },
	     { TNamedClrIds::e_WhiteSmoke          , TNamedColor(RGB(0xf5, 0xf5, 0xf5), _T("WhiteSmoke")          ) },
	     { TNamedClrIds::e_Yellow              , TNamedColor(RGB(0xff, 0xff, 0x00), _T("Yellow")              ) },
	     { TNamedClrIds::e_YellowGreen         , TNamedColor(RGB(0x9a, 0xcd, 0x32), _T("YellowGreen")         ) },
	};

}}}
using namespace ex_ui::color::_impl;
/////////////////////////////////////////////////////////////////////////////

CNamed_Enum:: CNamed_Enum (void) {}
CNamed_Enum::~CNamed_Enum (void) {}

/////////////////////////////////////////////////////////////////////////////
const
TNamedColor&  CNamed_Enum::Get (const TNamedClrIds e_id) const {
	e_id;
	TNamedClrRaw::const_iterator it_ = named_colors.find(e_id);
	if (it_ == named_colors.end ()) // hardly possible, but anyway;
	{
		static TNamedColor clr_inv(TNamedClrIds::e__undef, _T("#undef"));
		return clr_inv;
	}
	else
		return it_->second;
}

/////////////////////////////////////////////////////////////////////////////
const
TNamedClrRaw&  CNamed_Enum::Raw (void) const { return named_colors; }