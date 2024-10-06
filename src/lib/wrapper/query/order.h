//
// Created by joshua-tim.ebert on 13.08.2024.
//

#ifndef ORDER_H
#define ORDER_H
#include <initializer_list>

#include "../query_builder.h"
#include "../util/order_utils.h"

namespace wrapper::query {
    struct query_builder;
}

namespace wrapper::query::types {
    inline auto order_by(std::initializer_list<std::string_view> columns, sort_order order = sort_order::asc) noexcept {
        return [columns, order](query_builder &qb) -> query_builder & {
            return qb.order_by(columns, order);
        };
    }

    inline auto order_by(std::string_view column, sort_order order = sort_order::asc) noexcept {
        return order_by({column}, order);
    }

    inline auto order_by(std::initializer_list<order_pair> columns_orders) noexcept {
        return [columns_orders](query_builder &qb) -> query_builder & {
            return qb.order_by(columns_orders);
        };
    }
}

#endif //ORDER_H
