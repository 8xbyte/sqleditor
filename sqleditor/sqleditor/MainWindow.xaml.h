#pragma once

#include "MainWindow.g.h"

#include "NavigationService.h"

namespace winrt::sqleditor::implementation {
	struct MainWindow : MainWindowT<MainWindow> {
		MainWindow() : m_navigationService(services::NavigationService::Instance()) {
			this->InitializeComponent();

			auto titleBar = this->AppWindow().TitleBar();

			titleBar.ExtendsContentIntoTitleBar(true);
			titleBar.ButtonBackgroundColor(Windows::UI::Colors::Transparent());
			titleBar.ButtonInactiveBackgroundColor(Windows::UI::Colors::Transparent());

			m_navigationService->DispatcherQueue(Microsoft::UI::Dispatching::DispatcherQueue::GetForCurrentThread());
			m_navigationService->NavigationView(rootNavigationView());
			m_navigationService->Frame(rootFrame());

			m_navigationService->Navigate(L"Home");
		}

		int32_t MyProperty();
		void MyProperty(int32_t);

		void ChangeViewHandler(Microsoft::UI::Xaml::Controls::NavigationView const& sender, Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);

	private:
		services::NavigationService* m_navigationService;
	};
}

namespace winrt::sqleditor::factory_implementation {
	struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow> {};
}
