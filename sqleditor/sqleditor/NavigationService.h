#pragma once

namespace winrt::sqleditor::services {
	class NavigationService {
	public:
		explicit NavigationService() noexcept : m_dispatcherQueue(Microsoft::UI::Dispatching::DispatcherQueue::GetForCurrentThread()) {}

		static NavigationService* Instance() noexcept;

		Microsoft::UI::Dispatching::DispatcherQueue DispatcherQueue() noexcept;
		void DispatcherQueue(Microsoft::UI::Dispatching::DispatcherQueue dispatcherQueue) noexcept;

		Microsoft::UI::Xaml::Controls::Frame Frame() noexcept;
		void Frame(Microsoft::UI::Xaml::Controls::Frame frame) noexcept;

		Microsoft::UI::Xaml::Controls::NavigationView NavigationView() noexcept;
		void NavigationView(Microsoft::UI::Xaml::Controls::NavigationView navigationView) noexcept;

		void Navigate(hstring tag) noexcept;
		Microsoft::UI::Xaml::Controls::NavigationViewItem SelectedView() noexcept;
		void AddView(hstring content, hstring tag) noexcept;

	private:
		Microsoft::UI::Dispatching::DispatcherQueue m_dispatcherQueue;
		Microsoft::UI::Xaml::Controls::NavigationView m_navigationView;
		Microsoft::UI::Xaml::Controls::Frame m_frame;
	};
}