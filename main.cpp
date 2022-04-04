/* Includes */
#include <iostream>
#include "inc/typedefs.h"
#include "class/player.h"
#include "class/viewer.h"
#include "class/judgeman.h"

using namespace std;

/* Defines */

/* Structs */

/* Variables */

/* Constants */

/* Prototypes */

/* Public */
main () {
    Player      player_white(White);
    Player      player_black(Black);
    Viewer      viewer;
    Judgeman    judgeman;
    
    viewer.showPosition(player_white, player_black);

    player_white.moveManually(player_black, 4, -1, 0);

    viewer.showPosition(player_white, player_black);

}