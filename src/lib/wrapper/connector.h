//
// Created by Joshua Ebert on 06.08.24.
//

#ifndef PQXX_TEST_CONNECTOR_H
#define PQXX_TEST_CONNECTOR_H

#include <string>
#include <type_traits>
#include <memory>

/* forward declarations */
namespace pqxx {
    class connection;
}

namespace wrapper {

    struct connector;

    template<typename T>
    concept connector_type = std::is_base_of_v<connector, T>;

    template<connector_type T>
    [[nodiscard]] static auto make_connector() noexcept -> T {
        return T{};
    }

    struct connection_details {
        std::string host{};
        int port{};
        std::string user{};
        std::string password{};
        std::string dbname{};

        [[nodiscard]] auto empty() const noexcept -> bool {
            return host.empty() || port == 0 || user.empty() || password.empty() || dbname.empty();
        }
    };

    struct connector {
    protected:
        virtual void connect() noexcept = 0;

        [[nodiscard]] virtual auto is_connected() const noexcept -> bool = 0;

        virtual void disconnect() noexcept = 0;

        virtual void set_connection_details(const connection_details &connection_details) noexcept = 0;

        virtual ~connector() = default;
    };

    struct postgres_connector : connector {
        void connect() noexcept override;

        [[nodiscard]] auto is_connected() const noexcept -> bool override;

        void disconnect() noexcept override;

        void set_connection_details(const connection_details &connection_details) noexcept override;

        ~postgres_connector() override;

    private:
        explicit postgres_connector();

        template<connector_type T>
        friend auto make_connector() noexcept -> T;

        connection_details details;
        std::unique_ptr<pqxx::connection> pqxx_connection;
    };

    struct mock_connector : connector {
        void connect() noexcept override;

        void disconnect() noexcept override;

        void set_connection_details(const connection_details &connection_details) noexcept override;

        [[nodiscard]] auto is_connected() const noexcept -> bool override;

        ~mock_connector() override;

    private:
        explicit mock_connector() = default;

        template<connector_type T>
        friend auto make_connector() noexcept -> T;

        connection_details details;
        bool connected{};
    };
} // wrapper

#endif //PQXX_TEST_CONNECTOR_H
