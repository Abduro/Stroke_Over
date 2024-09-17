/*
	Created by Tech_dog (ebontrop@gmail.com) on 7-Oct-2021 at 11:59:54.1087443 pm, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack UIX metallic color interface implementation file.
*/
#include "color.metallic.h"

using namespace ex_ui::color;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace color { namespace _impl {

	static TMetallicClrRaw metallic_colors = {
		 { TMetallicClrIds::e_Aluminum    , TMetallicColor(RGB(0x99, 0x99, 0x99), _T("Aluminum")) },
		 { TMetallicClrIds::e_CoolCopper  , TMetallicColor(RGB(0xd9, 0x87, 0x19), _T("CoolCopper")) },
		 { TMetallicClrIds::e_Copper      , TMetallicColor(RGB(0xb8, 0x73, 0x33), _T("Copper")) },
		 { TMetallicClrIds::e_Iron        , TMetallicColor(RGB(0x4c, 0x4c, 0x4c), _T("Iron")) },
		 { TMetallicClrIds::e_Lead        , TMetallicColor(RGB(0x19, 0x19, 0x19), _T("Lead")) },
		 { TMetallicClrIds::e_Magnesium   , TMetallicColor(RGB(0xb3, 0xb3, 0xb3), _T("Magnesium")) },
		 { TMetallicClrIds::e_Mercury     , TMetallicColor(RGB(0xe6, 0xe6, 0xe6), _T("Mercury")) },
		 { TMetallicClrIds::e_Nickel      , TMetallicColor(RGB(0x80, 0x80, 0x80), _T("Nickel")) },
		 { TMetallicClrIds::e_Poly        , TMetallicColor(RGB(0x80, 0x80, 0x80), _T("Poly")) },
		 { TMetallicClrIds::e_PolySilicon , TMetallicColor(RGB(0x60, 0x00, 0x00), _T("PolySilicon")) },
		 { TMetallicClrIds::e_Silver      , TMetallicColor(RGB(0xcc, 0xcc, 0xcc), _T("Silver")) },
		 { TMetallicClrIds::e_Steel       , TMetallicColor(RGB(0x66, 0x66, 0x66), _T("Steel")) },
		 { TMetallicClrIds::e_Tin         , TMetallicColor(RGB(0x7f, 0x7f, 0x7f), _T("Tin")) },
		 { TMetallicClrIds::e_Tungsten    , TMetallicColor(RGB(0x33, 0x33, 0x33), _T("Tungsten")) }
	};

}}}
using namespace ex_ui::color::_impl;
/////////////////////////////////////////////////////////////////////////////

CMetallic:: CMetallic (void) : TBase() {}
CMetallic:: CMetallic (const CMetallic& _ref) : CMetallic() { *this = _ref; }
CMetallic:: CMetallic (const COLORREF _clr, LPCTSTR _lp_sz_name) : CMetallic() { (TBase&)*this << _clr << _lp_sz_name; }
CMetallic::~CMetallic (void) {}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

CMetallic&  CMetallic::operator = (const CMetallic& _ref) { (TBase&)*this = (const TBase&)_ref; return *this; }
CMetallic&  CMetallic::operator <<(const COLORREF _clr) { (TBase&)*this << _clr; return *this; }
CMetallic&  CMetallic::operator <<(LPCTSTR _lp_sz_name) { (TBase&)*this << _lp_sz_name; return *this; }