#pragma once

#include <cmath>
#include <cstdint>

constexpr uint32_t CACHE_SIZE = 1024;
constexpr uint32_t BLOCK_SIZE = 16;
constexpr uint32_t ASSOCIATIVITY = 2;

constexpr uint32_t NUM_BLOCKS = CACHE_SIZE / BLOCK_SIZE;
constexpr uint32_t NUM_SETS = NUM_BLOCKS / ASSOCIATIVITY;

constexpr uint32_t NUM_INDEX_BITS = log2(NUM_SETS);
constexpr uint32_t NUM_OFFSET_BITS = log2(BLOCK_SIZE);

constexpr uint32_t NUM_TAG_BITS = 32 - (NUM_INDEX_BITS + NUM_OFFSET_BITS);

static_assert(NUM_OFFSET_BITS + NUM_INDEX_BITS + NUM_TAG_BITS == 32);