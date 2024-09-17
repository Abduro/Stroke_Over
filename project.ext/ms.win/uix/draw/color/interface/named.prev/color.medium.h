#ifndef _COLOR_MEDIUM_H_INCLUDED
#define _COLOR_MEDIUM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 9-Oct-2021 at 10:18:38.0710610 am, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack UIX medium color interface declaration file.
*/
#include "color.named.h"

namespace ex_ui { namespace color {

	class CMedium_Ids {
	public:
		enum _ids {
			e__undef              , // #undefined; i.e RGB(0) and alpha is also zero;
			e_MediumAquaMarine    , // [0x66, 0xcd, 0xaa]
			e_MediumAquamarine    , // [0x66, 0xcd, 0xaa]
			e_MediumBlue          , // [0x00, 0x00, 0xcd]
			e_MediumOrchid        , // [0xba, 0x55, 0xd3]
			e_MediumPurple        , // [0x93, 0x70, 0xdb]
			e_MediumSeaGreen      , // [0x3c, 0xb3, 0x71]
			e_MediumSlateBlue     , // [0x7b, 0x68, 0xee]
			e_MediumSpringGreen   , // [0x00, 0xfa, 0x9a]
			e_MediumTurquoise     , // [0x48, 0xd1, 0xcc]
			e_MediumVioletRed     , // [0xc7, 0x15, 0x85]
		};
	};

	class CMedium : public CNamed { typedef CNamed TBase;
	public:
		 CMedium (void);
		 CMedium (const CMedium&);
		 CMedium (const COLORREF, LPCTSTR _lp_sz_name);
		~CMedium (void);

	public:
		 CMedium& operator = (const CMedium&);
		 CMedium& operator <<(const COLORREF);
		 CMedium& operator <<(LPCTSTR _lp_sz_name);
	};
}}

typedef ex_ui::color::CMedium           TMediumColor;
typedef ex_ui::color::CMedium_Ids::_ids TMediumClrIds;

typedef ::std::map<TMediumClrIds, TMediumColor> TMediumClrRaw;

namespace ex_ui { namespace color {

	class CMedium_Enum {
	public:
		 CMedium_Enum (void);
		~CMedium_Enum (void);

	public:
		const
		TMediumColor&  Get(const TMediumClrIds) const; // returns a reference to fake object, if not found; it's hardly possible do not find, but to guarantee a result;
	public:
		const
		TMediumClrRaw& Raw (void) const;
	};

}}

#endif/*_COLOR_MEDIUM_H_INCLUDED*/