#ifndef BOARD_H
#define BOARD_H

/* Incluldes */
#include "..\inc\typedefs.h"
#include "block.h"

/* Defines */

/* Macro Functions */

/* Variables */

/* Constants */

/* Class */
class Board {
public:
	Board(void);
	~Board(void);
    void        showBoard(void);
    /* update board */
    void        updateBoard(S4 s4_idx, S4 s4_dx, S4 s4_dy, EN_COLOR en_color);
    bool        bl_checkMove(S4 s4_idx, S4 s4_dx, S4 s4_dy, EN_COLOR en_color);
    bool        bl_checkBlockOn(S4 s4_idx, EN_COLOR en_color);
    void        vdg_updateBoard(S4 s4_idx, S4 s4_dx, S4 s4_dy, EN_COLOR en_color);
    /* judge win-lose */
    EN_STATE    judgeWinLose(EN_STATE en_state);
    void        calcDiff(void);
    void        updateBlocksPre(void);
    EN_STATE    checkDiff(EN_STATE en_state);
    EN_STATE    checkOutOfBoard(EN_STATE en_state);
    EN_STATE    checkReachEndline(EN_STATE en_state);
    EN_STATE    checkOverwhelm(EN_STATE en_state);

    Block       blocks[10];
    Block       blocks_pre[10];
    Block       blocks_diff[10];

private:
    
};

/* Prototypes */

#endif /* #ifndef BOARD_H */