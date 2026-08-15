#pragma once

#include "CacheConfig.h"
#include "Memory.h"

#include <cstdint>
#include <vector>

struct CacheBlock {
    bool valid = false;
    bool dirty = false;
    uint32_t tag = 0;
    uint8_t data[BLOCK_SIZE] = {};
};

struct CacheSet {
    CacheBlock  ways[ASSOCIATIVITY];
    int lru_counter[ASSOCIATIVITY] = {};
};

class Cache {
    public:
        Cache(Memory& mem);
        uint32_t loadWord(uint32_t addr);
        void     storeWord(uint32_t addr, uint32_t val);
        uint8_t  loadByte(uint32_t addr);
        void     storeByte(uint32_t addr, uint8_t val);
        void     printStats() const;

    private:
        CacheSet sets[NUM_SETS];
        Memory&  memory;

        // Stats
        uint64_t hits   = 0;
        uint64_t misses = 0;

        // Helpers
        uint32_t getTag(uint32_t addr)    const;
        uint32_t getIndex(uint32_t addr)  const;
        uint32_t getOffset(uint32_t addr) const;
        int      findWay(uint32_t set_idx, uint32_t tag) const;  // -1 = miss
        int      getLRUWay(uint32_t set_idx)             const;
        void     updateLRU(uint32_t set_idx, int used_way);
        void     fetchBlock(uint32_t addr, CacheSet& set, int way);
        void     evictBlock(uint32_t addr, CacheSet& set, int way);
};