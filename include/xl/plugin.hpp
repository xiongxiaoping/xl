#pragma once

#include "concrete.hpp"

namespace xl {

class plugin {
public:
    virtual ~plugin() = default;

    virtual err_code_t init() = 0;

    virtual err_code_t release() = 0;

    void add_concrete(concrete_hdl hdl);

    void remove_concrete(concrete_hdl hdl);

    const std::vector<concrete_hdl> &get_concretes() const;

private:
    std::vector<concrete_hdl> concretes_;
};

using plugin_instance_function = plugin *(*)();

} // namespace xl

#define XL_NAME_CAT_(a, b) a##b

#define XL_NAME_CAT(a, b) XL_NAME_CAT_(a, b)

#define PLUGIN_INSTANCE_FUNCTION_NAME "xl_plugin_instance"

#define DECLARE_PLUGIN(plugin_name) \
    extern "C" ::xl::plugin *xl_plugin_instance();

#define IMPLEMENT_PLUGIN(plugin_name) \
    ::xl::plugin *xl_plugin_instance() \
    { \
        static plugin_name ins; \
        return &ins; \
    }

#define ADD_CONCRETE(gid, cid, func) \
    namespace { \
        static struct XL_NAME_CAT(add_concrete_, __LINE__) { \
            XL_NAME_CAT(add_concrete_, __LINE__)() { \
                xl_plugin_instance()->add_concrete(xl::make_concrete(gid, cid, func)); \
            } \
        } XL_NAME_CAT(instance_, __LINE__); \
    } 

#define ADD_CONCRETE_MF(gid, cid, c, memfunc) \
    namespace { \
        static struct XL_NAME_CAT(add_concrete_, __LINE__) { \
            XL_NAME_CAT(add_concrete_, __LINE__)() { \
                xl_plugin_instance()->add_concrete(xl::make_concrete(gid, cid, c, memfunc)); \
            } \
        } XL_NAME_CAT(instance_, __LINE__); \
    }
