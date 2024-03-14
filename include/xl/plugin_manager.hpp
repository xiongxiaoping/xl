#pragma once

#include "define.hpp"
#include "noncopyable.hpp"
#include "plugin.hpp"

XL_NAMESPACE_BEGIN

class plugin_manager : public noncopyable {
private:
    plugin_manager();

public:
    static plugin_manager &instance();

    err_code_t load_plugin(const std::string &path);

    err_code_t unload_plugin(const std::string &path);

private:
    class impl;
    std::unique_ptr<impl> impl_;
};

XL_NAMESPACE_END
