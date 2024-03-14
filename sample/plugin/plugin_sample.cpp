#include "plugin_sample.hpp"

xl::err_code_t plugin_sample::init()
{
    return 0;
}

xl::err_code_t plugin_sample::release()
{
    return 0;
}

IMPLEMENT_PLUGIN(plugin_sample)
