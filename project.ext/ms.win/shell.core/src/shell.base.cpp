/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Sep-2024 at 15:37:45.002, GMT+7, Novosibirsk, Wednesday;
	This is Ebo pack windows shell extension base interface implementation file;
*/
#include "shell.base.h"

using namespace shell::ext::core;

/////////////////////////////////////////////////////////////////////////////

CShellExtInit:: CShellExtInit (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CShellExtInit:: CShellExtInit (const CShellExtInit& _src) : CShellExtInit() { *this = _src; }
//CShellExtInit:: CShellExtInit (CShellExtInit&& _victim) : CShellExtInit() { *this = _victim; }
CShellExtInit::~CShellExtInit (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&  CShellExtInit::Error (void) const { return this->m_error; }

/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString  CShellExtInit::Print (const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s]>>{error=%s}");
	static _pc_sz pc_sz_pat_r = _T("is_valid(%s)");

	CString cs_out;

	if (e_print::e_all == e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__CLASS__, (_pc_sz)this->Error().Print(CError::e_all)); }
	if (e_print::e_req == e_opt) { cs_out.Format(pc_sz_pat_r, TString().Bool(false == this->Error())); }

	if (cs_out.IsEmpty())
		cs_out.Format (_T("[%s].[%s](#inv_arg<%d>)"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CShellExtInit&  CShellExtInit::operator = (const CShellExtInit& _src) { _src; return *this; }
//CShellExtInit&  CShellExtInit::operator = (CShellExtInit&& _victim) { _victim; return *this; }