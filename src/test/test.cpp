//
// Created by Joshua Ebert on 07.08.24.
//
#include "gtest/gtest.h"
#include "../lib/wrapper/connector.h"
#include "../lib/wrapper/transaction.h"
#include "../lib/wrapper/util/operation_utils.h"
#include "../lib/wrapper/query_types.h"

TEST(pqxx_test, connect) {
    wrapper::connector_type auto conn = wrapper::make_connector<wrapper::postgres_connector>();

    ASSERT_FALSE(conn.is_connected()) << "Connection should not be established yet!";
    conn.connect();
    ASSERT_FALSE(conn.is_connected()) << "No connection details set but connection was established!";
    conn.set_connection_details(wrapper::connection_details{
        .host = "mock",
        .port = 1337,
        .user = "mock",
        .password = "mock",
        .dbname = "mock"
    });
    conn.connect();
    ASSERT_TRUE(conn.is_connected()) << "Connection should be est established!";
}

TEST(pqxx_test, builder) {
    using namespace wrapper::query;
    using namespace wrapper::query::types;

    wrapper::connector_type auto conn = wrapper::make_connector<wrapper::mock_connector>();
    wrapper::transaction transaction{conn};

    using enum comparision_operation;

    auto builder = transaction.builder()
                   | select({"test", "test2"})
                   | from("test_table")
                   | where([](query_builder &qb) {
                       qb
                        | and_op("test", geq, "10");
                   })
                   | and_op("test2", eq, "11")
                   | order_by({{.column = "test"}, {.column = "test2", .order = sort_order::desc}});

    const auto query = builder.build();
    ASSERT_EQ(
        query,
        "SELECT test, test2 FROM test_table WHERE NOT (test >= '10') ORDER BY test ASC, test2 DESC"
    );
}
