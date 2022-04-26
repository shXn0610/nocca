#ifndef PLAYER_H
#define PLAYER_H

/* Incluldes */
#include "..\inc\typedefs.h"
#include "board.h"
#include "gene.h"

/* Defines */

/* Macro Functions */

/* Variables */

/* Constants */

/* Class */
class Player {
public:
	Player(EN_COLOR en_color);
	~Player(void);
	void moveManually(Board &board);
	void moveAuto(Board &board);
	void moveAutoGA(Board &board, Gene &gene);

	EN_COLOR color;

private:
    
};

/* Prototypes */

#endif /* #ifndef PLAYER_H */