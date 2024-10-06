//
// Created by joshua-tim.ebert on 12.08.2024.
//

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <string>
#include <utility>

namespace wrapper::query {
    enum class arithmetic_operation {
        add, sub, mul, div, mod
    };

    enum class bitwise_operation {
        bit_and, bit_or, bit_xor
    };

    enum class comparision_operation {
        eq, neq, gt, lt, geq, leq,
    };

    template<typename T>
    concept operation_type = std::is_same_v<T, arithmetic_operation> || std::is_same_v<T, bitwise_operation> ||
                        std::is_same_v<T, comparision_operation>;

    inline auto op_code_to_string(arithmetic_operation op_code) noexcept -> std::string {
        using enum arithmetic_operation;
        const auto to_string = [&op_code] {
            switch (op_code) {
                case add:
                    return "+";
                case sub:
                    return "-";
                case mul:
                    return "*";
                case div:
                    return "/";
                case mod:
                    return "%";
            }
            std::unreachable();
        };

        return std::invoke(to_string);
    }

    inline auto op_code_to_string(bitwise_operation op_code) noexcept -> std::string {
        using enum bitwise_operation;
        const auto to_string = [&op_code] {
            switch (op_code) {
                case bit_and:
                    return "&";
                case bit_or:
                    return "|";
                case bit_xor:
                    return "^";
            }
            std::unreachable();
        };

        return std::invoke(to_string);
    }

    inline auto op_code_to_string(comparision_operation op_code) noexcept -> std::string {
        using enum comparision_operation;
        const auto to_string = [&op_code] {
            switch (op_code) {
                case eq:
                    return "=";
                case neq:
                    return "<>";
                case gt:
                    return ">";
                case lt:
                    return "<";
                case geq:
                    return ">=";
                case leq:
                    return "<=";
            }
            std::unreachable();
        };

        return std::invoke(to_string);
    }
}


#endif //OPERATIONS_H
