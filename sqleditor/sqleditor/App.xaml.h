#pragma once

#include "App.xaml.g.h"

#include "SQLCoreService.h"

namespace winrt::sqleditor::implementation {
	struct App : AppT<App> {
		App();

		void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

	private:
		services::SQLCoreService* m_sqlCoreService;
		winrt::Microsoft::UI::Xaml::Window window{ nullptr };
	};
}
