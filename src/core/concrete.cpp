#include "concrete.hpp"

XL_NAMESPACE_BEGIN

concrete_base::~concrete_base()
{}

const gid_t &concrete_base::gid() const
{
    return gid_;
}

const cid_t &concrete_base::cid() const
{
    return cid_;
}

XL_NAMESPACE_END
