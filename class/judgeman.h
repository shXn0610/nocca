#ifndef JUDGEMAN_H
#define JUDGEMAN_H

/* Incluldes */
#include "..\inc\typedefs.h"
#include "..\class\player.h"

/* Defines */

/* Macro Functions */

/* Variables */

/* Constants */

/* Class */
class Judgeman {
public:
	S4		s4_positionWhite_save[15];
	S4		s4_positionBlack_save[15];
	Judgeman(Player player_white, Player player_black);
	~Judgeman(void);
	EN_STATE judgeWinLose(Player player_white, Player player_black, EN_STATE en_state);

private:
    
};

/* Prototypes */

#endif /* #ifndef JUDGEMAN_H */