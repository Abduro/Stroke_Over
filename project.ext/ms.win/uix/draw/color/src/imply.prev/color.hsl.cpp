/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Sep-2018 at 5:34:48a, UTC+7, Novosibirsk, Wednesday;
	This is UIX shared draw library generic HSL/RGB (hue-saturation-lightness) conversion interface implementation file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack color project on 10-Oct-2021 at 5:30:40.0256825 am, UTC+7, Novosibirsk, Sunday;
*/
#include "color.hsl.h"

using namespace ex_ui::color;

#define _get_b(_rgb) GetBValue(_rgb)
#define _get_g(_rgb) GetGValue(_rgb)
#define _get_r(_rgb) GetRValue(_rgb)

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace color { namespace _impl {

	BYTE  C_hls_toRGB (float rm1, float rm2, float rh)
	{
		if      (rh > 360.0f) rh -= 360.0f;
		else if (rh <   0.0f) rh += 360.0f;

		if      (rh <  60.0f) rm1 = rm1 + (rm2 - rm1) * rh / 60.0f;
		else if (rh < 180.0f) rm1 = rm2;
		else if (rh < 240.0f) rm1 = rm1 + (rm2 - rm1) * (240.0f - rh) / 60.0f;

		return (BYTE)(rm1 * 255);
	}

	class C_hsl_comparator {
	private:
		COLORREF m_rgb;

	public:
		C_hsl_comparator(const COLORREF _rgb) : m_rgb(_rgb) {}

	public:
		FLOAT    _b(void)   const { return _get_b(m_rgb) / 255.0f; }
		FLOAT    _g(void)   const { return _get_g(m_rgb) / 255.0f; }
		FLOAT    _r(void)   const { return _get_r(m_rgb) / 255.0f; }

	public:
		FLOAT    _max(void) const { return (_g() > _b() ?
		                                   (_r() > _g() ? _r() : _g()) :
		                                   (_r() > _b() ? _r() : _b()) ); }
		FLOAT    _min(void) const { return (_g() < _b() ?
		                                   (_r() < _g() ? _r() : _g()) :
		                                   (_r() < _b() ? _r() : _b()) ); }
	};

}}}
using namespace ex_ui::color::_impl;
/////////////////////////////////////////////////////////////////////////////

C_hls:: C_hls (void) : m_hls(0) {}
C_hls:: C_hls (const C_hls& _ref) : C_hls() { *this = _ref; }
C_hls:: C_hls (const BYTE _h, const BYTE _l, const BYTE _s) : C_hls () { this->ToHLS(_h, _l, _s); }
C_hls:: C_hls (const COLORREF _rgb) : C_hls() { *this << _rgb; }
C_hls::~C_hls (void) {}

/////////////////////////////////////////////////////////////////////////////

BYTE     C_hls::Get_H(void) const { return ((BYTE)(m_hls)); }
BYTE     C_hls::Get_L(void) const { return ((BYTE)(((WORD)(m_hls)) >> 8)); }
BYTE     C_hls::Get_S(void) const { return ((BYTE)((m_hls)>>16)); }
const
bool     C_hls::Is   (void) const { return (0 != this->m_hls); }

HLSCOLOR C_hls::ToHLS (const BYTE _h, const BYTE _l, const BYTE _s) {
	return (m_hls = (DWORD)(((BYTE)(_h)|((WORD)((BYTE)(_l))<<8))|(((DWORD)(BYTE)(_s))<<16)));
}

HLSCOLOR C_hls::ToHLS (COLORREF _rgb) {

	unsigned char minval = min(GetRValue(_rgb), min(GetGValue(_rgb), GetBValue(_rgb)));
	unsigned char maxval = max(GetRValue(_rgb), max(GetGValue(_rgb), GetBValue(_rgb)));

	float mdiff  = float(maxval) - float(minval);
	float msum   = float(maxval) + float(minval);

	float l__ = msum / 510.0f;
	float s__ = 0.0f;
	float h__ = 0.0f;

	if ( maxval != minval )
	{
		float rnorm = (maxval - GetRValue(_rgb)) / mdiff;
		float gnorm = (maxval - GetGValue(_rgb)) / mdiff;
		float bnorm = (maxval - GetBValue(_rgb)) / mdiff;

		s__ = (l__ <= 0.5f) ? (mdiff / msum) : (mdiff / (510.0f - msum));
		if (GetRValue(_rgb) == maxval) h__ = 60.0f * (6.0f + bnorm - gnorm);
		if (GetGValue(_rgb) == maxval) h__ = 60.0f * (2.0f + rnorm - bnorm);
		if (GetBValue(_rgb) == maxval) h__ = 60.0f * (4.0f + gnorm - rnorm);
		if (h__ > 360.0f) h__ -= 360.0f;
	}
	return this->ToHLS (BYTE((h__ * 255.0f) / 360.0f), BYTE(l__ * 255.0f), BYTE(s__ * 255.0f));
}

HLSCOLOR C_hls::ToHLS(const COLORREF _rgb, __int8 percent_L, __int8 percent_S) {
	_rgb; percent_L; percent_S;

	this->ToHLS (_rgb);

	BYTE h__  = this->Get_H();
	BYTE l__  = this->Get_L();
	BYTE s__  = this->Get_S();

	if ( percent_L > 0 ) {
		l__ = BYTE(l__ + ((255 - l__) * percent_L) / 100);
	}
	else if ( percent_L < 0 ) {
		l__ = BYTE((l__ * (100 + percent_L)) / 100);
	}
	if ( percent_S > 0 ) {
		s__ = BYTE(s__ + ((255 - s__) * percent_S) / 100);
	}
	else if ( percent_S < 0 ) {
		s__ = BYTE((s__ * (100 + percent_S)) / 100);
	}
	m_hls = ToHLS(h__, l__, s__);
	return m_hls;
}

COLORREF C_hls::ToRGB(void) const {

	if (this->Is() == false)
		return (CLR_NONE);

	BYTE h__ = this->Get_H();
	BYTE l__ = this->Get_L();
	BYTE s__ = this->Get_S();

	float __h = ((int)h__ * 360) / 255.0f;
	float __l = l__ / 255.0f;
	float __s = s__ / 255.0f;

	if ( __s < 0.0001f ) {
		return RGB (l__, l__, l__);
	}
	float rm1 = 0.0f;
	float rm2 = 0.0f;

	if ( __l <= 0.5f ) rm2 = __l + __l * __s;
	else               rm2 = __l + __s - __l * __s;
	rm1 = 2.0f * __l - rm2;

	BYTE r__ = C_hls_toRGB (rm1, rm2, __h + 120.0f);
	BYTE g__ = C_hls_toRGB (rm1, rm2, __h);
	BYTE b__ = C_hls_toRGB (rm1, rm2, __h - 120.0f);

	return RGB(r__, g__, b__);
}

/////////////////////////////////////////////////////////////////////////////

C_hls&   C_hls::operator = (const C_hls& _ref) { *this << _ref.ToRGB(); return *this; }
C_hls&   C_hls::operator <<(const COLORREF _rgb) { this->ToHLS(_rgb); return *this; }

/////////////////////////////////////////////////////////////////////////////

C_hls::operator bool     (void) const { return (this->m_hls != 0 && CLR_NONE != this->ToRGB()); }
C_hls::operator COLORREF (void) const { return  this->ToRGB(); }

/////////////////////////////////////////////////////////////////////////////

C_hsl:: C_hsl (void) : m_h(0.0), m_l(0.0), m_s(0.0) {}
C_hsl:: C_hsl (const C_hsl& _ref) : C_hsl() { *this = _ref; }
C_hsl:: C_hsl (const FLOAT _h, const FLOAT _l, const FLOAT _s) : m_h(_h), m_l(_l), m_s(_s) {}
C_hsl:: C_hsl (const COLORREF _rgb) : C_hsl() { *this << _rgb; }
C_hsl::~C_hsl (void) {}

/////////////////////////////////////////////////////////////////////////////

FLOAT      C_hsl::_h(void) const      { return m_h; }
HRESULT    C_hsl::_h(const FLOAT  _v) { if (C_hsl::H_is_valid(_v) == false) return E_INVALIDARG; m_h = _v; return S_OK; }
FLOAT      C_hsl::_l(void) const      { return m_l; }
HRESULT    C_hsl::_l(const FLOAT  _v) { if (C_hsl::L_is_valid(_v) == false) return E_INVALIDARG; m_l = _v; return S_OK; }
FLOAT      C_hsl::_s(void) const      { return m_s; }
HRESULT    C_hsl::_s(const FLOAT  _v) { if (C_hsl::S_is_valid(_v) == false) return E_INVALIDARG; m_s = _v; return S_OK; }

/////////////////////////////////////////////////////////////////////////////

void       C_hsl::Clear  (void)       { m_h = m_l = m_s = 0.0; }
bool       C_hsl::IsValid(void) const { return ( C_hsl::H_is_valid(m_h) && C_hsl::L_is_valid(m_l) && C_hsl::S_is_valid(m_s)); }
COLORREF   C_hsl::To_rgb (void) const {

	if (this->IsValid() == false)
		return CLR_NONE;

	const FLOAT  d_q =(m_l <  0.5f ? m_l * (1.0f + m_s) : m_l + m_s - (m_l * m_s));
	const FLOAT  d_p = m_l *  2.0f - d_q;
	const FLOAT  d_h = m_h / 360.0f;

	FLOAT d_t[] = {
		d_h + 1.0f / 3.0f, d_h, d_h - 1.0f / 3.0f // r, g, b;
	};

	for (INT i_ = 0; i_ < _countof(d_t); i_++) {

		if (0 > d_t[i_]) d_t[i_] += 1.0f;
		else if (1.0 < d_t[i_]) d_t[i_] -= 1.0f;

		if (1.0f / 6.0f > d_t[i_]) d_t[i_] = d_p + ((d_q - d_p) * d_t[i_] * 6.0f);
		else if (  0.5f > d_t[i_]) d_t[i_] = d_q;
		else if (  2.0f / 3.0f > d_t[i_]) d_t[i_] = d_p + (d_q - d_p) * (4.0f - 6.0f * d_t[i_]);
		else      d_t[i_] = d_p;
	}

	return RGB(
		static_cast<int>(d_t[0] * 255.0 + 0.5),
		static_cast<int>(d_t[1] * 255.0 + 0.5),
		static_cast<int>(d_t[2] * 255.0 + 0.5)
	);
}

/////////////////////////////////////////////////////////////////////////////

C_hsl::operator const COLORREF(void) const { return this->To_rgb(); }

/////////////////////////////////////////////////////////////////////////////

C_hsl& C_hsl::operator = (const C_hsl& _ref) { *this << _ref.To_rgb(); return *this; }

C_hsl& C_hsl::operator <<(const COLORREF _rgb) {

	C_hsl_comparator comp_(_rgb);
	const FLOAT d_max = comp_._max();
	const FLOAT d_min = comp_._min();

	this->m_l = (d_min + d_max) / 2.0f;
	if (d_max == d_min) // grayscale or in other words, achromatic case; it is assumed that saturation is already 0.0;
		return *this;

	const FLOAT  d_chr  = (d_max - d_min); // chroma value;

	if (m_l <= 0.5f) m_s = (d_chr) / 2.0f / m_l;
	else             m_s = (d_chr) /(2.0f - 2.0f * m_l);

	if (d_max == comp_._r()) {
		m_h = 60.0f * (comp_._g() - comp_._b()) / (d_chr);
		if (m_h < 0.0f)
			m_h += 360.0f;
	}
	else if (d_max == comp_._g()) m_h = 120.0f + 60.0f * (comp_._b() - comp_._r()) / (d_chr);
	else                          m_h = 240.0f + 60.0f * (comp_._r() - comp_._g()) / (d_chr);

	return *this;
}

/////////////////////////////////////////////////////////////////////////////

bool C_hsl::H_is_valid(const FLOAT _val) { return (0.0f <= _val && 360.0f >  _val); }
bool C_hsl::L_is_valid(const FLOAT _val) { return (0.0f <= _val &&   1.0f >= _val); }
bool C_hsl::S_is_valid(const FLOAT _val) { return (0.0f <= _val &&   1.0f >= _val); }

/////////////////////////////////////////////////////////////////////////////

C_hsl_clr:: C_hsl_clr (void) : m_rgb(CLR_NONE), m_hue(0), m_chr(0), m_lgt(0) {}
C_hsl_clr:: C_hsl_clr (const C_hsl_clr& _ref) : C_hsl_clr() { *this = _ref; }
C_hsl_clr::~C_hsl_clr (void) {}

/////////////////////////////////////////////////////////////////////////////

LPCTSTR     C_hsl_clr::Cga(void) const       { return m_cga.GetString(); }
VOID        C_hsl_clr::Cga(LPCTSTR _v)       { m_cga = _v;   }
UCHAR       C_hsl_clr::Chrome(void) const    { return m_chr; }
HRESULT     C_hsl_clr::Chrome(const UCHAR _v){ if (_v > 100) return E_INVALIDARG; m_chr = _v; return S_OK; }
USHORT      C_hsl_clr::Hue(void) const       { return m_hue; }
HRESULT     C_hsl_clr::Hue(const USHORT   _v){ if (_v > 360) return E_INVALIDARG; m_hue = _v; return S_OK; }
UCHAR       C_hsl_clr::Light(void) const     { return m_lgt; }
HRESULT     C_hsl_clr::Light(const UCHAR  _v){ if (_v > 100) return E_INVALIDARG; m_lgt = _v; return S_OK; }
COLORREF    C_hsl_clr::Rgb(void) const       { return m_rgb; }
HRESULT     C_hsl_clr::Rgb(const COLORREF _v){ if (CLR_NONE == _v) return E_INVALIDARG; m_rgb = _v; return S_OK; }
LPCTSTR     C_hsl_clr::Web(void) const       { return m_web.GetString(); }
VOID        C_hsl_clr::Web(LPCTSTR _v)       { m_web = _v;   }

/////////////////////////////////////////////////////////////////////////////

C_hsl_clr&  C_hsl_clr::operator = (const C_hsl_clr& _ref) {
	this->m_cga = _ref.m_cga;
	this->m_chr = _ref.m_chr;
	this->m_hue = _ref.m_hue;
	this->m_lgt = _ref.m_lgt;
	this->m_rgb = _ref.m_rgb;
	this->m_web = _ref.m_web;
	return *this;
}

C_hsl_clr&  C_hsl_clr::operator <<(const COLORREF _rgb) { this->Rgb(_rgb); return *this; }

/////////////////////////////////////////////////////////////////////////////

C_hsl_clr::operator const COLORREF(void) const { return this->Rgb(); }

/////////////////////////////////////////////////////////////////////////////

float C_hsl_clr::Chrome (const COLORREF _rgb) {
	_rgb;
	float __u = 0.0f;
	CColourQuad __q(_rgb, _Opaque);
	float __r = (float)__q.GetR(); __r/= float(_Opaque);
	float __g = (float)__q.GetG(); __g/= float(_Opaque);
	float __b = (float)__q.GetB(); __b/= float(_Opaque);

	__u  = ::sqrt(__r * __r + __g * __g + __b * __b);
	return __u;
}

/////////////////////////////////////////////////////////////////////////////

C_hsl_clr_set:: C_hsl_clr_set(void) {}
C_hsl_clr_set::~C_hsl_clr_set(void) {}

/////////////////////////////////////////////////////////////////////////////

HRESULT       C_hsl_clr_set::Append(const C_hsl_clr& _cls) {

	HRESULT hr_ = S_OK;
	try {
		m_set.push_back(_cls);
	}
	catch (::std::bad_alloc&){
		hr_ = E_OUTOFMEMORY;
	}

	return  hr_;
}

VOID          C_hsl_clr_set::Clear (void) { if (m_set.empty() == false) m_set.clear(); }
UINT          C_hsl_clr_set::Count (void) const { return static_cast<UINT>(m_set.size()); }
const
C_hsl_clr&    C_hsl_clr_set::Colour(const INT _ndx) const {

	if (0 > _ndx || _ndx > (INT)this->Count() - 1) {

		static C_hsl_clr na_; na_.Web(_T("#n/a"));
		return na_;
	}
	else
		return m_set[_ndx];
}

/////////////////////////////////////////////////////////////////////////////

C_hsl_clr_std::C_hsl_clr_std(void) {

	C_hsl_clr c_0; c_0.Cga(_T("15 (white)"));      c_0.Chrome((UCHAR)  0); c_0.Hue(  0); c_0.Light(100); c_0.Rgb(0xFFFFFF); c_0.Web(_T("White"));
	C_hsl_clr c_1; c_1.Cga(_T("07 (light gray)")); c_1.Chrome((UCHAR)  0); c_1.Hue(  0); c_1.Light( 75); c_1.Rgb(0xC0C0C0); c_1.Web(_T("Silver"));
	C_hsl_clr c_2; c_2.Cga(_T("08 (dark gray)"));  c_2.Chrome((UCHAR)  0); c_2.Hue(  0); c_2.Light( 50); c_2.Rgb(0x808080); c_2.Web(_T("Gray"));
	C_hsl_clr c_3; c_3.Cga(_T("00 (black)"));      c_3.Chrome((UCHAR)  0); c_3.Hue(  0); c_3.Light(  0); c_3.Rgb(0x000000); c_3.Web(_T("Black"));
	C_hsl_clr c_4; c_4.Cga(_T("12 (high red)"));   c_4.Chrome((UCHAR)100); c_4.Hue(  0); c_4.Light( 50); c_4.Rgb(0xFF0000); c_4.Web(_T("Red"));
	C_hsl_clr c_5; c_5.Cga(_T("04 (low red)"));    c_5.Chrome((UCHAR)100); c_5.Hue(  0); c_5.Light( 25); c_5.Rgb(0x800000); c_5.Web(_T("Maroon"));
	C_hsl_clr c_6; c_6.Cga(_T("14 (yellow)"));     c_6.Chrome((UCHAR)100); c_6.Hue( 60); c_6.Light( 50); c_6.Rgb(0xFFFF00); c_6.Web(_T("Yellow"));
	C_hsl_clr c_7; c_7.Cga(_T("06 (brown)"));      c_7.Chrome((UCHAR)100); c_7.Hue( 60); c_7.Light( 25); c_7.Rgb(0x808000); c_7.Web(_T("Olive"));
	C_hsl_clr c_8; c_8.Cga(_T("10 (high green)")); c_8.Chrome((UCHAR)100); c_8.Hue(120); c_8.Light( 50); c_8.Rgb(0x00FF00); c_8.Web(_T("Lime"));
	C_hsl_clr c_9; c_9.Cga(_T("02 (low green)"));  c_9.Chrome((UCHAR)100); c_9.Hue(120); c_9.Light( 25); c_9.Rgb(0x008000); c_9.Web(_T("Green"));
	C_hsl_clr c_a; c_a.Cga(_T("11 (high cyan)"));  c_a.Chrome((UCHAR)100); c_a.Hue(180); c_a.Light( 50); c_a.Rgb(0x00FFFF); c_a.Web(_T("Aqua"));
	C_hsl_clr c_b; c_b.Cga(_T("03 (low cyan)"));   c_b.Chrome((UCHAR)100); c_b.Hue(180); c_b.Light( 25); c_b.Rgb(0x008080); c_b.Web(_T("Teal"));
	C_hsl_clr c_c; c_c.Cga(_T("09 (high blue)"));  c_c.Chrome((UCHAR)100); c_c.Hue(240); c_c.Light( 50); c_c.Rgb(0x0000FF); c_b.Web(_T("Blue"));
	C_hsl_clr c_d; c_d.Cga(_T("01 (low blue)"));   c_d.Chrome((UCHAR)100); c_d.Hue(240); c_d.Light( 25); c_d.Rgb(0x000080); c_d.Web(_T("Navy"));
	C_hsl_clr c_e; c_e.Cga(_T("13 (magenta)"));    c_e.Chrome((UCHAR)100); c_e.Hue(300); c_e.Light( 50); c_d.Rgb(0xFF00FF); c_e.Web(_T("Fuchsia"));
	C_hsl_clr c_f; c_f.Cga(_T("05 (low magenta)"));c_f.Chrome((UCHAR)100); c_f.Hue(300); c_f.Light( 25); c_f.Rgb(0x800080); c_f.Web(_T("Purple"));

	T_base::Append(c_0);
	T_base::Append(c_1);
	T_base::Append(c_2);
	T_base::Append(c_3);
	T_base::Append(c_4);
	T_base::Append(c_5);
	T_base::Append(c_6);
	T_base::Append(c_7);
	T_base::Append(c_8);
	T_base::Append(c_9);
	T_base::Append(c_a);
	T_base::Append(c_b);
	T_base::Append(c_c);
	T_base::Append(c_d);
	T_base::Append(c_e);
	T_base::Append(c_f);
}