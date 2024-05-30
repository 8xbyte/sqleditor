#include "pch.h"

#include "AddConnectionPage.xaml.h"
#if __has_include("AddConnectionPage.g.cpp")
#include "AddConnectionPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::sqleditor::implementation {
	int32_t AddConnectionPage::MyProperty() {
		throw hresult_not_implemented();
	}

	void AddConnectionPage::MyProperty(int32_t) {
		throw hresult_not_implemented();
	}

	void AddConnectionPage::ChangeDialectHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e) {
		auto comboBox = sender.as<Microsoft::UI::Xaml::Controls::ComboBox>();
		auto selectedItem = comboBox.SelectedItem().as<Microsoft::UI::Xaml::Controls::ComboBoxItem>().Content().as<hstring>();

		for (auto plugin : m_sqlCoreService->Factory()->GetPlugins()) {
			if (to_hstring(plugin->GetDialect()) == selectedItem) {
				auto connector = plugin->GetConnector();
				auto version = plugin->GetVersion();
				if (plugin->GetType() == "Server") {
					hostBlock().Visibility(Microsoft::UI::Xaml::Visibility::Visible);
					userBlock().Visibility(Microsoft::UI::Xaml::Visibility::Visible);
					passwordBlock().Visibility(Microsoft::UI::Xaml::Visibility::Visible);
					databaseBlock().Visibility(Microsoft::UI::Xaml::Visibility::Visible);

					fileBlock().Visibility(Microsoft::UI::Xaml::Visibility::Collapsed);

					connectButton().Visibility(Microsoft::UI::Xaml::Visibility::Visible);
					connectButton().Content(box_value(L"Подключится"));
				} else if (plugin->GetType() == "File") {
					fileBlock().Visibility(Microsoft::UI::Xaml::Visibility::Visible);

					hostBlock().Visibility(Microsoft::UI::Xaml::Visibility::Collapsed);
					userBlock().Visibility(Microsoft::UI::Xaml::Visibility::Collapsed);
					passwordBlock().Visibility(Microsoft::UI::Xaml::Visibility::Collapsed);
					databaseBlock().Visibility(Microsoft::UI::Xaml::Visibility::Collapsed);

					connectButton().Visibility(Microsoft::UI::Xaml::Visibility::Visible);
					connectButton().Content(box_value(L"Открыть"));
				}
			}
		}
	}
	void AddConnectionPage::ConnectHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		auto comboBoxItem = dialectComboBox().SelectedItem().as<Microsoft::UI::Xaml::Controls::ComboBoxItem>();
		auto selectedItem = comboBoxItem.Content().as<hstring>();

		for (auto plugin : m_sqlCoreService->Factory()->GetPlugins()) {
			auto pluginDialect = plugin->GetDialect();
			if (to_hstring(pluginDialect) == selectedItem) {
				auto connect_uri = to_hstring(pluginDialect + "://");
				auto connection_name = to_hstring("[" + plugin->GetDialect() + "] ");

				if (plugin->GetType() == "Server") {
					auto password = passwordInput().Password();
					auto host = hostInput().Text();
					auto database = databaseInput().Text();
					auto user = userInput().Text();

					connect_uri = connect_uri + user + to_hstring(":");
					connect_uri = connect_uri + password + to_hstring("@");
					connect_uri = connect_uri + host + to_hstring("/");
					connect_uri = connect_uri + database;

					connection_name = connection_name + host;
				} else if (plugin->GetType() == "File") {
					auto file = fileInput().Text();

					connect_uri = connect_uri + file;

					connection_name = connection_name + fileInput().Text();
				}

				auto database = m_sqlCoreService->Factory()->Connect(to_string(connect_uri));

				if (database->IsConnect()) {
					std::wstringstream stream;
					stream << database;
					auto tag = hstring(stream.str());

					m_navigationService->AddView(connection_name, tag);
					m_navigationService->Navigate(tag);
				} else {
					database->Release();
				}

				break;
			}
		}
	}
}
