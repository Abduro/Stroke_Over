#ifndef _ENTRY_POINT_H_INCLUDED
#define _ENTRY_POINT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 8-Aug-2024 at 23:51:07.5673747, UTC+7, Novosibirsk, Thursday;
	This is Stroke Over project MS Windows shell extension entry point interface declaration file;
*/
#include <atlbase.h>     // https://learn.microsoft.com/en-us/cpp/atl/reference/ccommodule-class ;
#include <combaseapi.h>  // https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-dllgetclassobject ;
#include <olectl.h>      // https://learn.microsoft.com/en-us/windows/win32/api/olectl/nf-olectl-dllregisterserver ;

namespace shell { namespace ext {

	using guid = GUID;
	using cls_id   = const guid;
	using iface_id = const guid;

	class cls_load_reason {
		public:
		enum _e_reason { // https://learn.microsoft.com/en-us/windows/win32/dlls/dllmain ;
			e_proc_attach   = DLL_PROCESS_ATTACH, // is being loaded into the virtual address space of the current process; LoadLibrary is the same;
			e_proc_detach   = DLL_PROCESS_DETACH, // is being unloaded from the virtual address space of the calling process; FreeLibrary is the same;
			e_thread_attach = DLL_THREAD_ATTACH , // current process is creating a new thread;
			e_thread_detach = DLL_THREAD_DETACH , // thread is exiting cleanly;
		};
	public:
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-dllgetclassobject ;
	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-dllcanunloadnow ;
	// https://learn.microsoft.com/en-us/windows/win32/api/olectl/nf-olectl-dllregisterserver ;
	// https://learn.microsoft.com/en-us/windows/win32/api/olectl/nf-olectl-dllunregisterserver ;

	class CLoader {
	public:
		CLoader (void) = delete; CLoader (const CLoader&) = delete; CLoader (CLoader&&) = delete; ~CLoader (void) = delete;

	public: // dll api function(s)/method(s);
		static HRESULT __stdcall DllCanUnloadNow (void);
		static HRESULT __stdcall DllGetClassObject (cls_id& _cls_id, iface_id& _iface_id, void** _ppv);
		static HRESULT __stdcall DllRegisterServer (void);
		static HRESULT __stdcall DllUnregisterServer (void);

	private:
		CLoader& operator = (const CLoader&) = delete;
		CLoader& operator = (CLoader&&) = delete;
	};

}}

#endif/*_ENTRY_POINT_H_INCLUDED*/