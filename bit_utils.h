#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#include "types.h"

#define get_bit(bitboard, square) (((bitboard) >> (square)) & 1ULL)? 1 : 0
#define set_bit(bitboard, square) (bitboard) |= (1ULL << (square))
#define pop_bit(bitboard, square) (((bitboard) >> (square)) & 1ULL)? (bitboard) ^= (1ULL << (square)) : (bitboard)
#define pop_ls1b(bitboard) ((bitboard) &= (bitboard-1))

static inline int count_bits(u64 bitboard) {
    int count = 0;

    while(bitboard) {
        count++;
        
        // x & (x - 1) pops the least significant bit in x
        bitboard &= (bitboard - 1);
    }

    return count;
}

static inline int get_ls1b_index(u64 bitboard) {
    if(!bitboard) return -1;

    // x & -x isolates the least significant bit from x, all the bits are popped
    // also -x = x_comp + 1
    bitboard &= -bitboard;

    //(x - 1) flips all the bits before lsb to 1, and lsb to 0
    bitboard -= 1;


    //now since all the bits before lsb are 1, we simply count them
    int index = count_bits(bitboard);

    return index;
}

#endif

