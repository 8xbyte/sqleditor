#pragma once

#include "DatabasePage.g.h"

#include "NavigationService.h"
#include "SQLCoreService.h"

namespace winrt::sqleditor::implementation {
	struct DatabasePage : DatabasePageT<DatabasePage> {
		DatabasePage() : m_navigationService(services::NavigationService::Instance()), m_sqlCoreService(services::SQLCoreService::Instance()){
			this->InitializeComponent();

			auto navigationView = m_navigationService->NavigationView();
			auto selectedView = navigationView.SelectedItem().as<Microsoft::UI::Xaml::Controls::NavigationViewItem>();
			m_database = m_sqlCoreService->Connection(selectedView.Tag().as<hstring>());

			for (auto scheme : m_database->GetSchemas()) {
				auto scheme_node = Microsoft::UI::Xaml::Controls::TreeViewNode();
				scheme_node.Content(box_value(to_hstring(scheme)));

				for (auto table : m_database->GetTables(scheme)) {
					auto table_node = Microsoft::UI::Xaml::Controls::TreeViewNode();
					table_node.Content(box_value(to_hstring(table)));

					for (auto field : m_database->GetFields(scheme, table)) {
						auto field_node = Microsoft::UI::Xaml::Controls::TreeViewNode();
						field_node.Content(box_value(to_hstring(field)));
						table_node.Children().Append(field_node);
					}

					scheme_node.Children().Append(table_node);
				}

				this->database().RootNodes().Append(scheme_node);
			}
		}

		int32_t MyProperty();
		void MyProperty(int32_t value);

		void AddTableRowDefinition();
		void AddTableColumnDefinition();
		void AddTableValue(hstring value, int32_t row, int32_t column);

		Microsoft::UI::Xaml::Controls::TextBlock CreateOutputText(hstring text);
		Microsoft::UI::Xaml::Controls::ScrollViewer CreateOutputTextBlock(Microsoft::UI::Xaml::Controls::TextBlock textBlock, int32_t row, int32_t column);
		void AddOutputValue(hstring status, hstring query, hstring message);

		void SqlQueryHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);

	private:
		SQLCore::IDatabase* m_database;
		services::NavigationService* m_navigationService;
		services::SQLCoreService* m_sqlCoreService;
	};
}

namespace winrt::sqleditor::factory_implementation {
	struct DatabasePage : DatabasePageT<DatabasePage, implementation::DatabasePage> {};
}
