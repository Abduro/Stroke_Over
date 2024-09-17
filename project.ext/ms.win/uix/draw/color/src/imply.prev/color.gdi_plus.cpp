/*
	Created by Tech_dog (ebontrop@gmail.com) on 4-Nov-2007 at 9:57:**pm, GMT+3, Rostov-on-Don, Sunday;
	This is Sfx package owner-drawn colour related classe(s) declaration.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 2-May-2020 at 2:08:25p, UTC+7, Novosibirsk, Saturday;
	Adopted to Ebo Pack color project on 12-Oct-2021 at 1:30:16.2788651 am, UTC+7, Novosibirsk, Tuesday;
*/
#include "color.gdi_plus.h"

using namespace ex_ui::color;

/////////////////////////////////////////////////////////////////////////////

TDbgPrint:: CDebugPrint (void) {}
TDbgPrint:: CDebugPrint (const TDbgPrint& _ref) : TDbgPrint() { *this =  _ref; }
TDbgPrint::~CDebugPrint (void) {}

/////////////////////////////////////////////////////////////////////////////

CString    TDbgPrint::Print (const COLORREF _clr) const {
	static
	LPCTSTR lp_sz_pat = _T("argb={%u|%u|%u|%u}");
	CString cs_clr;
	if (CLR_NONE == _clr) cs_clr = _T("CLR_NONE");
	else cs_clr.Format(lp_sz_pat, GetAValue(_clr), GetRValue(_clr), GetGValue(_clr), GetBValue(_clr));
	return cs_clr;
}

/////////////////////////////////////////////////////////////////////////////

TDbgPrint&  TDbgPrint::operator = (const TDbgPrint& _ref) { _ref; return *this; }
CString     TDbgPrint::operator <<(const COLORREF _clr) const { return this->Print(_clr); }

/////////////////////////////////////////////////////////////////////////////

CColour:: CColour(void) : m_clr(0, 0, 0, 0) { }
CColour:: CColour(const CColour& _clr ) : CColour() { *this = _clr; }
CColour:: CColour(const COLORREF  clr , const BYTE alpha): m_clr(alpha, GetRValue(clr), GetGValue(clr), GetBValue(clr)) { }
CColour:: CColour(const TColor&  _clr ) : m_clr(_clr) {}
CColour::~CColour(void) { }

/////////////////////////////////////////////////////////////////////////////

BYTE     CColour::Alpha  (void) const { return m_clr.GetA(); }
VOID     CColour::Alpha  (const BYTE _alpha) {
	const BYTE r_ = m_clr.GetR();
	const BYTE g_ = m_clr.GetG();
	const BYTE b_ = m_clr.GetB();
	m_clr = TColor(_alpha, r_, g_, b_);
}
VOID     CColour::Create (const COLORREF clr, const BYTE _alpha) {
	m_clr  = Gdiplus::Color::MakeARGB(_alpha, (BYTE)GetRValue(clr), (BYTE)GetGValue(clr), (BYTE)GetBValue(clr));
#if defined(_DEBUG)
	CStringW cs_clr = TDbgPrint().Print(m_clr.ToCOLORREF());
#endif
}
const
TColor&  CColour::Data   (void) const { return m_clr; }
VOID     CColour::Empty  (void)       { m_clr = TColor(0,0,0,0); }
bool     CColour::Is     (void) const {
	return (m_clr.GetA() != 0 && m_clr.ToCOLORREF() != CLR_NONE);
}
#if defined(_DEBUG)
CStringW CColour::Print  (void) const {
	CStringW cs_print; cs_print.Format(_T("Colour: a=%u; rgb=%u|%u|%u;"), m_clr.GetA(), m_clr.GetR(), m_clr.GetG(), m_clr.GetB()); return cs_print; }
#endif
COLORREF CColour::Rgb    (void) const { return m_clr.ToCOLORREF(); }
VOID     CColour::Rgb    (const COLORREF _clr) {
	_clr;
	const BYTE alpha_ = m_clr.GetA();
	this->Create(_clr, alpha_);
}

/////////////////////////////////////////////////////////////////////////////

CColour::operator const TColor& (void)const { return  m_clr;  }
CColour::operator const TColor* (void)const { return &m_clr;  }
CColour::operator const COLORREF(void)const { return  m_clr.ToCOLORREF(); }

/////////////////////////////////////////////////////////////////////////////

CColour& CColour::operator = (const CColour& _clr) { m_clr = _clr.m_clr; return *this; }

CColour& CColour::operator = (const TColor&  _clr) { m_clr = _clr; return *this; }

CColour& CColour::operator <<(const BYTE _alpha) { this->Alpha(_alpha); return *this; }

CColour& CColour::operator <<(const COLORREF _clr){ this->Rgb(_clr); return *this; }

/////////////////////////////////////////////////////////////////////////////

bool CColour::operator == (const CColour& _clr) const { return (this->Rgb() == _clr.Rgb()); }
bool CColour::operator != (const CColour& _clr) const { return (this->Rgb() != _clr.Rgb()); }
bool CColour::operator == (COLORREF _clr) const { return (this->Rgb() == _clr); }
bool CColour::operator != (COLORREF _clr) const { return (this->Rgb() != _clr); }

/////////////////////////////////////////////////////////////////////////////

CColour_Ex:: CColour_Ex(void) : TBase() {}
CColour_Ex:: CColour_Ex(const CColour& _clr) : TBase() { *this << _clr; }
CColour_Ex:: CColour_Ex(const CColour_Ex& _ref) : TBase() { *this = _ref; }
CColour_Ex:: CColour_Ex(const COLORREF clr, const BYTE alpha) : TBase(clr, alpha) {}
CColour_Ex::~CColour_Ex(void) {}

/////////////////////////////////////////////////////////////////////////////

HRESULT  CColour_Ex::Darken (const __int8 btValue) {
	int a__ = TBase::m_clr.GetA();
	int r__ = TBase::m_clr.GetR() - btValue; if (r__ < 0) r__ = 0;
	int g__ = TBase::m_clr.GetG() - btValue; if (g__ < 0) g__ = 0;
	int b__ = TBase::m_clr.GetB() - btValue; if (b__ < 0) b__ = 0;
	TBase::m_clr = Gdiplus::Color::MakeARGB((BYTE)a__, (BYTE)r__, (BYTE)g__, (BYTE)b__);
	return S_OK;
}
HRESULT  CColour_Ex::Lighten(const __int8 btValue) {
	int a__ = TBase::m_clr.GetA();
	int r__ = TBase::m_clr.GetR() + btValue; if (r__ > 255) r__ = 255;
	int g__ = TBase::m_clr.GetG() + btValue; if (g__ > 255) g__ = 255;
	int b__ = TBase::m_clr.GetB() + btValue; if (b__ > 255) b__ = 255;
	TBase::m_clr = Gdiplus::Color::MakeARGB((BYTE)a__, (BYTE)r__, (BYTE)g__, (BYTE)b__);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////

CColour_Ex& CColour_Ex::operator+= (const __int8 btValue) { this->Lighten(btValue); return *this; }
CColour_Ex& CColour_Ex::operator-= (const __int8 btValue) { this->Darken (btValue); return *this; }
CColour_Ex& CColour_Ex::operator = (const CColour& _clr ) {
	(CColour&)*this = _clr; return *this;
}
CColour_Ex& CColour_Ex::operator = (const CColour_Ex& _clr) {
	(CColour&)*this = (CColour&)_clr;
	return *this;
}