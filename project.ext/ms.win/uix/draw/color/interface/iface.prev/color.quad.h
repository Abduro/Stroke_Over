#ifndef __SFXSOACLIENTDRAWINGSERVICECOLOURQUAD_H_
#define __SFXSOACLIENTDRAWINGSERVICECOLOURQUAD_H_
/*
	Created by Tech_dog (ebontrop@gmail.com) on 8-Mar-2012 at 9:59:04pm, GMT+3, Rostov-on-Don, Thursday;
	This is SfxSOA Client Drawing Service Colour Quad class declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 2-May-2020 at 8:53:42p, UTC+7, Novosibirsk, Saturday;
	Adopted to Ebo Pack color project on 10-Oct-2021 at 4:28:57.0784593 am, UTC+7, Novosibirsk, Sunday;
*/
#ifndef _Opaque
#define _Opaque (0xff)
#endif

#ifndef RGBA
#define RGBA(r,g,b,a)	( RGB(r,g,b) | (((DWORD)(BYTE)(a))<<24) )
#endif

namespace ex_ui { namespace color {

	// TODO: maybe using __int8 insted of BYTE would be better; not sure;
	//       DWORD or COLORREF can be considered as RGB+A;

	class CColourQuad
	{
	private: // using array of 4 bytes may be have better compactness of the code; but it is not so readable at the same time;
		BYTE    m_r;
		BYTE    m_g;
		BYTE    m_b;
		BYTE    m_a; // alpha channel value;

	public:
		 CColourQuad(void);                // initiates color to "absolute" black emptiness;
		 CColourQuad(const CColourQuad&);
		 CColourQuad(const COLORREF _rgb, const BYTE _alpha);
		~CColourQuad(void);

	public:
		CColourQuad& operator = (const CColourQuad&);  // just copying a source;
		CColourQuad& operator <<(const COLORREF);      // assigning classic or plain color value; transparency value or alpha is set to opaque;
		CColourQuad& operator <<(const BYTE alpha  );  // accepts a magic alpha;
		CColourQuad& operator +=(const CColourQuad&);  // makes more brightness;
		CColourQuad& operator +=(const COLORREF);      // makes more brightness as above;
		CColourQuad& operator /=(const BYTE b__);      // creates a part of the original color value by division; it seems to be a dummy approach;

	public:
		operator bool    (void) const;     // returns true in case when color value is not CLR_NONE;
		operator COLORREF(void) const;     // there is a trick: returns alpha channel value in 4th byte;

	public:
		void     Darken (const BYTE b__);                         // darkens a color by specified percent value in [0...100] range;
		void     Differ (const COLORREF _src, const __int8  b__); // differs rgb value with specified color by percent given in [-100...+100];
		bool     Is     (void) const;      // returns true if the quad does not equal to CLR_NONE; *important*: alpha value is also taken into account;
		void     Lighten(const BYTE b__);  // lightens a color by specified percent value (b__ is in [0...100])
		COLORREF ToRgb  (void) const;      // classic or plain color reference that actually does not care about transparency;
		COLORREF ToRgbA (void) const;      // this is complete color value that has alpha channel set to some level;

	public:
		__inline  BYTE  GetA(void) const {return m_a;}
		__inline  BYTE  GetB(void) const {return m_b;}
		__inline  BYTE  GetG(void) const {return m_g;}
		__inline  BYTE  GetR(void) const {return m_r;}

	public:
		  const   BYTE  SetA(const BYTE);  // returns previous value of alpha;
		  const   BYTE  SetB(const BYTE);  // returns previous value of blue ;
		  const   BYTE  SetG(const BYTE);  // returns previous value of green;
		  const   BYTE  SetR(const BYTE);  // returns previous value of red  ;
	};

}}

typedef ex_ui::color::CColourQuad  TColorQuad;

#endif/*__SFXSOACLIENTDRAWINGSERVICECOLOURQUAD_H_*/