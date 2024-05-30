#pragma once

#include "AddConnectionPage.g.h"

#include "NavigationService.h"
#include "SQLCoreService.h"

namespace winrt::sqleditor::implementation {
	struct AddConnectionPage : AddConnectionPageT<AddConnectionPage> {
		AddConnectionPage() : m_navigationService(services::NavigationService::Instance()), m_sqlCoreService(services::SQLCoreService::Instance()) {
			this->InitializeComponent();

			for (auto plugin : m_sqlCoreService->Factory()->GetPlugins()) {
				auto pluginDialect = plugin->GetDialect();
				auto comboBoxItem = Microsoft::UI::Xaml::Controls::ComboBoxItem();
				comboBoxItem.Content(box_value(to_hstring(pluginDialect)));
				dialectComboBox().Items().Append(comboBoxItem);
			}

			if (dialectComboBox().Items().Size() > 0) {
				dialectComboBox().SelectedIndex(0);
			}
		}

		int32_t MyProperty();
		void MyProperty(int32_t value);

		void ChangeDialectHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
		void ConnectHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);

	private:
		services::NavigationService* m_navigationService;
		services::SQLCoreService* m_sqlCoreService;
	};
}

namespace winrt::sqleditor::factory_implementation {
	struct AddConnectionPage : AddConnectionPageT<AddConnectionPage, implementation::AddConnectionPage> {};
}
