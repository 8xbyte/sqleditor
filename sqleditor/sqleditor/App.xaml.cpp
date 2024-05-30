#include "pch.h"

#include "App.xaml.h"
#include "MainWindow.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::sqleditor::implementation {
	App::App() : m_sqlCoreService(services::SQLCoreService::Instance()) {
		#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
		UnhandledException([] (IInspectable const&, UnhandledExceptionEventArgs const& e) {
			if (IsDebuggerPresent()) {
				auto errorMessage = e.Message();
				__debugbreak();
			}
		});
		#endif
	}

	void App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs const& e) {
		window = make<MainWindow>();
		window.Activate();
		
		auto package_wpath = Windows::ApplicationModel::Package::Current().InstalledPath();
		m_sqlCoreService->Factory()->AddPluginsDirectory(to_string(package_wpath));
	}
}
