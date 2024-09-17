#ifndef _COLOR_GREYED_H_INCLUDED
#define _COLOR_GREYED_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 9-Oct-2021 at 00:28:17.6824658 am, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack UIX greyed color interface declaration file.
*/
#include "color.named.h"

namespace ex_ui { namespace color {

	class CGreyed_Ids {
	public:
		enum _ids {
			e__undef   , // #undefined; i.e RGB(0);
			e_Gray     , // [0x80, 0x80, 0x80]
			e_Grey     , // [0x80, 0x80, 0x80]
			e_Gray10   , // [0x10, 0x10, 0x10]
			e_Grey10   , // [0x10, 0x10, 0x10]
			e_Gray20   , // [0x20, 0x20, 0x20]
			e_Grey20   , // [0x20, 0x20, 0x20]
			e_Gray30   , // [0x30, 0x30, 0x30]
			e_Grey30   , // [0x30, 0x30, 0x30]
			e_Gray40   , // [0x40, 0x40, 0x40]
			e_Grey40   , // [0x40, 0x40, 0x40]
			e_Gray50   , // [0x50, 0x50, 0x50]
			e_Grey50   , // [0x50, 0x50, 0x50]
			e_Gray60   , // [0x60, 0x60, 0x60]
			e_Grey60   , // [0x60, 0x60, 0x60]
			e_Gray70   , // [0x70, 0x70, 0x70]
			e_Grey70   , // [0x70, 0x70, 0x70]
			e_Gray80   , // [0x80, 0x80, 0x80]
			e_Grey80   , // [0x80, 0x80, 0x80]
			e_Gray90   , // [0x90, 0x90, 0x90]
			e_Grey90   , // [0x90, 0x90, 0x90]
		};
	};

	class CGreyed : public CNamed { typedef CNamed TBase;
	public:
		 CGreyed (void);
		 CGreyed (const CGreyed&);
		 CGreyed (const COLORREF, LPCTSTR _lp_sz_name);
		~CGreyed (void);

	public:
		CGreyed&  operator = (const CGreyed&);
		CGreyed&  operator <<(const COLORREF);
		CGreyed&  operator <<(LPCTSTR _lp_sz_name);
	};
}}

typedef ex_ui::color::CGreyed           TGreyedColor;
typedef ex_ui::color::CGreyed_Ids::_ids TGreyedClrIds;

typedef ::std::map<TGreyedClrIds, TGreyedColor> TGreyedClrRaw;

namespace ex_ui { namespace color {

	class CGreyed_Enum {
	public:
		 CGreyed_Enum (void);
		~CGreyed_Enum (void);

	public:
		const
		TGreyedColor&  Get(const TGreyedClrIds) const; // returns a reference to fake object, if not found; it's hardly possible do not find, but to guarantee a result;
	public:
		const
		TGreyedClrRaw& Raw (void) const;
	};

}}

#endif/*_COLOR_GREYED_H_INCLUDED*/