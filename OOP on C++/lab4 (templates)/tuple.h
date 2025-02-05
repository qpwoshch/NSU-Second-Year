#ifndef TUPLE_H
#define TUPLE_H

#include <iostream>
#include <tuple>
#include <utility>


template <typename Tuple, std::size_t... Is>
void printTupleHelper(std::ostream& os, const Tuple& t, std::index_sequence<Is...>) {
    ((os << (Is == 0 ? "" : " ") << std::get<Is>(t)), ...);
}

template <typename... Args>
auto operator<<(std::ostream& os, const std::tuple<Args...>& t) -> std::ostream& {
    printTupleHelper(os, t, std::index_sequence_for<Args...>{});
    return os;
}

#endif // TUPLE_H