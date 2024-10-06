//
// Created by joshua-tim.ebert on 09.08.2024.
//

#ifndef QUERY_BUILDER_H
#define QUERY_BUILDER_H

#include <functional>
#include <format>

#include "util/operation_utils.h"
#include "util/order_utils.h"

namespace wrapper::query {
    struct query_builder {
        auto select_all() noexcept -> query_builder &;

        auto select(const std::initializer_list<std::string_view> &columns) noexcept -> query_builder &;

        auto from_tables(const std::initializer_list<std::string_view> &tables) noexcept -> query_builder &;

        auto raw(std::string_view raw) noexcept -> query_builder &;

        auto where(std::string_view column, comparision_operation op_code,
                   std::string_view value) noexcept -> query_builder &;

        auto where(
            std::function<query_builder &(query_builder &)> &&functor) noexcept -> query_builder &;

        auto order_by(std::initializer_list<std::string_view> columns, sort_order order) noexcept -> query_builder &;

        auto order_by(std::initializer_list<order_pair> column_order_list) noexcept -> query_builder &;

        auto not_op(std::string_view column, comparision_operation op_code,
                    std::string_view value) noexcept -> query_builder &;

        auto compare(std::string_view column, comparision_operation op_code,
                     std::string_view value) noexcept -> query_builder &;

        /**
         * @brief Builds the query string
         * @return The query string
         */
        [[nodiscard]]
        auto build() const noexcept {
            return query;
        }

        template<typename Functor>
            requires std::invocable<Functor, query_builder &>
        friend auto operator|(query_builder &qb, Functor &&functor) noexcept -> query_builder & {
            return functor(qb);
        }

        template<typename Functor>
            requires std::invocable<Functor, query_builder &>
        friend auto operator|(query_builder &&qb, Functor &&functor) noexcept -> query_builder & {
            return functor(qb);
        }

    private:
        auto add_to_query(std::string_view q) noexcept -> void;

        std::string query{};
    };


    /**
     * Raw sql query
     * @see{raw}
     * @param raw: the sql query
     */
    inline auto raw = [](std::string_view raw) -> std::function<query_builder &(query_builder &)> {
        return [raw](query_builder &qb) -> query_builder &{
            return qb.raw(raw);
        };
    };
}

#endif //QUERY_BUILDER_H
