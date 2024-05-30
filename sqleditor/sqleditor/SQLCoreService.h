#pragma once

#include <sqlcore/factory.hpp>

namespace winrt::sqleditor::services {
	class SQLCoreService {
	public:
		explicit SQLCoreService() noexcept {
			m_factory = SQLCore::CreateFactory(SQLCore::FactoryType::MultiThreaded);
			m_factory->EnablePreloadPlugins();
		}

		static SQLCoreService* Instance() noexcept;

		SQLCore::IDatabase* Connection(hstring _database) noexcept;
		SQLCore::IFactory* Factory() noexcept;

		~SQLCoreService() noexcept {
			m_factory->Release();
		}

	private:
		SQLCore::IFactory* m_factory;
	};
}