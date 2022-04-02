#ifndef VIEWER_H
#define VIEWER_H

/* Incluldes */
#include "..\inc\typedefs.h"
#include "..\class\player.h"

/* Defines */

/* Macro Functions */

/* Variables */

/* Constants */

/* Class */
class Viewer {
public:
	Viewer(void);
	~Viewer(void);
	void showPosition(Player player_white, Player player_black);

private:
    
};

/* Prototypes */

#endif /* #ifndef VIEWER_H */