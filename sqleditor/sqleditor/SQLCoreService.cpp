#include "pch.h"

#include "SQLCoreService.h"

namespace winrt::sqleditor::services {
	SQLCoreService* SQLCoreService::Instance() noexcept {
		static SQLCoreService instance;
		return &instance;
	}

	SQLCore::IDatabase* SQLCoreService::Connection(hstring _database) noexcept {
		for (auto connection : m_factory->GetConnections()) {
			std::wstringstream stream;
			stream << connection;
			if (stream.str() == _database) {
				return connection;
			}
		}
		return nullptr;
	}

	SQLCore::IFactory* SQLCoreService::Factory() noexcept {
		return m_factory;
	}
}