#include "pch.h"
#include "SettingsPage.xaml.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::sqleditor::implementation {
	int32_t SettingsPage::MyProperty() {
		throw hresult_not_implemented();
	}

	void SettingsPage::MyProperty(int32_t) {
		throw hresult_not_implemented();
	}
}
