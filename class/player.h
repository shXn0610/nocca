#ifndef PLAYER_H
#define PLAYER_H

/* Incluldes */
#include "..\inc\typedefs.h"

/* Defines */

/* Macro Functions */

/* Variables */

/* Constants */

/* Class */
class Player {
public:
	Player(EN_COLOR en_color);
	~Player(void);
	void showPosition1(void);
	void showPosition2(void);
	S4	 moveManually(Player player_enemy, S4 s4_num, S4 s4_x, S4 s4_y);

	EN_COLOR	en_color;
	S4			as4_position[15];
private:
    
};

/* Prototypes */

#endif /* #ifndef PLAYER_H */