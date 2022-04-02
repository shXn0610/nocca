/* Includes */
#include <iostream>
#include "inc/typedefs.h"
#include "class/player.h"
#include "class/viewer.h"

using namespace std;

/* Defines */

/* Structs */

/* Variables */

/* Constants */

/* Prototypes */

/* Public */
main () {
    S4      s4g_state;
    Player  player_white(White);
    Player  player_black(Black);
    Viewer  viewer;
    
    viewer.showPosition(player_white, player_black);

    s4g_state = player_white.moveManually(player_black, 4, -1, 0);

    if (s4g_state == 0) {
        cout << "Error.\n";
    }
    else if (s4g_state == 1) {
        cout << "Moved.\n";
    }
    else {
        /* NOP */
    }

}