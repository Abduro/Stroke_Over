#ifndef _COLOR_MODEL_H_INCLUDED
#define _COLOR_MODEL_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Feb-2011 at 10:50:12pm, GMT+3, Rostov-on-Don, Thursday;
	This is SfxSOA package client UI drawing color related class(es) declaration file.
	----------------------------------------------------------------------------
	Adopted to Ebo Pack on 23-Apr-2021 at 11:32:12.068 pm, UTC+7, Novosibirsk, Friday;
	Adopted to Ebo Pack color project on 12-Oct-2021 at 2:04:46.4342040 am, UTC+7, Novosibirsk, Tuesday;
*/
#include "color.generic.h"
#include "color.hsl.h"
#include "color.quad.h"

namespace ex_ui { namespace color {

	// this class is intended for making relations between different color representations;
	class CColorModel
	{
	public:
		enum _type {         // there is no SMYC, because it is just for great typography;
			CM_RGB    = 0x0, // stands for red-green-blue-alpha/transparency;
			CM_HLS    = 0x1, // stands for hue-luminosity-saturation;
			CM_HSL    = 0x2, // stands for hue-saturation-lightness;
		};

	private:
		THlsColor     m_hls; // HLS   color component;
		THslColor     m_hsl; // HSL   color component; 
		TColorQuad    m_rgb; // RGB+A color component;

	public:
		 CColorModel (void) ;
		 CColorModel (const CColorModel& );
		 CColorModel (const COLORREF _rgb); // creates all components from given RGB value; alpha channel is set to opaque by default;
		 CColorModel (const THlsColor& );   // sets HLS color; updates RGB and HSL if possible, otherwise keeps them clear;
		~CColorModel (void);
	
	public:
		const THlsColor&  Get_HLS (void) const;
		const THslColor&  Get_HSL (void) const;
		const TColorQuad& Get_RGB (void) const;
		HLSCOLOR   To_HLS (void) const;           // converts RGB source to HLS color; if RGB is valid, otherwise, HSL component is returned;
		COLORREF   To_RGB (void) const;           // converts HLS source to RGB color; actually, HSL component can do that;

	public:
		COLORREF   Darken (const BYTE);   // darkens RGB value by specified percent value [0...100]; other components update their values also;
		COLORREF   Differ (const __int8); // differs RGB value by specified percent given in [-100...+100]; other components are updated too;
		const bool IsDark (const bool bInvert, const float _coef) const; // compare chroma value of RGB with black or white colors, comparison threshold can be used;

	public:
		COLORREF   Invert(void) const;                             // inverts RGB color, if the color model is HLS, it is converted to RGB internally;
		const bool SplitToHLS(BYTE& _h, BYTE& _l, BYTE& _s) const; // splits RGB colour component to hue, luminosity and saturation values;
		const bool SplitToRGB(BYTE& _r, BYTE& _g, BYTE& _b) const; // splits HLS colour component to red, blue and green values;
		COLORREF   Transform (const __int8 lum, const __int8 sat); // changes a luminance [-100...+100] and a saturation [-100...+100] of HLS component;
		
	public:
		CColorModel& operator = (const CColorModel&);
		CColorModel& operator <<(const COLORREF    _rgb );   // updates *all* components by given RGB-color;
		CColorModel& operator <<(const THlsColor&  _hls );   // sets HLS component only;
		CColorModel& operator <<(const THslColor&  _hsl );   // sets HSL component only;
		CColorModel& operator <<(const TColorQuad& _rgb );   // sets RGB component only; alpha value is included;
	};
}}

typedef ex_ui::color::CColorModel        TClrModel;
typedef ex_ui::color::CColorModel::_type TClrModelType;

#endif/*_COLOR_MODEL_H_INCLUDED*/