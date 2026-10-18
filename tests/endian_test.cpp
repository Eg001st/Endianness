
#include <cstdint>
#include <cstddef>

#include<array>
#include<string>
#include<vector>
#include<tuple>
#include<span>

#include "endianness/converter.hpp"

#include <gtest/gtest.h>


using InFn = std::uint32_t(*)(std::span<const std::byte, endianness::kBytesIn32Value>);
using InputData = std::array<std::byte, endianness::kBytesIn32Value>;

struct CaseData
{
    std::string name{};
    InFn functionForTest{};
};

struct InputOutputData
{
    std::string name{};
    std::uint32_t outputData{};
    InputData inputData{};
};

const std::vector<InputOutputData> kTestParametersSet
{
    {.name = "all_distinct_bytes",
    .outputData = 0x0A0B0C0Du,
    .inputData = {std::byte{0x0A}, std::byte{0x0B}, std::byte{0x0C}, std::byte{0x0D}}},
    
    {.name = "ascending",
    .outputData = 0x01020304u,
    .inputData = {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}, std::byte{0x04}}},
    
    {.name = "high_bit",
    .outputData = 0x80000000u,
    .inputData = {std::byte{0x80}, std::byte{0x00}, std::byte{0x00}, std::byte{0x00}}},
}; 

const std::vector<CaseData> kTestFunctionsSet
{
    {.name = "read_be32_loop", .functionForTest = &endianness::read_be32_loop},

    {.name = "read_be32_fold", .functionForTest = &endianness::read_be32_fold}
};

class GoldenVectorParametrizedTest : public ::testing::TestWithParam<std::tuple<CaseData, InputOutputData>>{};

TEST_P(GoldenVectorParametrizedTest, OutputHasExpectedKnownResult) 
{
    const auto& [impl, vec] = GetParam();

    const auto& input = vec.inputData;
    const InFn fn = impl.functionForTest;
    const std::uint32_t output = fn(input);

	EXPECT_EQ(vec.outputData, output);
} 

INSTANTIATE_TEST_SUITE_P(GoldenVectorReadBE32, GoldenVectorParametrizedTest, ::testing::Combine(::testing::ValuesIn(kTestFunctionsSet), 
                                                                             ::testing::ValuesIn(kTestParametersSet)),
                                                                             [](const testing::TestParamInfo<GoldenVectorParametrizedTest::ParamType>& info)
    { return std::get<0>(info.param).name + "_" + std::get<1>(info.param).name; });


