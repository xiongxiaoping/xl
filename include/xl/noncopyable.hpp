#pragma once

namespace xl {

class noncopyable {
public:
    noncopyable() = default;
    ~noncopyable() = default;
    noncopyable(noncopyable &) = delete;
    noncopyable &operator=(noncopyable &) = delete;
};    

} // namespace xl

