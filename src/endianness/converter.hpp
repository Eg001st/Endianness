#pragma once

#include <cstddef>
#include <cstdint>
#include <climits>

#include <algorithm>

#include <span>

namespace endianness
{
    inline constexpr std::size_t kBytesIn32Value{sizeof(std::uint32_t)};

    inline std::uint32_t read_be32_loop(std::span<const std::byte, kBytesIn32Value> byteSpan)
    {
        std::uint32_t result{};
        constexpr std::size_t lastIndex{kBytesIn32Value - 1};
        for (std::size_t i{0}; i < kBytesIn32Value; ++i)
        {
            result |= std::to_integer<std::uint32_t>(byteSpan[i]) << (CHAR_BIT * (lastIndex - i));
        }

        return result;
    }

    inline std::uint32_t read_be32_fold(std::span<const std::byte, kBytesIn32Value> byteSpan) 
    {
        return std::ranges::fold_left(byteSpan, std::uint32_t{},
            [](std::uint32_t accum, std::byte nextByte) { return (accum << CHAR_BIT) + std::to_integer<std::uint32_t>(nextByte); });
    }

    }  // namespace endianness