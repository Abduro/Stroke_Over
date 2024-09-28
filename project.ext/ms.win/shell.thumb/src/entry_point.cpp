/*
	Created by Tech_dog (ebontrop@gmail.com) on 8-Aug-2024 at 23:59:39.8346699, UTC+7, Novosibirsk, Thursday;
	This is Stroke Over project MS Windows shell extension entry point interface implementation file;
*/
#include "entry_point.h"

using namespace ATL;
using namespace shell::ext;

// https://learn.microsoft.com/en-us/cpp/atl/reference/ccommodule-class ;
// https://learn.microsoft.com/en-us/cpp/atl/atl-module-classes ;
CComModule _Module;

#define __ext_c  extern "C"
using dword = DWORD;
using instance_or_module = HINSTANCE; // HMODULE;
/////////////////////////////////////////////////////////////////////////////
__ext_c
bool __stdcall DllMain(instance_or_module _h_module, dword _u_reason, void* _p_reserved_that_be_not_used_forever) {
	_h_module; _u_reason; _p_reserved_that_be_not_used_forever;

	switch (_u_reason) {
	case cls_load_reason::e_proc_attach: {
		// https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-disablethreadlibrarycalls ;
		::DisableThreadLibraryCalls(_h_module);
	} break;
	case cls_load_reason::e_proc_detach: {} break;
	}
    return true;
}

/////////////////////////////////////////////////////////////////////////////

HRESULT CLoader::DllCanUnloadNow (void) {
	return 0;
}

HRESULT CLoader::DllGetClassObject (cls_id& _cls_id, iface_id& _iface_id, void** _ppv) {
	_cls_id; _iface_id; _ppv;

	return 0;
}

HRESULT __stdcall CLoader::DllRegisterServer (void) {
	return 0;
}

HRESULT __stdcall CLoader::DllUnregisterServer (void) {
	return 0;
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////