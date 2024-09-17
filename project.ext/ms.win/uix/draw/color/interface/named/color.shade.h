#ifndef _COLOR_SHADE_H_INCLUDED
#define _COLOR_SHADE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 9-Apr-2024 at 09:48:58.9145177, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack X11 Windows system color shade enumeration interface declaration file; 
*/
#include <vector>
#include "color.named.h"

namespace ex_ui { namespace color { namespace rgb {

	/*
		Blue  >> https://en.wikipedia.org/wiki/Shades_of_blue  << e_AliceBlue << e_Aqua;
		Cyan  >> https://en.wikipedia.org/wiki/Shades_of_cyan  << e_AliceBlue << e_Aqua << e_Aquamarine;
		Green >> https://en.wikipedia.org/wiki/Shades_of_green << e_Aqua << e_Aquamarine;
		White >> https://en.wikipedia.org/wiki/Shades_of_white << e_AliceBlue << e_AntiqueWhite;
	*/

	class CNamedShades : public CNamed_Enum {
	public:
		 CNamedShades (void);
		 CNamedShades (const CNamedShades&) = delete;
		 CNamedShades (CNamedShades&&) = delete;
		~CNamedShades (void);

	public:
		CNamedShades& operator = (const CNamedShades&) = delete;
		CNamedShades& operator = (CNamedShades&&) = delete;
	};

}}}

typedef ex_ui::color::rgb::CNamedShades   TRgbShades;

#endif/*_COLOR_SHADE_H_INCLUDED*/