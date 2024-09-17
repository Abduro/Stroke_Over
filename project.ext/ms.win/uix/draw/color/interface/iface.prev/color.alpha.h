#ifndef _COLOR_ALPHA_H_INCLUDED
#define _COLOR_ALPHA_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Oct-2021 at 1:45:38.8392778 am, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack color alpha value interface declaration file;
*/
#ifndef RGBA
#define RGBA(r,g,b,a)	( RGB(r,g,b) | (((DWORD)(BYTE)(a))<<24) )
#endif
#ifndef GetAValue
#define GetAValue(_clr)	( 0 == LOBYTE((_clr)>>24) ? 255 : LOBYTE((_clr)>>24) )
#endif

namespace ex_ui { namespace color {

	class CAlpha {
	public:
		enum e_value : BYTE{
			eTransparent     = 0x00,      // transparent
			eTransparent95   = 0x0D,      // 05% opacity
			eTransparent90   = 0x19,      // 10% opacity
			eTransparent85   = 0x26,      // 15% opacity
			eTransparent80   = 0x33,      // 20% opacity
			eTransparent75   = 0x40,      // 25% opacity
			eTransparent70   = 0x4C,      // 30% opacity
			eTransparent65   = 0x59,      // 35% opacity
			eTransparent60   = 0x66,      // 40% opacity
			eTransparent55   = 0x73,      // 45% opacity
			eSemitransparent = 0x7F,      // 50% opacity
			eTransparent45   = 0x8C,      // 55% opacity
			eTransparent40   = 0x99,      // 60% opacity
			eTransparent35   = 0xA6,      // 65% opacity
			eTransparent30   = 0xB2,      // 70% opacity
			eTransparent25   = 0xBF,      // 75% opacity
			eTransparent20   = 0xCC,      // 80% opacity
			eTransparent15   = 0xD9,      // 85% opacity
			eTransparent10   = 0xE5,      // 90% opacity
			eTransparent05   = 0xF2,      // 95% opacity
			eOpaque          = 0xFF       //100% opacity
		};
	};

}}

typedef ex_ui::color::CAlpha::e_value TAlpha;

#endif/*_COLOR_ALPHA_H_INCLUDED*/