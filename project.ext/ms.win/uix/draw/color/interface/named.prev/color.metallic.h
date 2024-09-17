#ifndef _COLOR_METALLIC_INCLUDED
#define _COLOR_METALLIC_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 7-Oct-2021 at 11:52:49.6180837 pm, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack UIX metallic color interface declaration file.
*/
#include "color.named.h"

namespace ex_ui { namespace color {

	class CMetallic_Ids {
	public:
		enum _ids {
			e__undef      , // [0x00, 0x00, 0x00]
			e_Aluminum    , // [0x99, 0x99, 0x99]
			e_CoolCopper  , // [0xd9, 0x87, 0x19]
			e_Copper      , // [0xb8, 0x73, 0x33]
			e_Iron        , // [0x4c, 0x4c, 0x4c]
			e_Lead        , // [0x19, 0x19, 0x19]
			e_Magnesium   , // [0xb3, 0xb3, 0xb3]
			e_Mercury     , // [0xe6, 0xe6, 0xe6]
			e_Nickel      , // [0x80, 0x80, 0x80]
			e_Poly        , // [0x80, 0x80, 0x80]
			e_PolySilicon , // [0x60, 0x00, 0x00]
			e_Silver      , // [0xcc, 0xcc, 0xcc]
			e_Steel       , // [0x66, 0x66, 0x66]
			e_Tin         , // [0x7f, 0x7f, 0x7f]
			e_Tungsten    , // [0x33, 0x33, 0x33]
		};
	};

	class CMetallic : public CNamed { typedef CNamed TBase;
	public:
		 CMetallic (void);
		 CMetallic (const CMetallic&);
		 CMetallic (const COLORREF, LPCTSTR _lp_sz_name);
		~CMetallic (void);

	public:
		CMetallic&  operator = (const CMetallic&);
		CMetallic&  operator <<(const COLORREF);
		CMetallic&  operator <<(LPCTSTR _lp_sz_name);
	};

}}

typedef ex_ui::color::CMetallic           TMetallicColor;
typedef ex_ui::color::CMetallic_Ids::_ids TMetallicClrIds;

typedef ::std::map<TMetallicClrIds, TMetallicColor> TMetallicClrRaw;

namespace ex_ui { namespace color {

	class CMetallic_Enum {
	public:
		 CMetallic_Enum (void);
		~CMetallic_Enum (void);

	public:
		const
		TMetallicColor&  Get(const TMetallicClrIds) const; // returns a reference to fake object, if not found;
	public:
		const
		TMetallicClrRaw& Raw (void) const;
	};

}}

#endif/*_COLOR_METALLIC_INCLUDED*/