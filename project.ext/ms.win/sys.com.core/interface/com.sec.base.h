#ifndef _COMSECBASE_H_INCLUDED
#define _COMSECBASE_H_INCLUDED
/*
	Cretaed by Tech_dog (ebontrop@gmail.com) on 17-Aug-2024 at 19:20:38.1648420, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack project comp-obj-model service security base level wrapper interface declaration file;
*/
#include <objbase.h>
#include "com.svc.base.h" // possibly is useless reference for the time being;

namespace shared { namespace sys_core { namespace com { namespace security {

	// https://learn.microsoft.com/en-us/windows/win32/api/objidlbase/nn-objidlbase-iserversecurity ;
	// https://learn.microsoft.com/en-us/windows/win32/api/objidl/nn-objidl-iclientsecurity ;

	class CProvider {
	};

	// https://cyral.com/glossary/authentication-authn-versus-authorization-authz/ ;
	using dword = DWORD;

	class CImpersonate {
		// https://docs.microsoft.com/en-us/windows/desktop/com/com-impersonation-level-constants ;
	public:
		enum _e : dword {
			eDefault    = RPC_C_IMP_LEVEL_DEFAULT    , // DCOM can choose the impersonation level using its normal security blanket negotiation algorithm;
			eAnonymous  = RPC_C_IMP_LEVEL_ANONYMOUS  , // a client is anonymous to the server;
			eIdentity   = RPC_C_IMP_LEVEL_IDENTIFY   , // a server can obtain the client's identity and to impersonate the client for ACL checking;
			eImpersonate= RPC_C_IMP_LEVEL_IMPERSONATE, // a server can impersonate a client's security context while acting on behalf of the client; (for local resource only);
			eDelegate   = RPC_C_IMP_LEVEL_DELEGATE     // a server may use a client's security context on other machines to access local and remote resources as a client;
		};
	};

	class CNetwork {
		// https://docs.microsoft.com/en-us/windows/desktop/com/com-authentication-level-constants ;
	public:
		enum _e : dword {
			eDefault    = RPC_C_AUTHN_LEVEL_DEFAULT, // DCOM to choose the authentication level using its normal security blanket negotiation algorithm;
			eNone       = RPC_C_AUTHN_LEVEL_NONE   , // no authentication;
			eConnect    = RPC_C_AUTHN_LEVEL_CONNECT, // for a relationship with the server; datagram transports always use RPC_AUTHN_LEVEL_PKT instead;
			eRemote     = RPC_C_AUTHN_LEVEL_CALL   , // for remote procedure call; datagram transports use RPC_C_AUTHN_LEVEL_PKT instead;
			eExpected   = RPC_C_AUTHN_LEVEL_PKT    , // authenticates that all data received is from the expected client;
			eIntegrity  = RPC_C_AUTHN_LEVEL_PKT_INTEGRITY, // verifies that none of the data transferred between client and server has been modified;
			ePrivacy    = RPC_C_AUTHN_LEVEL_PKT_PRIVACY    // encrypts the argument value of each remote procedure call;
		};
	};
	// https://learn.microsoft.com/en-us/windows/win32/com/security-in-com ;
}}}}

#endif/*_COMSECBASE_H_INCLUDED*/