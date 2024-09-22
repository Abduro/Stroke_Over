/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Sep-2024 at 00:45:26.771, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack shared gdi+ render test unit interface implementation file; 
*/
#include "ebo_test_$5$.h"

namespace ebo { namespace boo { namespace test {

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx   ;

	namespace draw { namespace render {

		using t_stat = ex_ui::draw::gdi_pls::t_stat;
		using e_status = ex_ui::draw::gdi_pls::e_status;

		__class(CErr_Assoc) {
			__ctor(_ctor) {

				TErrAssoc err_assoc(t_stat::Aborted, __e_aborted, true);

				_out() += TLog_Acc::e_new_line;
				_out() += err_assoc.Print(TErrAssoc::e_all);
				_out()();
			}
		};

		__class(CErr_Adapt) {
			__ctor(_ctor) {

				TErrAdapt err_adopt(e_status::e_no_err, _T("no error"));

				_out() += TLog_Acc::e_new_line;
				_out() += err_adopt.Print(TErrAdapt::e_all);
				_out()();
			}
		
		};

		__class(CErr_Adapt_enum) {
			__ctor(_ctor) {

				const TRawStatus& sta_raw = TErrAdapt_enum::Ref().Raw();

				_out() += TLog_Acc::e_new_line;
				_out() += _T("Error adapter enum:");

				for (TRawStatus::const_iterator it_ = sta_raw.begin(); it_ != sta_raw.end(); ++it_) {

					_out() += it_->second.Print(TErrAdapt::e_all);
				}

				if (sta_raw.empty())
					_out() += _T("#no_elements;");

				_out()();
			}

			__method(Find) {

				const uint32_t id_to_found = TStatus::GdiplusNotInitialized;
				const uint32_t id_to_lost  = 32;

				_out() += TLog_Acc::e_new_line;
				_out() += TStringEx().Format(_T("Trying to find by the status=%u: %s"), id_to_found, (_pc_sz) TErrAdapt_enum::Ref().Get(id_to_found).Print(TErrAdapt::e_all));
				_out() += TStringEx().Format(_T("Trying to lost by the status=%u: %s"), id_to_lost, (_pc_sz) TErrAdapt_enum::Ref().Get(id_to_lost).Print(TErrAdapt::e_all));
				_out()();
			}
		};

		__class(CGuard) {
			__ctor(_ctor) {

				TGdiPlsGuard guard(false); // the auto-mode is turned off;

				_out() += TLog_Acc::e_new_line;
#if (0)
				guard.Capture();
				_out() += TStringEx().Format(_T("Gdi_pls >> capture(): %s;"), TStringEx().Bool(guard.Secured()));

				guard.Release();
				_out() += TStringEx().Format(_T("Gdi_pls >> release(): %s;"), TStringEx().Bool(guard.Secured()));
#else
				_out() +=  _T("Trying to init gdi+ lib:"); guard.Capture();
				_out() += (_pc_sz) guard.Print(TGdiPlsGuard::e_all);
				_out() +=  _T("Trying to shut down gdi+ lib:"); guard.Release();
				_out() += (_pc_sz) guard.Print(TGdiPlsGuard::e_all);
#endif
				_out()();
			}
			__method(GetErrState) {

				TGdiPlsGuard guard(false); // the auto-mode is turned off intentionally for creating test cases of error state;

				_out() += TLog_Acc::e_new_line;
				{
					 guard.Capture();      // loading gdi+ module manually;
					_out() += (_pc_sz) guard.Print(TGdiPlsGuard::e_all);

					if (guard.Secured()) {
						_out() += _T("Trying to initialize gdi+ twice:"); guard.Capture(); // making the capture twice intentionally;
						_out() += (_pc_sz) guard.Print(TGdiPlsGuard::e_all);

						guard.Release();   // unloading gdi+ module manually;
					}

					_out() += _T("Trying to shutdown gdi+ twice:"); guard.Release();
					_out() += (_pc_sz) guard.Print(TGdiPlsGuard::e_all);
				}
				_out()();
			} 
		};
	}}
}}}