/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Sep-2020 at 1:14:29p, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack UIX draw library gdi++ common definition implementation file;
	-----------------------------------------------------------------------------
	Adopted to Geometry Curve project on 17-Feb-2024 at 10:57:27.7589244, UTC+7, Novosibirsk, Saturday;
*/
#include "gdi_plus.defs.h"

using namespace ex_ui::draw::gdi_pls;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace gdi_pls { namespace _impl {

	using err_status = Gdiplus::Status;

	typedef struct  {
		uint32_t   n_el_id ;   // this is Gdiplus::Status enum element value; one byte is enough for that but taking into account the performance, 4 bytes are better;
		err_code   h_result;   // this is error handling result that can be associated with particular gdi+ status enum element;
		_pc_sz     p_desc  ;   // a pointer to description string;
		bool       b_is_sys;   // this is the flag that can indicate that get last error may be used for getting error details from win api;
	}
	raw_stat_data ;
	raw_stat_data raw_stats[] = { // the status description is little bit changed: the past time of verbs is replaced by base/current one or the desc is made shorter;
		{ e_status::e_no_err    , TErrCodes::no_error            , _T("No error;"), false  },
		{ e_status::e_generic   , __e_fail                       , _T("There is an error on the method call;"), true  },
		{ e_status::e_inv_arg   , __e_inv_arg                    , _T("Invalid arg;"), true  },
		{ e_status::e_no_memory , __e_no_memory                  , _T("Out of memory;"), true  },
		{ e_status::e_obj_busy  , TErrCodes::eObject::eBusy      , _T("One of the arguments is already in use in another thread;"), false  },
		{ e_status::e_out_buff  , TErrCodes::eData::eBuffer      , _T("The buffer is not large enough;"), true  },
		{ e_status::e_not_impl  , __e_not_impl                   , _T("Not implrmrnted;"), true  },
		{ e_status::e_win_err   , __e_fail                       , _T("Win api error occurred;"), true  },
		{ e_status::e_inv_state , TErrCodes::eExecute::eState    , _T("The object is in an invalid state;"), true  },
		{ e_status::e_aborted   , __e_aborted                    , _T("The method is aborted;"), true  },
		{ e_status::e_no_file   , TErrCodes::ePath::eNoFile      , _T("Specified image file or metafile cannot be found;"), false  },
		{ e_status::e_overflow  , TErrCodes::eExecute::eOverflow , _T("Arithmetic operation produced a numeric overflow;"), false  },
		{ e_status::e_no_access , TErrCodes::eAccess::eDenied    , _T("Write operation is not allowed on the specified file;"), true  },
		{ e_status::e_unk_image , TErrCodes::eData::eUnsupport   , _T("Specified image file format is not known;"), false  },
		{ e_status::e_no_family , TErrCodes::eFont::eNoFamily    , _T("Specified font family cannot be found;"), false  },
		{ e_status::e_no_style  , TErrCodes::eFont::eNoStyle     , _T("Specified style is not available;"), false  },
		{ e_status::e_not_ttf   , TErrCodes::eFont::eTrueType    , _T("It is not a TrueType font;"), false  },
		{ e_status::e_unsup_ver , TErrCodes::eResource::eVersion , _T("Unsupported version;"), true  },
		{ e_status::e_not_init  , TErrCodes::eObject::eInited    , _T("Not initialized;"), true  },
		{ e_status::e_no_prop   , TErrCodes::eObject::eProperty  , _T("Specified property does not exist in the image;"), false  },
		{ e_status::e_unsup_prop, TErrCodes::eObject::eProperty  , _T("Specified property is not supported;"), false  },
		{ e_status::e_inited    , TErrCodes::eObject::eInited    , _T("The object is already initialized;"), true  },
		{ e_status::e_uninited  , __e_not_inited                 , _T("The object is uninitialized;"), true  },
	};

	class CExclusion_Def : public ex_ui::draw::defs::IExclusion {
	private:
		RECT m_empty;
	public:
		 CExclusion_Def (void) : m_empty{0, 0, 0, 0} {}
		~CExclusion_Def (void) {}

	public: // IExclusionvirtual
		RECT&     Get  (const ULONG _ndx) override { _ndx; return m_empty; }
	};
}}}}

using namespace ex_ui::draw::gdi_pls::_impl;

/////////////////////////////////////////////////////////////////////////////

CErr_Assoc:: CErr_Assoc (const t_stat _status, const err_code _h_result, const bool b_is_sys) : m_status(_status), m_b_sys(b_is_sys), m_err_code(_h_result) {}
CErr_Assoc:: CErr_Assoc (const CErr_Assoc& _src) : CErr_Assoc() { *this = _src; }
CErr_Assoc::~CErr_Assoc (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code   CErr_Assoc::Code (void) const { return this->m_err_code; }
const bool CErr_Assoc::Code (const err_code _code) { const bool b_changed = _code != this->Code(); if (b_changed) this->m_err_code = _code; return b_changed; }

bool CErr_Assoc::Is_sys (void) const { return this->m_b_sys; }
void CErr_Assoc::Is_sys (const bool _is_sys) { this->m_b_sys = _is_sys; }

t_stat CErr_Assoc::Status (void) const { return this->m_status; }
bool   CErr_Assoc::Status (const t_stat _status) { const bool b_changed = _status != this->Status(); if (b_changed) this->m_status = _status; return b_changed; }

/////////////////////////////////////////////////////////////////////////////

bool   CErr_Assoc::Set (const t_stat _status, const err_code _code, const bool b_is_sys) {
	_status; _code; b_is_sys;
	bool b_changed = this->Is_sys() != b_is_sys;

	b_changed |= this->Code(_code);
	b_changed |= this->Status(_status);

	this->Is_sys(b_is_sys);

	return b_changed;
}

#if defined(_DEBUG)
CString CErr_Assoc::Print (const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s]>>{stat=%u;hres=0x%08x;is_sys=%s}");
	static _pc_sz pc_sz_pat_r = _T("stat=%u;hres=0x%08x;is_sys=%s");

	CString cs_out;

	if (e_print::e_all == e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__CLASS__, this->Status(), this->Code(), TStringEx().Bool(this->Is_sys())); }
	if (e_print::e_req == e_opt) { cs_out.Format(pc_sz_pat_r, this->Status(), this->Code(), TStringEx().Bool(this->Is_sys())); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("[%s].%s(#unsupp_arg);"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CErr_Assoc& CErr_Assoc::operator = (const CErr_Assoc& _src) { *this << _src.Code() << _src.Is_sys() << _src.Status(); return *this; }
CErr_Assoc& CErr_Assoc::operator <<(const err_code _code) { this->Code(_code); return *this; }
CErr_Assoc& CErr_Assoc::operator <<(const bool _is_sys) { this->Is_sys(_is_sys); return *this; }
CErr_Assoc& CErr_Assoc::operator <<(const t_stat _status) { this->Status(_status); return *this; }

/////////////////////////////////////////////////////////////////////////////

CErr_Adapter:: CErr_Adapter (const e_status _st_val, _pc_sz _p_desc) : m_status(_st_val), m_desc(_p_desc) {}
CErr_Adapter:: CErr_Adapter (const CErr_Adapter& _src) : CErr_Adapter() { *this = _src; }
CErr_Adapter::~CErr_Adapter (void) {}

/////////////////////////////////////////////////////////////////////////////

_pc_sz CErr_Adapter::Desc (void) const { return this->m_desc.GetString(); }
bool   CErr_Adapter::Desc (_pc_sz _p_desc) {
	_p_desc;
	// https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/cstringt-class#compare ;
	const bool b_changed = (nullptr != _p_desc && !!::_tcslen(_p_desc) && !!this->m_desc.Compare(_p_desc));
	if (b_changed)
		this->m_desc = _p_desc;

	return b_changed;
}

e_status CErr_Adapter::Status (void) const { return this->m_status; }
bool     CErr_Adapter::Status (const e_status _status) {
	_status;

	const bool b_changed = this->Status() != _status;
	if (b_changed)
		this->m_status = _status;

	return b_changed;
}

const
CErr_Assoc&  CErr_Adapter::Sys_err (void) const { return this->m_assoc; }
CErr_Assoc&  CErr_Adapter::Sys_err (void)       { return this->m_assoc; }

#if defined(_DEBUG)
CString   CErr_Adapter::Print (const e_print e_opt) const {
	e_opt;

	static _pc_sz pc_sz_pat_a = _T("cls::[%s]>>{status=%u;desc='%s';assoc={sys_err=0x%08x;qry_info=%s}}");
	static _pc_sz pc_sz_pat_v = _T("status=%u;desc='%s'");

	CString cs_out;

	if (e_print::e_all == e_opt) {
		cs_out.Format(pc_sz_pat_a,(_pc_sz)__CLASS__, this->Status(), this->Desc(), this->Sys_err().Code(), TStringEx().Bool(this->Sys_err().Is_sys())); }
	if (e_print::e_val == e_opt) { cs_out.Format(pc_sz_pat_v, this->Status(), this->Desc()); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("[%s].%s(#unsupp_arg);"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CErr_Adapter& CErr_Adapter::operator = (const CErr_Adapter& _src) { *this << _src.Desc() << _src.Status() << _src.Sys_err(); return *this; }

CErr_Adapter& CErr_Adapter::operator <<(_pc_sz _p_desc) { this->Desc(_p_desc); return *this; }
CErr_Adapter& CErr_Adapter::operator <<(const e_status _status) { this->Status(_status); return *this; }

CErr_Adapter& CErr_Adapter::operator <<(const CErr_Assoc& _sys_err) { this->Sys_err() = _sys_err; return *this; }

/////////////////////////////////////////////////////////////////////////////

CErr_Adapt_enum:: CErr_Adapt_enum (const bool _b_auto) { if (_b_auto) this->Set(); }
CErr_Adapt_enum::~CErr_Adapt_enum (void) {}

/////////////////////////////////////////////////////////////////////////////

const TErrAdapt&  CErr_Adapt_enum::Get (const uint32_t _code) const {
	_code;
	TRawStatus::const_iterator it_found = this->Raw().find(_code);

	if (this->Raw().end() == it_found) {

		static TErrAssoc assoc(t_stat::NotImplemented, TErrCodes::eData::eNotFound, _T("#not_found"));
		static TErrAdapt fake_;

		fake_ << TStringEx().Format(_T("Fake status code<%d>"), _code) << e_status::e_not_impl << assoc;

		return fake_;
	}
	else
		return it_found->second;
};
const TRawStatus& CErr_Adapt_enum::Raw (void) const { return this->m_raw_stats; }

err_code CErr_Adapt_enum::Set (void) {

	err_code n_result = TErrCodes::no_error;
	try { // not sure that this try-catch block is necessary, but out of habit;
		if (this->m_raw_stats.empty() == false)
			this->m_raw_stats.clear();

		for (uint16_t i_ = 0; i_ < _countof(raw_stats); i_++)
		{
			const e_status t_id = (e_status)raw_stats[i_].n_el_id;
			// ToDo: the things remain to be the same, different types of gdi+ status enumeration must be re-viewed;
			TErrAdapt err_adopt(t_id, raw_stats[i_].p_desc); err_adopt.Sys_err() << (t_stat)t_id << raw_stats[i_].h_result << raw_stats[i_].b_is_sys;

			this->m_raw_stats.insert(
				::std::make_pair(
					raw_stats[i_].n_el_id,  err_adopt
				));
		}
	}
	catch(...) {
		n_result = __e_fail;
	}

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

CErr_Adapt_enum&  CErr_Adapt_enum::Ref (void) {
	static CErr_Adapt_enum sta_enum;
	return sta_enum;
}

/////////////////////////////////////////////////////////////////////////////