set(target_name ${project_name}_lib)
set(sources wrapper/connector.cpp wrapper/connector.h wrapper/transaction.h
        wrapper/query_builder.h
        wrapper/query_builder.cpp
        wrapper/util/operation_utils.h
        wrapper/util/operation_utils.h
        wrapper/query/where.h
        wrapper/query/select.h
        wrapper/query_types.h
        wrapper/query/from.h
        wrapper/query/order.h
        wrapper/util/operation_utils.h
        wrapper/util/order_utils.h
        wrapper/query/chain.h
)

find_package(PostgreSQL REQUIRED)

include_directories(${PostgreSQL_INCLUDE_DIRS})

add_library(${target_name} STATIC ${sources})

target_link_libraries(${target_name} PRIVATE pqxx ${PostgreSQL_Libraries})