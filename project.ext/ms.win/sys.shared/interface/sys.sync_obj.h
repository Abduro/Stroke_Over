#ifndef _SHARED_SYS_SYNC_H_INCLUDED
#define _SHARED_SYS_SYNC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 1-May-2012 at 10:29:48pm, GMT+3, Rostov-on-Don, Tuesday;
	This is Shared Lite Library Generic Synchronize Object class declaration file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 27-May-2018 at 1:20:24p, UTC+7, Phuket, Rawai, Sunday;
	Adopted to FakeGPS driver project on 13-Dec-2019 at 9:22:22a, UTC+7, Novosibirsk, Friday;
	Adopted to Geometry Curve project on 17-Feb-2024 at 06:32:33.6343384, UTC+7, Novosibirsk, Saturday;
*/
#include <atlbase.h>

namespace shared { namespace sys_core {

	class CSyncObject {
	protected:
		mutable
		CRITICAL_SECTION m_sec;

	public:
		virtual
		~CSyncObject(void);
		 CSyncObject(void);

	public:
		VOID Lock   (void) const;
		BOOL TryLock(void) const;
		VOID Unlock (void) const;

	private:  // non-copyable;
		CSyncObject(const CSyncObject&);
		CSyncObject& operator= (const CSyncObject&);
	};

	template<typename TLocker>
	class CGenericAutoLocker {
	private:
		TLocker&    m_locker_ref;

	public:
		 CGenericAutoLocker(TLocker& locker_ref) : m_locker_ref(locker_ref) { m_locker_ref.Lock(); }
		~CGenericAutoLocker(void) { m_locker_ref.Unlock(); }

	private: // non-copyable;
		 CGenericAutoLocker(const CGenericAutoLocker&);
		 CGenericAutoLocker& operator= (const CGenericAutoLocker&);
	};

	template<typename TLocker>
	class CGenericAutoLockerEx
	{
	private:
		BOOL        m_locked;
		TLocker&    m_locker_ref;
	public:
		 CGenericAutoLockerEx(TLocker& locker_ref) : m_locker_ref(locker_ref), m_locked(FALSE) { m_locked = m_locker_ref.TryLock(); }
		~CGenericAutoLockerEx(void) {
			if (m_locked)
				m_locker_ref.Unlock();
		}
	public:
		BOOL   IsLocked(void)const { return m_locked; }
	private: // non-copyable;
		CGenericAutoLockerEx(const CGenericAutoLockerEx&);
		CGenericAutoLockerEx& operator= (const CGenericAutoLockerEx&);
	};
}}

typedef shared::sys_core::CSyncObject& TSyncRef;

typedef const shared::sys_core::CGenericAutoLocker<const shared::sys_core::CSyncObject> TAutoLocker;
#define SAFE_LOCK(cs)    TAutoLocker   tAutoLocker(cs);

typedef const shared::sys_core::CGenericAutoLockerEx<const shared::sys_core::CSyncObject> TAutoLockerEx;
#define SAFE_LOCK_EX(cs) TAutoLockerEx tAutoLockerEx(cs); if (!tAutoLockerEx.IsLocked()) return S_OK;

#endif/*_SHARED_SYS_SYNC_H_INCLUDED*/