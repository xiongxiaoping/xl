#include "plugin.hpp"

XL_NAMESPACE_BEGIN

void plugin::add_concrete(concrete_hdl hdl)
{
    concretes_.emplace_back(hdl);
}

void xl::plugin::remove_concrete(concrete_hdl hdl)
{
    // todo
}

const std::vector<concrete_hdl> &plugin::get_concretes() const
{
    return concretes_;
}

XL_NAMESPACE_END
