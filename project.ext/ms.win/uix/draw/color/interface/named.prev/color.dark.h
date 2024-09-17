#ifndef _COLOR_DARK_H_INCLUDED
#define _COLOR_DARK_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 9-Oct-2021 at 1:10:22.6414364 am, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack UIX dark color interface declaration file.
*/
#include "color.named.h"

namespace ex_ui { namespace color {

	class CDark_Ids {
	public:
		enum _ids {
			e__undef              , // #undefined; i.e RGB(0);
			e_DarkBlue            , // [0x00, 0x00, 0x8b]
			e_DarkCyan            , // [0x00, 0x8b, 0x8b]
			e_DarkGoldenRod       , // [0xb8, 0x86, 0x0b]
			e_DarkGoldenrod       , // [0xb8, 0x86, 0x0b]
			e_DarkGray            , // [0xa9, 0xa9, 0xa9]
			e_DarkGrey            , // [0xa9, 0xa9, 0xa9]
			e_DarkGreen           , // [0x00, 0x64, 0x00]
			e_DarkKhaki           , // [0xbd, 0xb7, 0x6b]
			e_DarkMagenta         , // [0x8b, 0x00, 0x8b]
			e_DarkOliveGreen      , // [0x55, 0x6b, 0x2f]
			e_DarkoliveGreen      , // [0x55, 0x6b, 0x2f]
			e_DarkOrange          , // [0xff, 0x8c, 0x00]
			e_DarkOrchid          , // [0x99, 0x32, 0xcc]
			e_DarkRed             , // [0x8b, 0x00, 0x00]
			e_DarkSalmon          , // [0xe9, 0x96, 0x7a]
			e_Darksalmon          , // [0xe9, 0x96, 0x7a]
			e_DarkSeaGreen        , // [0x8f, 0xbc, 0x8f]
			e_DarkSlateBlue       , // [0x48, 0x3d, 0x8b]
			e_DarkSlateGray       , // [0x2f, 0x4f, 0x4f]
			e_DarkSlateGrey       , // [0x2f, 0x4f, 0x4f]
			e_DarkTurquoise       , // [0x00, 0xce, 0xd1]
			e_DarkViolet          , // [0x94, 0x00, 0xd3]
			e_Darkorange          , // [0xff, 0x8c, 0x00]
		};
	};

	class CDark : public CNamed { typedef CNamed TBase;
	public:
		 CDark (void);
		 CDark (const CDark&);
		 CDark (const COLORREF, LPCTSTR _lp_sz_name);
		~CDark (void);

	public:
		CDark&  operator = (const CDark&);
		CDark&  operator <<(const COLORREF);
		CDark&  operator <<(LPCTSTR _lp_sz_name);
	};
}}

typedef ex_ui::color::CDark           TDarkColor;
typedef ex_ui::color::CDark_Ids::_ids TDarkClrIds;

typedef ::std::map<TDarkClrIds, TDarkColor> TDarkClrRaw;

namespace ex_ui { namespace color {

	class CDark_Enum {
	public:
		 CDark_Enum (void);
		~CDark_Enum (void);

	public:
		const
		TDarkColor&  Get(const TDarkClrIds) const; // returns a reference to fake object, if not found; it's hardly possible do not find, but to guarantee a result;
	public:
		const
		TDarkClrRaw& Raw (void) const;
	};

}}

#endif/*_COLOR_DARK_H_INCLUDED*/