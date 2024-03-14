#pragma once

#include <xl/plugin.hpp>

class plugin_sample : public xl::plugin {
public:
    virtual xl::err_code_t init() override;

    virtual xl::err_code_t release() override;
};

DECLARE_PLUGIN()
