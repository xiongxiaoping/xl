#pragma once

#include <cstdint>
#include <string>
#include <functional>
#include <memory>
#include <iostream>

#define XL_NAMESPACE_BEGIN namespace xl {
#define XL_NAMESPACE_END }

XL_NAMESPACE_BEGIN

using gid_t = std::string;
using cid_t = std::string;
using err_code_t = int32_t;

template<typename Ret, typename... Args>
using functor_t = std::function<Ret(Args...)>;

template<typename T>
struct return_t;

// template<typename... Args>
// struct params;

template<typename... Args>
struct params_in;

template<typename... Args>
struct params_out;

XL_NAMESPACE_END
