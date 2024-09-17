/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Feb-2011 at 11:03:38pm, GMT+3, Rostov-on-Don, Thursday;
	This is SfxSOA package client UI drawing color related class(es) implementation file.
	----------------------------------------------------------------------------
	Adopted to Ebo Pack on 24-Apr-2021 at 0:30:58.518 am, UTC+7, Novosibirsk, Saturday;
	Adopted to Ebo Pack color project on 12-Oct-2021 at 2:09:37.9718941 am, UTC+7, Novosibirsk, Tuesday;
*/
#include "color.model.h"

using namespace ex_ui::color;
/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace color { namespace _impl {
	// calculates a color component value by using luminocity (OR lightness, must be cleared) reminders and hue value;
	BYTE  To_rgb (const float lum_part_0, const float lum_part_1, const float _hue)
	{
		float hue_ = _hue;
		float lum_ = lum_part_0;

		if      (_hue > 360.0f) hue_ -= 360.0f;
		else if (_hue <   0.0f) hue_ += 360.0f;

		if      (hue_ <  60.0f) lum_ = lum_part_0 + (lum_part_1 - lum_part_0) * hue_ / 60.0f;   
		else if (hue_ < 180.0f) lum_ = lum_part_1;
		else if (hue_ < 240.0f) lum_ = lum_part_0 + (lum_part_1 - lum_part_0) * (240.0f - hue_) / 60.0f;      

		return (BYTE)(lum_) * 255;
	}
	
} } }

using namespace ex_ui::color::_impl;
/////////////////////////////////////////////////////////////////////////////

TClrModel:: CColorModel (void) {}
TClrModel:: CColorModel (const CColorModel& _ref) : TClrModel() { *this = _ref; }
TClrModel:: CColorModel (const COLORREF _rgb) : TClrModel() { *this << _rgb; }
TClrModel:: CColorModel (const THlsColor& _hls) : TClrModel() { *this << _hls; }
TClrModel::~CColorModel (void) {}

/////////////////////////////////////////////////////////////////////////////

const THlsColor&    TClrModel::Get_HLS (void) const { return m_hls; }
const THslColor&    TClrModel::Get_HSL (void) const { return m_hsl; }
const TColorQuad&   TClrModel::Get_RGB (void) const { return m_rgb; }

/////////////////////////////////////////////////////////////////////////////

COLORREF    TClrModel::Darken (const BYTE b__) {
	b__;
	if (!!m_rgb)
		return m_rgb;

	TColorQuad rgb(m_rgb); rgb.Darken(b__); *this << rgb.ToRgbA();

	return rgb.ToRgbA();
}

COLORREF    TClrModel::Differ (const __int8 b__) {
	b__;
	if (!!m_rgb)
		return m_rgb;

	TColorQuad rgb(m_rgb); rgb.Differ(m_rgb, b__); *this << rgb.ToRgbA();

	return rgb.ToRgbA();
}

const bool  TClrModel::IsDark(const bool bInvert, const float _thresh) const { bool b_result = false;
	bInvert; _thresh;
	if (!!m_rgb)
		return b_result;

	static const float __f_m  = ::sqrt((float)3)/float(2);

	float __f_pt = C_hsl_clr().Chrome(m_rgb);
	if ( __f_pt >= (__f_m + _thresh))
		b_result = (bInvert ? true : false);
	else
		b_result = (bInvert ? false : true);

	return b_result;
}

/////////////////////////////////////////////////////////////////////////////

COLORREF    TClrModel::Invert(void) const
{
	COLORREF rgb__ = (m_rgb.Is() ? m_rgb.ToRgbA() : To_RGB());
	BYTE r__ = ~GetRValue(rgb__);
	BYTE g__ = ~GetGValue(rgb__);
	BYTE b__ = ~GetBValue(rgb__);
	if (125 < r__ && r__ < 131 && 125 < g__ && g__ < 131 && 125 < b__ && b__ < 131) // this is a grey that is inverted to grey
	{
		r__ = g__ = b__ = 96;
	}
	rgb__ = RGB(r__, g__, b__);
	return rgb__;
}

const bool  TClrModel::SplitToHLS(BYTE& h__, BYTE& l__, BYTE& s__) const { bool b_result = true;
	h__; l__; s__;
	if (!!m_rgb)
	{
		h__ = m_hls.Get_H();
		l__ = m_hls.Get_L();
		s__ = m_hls.Get_S();
		return (b_result = false);
	}

	BYTE __r = m_rgb.GetR();
	BYTE __g = m_rgb.GetG();
	BYTE __b = m_rgb.GetB();

	BYTE __min = min(__r, min(__g, __b));
	BYTE __max = max(__r, max(__g, __b));

	float __rng = float(__max) - float(__min);  // chroma;
	float __sum = float(__max) + float(__min);

	float __l = __sum / 510.0f;
	float __s = 0.0f;
	float __h = 0.0f;

	if ( __max != __min )
	{ 
		float __rn = (__max - __r) / __rng;      
		float __gn = (__max - __g) / __rng;
		float __bn = (__max - __b) / __rng;   

		__s = (__l <= 0.5f) ? (__rng / __sum) : (__rng / (510.0f - __sum));

		if (__r == __max) __h = 60.0f * (6.0f + __bn - __gn);
		if (__g == __max) __h = 60.0f * (2.0f + __rn - __bn);
		if (__b == __max) __h = 60.0f * (4.0f + __gn - __rn);
		if (__h > 360.0f) __h = __h - 360.0f;
	}
	h__ = BYTE(__h  * 255.0f / 360.0f);
	l__ = BYTE(__l  * 255.0f);
	s__ = BYTE(__s  * 255.0f);

	return b_result;
}

const bool  TClrModel::SplitToRGB(BYTE& r__, BYTE& g__, BYTE& b__) const {  bool b_result = true;
	r__; g__; b__;
	if (m_hls.Is() == false)
	{
		r__ = g__ = b__ = 0;
		return (b_result = false);
	}

	float __h = (m_hls.Get_H() * 360) / 255.0f;
	float __l =  m_hls.Get_L() / 255.0f;
	float __s =  m_hls.Get_S() / 255.0f;

	if ( __s == 0.0f )
	{
		r__ = BYTE(__l) * TAlpha::eOpaque;
		g__ = r__;
		b__ = g__;
	}
	float rm1 = 0.0f;
	float rm2 = 0.0f;

	if ( __l <= 0.5f ) rm2 = __l + __l * __s;
	else               rm2 = __l + __s - __l * __s;

	rm1 = 2.0f * __l - rm2;   
	r__ = To_rgb(rm1 , rm2, __h + 120.0f);   
	g__ = To_rgb(rm1 , rm2, __h);
	b__ = To_rgb(rm1 , rm2, __h - 120.0f);

	return b_result;
}

COLORREF    TClrModel::Transform (const __int8 _lum, const __int8 _sat) {
	_lum; _sat;

	if (!!m_rgb)
		return m_rgb;

	__int8 lum_ = _lum;
	__int8 sat_ = _sat;
	lum_ = (lum_ < -100 ? -100 : (lum_ > 100 ? 100 : lum_));
	sat_ = (sat_ < -100 ? -100 : (sat_ > 100 ? 100 : sat_));

	HLSCOLOR hls_ = To_HLS();

	BYTE h__ = HLS_H (hls_);
	BYTE l__ = HLS_L (hls_);
	BYTE s__ = HLS_S (hls_);

	if ( lum_ > 0 )
	{
		l__ = BYTE(l__ + ((255 - l__) * lum_) / 100);
	}
	else if ( lum_ < 0 )
	{
		l__ = BYTE((l__ * (100 + lum_)) / 100);
	}
	if ( sat_ > 0 )
	{
		s__ = BYTE(s__ + ((255 - s__) * sat_) / 100);
	}
	else if ( sat_ < 0 )
	{
		s__ = BYTE((s__ * (100 + sat_)) / 100);
	}

	m_hls.ToHLS(h__, l__, s__);
	m_rgb << m_hls.ToRGB();

	return m_rgb;
}

HLSCOLOR    TClrModel::To_HLS (void) const {
	if (!!m_rgb)
		return m_hls;

	BYTE l__ = 0;
	BYTE s__ = 0;
	BYTE h__ = 0; 
	SplitToHLS(h__, l__, s__);
	return HLS(h__, l__, s__);
}

COLORREF    TClrModel::To_RGB(void) const
{
	BYTE r__ = 0;
	BYTE g__ = 0;
	BYTE b__ = 0;
	SplitToRGB(r__, g__, b__);
	return RGB(r__, g__, b__);
}

/////////////////////////////////////////////////////////////////////////////

TClrModel& TClrModel::operator = (const TClrModel& _ref) { *this << _ref.Get_HLS() << _ref.Get_HSL() << _ref.Get_RGB(); return *this; }

TClrModel& TClrModel::operator <<(const COLORREF _rgb) {

	this->m_hls << _rgb;
	this->m_hsl << _rgb;
	this->m_rgb << _rgb;

	return *this;
}

TClrModel& TClrModel::operator <<(const THlsColor&  _hls ) { this->m_hls = _hls; return *this; }
TClrModel& TClrModel::operator <<(const THslColor&  _hsl ) { this->m_hsl = _hsl; return *this; }
TClrModel& TClrModel::operator <<(const TColorQuad& _rgb ) { this->m_rgb = _rgb; return *this; }