#pragma once

#include "noncopyable.hpp"
#include "concrete.hpp"

namespace xl {

class engine : public noncopyable {
private:
    engine();
    
public:
    static engine &instance();

    int32_t regist(concrete_hdl hdl);

    int32_t unregist(concrete_hdl hdl);

    std::vector<concrete_hdl> query(const gid_t &gid) const;
    
private:
    class impl;
    std::unique_ptr<impl> impl_;
};

} // namespace xl
