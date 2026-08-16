#include "../include/Cache.h"
#include "../include/CacheConfig.h"

#include <cstdint>

std::uint32_t Cache::getTag(std::uint32_t addr) const {
    return addr >> (NUM_OFFSET_BITS + NUM_INDEX_BITS);
}

std::uint32_t Cache::getIndex(std::uint32_t addr) const {
    return (addr >> NUM_OFFSET_BITS) & ((1U << NUM_INDEX_BITS) - 1);
}

std::uint32_t Cache::getOffset(std::uint32_t addr) const {
    return addr & ((1U << NUM_OFFSET_BITS) - 1);
}

int Cache::findWay(std::uint32_t set_idx, std::uint32_t tag) const {
    for (uint32_t i = 0; i < ASSOCIATIVITY; i++){
        if(sets[set_idx].ways[i].valid && sets[set_idx].ways[i].tag == tag){
            return i;
        }
    }
    return -1;
}

int Cache::getLRUWay(std::uint32_t set_idx) const {
    for (uint32_t i = 0; i < ASSOCIATIVITY; i++){
        if(sets[set_idx].ways[i].valid == false){
            return i;
        }
    }

    int lru_way = 0;
    int max_val = -1;

    for (uint32_t i = 0; i < ASSOCIATIVITY; i++){
        if(sets[set_idx].lru_counter[i] > max_val){
            max_val = sets[set_idx].lru_counter[i];
            lru_way = i;
        }
    }
    return lru_way;

}

void Cache::updateLRU(std::uint32_t set_idx, int used_way) {

    for (uint32_t i = 0; i < ASSOCIATIVITY; i++) {
        if (sets[set_idx].lru_counter[i] < sets[set_idx].lru_counter[used_way]) {
            sets[set_idx].lru_counter[i]++;
        }
    }
    
    sets[set_idx].lru_counter[used_way] = 0;
}

