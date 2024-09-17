/*
	Created by Tech_dog (ebontrop@gmail.com) on 9-Oct-2021 at 1:02:49.5480024 am, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack UIX light color interface implementation file.
*/
#include "color.light.h"

using namespace ex_ui::color;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace color { namespace _impl {

	static TLightClrRaw light_colors = {
		{ TLightClrIds::e_LightBlue           , TLightColor(RGB(0xad, 0xd8, 0xe6), _T("LightBlue")           ) },
		{ TLightClrIds::e_LightCoral          , TLightColor(RGB(0xf0, 0x80, 0x80), _T("LightCoral")          ) },
		{ TLightClrIds::e_LightCyan           , TLightColor(RGB(0xe0, 0xff, 0xff), _T("LightCyan")           ) },
		{ TLightClrIds::e_LightGoldenRodYellow, TLightColor(RGB(0xfa, 0xfa, 0xd2), _T("LightGoldenRodYellow")) },
		{ TLightClrIds::e_LightGoldenrodYellow, TLightColor(RGB(0xfa, 0xfa, 0xd2), _T("LightGoldenrodYellow")) },
		{ TLightClrIds::e_LightGray           , TLightColor(RGB(0xd3, 0xd3, 0xd3), _T("LightGray")           ) },
		{ TLightClrIds::e_LightGrey           , TLightColor(RGB(0xd3, 0xd3, 0xd3), _T("LightGrey")           ) },
		{ TLightClrIds::e_LightGreen          , TLightColor(RGB(0x90, 0xee, 0x90), _T("LightGreen")          ) },
		{ TLightClrIds::e_LightPink           , TLightColor(RGB(0xff, 0xb6, 0xc1), _T("LightPink")           ) },
		{ TLightClrIds::e_LightSalmon         , TLightColor(RGB(0xff, 0xa0, 0x7a), _T("LightSalmon")         ) },
		{ TLightClrIds::e_Lightsalmon         , TLightColor(RGB(0xff, 0xa0, 0x7a), _T("Lightsalmon")         ) },
		{ TLightClrIds::e_LightSeaGreen       , TLightColor(RGB(0x20, 0xb2, 0xaa), _T("LightSeaGreen")       ) },
		{ TLightClrIds::e_LightSkyBlue        , TLightColor(RGB(0x87, 0xce, 0xfa), _T("LightSkyBlue")        ) },
		{ TLightClrIds::e_LightSlateBlue      , TLightColor(RGB(0x84, 0x70, 0xff), _T("LightSlateBlue")      ) },
		{ TLightClrIds::e_LightSlateGray      , TLightColor(RGB(0x77, 0x88, 0x99), _T("LightSlateGray")      ) },
		{ TLightClrIds::e_LightSlateGrey      , TLightColor(RGB(0x77, 0x88, 0x99), _T("LightSlateGrey")      ) },
		{ TLightClrIds::e_LightSteelBlue      , TLightColor(RGB(0xb0, 0xc4, 0xde), _T("LightSteelBlue")      ) },
		{ TLightClrIds::e_LightsteelBlue      , TLightColor(RGB(0xb0, 0xc4, 0xde), _T("LightsteelBlue")      ) },
		{ TLightClrIds::e_LightYellow         , TLightColor(RGB(0xff, 0xff, 0xe0), _T("LightYellow")         ) },
	};

}}}
using namespace ex_ui::color::_impl;
/////////////////////////////////////////////////////////////////////////////

CLight:: CLight (void) : TBase() {}
CLight:: CLight (const CLight& _ref) : CLight() { *this = _ref; }
CLight:: CLight (const COLORREF _clr, LPCTSTR _lp_sz_name) : CLight() { (TBase&)*this << _clr << _lp_sz_name; }
CLight::~CLight (void) {}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

CLight&  CLight::operator = (const CLight& _ref)  { (TBase&)*this = (const TBase&)_ref; return *this; }
CLight&  CLight::operator <<(const COLORREF _clr) { (TBase&)*this << _clr; return *this; }
CLight&  CLight::operator <<(LPCTSTR _lp_sz_name) { (TBase&)*this << _lp_sz_name; return *this; }

/////////////////////////////////////////////////////////////////////////////

CLight_Enum:: CLight_Enum (void) {}
CLight_Enum::~CLight_Enum (void) {}

/////////////////////////////////////////////////////////////////////////////
const
TLightColor&  CLight_Enum::Get (const TLightClrIds e_id) const {
	e_id;
	TLightClrRaw::const_iterator it_ = light_colors.find(e_id);
	if (it_ == light_colors.end ()) // hardly possible, but anyway;
	{
		static TLightColor clr_inv(TLightClrIds::e__undef, _T("#undef"));
		return clr_inv;
	}
	else
		return it_->second;
}

/////////////////////////////////////////////////////////////////////////////
const
TLightClrRaw&  CLight_Enum::Raw (void) const { return light_colors; }