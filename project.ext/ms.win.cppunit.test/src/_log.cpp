/*
	Created by Tech_dog (ebontrop@gmail.com) on 1-Apr-2024 at 08:24:31.4391778, UTC+7, Novosibirsk, Monday;
	This is Ebo Pak UIX libs unit test logger interface implementation file.
*/
#include "_log.h"

using namespace ebo::boo::test;

/////////////////////////////////////////////////////////////////////////////

CCache:: CCache (void) : m_prefix(_T("\t")), m_suffix(_T("\n")) {}
CCache::~CCache (void) {}

/////////////////////////////////////////////////////////////////////////////

void CCache::Clear(void) { this->m_strings.clear(); }

const
TCached& CCache::Get (void) const { return this->m_strings; }
TCached& CCache::Get (void)       { return this->m_strings; }

_pc_sz   CCache::Prefix (void) const   { return this->m_prefix.GetString(); }
void     CCache::Prefix (_pc_sz _prfx) { this->m_prefix = _prfx; }
_pc_sz   CCache::Suffix (void) const   { return this->m_suffix.GetString(); }
void     CCache::Suffix (_pc_sz _sufx) { this->m_suffix = _sufx; }

void     CCache::Output (void) const {

	if (this->m_strings.empty())
		return ;

	CString cs_out;
	const bool b_prefix = !this->m_prefix.IsEmpty();
	const bool b_suffix = !this->m_suffix.IsEmpty(); if (b_suffix) cs_out += this->Suffix(); // for starting new line;

	CString cs_fmt;

	for (size_t i_ = 0; i_ < this->m_strings.size(); i_++) {
		const CString& cs_str = this->m_strings.at(i_);

		cs_fmt.Format(_T("%s%s%s"), (b_prefix ? this->Prefix() : _T("")), cs_str.GetString(), (b_suffix ? this->Suffix() : _T("")));
		cs_out += cs_fmt;
	}

	_out() << cs_out;
}

/////////////////////////////////////////////////////////////////////////////

CCache&  CCache::operator +=(_pc_sz _p_out) { this->Get().push_back(CString(_p_out)); return *this; };

CCache&  CCache::operator +=(const CString& _str)   { this->Get().push_back(_str); return *this; }
CCache&  CCache::operator +=(const TParts& _parts)  {
	// https://en.cppreference.com/w/cpp/container/vector/insert ;
	this->Get().insert(this->Get().end(), _parts.begin(), _parts.end());  // people saying there is no exception for catching, but maybe it's just words;
	return *this;
}

CCache&  CCache::operator <<(_pc_sz _lp_sz_prefix) { this->Prefix(_lp_sz_prefix); return *this; }
CCache&  CCache::operator >>(_pc_sz _lp_sz_suffix) { this->Suffix(_lp_sz_suffix); return *this; }
const
CCache&  CCache::operator ()(void) const { this->Output(); return *this; }

/////////////////////////////////////////////////////////////////////////////
const
CCache&  CLogger::Cached  (void) const { return this->m_cache; }
CCache&  CLogger::Cached  (void)       { return this->m_cache; }

_pc_sz   CLogger::Pattern (void) const { return (_pc_sz)this->m_pattern; }
bool     CLogger::Pattern (_pc_sz _lp_sz_pat) {
	_lp_sz_pat;
	bool b_is_set = false;

	if (0 == _lp_sz_pat || 0 == ::_tcslen(_lp_sz_pat))
		return b_is_set;

	this->m_pattern = _lp_sz_pat;
	this->m_pattern.Trim();

	return (b_is_set = !this->m_pattern.IsEmpty());
}

/////////////////////////////////////////////////////////////////////////////

CLog_Opts:: CLog_Opts (void) : m_accepted(_accepted::e_none) {}
CLog_Opts::~CLog_Opts (void) {}

/////////////////////////////////////////////////////////////////////////////

bool CLog_Opts::Get (_accepted _opt) const { return !!(_opt & this->m_accepted); }
void CLog_Opts::Set (_accepted _opt, bool _b_set) {
	if ( _b_set) this->m_accepted |= _opt;
	if (!_b_set) this->m_accepted &=~_opt; // https://stackoverflow.com/questions/3920307/how-can-i-remove-a-flag-in-c ;)
}

/////////////////////////////////////////////////////////////////////////////

CLog_Opts& CLog_Opts::operator +=(const CLog_Opts::_accepted _opt) { this->Set(_opt, true ); return *this; }
CLog_Opts& CLog_Opts::operator -=(const CLog_Opts::_accepted _opt) { this->Set(_opt, false); return *this; }

/////////////////////////////////////////////////////////////////////////////

void CLogger::Out (const CString& _str) const {
	this->Out((_pc_sz)_str.GetString());
}

void CLogger::Out (_pc_sz _lp_sz_text) const {
	_lp_sz_text;

	using ms_logger = Microsoft::VisualStudio::CppUnitTestFramework::Logger;

	const bool b_is_pat = this->m_pattern.IsEmpty() == false;
	if (b_is_pat) {

		CString cs_out;
		cs_out.Format(this->Pattern(), _lp_sz_text);
		
		ms_logger::WriteMessage(cs_out.GetString());
	}
	else {
		if (this->Opts().Get(CLog_Opts::e_new_line)) {
			CString cs_out(_T("\n")); cs_out += _lp_sz_text;
			ms_logger::WriteMessage((_pc_sz)cs_out);
		}
		else
		ms_logger::WriteMessage(_lp_sz_text);
	}
}
const
CLog_Opts& CLogger::Opts(void) const { return this->m_opts; }
CLog_Opts& CLogger::Opts(void)       { return this->m_opts; }

/////////////////////////////////////////////////////////////////////////////

const CLogger& CLogger::operator << (const CString& _str) const { this->Out(_str); return *this; }
const CLogger& CLogger::operator << (_pc_sz  _lp_sz_text) const { this->Out(_lp_sz_text); return *this; }

CLogger& CLogger::operator +=(const CLog_Opts::_accepted _opt)  { this->Opts() += _opt; return *this; }
CLogger& CLogger::operator -=(const CLog_Opts::_accepted _opt)  { this->Opts() -= _opt; return *this; }

CLogger& CLogger::operator +=(const CString& cs_out) { this->Cached() += cs_out; return *this; }
CLogger& CLogger::operator +=(_pc_sz _p_sz_out) { this->Cached() += _p_sz_out; return *this; }

/////////////////////////////////////////////////////////////////////////////

CLogger&  CLogger::operator >> (_pc_sz _lp_sz_pat) { this->Pattern(_lp_sz_pat); return *this; }

CLogger::operator CCache& (void) { return this->Cached(); }
const
CLogger& CLogger::operator ()(void) const { this->Cached()(); return *this; } 

/////////////////////////////////////////////////////////////////////////////

//namespace ebo { namespace boo { namespace test {

	/*const*/
	TLogger& _out(void) {
		static
		TLogger logger_;
		return  logger_;
	}

//}}}