/*
	Created by Tech_dog (ebontrop@gmail.com) on 8-Sep-2019 at 7:06:44a, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack shared lite library system error format interface implementation file.
	-----------------------------------------------------------------------------
	Adopted to Geometry Curve project on 17-Feb-2024 at 07:17:12.9469957, UTC+7, Novosibirsk, Saturday;
*/
#include "sys.err.format.h"

using namespace shared::sys_core;
using namespace shared::sys_core::_impl;

/////////////////////////////////////////////////////////////////////////////

CErr_Details:: CErr_Details (void) {}
CErr_Details::~CErr_Details (void) {}

/////////////////////////////////////////////////////////////////////////////

LPCTSTR CErr_Details::args     (LPCTSTR _lp_sz_pat, const va_list& _err_args) {
	this->clear();
	m_temp = _lp_sz_pat;
	if (m_temp.IsEmpty() == true)
		return m_desc.GetString();

	size_t t_size = 0;
	try {

		HRESULT hr_ = S_OK;

		do
		{
			t_size += 2048;
			TCHAR* t_buf = new TCHAR[t_size];

			::memset(t_buf, 0, t_size * sizeof(TCHAR));

			hr_ = ::StringCchVPrintfEx(
				t_buf     ,
				t_size    ,
				NULL      ,
				NULL      ,
				0         ,
				m_temp.GetString(),
				_err_args
			);
			if (S_OK  == hr_) {
				m_desc = t_buf;
				this->normalize();
			}
			if (NULL  != t_buf) {
				try {
					delete t_buf; t_buf = NULL;
				}
				catch (...) {
					break;
				}
			}
		}
		while(STRSAFE_E_INSUFFICIENT_BUFFER == hr_);
	}
	catch  (::std::bad_alloc&) {}

	return (LPCTSTR)m_desc;
}

VOID    CErr_Details::clear    (void) { if (m_desc.IsEmpty() == false) m_desc.Empty(); }
VOID    CErr_Details::normalize(void) {
	if (m_desc.IsEmpty() == false) {
		m_desc.Trim();
		m_desc.Replace(_T("\r")  , _T(" "));
		m_desc.Replace(_T("\n")  , _T(" "));
	}
}

DWORD   CErr_Details::size     (void) const { return static_cast<DWORD>(m_desc.GetLength()); }

/////////////////////////////////////////////////////////////////////////////

CErr_Details& CErr_Details::operator << (const CLang&   _err_lang) {
	m_lang = _err_lang;
	return *this;
}

CErr_Details& CErr_Details::operator << (const DWORD    _err_code) {
	this->clear();

	TCHAR t_buf[_MAX_PATH] = {0};

	::FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL         ,
		_err_code    ,
		m_lang.Id()  ,
		t_buf        ,
		_MAX_PATH - 1,
		NULL
	);

	if (ERROR_RESOURCE_LANG_NOT_FOUND == ::GetLastError()) {
		m_desc = CErr_Msg().NotFound();
	}
	else {
		m_desc = t_buf;
		this->normalize();
	}

	return *this;
}
CErr_Details& CErr_Details::operator << (const HRESULT  _err_code) {
	this->clear();

	WCHAR t_buf[_MAX_PATH] = {0};
	::FormatMessageW(
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL         ,
		_err_code    ,
		m_lang.Id()  ,
		t_buf        ,
		_MAX_PATH - 1,
		NULL
	);
	m_desc = t_buf;
	this->normalize();

	return *this;
}
CErr_Details& CErr_Details::operator << (const va_list& _err_args) {
	this->clear();
	this->args (m_temp.GetString(), _err_args);
	return *this;
}
CErr_Details& CErr_Details::operator << ( LPCTSTR _lp_sz_template) {
	m_temp = _lp_sz_template;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////

CErr_Details::operator LPCTSTR (void) const { return this->m_desc.GetString(); }

/////////////////////////////////////////////////////////////////////////////

CErr_Pattern:: CErr_Pattern (void) : m_active(_tp::e_line) {}
CErr_Pattern::~CErr_Pattern (void) {}

/////////////////////////////////////////////////////////////////////////////

CAtlStringW CErr_Pattern::Get (const _tp _e_type) const {
	CString  cs_pat;
	switch (_e_type) {
	case _tp::e_box  :
		cs_pat = _T(
				"Error details:  "
				"\n Code\t= 0x%x"
				"\n Desc\t= %s  "
				"\n Module\t= %s  "
				"\n Source\t= %s  "
		); break;
	case _tp::e_line :
		cs_pat = _T(
				"Code=0x%x; desc=%s; module=%s; source=%s"
		); break;
	case _tp::e_state:
		cs_pat = _T(
				"Code=0x%x; desc=%s"
		); break;
	}
	return cs_pat;
}

/////////////////////////////////////////////////////////////////////////////

CErr_Pattern& CErr_Pattern::operator << (const _tp _e_type) {
	m_active = _e_type;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////

CErr_Pattern::operator const   _tp (void) const { return this->m_active; }
CErr_Pattern::operator CAtlStringW (void) const { return this->Get(this->m_active); }

/////////////////////////////////////////////////////////////////////////////

CErr_Fmt:: CErr_Fmt(void) : m_sep(_T("; ")) {}
CErr_Fmt::~CErr_Fmt(void) {}

/////////////////////////////////////////////////////////////////////////////

LPCTSTR   CErr_Fmt::Format (TErrorRef _err) {
	
	CString cs_desc = _err.State().Get();
	if (cs_desc.IsEmpty()) {
		if (_err.Code() != 0) {
			cs_desc = CErr_Details() << _err.Lang() << _err.Code();
		}
		else {
			cs_desc = CErr_Details() << _err.Lang() << _err.Result();
		}
	}
	CString cs_pat = m_pat;
	if (CErr_Pattern::e_line == m_pat && m_sep.IsEmpty() == false) 
		cs_pat.Replace(_T("; "), (LPCTSTR)m_sep);

	m_fmt.Format(
		cs_pat.GetString(),
		_err.Result(),
		cs_desc.IsEmpty() == false ? (LPCTSTR)cs_desc : CErr_Msg().Na(),
		::lstrlenW(_err.Method())  ?    _err.Method() : CErr_Msg().Na(),
		::lstrlenW(_err.Class ())  ?    _err.Class () : CErr_Msg().Na()
	);

	return (LPCTSTR) m_fmt;
}

LPCTSTR   CErr_Fmt::Format (TErr_State& _state) {

	CString cs_desc = _state.Get();
	CString cs_pat  = m_pat;
	if (CErr_Pattern::e_line == m_pat && m_sep.IsEmpty() == false) 
		cs_pat.Replace(_T("; "), (LPCTSTR)m_sep);

	m_fmt.Format(
		cs_pat.GetString(),
		(HRESULT)_state,
		cs_desc.IsEmpty() == false ? (LPCTSTR)cs_desc : CErr_Msg().Na()
	);

	return (LPCTSTR) m_fmt;
}

/////////////////////////////////////////////////////////////////////////////

CErr_Fmt& CErr_Fmt::operator << (const CErr_Pattern& _pat) {
	this->m_pat = _pat; return *this;
}
CErr_Fmt& CErr_Fmt::operator << (LPCTSTR _lp_sz_sep   ) { this->m_sep = _lp_sz_sep; return *this; }
CErr_Fmt& CErr_Fmt::operator << (TErrorRef  _error_ref) { this->Format(_error_ref); return *this; }
CErr_Fmt& CErr_Fmt::operator << (TErr_State& _state   ) { this->Format(_state)    ; return *this; }

/////////////////////////////////////////////////////////////////////////////

CErr_Fmt::operator LPCTSTR (void) const { return m_fmt.GetString(); }

/////////////////////////////////////////////////////////////////////////////

CErr_Msg:: CErr_Msg(void) {}
CErr_Msg::~CErr_Msg(void) {}

/////////////////////////////////////////////////////////////////////////////

LPCTSTR     CErr_Msg::Na (void) const { static LPCTSTR lp_sz_na = _T("#n/a"); return lp_sz_na; }
LPCTSTR     CErr_Msg::NotFound(void) const {
	static LPCTSTR pszNotFound = _T("Error details not found;");
	return pszNotFound;
}