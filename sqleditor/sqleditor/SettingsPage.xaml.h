#pragma once

#include "SettingsPage.g.h"

#include "NavigationService.h"
#include "SQLCoreService.h"

namespace winrt::sqleditor::implementation {
	struct SettingsPage : SettingsPageT<SettingsPage> {
		SettingsPage() {
			this->InitializeComponent();
		}

		int32_t MyProperty();
		void MyProperty(int32_t);
	};
}

namespace winrt::sqleditor::factory_implementation {
	struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage> {};
}
