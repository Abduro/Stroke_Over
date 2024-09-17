/*
	Created by Tech_dog (ebontrop@gmail.com) on 9-Mar-2012 at 11:13:38am, GMT+3, Rostov-on-Don, Friday;
	This is SfxSOA Client Drawing Service Colour Quad class implementation file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 2-May-2020 at 9:17:09p, UTC+7, Novosibirsk, Saturday;
	Adopted to Ebo Pack color project on 10-Oct-2021 at 5:20:32.8287634 am, UTC+7, Novosibirsk, Sunday;
*/
#include "color.quad.h"
#include "color.hsl.h"

/////////////////////////////////////////////////////////////////////////////
using namespace ex_ui::color;
/////////////////////////////////////////////////////////////////////////////

TColorQuad:: CColourQuad (void) : m_r(0), m_g(0), m_b(0), m_a(0) { }
TColorQuad:: CColourQuad (const TColorQuad& _ref) : TColorQuad() { *this = _ref; }
TColorQuad:: CColourQuad (const COLORREF _rgb, const BYTE _alpha) : TColorQuad() { *this << _rgb << _alpha; }
TColorQuad::~CColourQuad (void) { }

/////////////////////////////////////////////////////////////////////////////

TColorQuad& TColorQuad::operator = (const TColorQuad& _ref) { *this << _ref.ToRgb() << _ref.GetA(); return *this; }
TColorQuad& TColorQuad::operator <<(const COLORREF _rgb)
{
	m_r = GetRValue(_rgb);
	m_g = GetGValue(_rgb);
	m_b = GetBValue(_rgb);
	m_a = _Opaque;
	return *this;
}

TColorQuad& TColorQuad::operator <<(const BYTE _alpha) { this->m_a = _alpha; return *this; }

TColorQuad& TColorQuad::operator +=(const COLORREF _rgb)
{
	CColourQuad q__(_rgb, _Opaque);
	return operator+=(q__);
}

TColorQuad& TColorQuad::operator +=(const TColorQuad& _ref)
{
	m_r = m_r + _ref.m_r  - (m_r + _ref.m_r > _Opaque ? _Opaque : 0);
	m_g = m_g + _ref.m_g  - (m_g + _ref.m_g > _Opaque ? _Opaque : 0);
	m_b = m_b + _ref.m_b  - (m_b + _ref.m_b > _Opaque ? _Opaque : 0);
	return *this;
}

TColorQuad& TColorQuad::operator /=(const BYTE b__)
{
	m_r /= (0==b__ ? 1 : b__);
	m_g /= (0==b__ ? 1 : b__);
	m_b /= (0==b__ ? 1 : b__);
	m_a /= (0==b__ ? 1 : b__);
	return *this;
}

/////////////////////////////////////////////////////////////////////////////

TColorQuad::operator bool     (void) const { return this->ToRgb() != CLR_NONE; }
TColorQuad::operator COLORREF (void) const { return ToRgbA(); }

/////////////////////////////////////////////////////////////////////////////

void     TColorQuad::Darken (const BYTE b)
{
	BYTE b__  = (b  > 100 ? 100 : b);
	float __f = float(b__)/ 100.0f;
	int m_rd  = int(m_r * __f);
	int m_gd  = int(m_g * __f);
	int m_bd  = int(m_b * __f);
	m_r = BYTE((int)m_r - m_rd < 0 ? 0 : (int)m_r - m_rd);
	m_g = BYTE((int)m_g - m_gd < 0 ? 0 : (int)m_g - m_gd);
	m_b = BYTE((int)m_b - m_bd < 0 ? 0 : (int)m_b - m_bd);
}

void     TColorQuad::Differ (const COLORREF _src, const __int8  b__) {
	_src; b__;
	if (CLR_NONE == _src)
		return;

	float __f__0 = C_hsl_clr().Chrome(this->ToRgbA());
	float __f__1 = C_hsl_clr().Chrome(_src);
	float __f__d = (__f__0 < __f__1 ? __f__1 - __f__0 : __f__0 - __f__1);

	*this << _src;

	if ( int(__f__d * 100) < abs(b__) )
	{
		if (b__ < 0)
			this->Darken((BYTE)abs(b__));
		else
			this->Lighten(b__);
	}
}

bool     TColorQuad::Is     (void) const { return this->ToRgbA() != CLR_NONE; }

void     TColorQuad::Lighten(const BYTE b)
{
	BYTE b__  = (b > 100 ? 100 : b);
	float __f = float(b__/ 100);
	int m_rd  = int(m_r *  __f);
	int m_gd  = int(m_g *  __f);
	int m_bd  = int(m_b *  __f);
	m_r = BYTE((int)m_r + m_rd > _Opaque ? _Opaque : (int)m_r + m_rd);
	m_g = BYTE((int)m_g + m_gd > _Opaque ? _Opaque : (int)m_g + m_gd);
	m_b = BYTE((int)m_b + m_bd > _Opaque ? _Opaque : (int)m_b + m_bd);
}

COLORREF TColorQuad::ToRgb  (void) const { return RGB (m_r, m_g, m_b); }
COLORREF TColorQuad::ToRgbA (void) const { return RGBA(m_r, m_g, m_b, m_a); }