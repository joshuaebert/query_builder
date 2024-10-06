//
// Created by Joshua Ebert on 07.08.24.
//

#ifndef PQXX_TEST_TRANSACTION_H
#define PQXX_TEST_TRANSACTION_H

#include "connector.h"
#include "query_builder.h"

namespace wrapper {
    struct connector;

    namespace query {
        struct query_builder;
    }

    template<connector_type T>
    struct transaction {
        explicit transaction(const T &conn) noexcept;

        [[nodiscard]] auto builder() noexcept -> query::query_builder; //could be made static perhaps. We'll see

    private:
        //Holds no ownership
        const connector &conn;
    };

    template<connector_type T>
    transaction<T>::transaction(const T &conn) noexcept : conn{conn} {
    }

    template<connector_type T>
    auto transaction<T>::builder() noexcept -> query::query_builder {
        return query::query_builder{};
    }
} // wrapper

#endif //PQXX_TEST_TRANSACTION_H
