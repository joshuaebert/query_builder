//
// Created by Joshua Ebert on 06.08.24.
//

#include "connector.h"
#include "pqxx/pqxx"

namespace wrapper {

    void postgres_connector::connect() noexcept {
        if (details.empty()) {
            return;
        }

        pqxx_connection = std::make_unique<pqxx::connection>(
                std::format("user={} "
                            "host={} "
                            "port={} "
                            "dbname={} "
                            "password={}",
                            details.user,
                            details.host,
                            details.port,
                            details.dbname,
                            details.password)
        );
    }

    void postgres_connector::disconnect() noexcept {
        if (!pqxx_connection) {
            return;
        }
        pqxx_connection->close();
    }

    void postgres_connector::set_connection_details(const connection_details &connection_details) noexcept {
        details = connection_details;
    }

    postgres_connector::~postgres_connector() {
        if (!pqxx_connection) {
            return;
        }

        pqxx_connection->close();
    }

    postgres_connector::postgres_connector() : pqxx_connection{nullptr} {
    }

    auto postgres_connector::is_connected() const noexcept -> bool {
        return pqxx_connection->is_open();
    }

    void mock_connector::connect() noexcept {
        if (details.empty()) {
            return;
        }
        connected = true;
    }

    void mock_connector::disconnect() noexcept {
        if (!connected) {
            return;
        }
        connected = false;
    }

    void mock_connector::set_connection_details(const connection_details &connection_details) noexcept {
        details = connection_details;
    }

    auto mock_connector::is_connected() const noexcept -> bool {
        return connected;
    }

    mock_connector::~mock_connector() {
        if (!connected) {
            return;
        }
        connected = false;
    }
} // wrapper