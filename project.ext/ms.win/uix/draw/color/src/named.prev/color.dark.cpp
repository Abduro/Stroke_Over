/*
	Created by Tech_dog (ebontrop@gmail.com) on 9-Oct-2021 at 8:27:56.4527071 am, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack UIX dark color interface implementation file.
*/
#include "color.dark.h"

using namespace ex_ui::color;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace color { namespace _impl {

	static TDarkClrRaw dark_colors = {
		{ TDarkClrIds::e_DarkBlue            , TDarkColor(RGB(0x00, 0x00, 0x8b), _T("DarkBlue")      ) },
		{ TDarkClrIds::e_DarkCyan            , TDarkColor(RGB(0x00, 0x8b, 0x8b), _T("DarkCyan")      ) },
		{ TDarkClrIds::e_DarkGoldenRod       , TDarkColor(RGB(0xb8, 0x86, 0x0b), _T("DarkGoldenRod") ) },
		{ TDarkClrIds::e_DarkGoldenrod       , TDarkColor(RGB(0xb8, 0x86, 0x0b), _T("DarkGoldenrod") ) },
		{ TDarkClrIds::e_DarkGray            , TDarkColor(RGB(0xa9, 0xa9, 0xa9), _T("DarkGray")      ) },
		{ TDarkClrIds::e_DarkGrey            , TDarkColor(RGB(0xa9, 0xa9, 0xa9), _T("DarkGrey")      ) },
		{ TDarkClrIds::e_DarkGreen           , TDarkColor(RGB(0x00, 0x64, 0x00), _T("DarkGreen")     ) },
		{ TDarkClrIds::e_DarkKhaki           , TDarkColor(RGB(0xbd, 0xb7, 0x6b), _T("DarkKhaki")     ) },
		{ TDarkClrIds::e_DarkMagenta         , TDarkColor(RGB(0x8b, 0x00, 0x8b), _T("DarkMagenta")   ) },
		{ TDarkClrIds::e_DarkOliveGreen      , TDarkColor(RGB(0x55, 0x6b, 0x2f), _T("DarkOliveGreen")) },
		{ TDarkClrIds::e_DarkoliveGreen      , TDarkColor(RGB(0x55, 0x6b, 0x2f), _T("DarkoliveGreen")) },
		{ TDarkClrIds::e_DarkOrange          , TDarkColor(RGB(0xff, 0x8c, 0x00), _T("DarkOrange")    ) },
		{ TDarkClrIds::e_DarkOrchid          , TDarkColor(RGB(0x99, 0x32, 0xcc), _T("DarkOrchid")    ) },
		{ TDarkClrIds::e_DarkRed             , TDarkColor(RGB(0x8b, 0x00, 0x00), _T("DarkRed")       ) },
		{ TDarkClrIds::e_DarkSalmon          , TDarkColor(RGB(0xe9, 0x96, 0x7a), _T("DarkSalmon")    ) },
		{ TDarkClrIds::e_Darksalmon          , TDarkColor(RGB(0xe9, 0x96, 0x7a), _T("Darksalmon")    ) },
		{ TDarkClrIds::e_DarkSeaGreen        , TDarkColor(RGB(0x8f, 0xbc, 0x8f), _T("DarkSeaGreen")  ) },
		{ TDarkClrIds::e_DarkSlateBlue       , TDarkColor(RGB(0x48, 0x3d, 0x8b), _T("DarkSlateBlue") ) },
		{ TDarkClrIds::e_DarkSlateGray       , TDarkColor(RGB(0x2f, 0x4f, 0x4f), _T("DarkSlateGray") ) },
		{ TDarkClrIds::e_DarkSlateGrey       , TDarkColor(RGB(0x2f, 0x4f, 0x4f), _T("DarkSlateGrey") ) },
		{ TDarkClrIds::e_DarkTurquoise       , TDarkColor(RGB(0x00, 0xce, 0xd1), _T("DarkTurquoise") ) },
		{ TDarkClrIds::e_DarkViolet          , TDarkColor(RGB(0x94, 0x00, 0xd3), _T("DarkViolet")    ) },
		{ TDarkClrIds::e_Darkorange          , TDarkColor(RGB(0xff, 0x8c, 0x00), _T("Darkorange")    ) },
	};
}}}
using namespace ex_ui::color::_impl;
/////////////////////////////////////////////////////////////////////////////

CDark_Enum:: CDark_Enum (void) {}
CDark_Enum::~CDark_Enum (void) {}

/////////////////////////////////////////////////////////////////////////////
const
TDarkColor&  CDark_Enum::Get (const TDarkClrIds e_id) const {
	e_id;
	TDarkClrRaw::const_iterator it_ = dark_colors.find(e_id);
	if (it_ == dark_colors.end ()) // hardly possible, but anyway;
	{
		static TDarkColor clr_inv(TDarkClrIds::e__undef, _T("#undef"));
		return clr_inv;
	}
	else
		return it_->second;
}

/////////////////////////////////////////////////////////////////////////////
const
TDarkClrRaw&  CDark_Enum::Raw (void) const { return dark_colors; }