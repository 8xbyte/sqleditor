#include "pch.h"

#include "NavigationService.h"

#include "HomePage.xaml.h"
#include "AddConnectionPage.xaml.h"
#include "SettingsPage.xaml.h"
#include "DatabasePage.xaml.h"

namespace winrt::sqleditor::services {
	NavigationService* NavigationService::Instance() noexcept {
		static NavigationService instance;
		return &instance;
	}

	Microsoft::UI::Dispatching::DispatcherQueue NavigationService::DispatcherQueue() noexcept {
		return m_dispatcherQueue;
	}
	void NavigationService::DispatcherQueue(Microsoft::UI::Dispatching::DispatcherQueue dispatcherQueue) noexcept {
		m_dispatcherQueue = dispatcherQueue;
	}

	Microsoft::UI::Xaml::Controls::Frame NavigationService::Frame() noexcept {
		return m_frame;
	}
	void NavigationService::Frame(Microsoft::UI::Xaml::Controls::Frame frame) noexcept {
		m_frame = frame;
	}

	Microsoft::UI::Xaml::Controls::NavigationView NavigationService::NavigationView() noexcept {
		return m_navigationView;
	}
	void NavigationService::NavigationView(Microsoft::UI::Xaml::Controls::NavigationView navigationView) noexcept {
		m_navigationView = navigationView;
	}

	void NavigationService::Navigate(hstring tag) noexcept {
		if (m_dispatcherQueue) {
			m_dispatcherQueue.TryEnqueue([this, tag] () {
				if (m_frame && m_navigationView) {
					for (auto const& menuItem : m_navigationView.MenuItems()) {
						if (auto navItem = menuItem.try_as<Microsoft::UI::Xaml::Controls::NavigationViewItem>()) {
							auto itemTag = navItem.Tag().as<hstring>();
							if (itemTag == tag) {
								m_navigationView.SelectedItem(navItem);
								break;
							}
						}
					}

					if (tag == L"Home") {
						m_frame.Navigate(xaml_typename<sqleditor::HomePage>());
					} else if (tag == L"Add") {
						m_frame.Navigate(xaml_typename<sqleditor::AddConnectionPage>());
					} else if (tag == L"Settings") {
						m_frame.Navigate(xaml_typename<sqleditor::SettingsPage>());
					} else {
						m_frame.Navigate(xaml_typename<sqleditor::DatabasePage>());
					}
				}
			});
		}
	}
	void NavigationService::AddView(hstring content, hstring tag) noexcept {
		if (m_dispatcherQueue) {
			m_dispatcherQueue.TryEnqueue([this, content, tag] () {
				if (m_navigationView) {
					auto navigationViewItem = Microsoft::UI::Xaml::Controls::NavigationViewItem();
					auto icon = Microsoft::UI::Xaml::Controls::FontIcon();
					icon.Glyph(L"\uE8CE");

					navigationViewItem.Icon(icon);
					navigationViewItem.Content(box_value(content));
					navigationViewItem.Tag(box_value(tag));

					m_navigationView.MenuItems().InsertAt(m_navigationView.MenuItems().Size() - 1, navigationViewItem);
				}
			});
		}
	}
	Microsoft::UI::Xaml::Controls::NavigationViewItem NavigationService::SelectedView() noexcept {
		return m_navigationView.SelectedItem().as<Microsoft::UI::Xaml::Controls::NavigationViewItem>();
	}
}