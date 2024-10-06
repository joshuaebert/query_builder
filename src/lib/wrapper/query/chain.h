//
// Created by joshua-tim.ebert on 13.08.2024.
//

#ifndef CHAIN_H
#define CHAIN_H

namespace wrapper::query {
    struct query_builder;
}

namespace wrapper::query::types {
    inline auto compare(std::string_view column, comparision_operation op_code, std::string_view value) noexcept {
        return [column, op_code, value](query_builder &qb) -> query_builder &{
            return qb.compare(column, op_code, value);
        };
    }

    inline auto not_op(std::string_view column, comparision_operation op_code, std::string_view value) noexcept {
        return [column, op_code, value](query_builder &qb) -> query_builder &{
            return qb.not_op(column, op_code, value);
        };
    }

    inline auto and_op(std::string_view column, comparision_operation op_code, std::string_view value) noexcept {
        return [column, op_code, value](query_builder &qb) -> query_builder &{
            return qb.compare(column, op_code, value);
        };
    }
}

/*namespace wrapper::query::types::chained {

    struct chained_query {

        template<typename Functor> requires std::invocable<Functor, chained_query &>
        friend auto operator|(chained_query &cq, Functor &&functor) -> chained_query & {
            return functor(cq);
        }

        template<typename Functor> requires std::invocable<Functor, chained_query &>
        friend auto operator|(chained_query &&cq, Functor &&functor) -> chained_query & {
            return functor(cq);
        }

        [[nodiscard]] auto get() const noexcept {
            return query;
        }
        std::string query{};
    };

    auto compare_op(std::string_view column, comparision_operation op_code, std::string_view value) noexcept {
        return [column, op_code, value, this](chained_query &cb) -> chained_query &{
            cb.query += std::format("WHERE {} {} {}", column, op_code_to_string(op_code), value);
            return cb;
        };
    }
}*/

#endif //CHAIN_H
