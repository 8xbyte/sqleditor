#include "pch.h"
#include "DatabasePage.xaml.h"
#if __has_include("DatabasePage.g.cpp")
#include "DatabasePage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::sqleditor::implementation {
	int32_t DatabasePage::MyProperty() {
		throw hresult_not_implemented();
	}

	void DatabasePage::MyProperty(int32_t) {
		throw hresult_not_implemented();
	}

	void DatabasePage::AddTableRowDefinition() {
		auto rowDefinition = Microsoft::UI::Xaml::Controls::RowDefinition();
		rowDefinition.Height(Microsoft::UI::Xaml::GridLengthHelper::Auto());
		this->table().RowDefinitions().Append(rowDefinition);
	}
	void DatabasePage::AddTableColumnDefinition() {
		auto columnDefinition = Microsoft::UI::Xaml::Controls::ColumnDefinition();
		columnDefinition.Width(Microsoft::UI::Xaml::GridLengthHelper::Auto());
		this->table().ColumnDefinitions().Append(columnDefinition);
	}
	void DatabasePage::AddTableValue(hstring value, int32_t row, int32_t column) {
		auto resources = this->Resources();
		auto style = resources.Lookup(box_value(L"TableBlockText")).as<Microsoft::UI::Xaml::Style>();
		auto textBlock = Microsoft::UI::Xaml::Controls::TextBlock();
		textBlock.Style(style);

		textBlock.Text(to_hstring(value));

		Microsoft::UI::Xaml::Controls::Grid::SetRow(textBlock, row);
		Microsoft::UI::Xaml::Controls::Grid::SetColumn(textBlock, column);

		this->table().Children().Append(textBlock);
	}

	Microsoft::UI::Xaml::Controls::TextBlock DatabasePage::CreateOutputText(hstring text) {
		auto resources = this->Resources();
		auto textBlockStyle = resources.Lookup(box_value(L"OutputBlockText")).as<Microsoft::UI::Xaml::Style>();

		auto textBlock = Microsoft::UI::Xaml::Controls::TextBlock();
		textBlock.Style(textBlockStyle);
		textBlock.Text(text);

		return textBlock;
	}

	Microsoft::UI::Xaml::Controls::ScrollViewer DatabasePage::CreateOutputTextBlock(Microsoft::UI::Xaml::Controls::TextBlock textBlock, int32_t row, int32_t column) {
		auto resources = this->Resources();
		auto scrollViewerStyle = resources.Lookup(box_value(L"OutputBlockTextBlock")).as<Microsoft::UI::Xaml::Style>();

		auto scrollViewer = Microsoft::UI::Xaml::Controls::ScrollViewer();

		scrollViewer.Style(scrollViewerStyle);
		scrollViewer.Content(textBlock);
		Microsoft::UI::Xaml::Controls::Grid::SetRow(scrollViewer, row);
		Microsoft::UI::Xaml::Controls::Grid::SetColumn(scrollViewer, column);

		return scrollViewer;
	}

	void DatabasePage::AddOutputValue(hstring status, hstring query, hstring message) {
		auto resources = this->Resources();
		auto scrollViewerStyle = resources.Lookup(box_value(L"OutputBlockTextBlock")).as<Microsoft::UI::Xaml::Style>();

		auto statusTextBlock = this->CreateOutputText(status);
		auto queryTextBlock = this->CreateOutputText(query);
		auto messageTextBlock = this->CreateOutputText(message);

		auto rowIndex = this->output().RowDefinitions().Size();

		auto rowDefinition = Microsoft::UI::Xaml::Controls::RowDefinition();
		rowDefinition.Height(Microsoft::UI::Xaml::GridLengthHelper::Auto());
		this->output().RowDefinitions().Append(rowDefinition);

		auto statusScrollViewer = this->CreateOutputTextBlock(statusTextBlock, rowIndex, 0);
		auto queryScrollViewer = this->CreateOutputTextBlock(queryTextBlock, rowIndex, 1);
		auto messageScrollViewer = this->CreateOutputTextBlock(messageTextBlock, rowIndex, 2);

		this->output().Children().Append(statusScrollViewer);
		this->output().Children().Append(queryScrollViewer);
		this->output().Children().Append(messageScrollViewer);
	}

	void DatabasePage::SqlQueryHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		if (m_database->IsConnect()) {
			auto sqlQueryText = sqlQueryInput().Text();

			auto queryResult = m_database->ExecuteQuery(to_string(sqlQueryText));

			if (queryResult->IsSuccess()) {
				this->AddTableRowDefinition();
				this->table().Children().Clear();

				for (auto column = 0ul; column < queryResult->GetColumnCount(); column++) {
					this->AddTableColumnDefinition();
					auto value = queryResult->GetColumnLabel(column);
					this->AddTableValue(to_hstring(value), 0, column);
				}

				for (auto row = 0ul; row < queryResult->GetRowCount(); row++) {
					this->AddTableRowDefinition();

					for (auto column = 0ul; column < queryResult->GetColumnCount(); column++) {
						this->AddTableColumnDefinition();

						auto value = queryResult->GetValue(row, column);

						this->AddTableValue(to_hstring(value), row + 1, column);
					}
				}

				this->AddOutputValue(L"Успешно", sqlQueryText, to_hstring(hstring(L"Успешно получено ") + to_hstring(queryResult->GetRowCount()) + hstring(L" строки")));
			} else {
				auto error = queryResult->GetError();
				this->AddOutputValue(L"Ошибка", sqlQueryText, to_hstring(error));
			}

			queryResult->Release();
		}
	}
}