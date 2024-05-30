#pragma once

#include "HomePage.g.h"

#include "NavigationService.h"

namespace winrt::sqleditor::implementation {
	struct HomePage : HomePageT<HomePage> {
		HomePage() : m_navigationService(services::NavigationService::Instance()) {
			this->InitializeComponent();
		}

		int32_t MyProperty();
		void MyProperty(int32_t value);
		void AddConnectionHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);

	private:
		services::NavigationService* m_navigationService;
	};
}

namespace winrt::sqleditor::factory_implementation {
	struct HomePage : HomePageT<HomePage, implementation::HomePage> {};
}
