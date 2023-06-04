#pragma once
#include <format>
#include <iostream>
#include <algorithm>

template <size_t N>
struct Fmt
{
    char fmt[N];
    constexpr Fmt(const char (&s)[N]) noexcept
    {
        std::copy_n(s, N, fmt);
    }
};

template <Fmt f>
constexpr auto operator""_fmt()
{
    return []<typename... Args>(Args&&... args) {
        return std::format(f.fmt, std::forward<Args>(args)...);
    };
}