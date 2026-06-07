#ifndef TYPES_H
#define TYPES_H

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600
#define BOARD_WIDTH 480
#define BOARD_HEIGHT 480
#define BOARD_CENTER_X WINDOW_WIDTH/2
#define BOARD_CENTER_Y WINDOW_HEIGHT/2
#define SQUARE_SIZE 60

#define u64 unsigned long long
#define square(r, f) ((r)*(8) + (f))
#define rank(square) (8 - ((square)/8))
#define file(square) ((square)%8)

#define WHITE 0x00
#define BLACK 0X01
#define BOTH 0x02

#define RANK8 0x00000000000000ffULL 
#define RANK7 0x000000000000ff00ULL 
#define RANK6 0x0000000000ff0000ULL 
#define RANK5 0x00000000ff000000ULL 
#define RANK4 0x000000ff00000000ULL 
#define RANK3 0x0000ff0000000000ULL 
#define RANK2 0x00ff000000000000ULL 
#define RANK1 0xff00000000000000ULL 

#define FILEA 0x0101010101010101ULL
#define FILEB 0x0202020202020202ULL
#define FILEC 0x0404040404040404ULL
#define FILED 0x0808080808080808ULL
#define FILEE 0x1010101010101010ULL
#define FILEF 0x2020202020202020ULL
#define FILEG 0x4040404040404040ULL
#define FILEH 0x8080808080808080ULL

typedef enum {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1,     nsq
} position;


typedef enum { BISHOP, ROOK } Slider ;
typedef enum { P, N, B, R, Q, K, p, n, b, r, q, k , none} Piece ;
typedef enum { WK = 1, WQ = 2, BK = 4, BQ = 8 } Castle ;
typedef enum { allMoves, capturesOnly} moveType;

extern char pieceAscii[] ;
extern int pieceIndex[] ;
extern char* square[] ;
extern char promotedPieces[] ;

extern int bishop_relevant_bits[] ;
extern int rook_relevant_bits[] ;
extern int queen_relevant_bits[] ;
extern int castlingRights[64] ;

#endif
