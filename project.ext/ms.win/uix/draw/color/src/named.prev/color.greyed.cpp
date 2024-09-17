/*
	Created by Tech_dog (ebontrop@gmail.com) on 9-Oct-2021 at 00:00:37:11.1788842 am, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack UIX greyed color interface implementation file.
*/
#include "color.greyed.h"

using namespace ex_ui::color;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace color { namespace _impl {

	static TGreyedClrRaw greyed_colors = {
		{ CGreyed_Ids::e_Gray    , TGreyedColor(RGB(0x80, 0x80, 0x80), _T("Gray")   ) },
		{ CGreyed_Ids::e_Grey    , TGreyedColor(RGB(0x80, 0x80, 0x80), _T("Grey")   ) },
	    	{ CGreyed_Ids::e_Gray10  , TGreyedColor(RGB(0x10, 0x10, 0x10), _T("Gray10") ) },
		{ CGreyed_Ids::e_Grey10  , TGreyedColor(RGB(0x10, 0x10, 0x10), _T("Grey10") ) },
		{ CGreyed_Ids::e_Gray20  , TGreyedColor(RGB(0x20, 0x20, 0x20), _T("Gray20") ) },
		{ CGreyed_Ids::e_Grey20  , TGreyedColor(RGB(0x20, 0x20, 0x20), _T("Grey20") ) },
		{ CGreyed_Ids::e_Gray30  , TGreyedColor(RGB(0x30, 0x30, 0x30), _T("Gray30") ) },
		{ CGreyed_Ids::e_Grey30  , TGreyedColor(RGB(0x30, 0x30, 0x30), _T("Grey30") ) },
		{ CGreyed_Ids::e_Gray40  , TGreyedColor(RGB(0x40, 0x40, 0x40), _T("Gray40") ) },
		{ CGreyed_Ids::e_Grey40  , TGreyedColor(RGB(0x40, 0x40, 0x40), _T("Grey40") ) },
		{ CGreyed_Ids::e_Gray50  , TGreyedColor(RGB(0x50, 0x50, 0x50), _T("Gray50") ) },
		{ CGreyed_Ids::e_Grey50  , TGreyedColor(RGB(0x50, 0x50, 0x50), _T("Grey50") ) },
		{ CGreyed_Ids::e_Gray60  , TGreyedColor(RGB(0x60, 0x60, 0x60), _T("Gray60") ) },
		{ CGreyed_Ids::e_Grey60  , TGreyedColor(RGB(0x60, 0x60, 0x60), _T("Grey60") ) },
		{ CGreyed_Ids::e_Gray70  , TGreyedColor(RGB(0x70, 0x70, 0x70), _T("Gray70") ) },
		{ CGreyed_Ids::e_Grey70  , TGreyedColor(RGB(0x70, 0x70, 0x70), _T("Grey70") ) },
		{ CGreyed_Ids::e_Gray80  , TGreyedColor(RGB(0x80, 0x80, 0x80), _T("Gray80") ) },
		{ CGreyed_Ids::e_Grey80  , TGreyedColor(RGB(0x80, 0x80, 0x80), _T("Grey80") ) },
		{ CGreyed_Ids::e_Gray90  , TGreyedColor(RGB(0x90, 0x90, 0x90), _T("Gray90") ) },
		{ CGreyed_Ids::e_Grey90  , TGreyedColor(RGB(0x90, 0x90, 0x90), _T("Grey90") ) },
	};

}}}
using namespace ex_ui::color::_impl;
/////////////////////////////////////////////////////////////////////////////

CGreyed:: CGreyed (void) : TBase() {}
CGreyed:: CGreyed (const CGreyed& _ref) : CGreyed() { *this = _ref; }
CGreyed:: CGreyed (const COLORREF _clr, LPCTSTR _lp_sz_name) : CGreyed() { (TBase&)*this << _clr << _lp_sz_name; }
CGreyed::~CGreyed (void) {}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

CGreyed&  CGreyed::operator = (const CGreyed& _ref) { (TBase&)*this = (const TBase&)_ref; return *this; }
CGreyed&  CGreyed::operator <<(const COLORREF _clr) { (TBase&)*this << _clr; return *this; }
CGreyed&  CGreyed::operator <<(LPCTSTR _lp_sz_name) { (TBase&)*this << _lp_sz_name; return *this; }

/////////////////////////////////////////////////////////////////////////////

CGreyed_Enum:: CGreyed_Enum (void) {}
CGreyed_Enum::~CGreyed_Enum (void) {}

/////////////////////////////////////////////////////////////////////////////
const
TGreyedColor&  CGreyed_Enum::Get (const TGreyedClrIds e_id) const {
	e_id;
	TGreyedClrRaw::const_iterator it_ = greyed_colors.find(e_id);
	if (it_ == greyed_colors.end ()) // hardly possible, but anyway;
	{
		static TGreyedColor clr_inv(TGreyedClrIds::e__undef, _T("#undef"));
		return clr_inv;
	}
	else
		return it_->second;
}

/////////////////////////////////////////////////////////////////////////////
const
TGreyedClrRaw&  CGreyed_Enum::Raw (void) const { return greyed_colors; }