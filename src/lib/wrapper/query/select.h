//
// Created by joshua-tim.ebert on 12.08.2024.
//

#ifndef SELECT_H
#define SELECT_H

namespace wrapper::query {
    struct query_builder;
}

namespace wrapper::query::types {

    /**
     * Selects all columns
     * @see{select_all}
     */
    inline auto select() noexcept {
        return [](query_builder &qb) -> query_builder & {
            qb.select_all();
            return qb;
        };
    }

    /**
     * Select specific columns
     * @see{select}
     * @param columns: the columns you want to select
     */
    inline auto select(std::initializer_list<std::string_view> columns) noexcept {
        return [columns](query_builder &qb) -> query_builder & {
            qb.select(columns);
            return qb;
        };
    }

    /**
     * Select a specific column
     * @see{select}
     * @param column: the column you want to select
     */
    inline auto select(std::string_view column) noexcept {
        return [column](query_builder &qb) -> query_builder & {
            qb.select({column});
            return qb;
        };
    }
}

#endif //SELECT_H
