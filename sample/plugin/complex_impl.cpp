#include "complex.hpp"

#include "plugin_sample.hpp"

namespace xl {
namespace sample {

complex_t complex_add_impl(const complex_t &x, const complex_t &y)
{
    return {x.real + y.real, x.image + y.image};
}
ADD_CONCRETE(complex_add::GID, "normal", complex_add_impl);

struct complex_subtract_impl {
    complex_t operator()(const complex_t &x, const complex_t &y) const {
        return {x.real - y.real, x.image - y.image};
    }
} g_subtract;
ADD_CONCRETE_MF(complex_subtract::GID, "operator() const",
    &g_subtract, &complex_subtract_impl::operator());

}
}
