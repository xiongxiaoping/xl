#pragma once

#include "define.hpp"

XL_NAMESPACE_BEGIN

class concrete_base {
public:
    concrete_base(const gid_t &gid, const cid_t &cid)
        : gid_(gid), cid_(cid)
    {}
    virtual ~concrete_base() = 0;
    concrete_base(concrete_base &) = default;
    concrete_base &operator=(concrete_base &) = default;
    concrete_base(concrete_base &&) = default;
    concrete_base &operator=(concrete_base &&) = default;

    const gid_t &gid() const;
    const cid_t &cid() const;

private:
    gid_t gid_;
    cid_t cid_;
};

using concrete_hdl = std::shared_ptr<concrete_base>;

template<typename Ret, typename... Args>
class concrete : public concrete_base {
public:
    concrete(const std::string &gid, const std::string &cid, functor_t<Ret, Args...> func)
        : concrete_base(gid, cid), func_(func)
    {}

    Ret operator()(Args... args) const noexcept
    {
        return func_(args...);
    }

private:
    functor_t<Ret, Args...> func_;
};

template<typename Ret, typename... Args, typename F>
concrete_hdl make_concrete(const gid_t &gid, const cid_t &cid, F&& f)
{
    return std::make_shared<concrete<Ret, Args...>>(gid, cid, std::forward<F>(f));
}

template<typename Ret, typename... Args>
concrete_hdl make_concrete(const gid_t &gid, const cid_t &cid, Ret(*f)(Args...))
{
    return std::make_shared<concrete<Ret, Args...>>(gid, cid, functor_t<Ret, Args...>(f));
}

template<typename C, typename Ret, typename... Args>
concrete_hdl make_concrete(const gid_t &gid, const cid_t &cid, C *c, Ret (C::*mf)(Args...))
{
    functor_t<Ret, Args...> f = [c, mf](Args... args) -> Ret {
            return (c->*mf)(args...);
    };
    return std::make_shared<concrete<Ret, Args...>>(gid, cid, f);
}

template<typename C, typename Ret, typename... Args>
concrete_hdl make_concrete(const gid_t &gid, const cid_t &cid, C *c, Ret (C::*mf)(Args...) const)
{
    functor_t<Ret, Args...> f = [c, mf](Args... args) -> Ret {
            return (c->*mf)(args...);
    };
    return std::make_shared<concrete<Ret, Args...>>(gid, cid, f);
}

XL_NAMESPACE_END
