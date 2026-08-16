#pragma once

#include "CacheConfig.h"
#include "Memory.h"

#include <cstdint>

struct CacheBlock {
    bool valid = false;
    bool dirty = false;
    std::uint32_t tag = 0;
    std::uint8_t data[BLOCK_SIZE] = {};
};

struct CacheSet {
    CacheBlock  ways[ASSOCIATIVITY];
    int lru_counter[ASSOCIATIVITY] = {};
};

class Cache {
    public:
        Cache(Memory& mem);
        std::uint32_t loadWord(std::uint32_t addr);
        void     storeWord(std::uint32_t addr, std::uint32_t val);
        std::uint8_t  loadByte(std::uint32_t addr);
        void     storeByte(std::uint32_t addr, std::uint8_t val);
        void     printStats() const;

    private:
        CacheSet sets[NUM_SETS];
        Memory&  memory;

        // Stats
        std::uint64_t hits   = 0;
        std::uint64_t misses = 0;

        // Helpers
        std::uint32_t getTag(std::uint32_t addr)                        const;
        std::uint32_t getIndex(std::uint32_t addr)                      const;
        std::uint32_t getOffset(std::uint32_t addr)                     const;
        int           findWay(std::uint32_t set_idx, std::uint32_t tag) const;  // -1 = miss
        int           getLRUWay(std::uint32_t set_idx)                  const;
        void          updateLRU(std::uint32_t set_idx, int used_way);
        void          fetchBlock(std::uint32_t addr, CacheSet& set, int way);
        void          evictBlock(std::uint32_t addr, CacheSet& set, int way);
};