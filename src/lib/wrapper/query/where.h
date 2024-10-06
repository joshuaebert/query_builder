//
// Created by joshua-tim.ebert on 12.08.2024.
//

#ifndef WHERE_H
#define WHERE_H
#include <functional>

#include "../util/operation_utils.h"
#include "chain.h"

namespace wrapper::query {
    struct query_builder;
}

namespace wrapper::query::types {

    /**
     * Creates a where clause
     * @param functor: a functor such as @see{not_op}
     * @return a function that constructs a where clause
     */
    inline auto where(std::function<query_builder&(query_builder &)> &&functor) noexcept {
        return [&functor](query_builder &qb) -> query_builder &{
            return qb.where(std::move(functor));
        };
    }

    /**
     * TODO: should be the standard function signature
     * @param functor
     * @return
     */
    auto where(std::invocable<query_builder&> auto &&functor) noexcept {
        return [&functor](query_builder &qb) -> query_builder &{
            functor(qb);
            return qb;
        };
    }

    /**
     * Creates a where clause
     * @param column: the column you want to check
     * @param op_code: the operation you want to use
     * @param value: the expected (or not expected) value
     * @return a function that constructs a where clause
     */
    inline auto where(std::string_view column, comparision_operation op_code, std::string_view value) noexcept {
        return [column, op_code, value](query_builder &qb) -> query_builder &{
            return qb.where(column, op_code, value);
        };
    }
}

namespace wrapper::query::types::chained {
    /**
     * Represents a chained where clause construction
     */
    using chained_builder = query_builder;

    /**
     * @param chained instance of a query_builder (chained_builder)
     * @return the original query_builder containing the chained where query
     */
    inline auto where(const query_builder &chained) {
        return [chained](query_builder &qb) -> query_builder &{
            //qb += chained;
            return qb;
        };
    }
}


#endif //WHERE_H
