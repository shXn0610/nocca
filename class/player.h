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

	S4	 moveManually(Player player_enemy);
	S4	 moveAuto(Player player_enemy);
	S4	 moveAutoNN(Player player_enemy);

	EN_COLOR	en_color;
	S4			as4_position[15];
	F4			af4_weight[1200];
private:
    
};

/* Prototypes */

#endif /* #ifndef PLAYER_H */