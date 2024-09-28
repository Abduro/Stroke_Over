#ifndef _COM_UNK_H_INCLUDED
#define _COM_UNK_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Sep-2024 at 14:04:51.304, UTC+7, Novosibirsk, Friday;
	This is Ebo Pack project comp-obj-model IUnknown interface base wrapper declaration file;
*/
#include <unknwn.h>

#include "sys.err.codes.h"
#include "com.guid.h"

#include "shared.preproc.h"
#include "shared.string.h"

namespace shared { namespace sys_core { namespace com {

	// https://learn.microsoft.com/en-us/windows/win32/api/unknwn/nn-unknwn-iunknown ;
	// https://learn.microsoft.com/en-us/windows/win32/com/rules-for-implementing-queryinterface ;
	// https://learn.microsoft.com/en-us/windows/win32/com/using-and-implementing-iunknown ;

	using u_long = ULONG;

#if (0)
	template < class ClassType, const GUID& _obj_iid >
	class CUnknown : public IUnknown {
	protected:
		 CUnknown (void) : m_lRef(0) {} CUnknown (const CUnknown&) = delete; CUnknown (CUnknown&&) = delete;
		~CUnknown (void) {}
	protected:
		// https://learn.microsoft.com/en-us/windows/win32/api/unknwn/nf-unknwn-iunknown-queryinterface(refiid_void) ;
		virtual HRESULT __stdcall QueryInterface( const GUID& _iid, void** ppv ) {
			_iid; ppv;
			if ( !ppv )
				return __e_pointer;

			if ( _iid == _obj_iid || _iid == IID_IUnknown )
			{
				*ppv = static_cast< ClassType* >( this );
				this->AddRef();
				return TErrCodes::no_error;
			}
			*ppv = 0;
			return __e_no_iface;
		}
		// https://learn.microsoft.com/en-us/windows/win32/api/winnt/nf-winnt-interlockedincrement ;
		virtual ULONG __stdcall AddRef (void) {
			return static_cast<ULONG>(InterlockedIncrement( &m_lRef )); // it is strange: different data types for func impl and iface decl;
		}
		virtual ULONG __stdcall Release(void) {
		
			LONG lRef = InterlockedDecrement( &m_lRef ); // https://learn.microsoft.com/en-us/windows/win32/api/winnt/nf-winnt-interlockeddecrement ;
			if ( lRef < 1 ) 
				delete this;

			return static_cast<ULONG>(lRef);
		}
	protected:
		ULONG  m_lRef;

	private:
		CUnknown& operator = (const CUnknown&) = delete;
		CUnknown& operator = (CUnknown&&) = delete;
	};
#endif

	class CUnknown : public IUnknown {
	protected:
		 CUnknown (void);            // when any version of the constructors is being invoked or used, the references count is auutomatically set to 1;
		 CUnknown (const GUID& _iface_id);
		 CUnknown (const CUnknown&) = delete;
		 CUnknown (CUnknown&&) = delete;
		virtual ~CUnknown (void);    // for playing with object destruction through one of the its base/inherited pointer(s) >> virtual #dtor;

	public: // IUnknown method(s) impl;
	        // https://learn.microsoft.com/en-us/windows/win32/api/unknwn/nf-unknwn-iunknown-queryinterface(refiid_void) ;
		virtual err_code __stdcall QueryInterface( const GUID& _iid, void** ppv ) override; // works only for IID_IUnknown, otherwise the owner must override this function;
		virtual u_long   __stdcall AddRef (void) override; // https://learn.microsoft.com/en-us/windows/win32/api/unknwn/nf-unknwn-iunknown-addref ;
		virtual u_long   __stdcall Release(void) override; // https://learn.microsoft.com/en-us/windows/win32/api/unknwn/nf-unknwn-iunknown-release ;

	public:
		const IUnknown* Ptr (void) const;  // gets the base interface pointer by applying static_cast<> to the instance of this class; 
		const u_long    Refs (void) const; // references' count, almost for debug purpose;
		const
		CGuid& Owner (void) const;
		CGuid& Owner (void) ;      // this property breaks the rule for QueryInterface(): The Set of Interfaces on an Object Instance Must Be Static;

#if defined(_DEBUG)
		enum e_print {
			e_all    = 0,  // outputs complete info of this class object: class name, address of the base interface pointer, reference count value;
			e_no_prx = 1,  // outputs a trimmed info for including to child class description;
			e_req    = 2,  // outputs attribute values of this class object only; 
		};
		CString Print (const e_print = e_print::e_all) const;
#endif
	private:
		CUnknown& operator = (const CUnknown&) = delete;
		CUnknown& operator = (CUnknown&&) = delete;

	private:
		ULONG  m_lRef ; // reference counting; https://learn.microsoft.com/en-us/windows/win32/directshow/cunknown-m-cref ;
		CGuid  m_owner; // child/owner class interface identifier;
	};

#if defined(_DEBUG)

	// __guid_null is used for identifying the default owner class of the unknown interface;
	class CDefault_unknown : public CUnknown { typedef CUnknown TBase;
	public:
		 CDefault_unknown (void); CDefault_unknown(const GUID&) = delete; CDefault_unknown(CDefault_unknown&&) = delete;
		~CDefault_unknown (void);

	public:
		CString Print (void) const;

	private:
		CDefault_unknown& operator = (const CDefault_unknown&) = delete;
		CDefault_unknown& operator = (CDefault_unknown&&) = delete;
	};
#endif
}}}

#endif/*_COM_UNK_H_INCLUDED*/