#pragma once

#include <xl/generic.hpp>

namespace xl {
namespace sample {

struct complex_t {
    double real;
    double image;
};

using complex_add_generic = xl::generic<
    complex_t,
    xl::params_in<const complex_t &, const complex_t &>>;
struct complex_add : complex_add_generic {
    static constexpr const char *GID = "complex_add";
    complex_add() : complex_add_generic(GID) {}
};

using complex_subtract_generic = xl::generic<
    complex_t,
    xl::params_in<const complex_t &, const complex_t &>>;
struct complex_subtract : complex_subtract_generic {
    static constexpr const char *GID = "complex_subtract";
    complex_subtract() : complex_subtract_generic(GID) {}
};

using complex_add_subtract_v1_generic = xl::generic<
    std::pair<complex_t, complex_t>,
    xl::params_in<complex_t const *, complex_t const *>>;
struct complex_add_subtract_v1 : complex_add_subtract_v1_generic {
    static constexpr const char *GID = "complex_add_subtract_v1";
    complex_add_subtract_v1() : complex_add_subtract_v1_generic(GID) {}
};

using complex_add_subtract_v2_generic = xl::generic<
    xl::params_in<const complex_t &, const complex_t &>,
    xl::params_out<complex_t &, complex_t &>>;
struct complex_add_subtract_v2 : complex_add_subtract_v2_generic {
    static constexpr const char *GID = "complex_add_subtract_v2";
    complex_add_subtract_v2() : complex_add_subtract_v2_generic(GID) {}
};

} // namespace sample
} // namespace xl

