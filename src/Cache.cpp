#include "../include/Cache.h"
#include "../include/CacheConfig.h"

#include <iostream>
#include <iomanip>

uint32_t Cache::getTag(uint32_t addr){
    return addr >> (NUM_OFFSET_BITS + NUM_INDEX_BITS);
}

uint32_t Cache::getIndex(uint32_t addr) const {
    return (addr >> NUM_OFFSET_BITS) & ((1U << NUM_INDEX_BITS) - 1);
}

uint32_t Cache::getOffset(uint32_t addr) const {
    return addr & ((1U << NUM_OFFSET_BITS) - 1);
}

