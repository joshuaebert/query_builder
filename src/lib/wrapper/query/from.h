//
// Created by joshua-tim.ebert on 12.08.2024.
//

#ifndef FROM_H
#define FROM_H

namespace wrapper::query {
    struct query_builder;
}

namespace wrapper::query::types {

    /**
     * Sets a specific table
     * @see{from_table}
     * @param table: the table you want to select
     */
    inline auto from(std::string_view table) noexcept {
        return [table](query_builder &qb) -> query_builder &{
            return qb.from_tables({table});
        };
    }

    /**
     * Sets tables
     * @see{from_tables}
     * @param tables: the tables you want to select
     */
    inline auto from(std::initializer_list<std::string_view> tables) noexcept {
        return [tables](query_builder &qb) -> query_builder &{
            return qb.from_tables(tables);
        };
    }
}

#endif //FROM_H
