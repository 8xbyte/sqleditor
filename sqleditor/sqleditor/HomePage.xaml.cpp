#include "pch.h"
#include "HomePage.xaml.h"
#if __has_include("HomePage.g.cpp")
#include "HomePage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::sqleditor::implementation {
	int32_t HomePage::MyProperty() {
		throw hresult_not_implemented();
	}

	void HomePage::MyProperty(int32_t) {
		throw hresult_not_implemented();
	}

	void HomePage::AddConnectionHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		m_navigationService->Navigate(L"Add");
	}
}