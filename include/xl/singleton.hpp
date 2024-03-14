#pragma once

#include "noncopyable.hpp"

namespace xl {

template<typename T>
class singleton : public noncopyable {
protected:
    singleton() = default;
    ~singleton() = default;

public:
    static T &instance() {
        static T ins;
        return ins;
    }
};

}
