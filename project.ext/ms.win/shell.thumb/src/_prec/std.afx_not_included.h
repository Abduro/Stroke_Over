#ifndef _STD_AFX_H_INCLUDED
#define _STD_AFX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 8-Aug-2024 at 21:59:16.2466991, UTC+7, Novosibirsk, Thursday;
	This is shell thumb extension project precompiled header declaration file;
*/

namespace ebo { namespace boo {
	/*
		C/C++ >> Advanced >> Forced Include Files = shared._std_afx.h;%(ForcedIncludeFiles) ;
		or in project file manually put the following nodes:
		<ClCompile>
			<ForcedIncludeFiles>std_afx.h;%(ForcedIncludeFiles)</ForcedIncludeFiles>
			<PrecompiledHeaderFile>std_afx.h</PrecompiledHeaderFile>
		</ClCompile>
		https://learn.microsoft.com/en-us/cpp/build/reference/fi-name-forced-include-file ;
		https://stackoverflow.com/questions/320723/visual-c-force-includes-option         ;
	*/
	class prec_head {
	public:
		prec_head(void) = delete; prec_head(const prec_head) = delete; prec_head(prec_head&&) = delete; ~prec_head(void) = delete;
	public:
		static void how_to_set_nothing (void) {}
	}

}}


#endif/*_STD_AFX_H_INCLUDED*/