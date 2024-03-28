#pragma once

#include <functional>
#include <future>
#include <thread>
#include <type_traits>
#include <memory>
#include <iostream>

namespace xl {
namespace task {

struct task_base {
public:
    virtual ~task_base() = default;
    virtual void execute() const = 0;
    virtual bool is_ready() const = 0;
    virtual bool depends_ready() const = 0;
};

using task_hdl = std::shared_ptr<task_base>;

template<typename Res>
struct task : task_base {
public:
    task() : prom_(std::make_shared<std::promise<Res>>()), fut_(std::make_shared<std::shared_future<Res>>(prom_->get_future())) {}

    template<typename F, typename... Args>
    void bind(F&& f, Args&&... args);

    virtual void execute() const override { func_(); }
    virtual bool is_ready() const override {
        using namespace std::chrono;
        return fut_->valid() && fut_->wait_for(0s) == std::future_status::ready;
    };
    virtual bool depends_ready() const override {
        std::cout << __FUNCTION__ << std::endl;
        for (auto &dep : depends_) {
            std::cout << "xxxxxxx" << std::endl;
            if (!dep->is_ready()) {
                return false;
            }
        }
        return true;
    }

    Res get() const {
        if (!is_ready()) {
            throw std::runtime_error("not ready");
        }
        return fut_->get();
    }

    void depend(std::shared_ptr<task_base> dep) {
        depends_.emplace_back(dep);
    }

private:
    std::shared_ptr<std::promise<Res>> prom_;
    std::shared_ptr<std::shared_future<Res>> fut_;
    std::vector<std::shared_ptr<task_base>> depends_;
    std::function<void()> func_;
};

namespace helper {
    template<typename Arg,
        typename = std::enable_if_t<!std::is_base_of_v<task_base, std::decay_t<Arg>>>>
    constexpr auto arg_extract(Arg&& arg) {
        return std::forward<Arg>(arg);
    }
    template<typename Arg>
    constexpr auto arg_extract(const task<Arg> &arg) {
        return arg.get();
    }
    template<typename Arg,
        typename = std::enable_if_t<!std::is_base_of_v<task_base, std::decay_t<Arg>>>>
    void add_depend(Arg&& arg, std::vector<std::shared_ptr<task_base>> &depends) {
        // do nothing
    }
    template<typename Arg>
    void add_depend(const task<Arg> &arg, std::vector<std::shared_ptr<task_base>> &depends) {
        depends.emplace_back(std::make_shared<task<Arg>>(arg));
    }
}

template<typename Res>
template<typename F, typename... Args>
void task<Res>::bind(F&& f, Args&&... args) {
    func_ = std::bind([this, f = std::forward<F>(f)](auto&&... args) {
        try {
            prom_->set_value(f(helper::arg_extract(std::forward<decltype(args)>(args))...));
        } catch (...) {
            prom_->set_exception(std::current_exception());
        }
    }, std::forward<Args>(args)...);
    (helper::add_depend(std::forward<Args>(args), depends_), ...);
}

} // namespace xl
} // namespace task
