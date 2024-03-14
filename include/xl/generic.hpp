#pragma once

#include <string>
#include <optional>

#include "invoker.hpp"

namespace xl {

template<typename...>
struct generic;

template<typename Ret, typename... ArgsIn, typename... ArgsOut>
struct generic<Ret, params_in<ArgsIn...>, params_out<ArgsOut...>> {
public:
    generic(const std::string &gid) : gid_(gid) {}

    using generic_ret = std::conditional_t<std::is_void_v<Ret>,
        int32_t,
        std::pair<int32_t, std::optional<Ret>>>;

    generic_ret operator()(ArgsIn... in, ArgsOut... out) const noexcept {
        return invoker_sync<Ret, params_in<ArgsIn...>, params_out<ArgsOut...>>()(gid_, in..., out...);
    }
    
private:
    std::string gid_;
};

template<typename... ArgsIn, typename... ArgsOut>
struct generic<params_in<ArgsIn...>, params_out<ArgsOut...>>
    : generic<void, params_in<ArgsIn...>, params_out<ArgsOut...>>
{
    explicit generic(const std::string &gid)
        : generic<void, params_in<ArgsIn...>, params_out<ArgsOut...>>(gid)
    {}
};

template<typename Ret, typename... ArgsIn>
struct generic<Ret, params_in<ArgsIn...>>
    : generic<Ret, params_in<ArgsIn...>, params_out<>>
{
    explicit generic(const std::string &gid)
        : generic<Ret, params_in<ArgsIn...>, params_out<>>(gid)
    {}
};

template<typename... ArgsIn>
struct generic<params_in<ArgsIn...>>
    : generic<void, params_in<ArgsIn...>, params_out<>>
{
    explicit generic(const std::string &gid)
        : generic<void, params_in<ArgsIn...>, params_out<>>(gid)
    {}
};

template<typename Ret, typename... ArgsOut>
struct generic<Ret, params_out<ArgsOut...>>
    : generic<Ret, params_in<>, params_out<ArgsOut...>>
{
    explicit generic(const std::string &gid)
        : generic<Ret, params_in<>, params_out<ArgsOut...>>(gid)
    {}
};

template<typename... ArgsOut>
struct generic<params_out<ArgsOut...>>
    : generic<void, params_in<>, params_out<ArgsOut...>>
{
    explicit generic(const std::string &gid)
        : generic<void, params_in<>, params_out<ArgsOut...>>(gid)
    {}
};

} // namespace xl
