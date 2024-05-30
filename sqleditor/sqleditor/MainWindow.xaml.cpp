#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::sqleditor::implementation {
	int32_t MainWindow::MyProperty() {
		throw hresult_not_implemented();
	}

	void MainWindow::MyProperty(int32_t) {
		throw hresult_not_implemented();
	}

	void MainWindow::ChangeViewHandler(Microsoft::UI::Xaml::Controls::NavigationView const& sender, Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args) {
		auto tag = args.SelectedItemContainer().Tag().as<hstring>();
		m_navigationService->Navigate(tag);
	}
}
