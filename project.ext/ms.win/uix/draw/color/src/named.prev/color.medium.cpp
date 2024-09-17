/*
	Created by Tech_dog (ebontrop@gmail.com) on 9-Oct-2021 at 10:18:38.0710610 am, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack UIX medium color interface declaration file.
*/
#include "color.medium.h"

using namespace ex_ui::color;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace color { namespace _impl {

	static TMediumClrRaw medium_colors = {
		{ TMediumClrIds::e_MediumAquaMarine    , TMediumColor(RGB(0x66, 0xcd, 0xaa), _T("MediumAquaMarine")    ) },
		{ TMediumClrIds::e_MediumAquamarine    , TMediumColor(RGB(0x66, 0xcd, 0xaa), _T("MediumAquamarine")    ) },
		{ TMediumClrIds::e_MediumBlue          , TMediumColor(RGB(0x00, 0x00, 0xcd), _T("MediumBlue")          ) },
		{ TMediumClrIds::e_MediumOrchid        , TMediumColor(RGB(0xba, 0x55, 0xd3), _T("MediumOrchid")        ) },
		{ TMediumClrIds::e_MediumPurple        , TMediumColor(RGB(0x93, 0x70, 0xdb), _T("MediumPurple")        ) },
		{ TMediumClrIds::e_MediumSeaGreen      , TMediumColor(RGB(0x3c, 0xb3, 0x71), _T("MediumSeaGreen")      ) },
		{ TMediumClrIds::e_MediumSlateBlue     , TMediumColor(RGB(0x7b, 0x68, 0xee), _T("MediumSlateBlue")     ) },
		{ TMediumClrIds::e_MediumSpringGreen   , TMediumColor(RGB(0x00, 0xfa, 0x9a), _T("MediumSpringGreen")   ) },
		{ TMediumClrIds::e_MediumTurquoise     , TMediumColor(RGB(0x48, 0xd1, 0xcc), _T("MediumTurquoise")     ) },
		{ TMediumClrIds::e_MediumVioletRed     , TMediumColor(RGB(0xc7, 0x15, 0x85), _T("MediumVioletRed")     ) },
	};

}}}
using namespace ex_ui::color::_impl;
/////////////////////////////////////////////////////////////////////////////

CMedium:: CMedium (void) : TBase() {}
CMedium:: CMedium (const CMedium& _ref) : CMedium() { *this = _ref; }
CMedium:: CMedium (const COLORREF _clr, LPCTSTR _lp_sz_name) : CMedium() { (TBase&)*this << _clr << _lp_sz_name; }
CMedium::~CMedium (void) {}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

CMedium&  CMedium::operator = (const CMedium& _ref) { (TBase&)*this = (const TBase&)_ref; return *this; }
CMedium&  CMedium::operator <<(const COLORREF _clr) { (TBase&)*this << _clr; return *this; }
CMedium&  CMedium::operator <<(LPCTSTR _lp_sz_name) { (TBase&)*this << _lp_sz_name; return *this; }

/////////////////////////////////////////////////////////////////////////////

CMedium_Enum:: CMedium_Enum (void) {}
CMedium_Enum::~CMedium_Enum (void) {}

/////////////////////////////////////////////////////////////////////////////
const
TMediumColor&  CMedium_Enum::Get (const TMediumClrIds e_id) const {
	e_id;
	TMediumClrRaw::const_iterator it_ = medium_colors.find(e_id);
	if (it_ == medium_colors.end ()) // hardly possible, but anyway;
	{
		static TMediumColor clr_inv(TMediumClrIds::e__undef, _T("#undef"));
		return clr_inv;
	}
	else
		return it_->second;
}

/////////////////////////////////////////////////////////////////////////////
const
TMediumClrRaw&  CMedium_Enum::Raw (void) const { return medium_colors; }