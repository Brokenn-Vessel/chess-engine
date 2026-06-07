#ifndef ATTACK_TABLES_H
#define ATTACK_TABLES_H

#include "bit_utils.h"

extern u64 pawnAttackTable[2][64] ;
extern u64 knightAttackTable[64] ;
extern u64 kingAttackTable[64] ;

extern u64 rookMagicNumber[64] ;
extern u64 bishopMagicNumber[64] ;
extern u64 rookAttackMask[64] ;
extern u64 bishopAttackMask[64] ;

extern u64 bishopAttackTable[64][512] ;
extern u64 rookAttackTable[64][4096] ;

u64 genPawnAttackMask(int square, int side) ;
u64 genKnightAttackMask(int square) ;
u64 genKingAttackMask(int square) ;
u64 setOccupancy(u64 attackMask, int bitsInAttackMask, int index) ;
u64 genRookAttack(int square, u64 blockers) ;
u64 genBishopAttack(int square, u64 blockers) ;
void initSliderAttacks() ;
u64 getRookAttack(int square, u64 occupancy) ;
u64 getBishopAttack(int square, u64 occupancy) ;
u64 getQueenAttack(int square, u64 occupancy) ;

#endif