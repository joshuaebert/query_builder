//
// Created by Joshua Ebert on 07.08.24.
//
#include "../lib/wrapper/connector.h"

auto main() -> int {
    wrapper::connector_type auto conn = wrapper::make_connector<wrapper::postgres_connector>();
    conn.set_connection_details(wrapper::connection_details{
            .host = "localhost",
            .port = 1337,
            .user = "postgres",
            .password = "",
            .dbname = "postgres"});
    conn.connect();

    return 0;
}