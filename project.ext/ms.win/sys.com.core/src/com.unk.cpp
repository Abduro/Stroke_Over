/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Sep-2024 at 15:11:53.577, UTC+7, Novosibirsk, Friday;
	This is Ebo Pack project comp-obj-model IUnknown interface base wrapper implementation file;
*/
#include "com.unk.h"

using namespace shared::sys_core::com;

/////////////////////////////////////////////////////////////////////////////

CUnknown:: CUnknown (void) : m_lRef(1) {}
CUnknown:: CUnknown (const GUID& _iface_id) : CUnknown() { m_owner << _iface_id; }
CUnknown::~CUnknown (void) {}

/////////////////////////////////////////////////////////////////////////////

u_long   CUnknown::AddRef (void) {
	return static_cast<ULONG>(InterlockedIncrement( &this->m_lRef )); // it is strange: different data types for func impl and iface decl;
}

err_code CUnknown::QueryInterface ( const GUID& _iid, void** ppv ) {
	_iid; ppv;
	if ( !ppv )
		return __e_pointer;

	if (_iid == IID_IUnknown )
	{
		*ppv = static_cast<IUnknown*>( this );
		this->AddRef();
		return TErrCodes::no_error;
	}
	*ppv = 0;
	return __e_no_iface;
}

u_long   CUnknown::Release (void) {
		
	LONG lRef = InterlockedDecrement( &this->m_lRef ); // https://learn.microsoft.com/en-us/windows/win32/api/winnt/nf-winnt-interlockeddecrement ;
	if ( lRef < 1 ) 
		delete this;

	return static_cast<u_long>(lRef);
}

/////////////////////////////////////////////////////////////////////////////

const  IUnknown* CUnknown::Ptr (void) const { return static_cast<const IUnknown*>(this); }
const  u_long CUnknown::Refs (void) const { return this->m_lRef; }
const
CGuid& CUnknown::Owner (void) const { return this->m_owner; }
CGuid& CUnknown::Owner (void)       { return this->m_owner; }

/////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG)
CString CUnknown::Print (const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s]>>{ptr->%s;refs=%u}");
	static _pc_sz pc_sz_pat_r = _T("{ptr->%s;refs=%u}");
	static _pc_sz pc_sz_pat_t = _T("[%s]>>{ptr->%s;refs=%u}");

	CString cs_out;
	if (e_print::e_all == e_opt) cs_out.Format(pc_sz_pat_a, (_pc_sz)__CLASS__, TStringEx().__address_of(this->Ptr()), this->Refs());
	if (e_print::e_no_prx == e_opt) cs_out.Format(pc_sz_pat_t, (_pc_sz)__CLASS__, TStringEx().__address_of(this->Ptr()), this->Refs());
	if (e_print::e_req == e_opt) cs_out.Format(pc_sz_pat_r, TStringEx().__address_of(this->Ptr()), this->Refs());

	if (cs_out.IsEmpty())
		cs_out.Format(_T("[%s].%s(#inv_arg=%d)"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif
#if defined(_DEBUG)
/////////////////////////////////////////////////////////////////////////////

CDefault_unknown:: CDefault_unknown (void) : TBase(__guid_null) {}
CDefault_unknown::~CDefault_unknown (void) {}

/////////////////////////////////////////////////////////////////////////////

CString CDefault_unknown::Print (void) const {

	static _pc_sz pc_sz_pat = _T("cls::[%s]::%s;"); 

	CString cs_out; cs_out.Format(pc_sz_pat, (_pc_sz) __CLASS__, (_pc_sz)TBase::Print(TBase::e_no_prx));
	return  cs_out;
}

#endif