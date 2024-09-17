/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Sep-2020 at 1:14:29p, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack UIX draw library gdi++ common definition implementation file;
	-----------------------------------------------------------------------------
	Adopted to Geometry Curve project on 17-Feb-2024 at 10:57:27.7589244, UTC+7, Novosibirsk, Saturday;
*/
#include "gdi_plus.defs.h"

using namespace ex_ui::draw;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace _impl {

	HRESULT   GdiplusStatusToHresult(const Gdiplus::Status st__)
	{
		HRESULT hr__ = E_UNEXPECTED;
		switch (st__)
		{
		case Gdiplus::Ok                       : hr__ = S_OK;                                        break;
		case Gdiplus::GenericError             : hr__ = E_FAIL;                                      break;
		case Gdiplus::InvalidParameter         : hr__ = E_INVALIDARG;                                break;
		case Gdiplus::OutOfMemory              : hr__ = E_OUTOFMEMORY;                               break;
		case Gdiplus::ObjectBusy               : hr__ = HRESULT_FROM_WIN32(ERROR_BUSY);              break;
		case Gdiplus::InsufficientBuffer       : hr__ = DISP_E_BUFFERTOOSMALL;                       break;
		case Gdiplus::NotImplemented           : hr__ = E_NOTIMPL;                                   break;
		case Gdiplus::Win32Error               : hr__ = E_FAIL;                                      break;
		case Gdiplus::WrongState               : hr__ = HRESULT_FROM_WIN32(ERROR_INVALID_STATE);     break;
		case Gdiplus::Aborted                  : hr__ = E_ABORT;                                     break;
		case Gdiplus::FileNotFound             : hr__ = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);    break;
		case Gdiplus::ValueOverflow            : hr__ = DISP_E_OVERFLOW;                             break;
		case Gdiplus::AccessDenied             : hr__ = E_ACCESSDENIED;                              break;
		case Gdiplus::UnknownImageFormat       : hr__ = HRESULT_FROM_WIN32(ERROR_UNSUPPORTED_TYPE);  break;
		case Gdiplus::FontFamilyNotFound       : hr__ = DISP_E_UNKNOWNNAME;                          break;
		case Gdiplus::FontStyleNotFound        : hr__ = HRESULT_FROM_WIN32(ERROR_UNSUPPORTED_TYPE);  break;
		case Gdiplus::NotTrueTypeFont          : hr__ = DISP_E_TYPEMISMATCH;                         break;
		case Gdiplus::UnsupportedGdiplusVersion: hr__ = HRESULT_FROM_WIN32(ERROR_PRODUCT_VERSION);   break;
		case Gdiplus::GdiplusNotInitialized    : hr__ = OLE_E_BLANK;                                 break;
		case Gdiplus::PropertyNotFound         : hr__ = HRESULT_FROM_WIN32(ERROR_UNKNOWN_PROPERTY);  break;
		case Gdiplus::PropertyNotSupported     : hr__ = HRESULT_FROM_WIN32(ERROR_UNKNOWN_PROPERTY);  break;
		default:
		break;
		}
		return  hr__;
	}

	class CExclusion_Def : public ex_ui::draw::defs::IExclusion {
	private:
		RECT m_empty;
	public:
		 CExclusion_Def (void) : m_empty{0, 0, 0, 0} {}
		~CExclusion_Def (void) {}

	public: // IExclusionvirtual
		RECT&     Get  (const ULONG _ndx) override { _ndx; return m_empty; }
	};
}}}
using namespace ex_ui::draw::_impl;
/////////////////////////////////////////////////////////////////////////////

CErr_drw:: CErr_drw (void) : m_result(S_OK), m_status(TStatus::Ok) {}
CErr_drw:: CErr_drw (const CErr_drw& _ref) : CErr_drw() { *this = _ref; }
CErr_drw:: CErr_drw (const TStatus _sta) : CErr_drw() { *this << _sta; }
CErr_drw::~CErr_drw (void) {}

/////////////////////////////////////////////////////////////////////////////

HRESULT  CErr_drw::Get (void) const { return m_result; }
HRESULT  CErr_drw::Set (const TStatus _sta) { m_result = GdiplusStatusToHresult(_sta); m_status = _sta; return m_result; }

/////////////////////////////////////////////////////////////////////////////

CErr_drw::operator HRESULT (void) const { return m_result; }
CErr_drw::operator TStatus (void) const { return m_status; }

/////////////////////////////////////////////////////////////////////////////

CErr_drw&  CErr_drw::operator = (const CErr_drw& _ref) { this->m_status = _ref.m_status; this->m_result = _ref.m_result; return *this; }
CErr_drw&  CErr_drw::operator <<(const TStatus _sta) { this->Set(_sta); return *this; }

/////////////////////////////////////////////////////////////////////////////
defs::IExclusion&
defs::IRenderer_Base::Excluded(void) { static CExclusion_Def exc_def; return exc_def; }

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////