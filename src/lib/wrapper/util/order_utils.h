//
// Created by joshua-tim.ebert on 13.08.2024.
//

#ifndef SORT_ORDER_H
#define SORT_ORDER_H
#include <utility>

enum class sort_order {
    asc, desc
};

inline auto sort_order_to_string(sort_order order) {
    const auto to_string = [order] {
        using enum sort_order;
        switch (order) {
            case asc:
                return "ASC";
            case desc:
                return "DESC";
        }
        std::unreachable();
    };
    return std::invoke(to_string);
}

struct order_pair {
    std::string_view column;
    sort_order order = sort_order::asc;
};

#endif //SORT_ORDER_H
