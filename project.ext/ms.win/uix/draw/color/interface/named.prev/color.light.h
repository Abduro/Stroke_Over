#ifndef _COLOR_LIGHT_H_INCLUDED
#define _COLOR_LIGHT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 9-Oct-2021 at 0:51:00.4496920 am, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack UIX light color interface declaration file.
*/
#include "color.named.h"

namespace ex_ui { namespace color {

	class CLight_Ids { // it might be useful to use 'bright' word, but english is not my first language, so I do not know the right choice;
	public:
		enum _ids {
			e__undef              , // #undefined; i.e RGB(0);
			e_LightBlue           , // [0xad, 0xd8, 0xe6]
			e_LightCoral          , // [0xf0, 0x80, 0x80]
			e_LightCyan           , // [0xe0, 0xff, 0xff]
			e_LightGoldenRodYellow, // [0xfa, 0xfa, 0xd2]
			e_LightGoldenrodYellow, // [0xfa, 0xfa, 0xd2] 
			e_LightGray           , // [0xd3, 0xd3, 0xd3]
			e_LightGrey           , // [0xd3, 0xd3, 0xd3] 
			e_LightGreen          , // [0x90, 0xee, 0x90]
			e_LightPink           , // [0xff, 0xb6, 0xc1]
			e_LightSalmon         , // [0xff, 0xa0, 0x7a]
			e_Lightsalmon         , // [0xff, 0xa0, 0x7a] 
			e_LightSeaGreen       , // [0x20, 0xb2, 0xaa]
			e_LightSkyBlue        , // [0x87, 0xce, 0xfa]
			e_LightSlateBlue      , // [0x84, 0x70, 0xff]
			e_LightSlateGray      , // [0x77, 0x88, 0x99]
			e_LightSlateGrey      , // [0x77, 0x88, 0x99] 
			e_LightSteelBlue      , // [0xb0, 0xc4, 0xde]
			e_LightsteelBlue      , // [0xb0, 0xc4, 0xde] 
			e_LightYellow         , // [0xff, 0xff, 0xe0]
		};
	};

	class CLight : public CNamed { typedef CNamed TBase;
	public:
		 CLight (void);
		 CLight (const CLight&);
		 CLight (const COLORREF, LPCTSTR _lp_sz_name);
		~CLight (void);

	public:
		 CLight&  operator = (const CLight&);
		 CLight&  operator <<(const COLORREF);
		 CLight&  operator <<(LPCTSTR _lp_sz_name);
	};
}}

typedef ex_ui::color::CLight           TLightColor;
typedef ex_ui::color::CLight_Ids::_ids TLightClrIds;

typedef ::std::map<TLightClrIds, TLightColor> TLightClrRaw;

namespace ex_ui { namespace color {

	class CLight_Enum {
	public:
		 CLight_Enum (void);
		~CLight_Enum (void);

	public:
		const
		TLightColor&  Get(const TLightClrIds) const; // returns a reference to fake object, if not found; it's hardly possible do not find, but to guarantee a result;
	public:
		const
		TLightClrRaw& Raw (void) const;
	};

}}

#endif/*_COLOR_LIGHT_H_INCLUDED*/