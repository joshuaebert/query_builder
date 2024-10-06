//
// Created by joshua-tim.ebert on 12.08.2024.
//

#include "query_builder.h"
#include <ranges>

#include "util/order_utils.h"

namespace wrapper::query {
    auto query_builder::select_all() noexcept -> query_builder & {
        add_to_query("SELECT *");
        return *this;
    }

    auto query_builder::select(const std::initializer_list<std::string_view> &columns) noexcept -> query_builder & {
        add_to_query("SELECT");

        for (const auto &column: columns | std::views::take(columns.size() - 1)) {
            add_to_query(std::format("{},", column));
        }
        add_to_query(*(columns.end() - 1));
        return *this;
    }

    auto query_builder::from_tables(const std::initializer_list<std::string_view> &tables) noexcept -> query_builder & {
        add_to_query("FROM");

        if (tables.size() == 1) {
            const auto table = *tables.begin();
            add_to_query(table);
            return *this;
        }

        for (const auto &column: tables | std::views::take(tables.size() - 1)) {
            add_to_query(std::format("{},", column));
        }
        add_to_query(*(tables.end() - 1)); //kinda cursed
        return *this;
    }

    auto query_builder::raw(std::string_view raw) noexcept -> query_builder & {
        add_to_query(raw);
        return *this;
    }

    auto query_builder::where(std::string_view column, comparision_operation op_code,
                              std::string_view value) noexcept -> query_builder & {
        add_to_query(std::format("WHERE {} {} '{}'", column, op_code_to_string(op_code), value));
        return *this;
    }

    auto query_builder::where(std::function<query_builder &(query_builder &)> &&functor) noexcept -> query_builder & {
        add_to_query("WHERE");

        return std::invoke_r<query_builder &>(functor, *this);
    }

    auto query_builder::order_by(std::initializer_list<std::string_view> columns,
                                 sort_order order) noexcept -> query_builder & {
        add_to_query("ORDER BY");

        if (columns.size() == 1) {
            const auto column = *columns.begin();
            add_to_query(column);
        } else {
            for (const auto &column: columns | std::views::take(columns.size() - 1)) {
                add_to_query(std::format("{},", column));
            }
            add_to_query(*(columns.end() - 1)); //kinda cursed
        }

        add_to_query(sort_order_to_string(order));

        return *this;
    }

    auto query_builder::order_by(std::initializer_list<order_pair> column_order_list) noexcept -> query_builder & {
        add_to_query("ORDER BY");
        if (column_order_list.size() == 1) {
            const auto [column, order] = *column_order_list.begin();

            add_to_query(std::format("{} {}", column, sort_order_to_string(order)));
            return *this;
        }

        for (const auto &[column, order]: column_order_list | std::views::take(column_order_list.size() - 1)) {
            add_to_query(std::format("{} {},", column, sort_order_to_string(order)));
        }
        const auto [column, order] = *(column_order_list.end() - 1);
        add_to_query(std::format("{} {}", column, sort_order_to_string(order)));

        return *this;
    }

    auto query_builder::not_op(std::string_view column, comparision_operation op_code,
                               std::string_view value) noexcept -> query_builder & {
        add_to_query(std::format("NOT ({} {} '{}')", column, op_code_to_string(op_code), value));
        return *this;
    }

    auto query_builder::compare(std::string_view column, comparision_operation op_code,
                               std::string_view value) noexcept -> query_builder & {
        add_to_query(std::format("({} {} '{}')", column, op_code_to_string(op_code), value));
        return *this;
    }

    auto query_builder::add_to_query(std::string_view q) noexcept -> void {
        if (query.empty()) {
            query += std::format("{}", q);
        } else {
            query += std::format(" {}", q);
        }
    }
}
