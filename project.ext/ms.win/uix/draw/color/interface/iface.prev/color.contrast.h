#ifndef _COLOR_CONTRAST_H_INCLUDED
#define _COLOR_CONTRAST_H_INCLUDED
/*
	Created by Tech_doc (ebontrop@gmail.com) on 9-Oct-2021 at 11:20:02.5364546 am, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack UIX color contrast interface declaration file;
*/
#include "color.alpha.h"
namespace ex_ui { namespace color {

	class CContrast {
	public:
		 CContrast (void);
		 CContrast (const CContrast&);
		~CContrast (void);

	public:
		 CContrast& operator = (const CContrast&);
	};

}}

#endif/*_COLOR_CONTRAST_H_INCLUDED*/