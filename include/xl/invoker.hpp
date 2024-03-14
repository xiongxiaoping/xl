#pragma once

#include <optional>

#include "engine.hpp"

namespace xl {

template<typename...>
struct invoker_sync;

template<typename Ret, typename... ArgsIn, typename... ArgsOut>
struct invoker_sync<Ret, params_in<ArgsIn...>, params_out<ArgsOut...>> {
    std::conditional_t<std::is_void_v<Ret>,
        int32_t,
        std::pair<int32_t, std::optional<Ret>>>
    operator()(const std::string &gid, ArgsIn... in, ArgsOut... out) const {
        auto hdls = engine::instance().query(gid);
        for (const auto &hdl : hdls) {
            auto conc = std::dynamic_pointer_cast<concrete<Ret, ArgsIn..., ArgsOut...>>(hdl);
            if (conc != nullptr) {
                if constexpr (std::is_void_v<Ret>) {
                    (*conc)(in..., out...);
                    return 0;
                } else {
                    return std::make_pair(0, (*conc)(in..., out...));
                }
            }
        }
        
        if constexpr (std::is_void_v<Ret>) {
            return -1;
        } else {
            return std::make_pair(-1, std::nullopt);
        }
    }
};

} // namespace xl
