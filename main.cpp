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
    Judgeman    judgeman(player_white, player_black);
    EN_STATE    en_state = WhitePlay;
    
    viewer.showPosition(player_white, player_black);

    while ((en_state == WhitePlay) || (en_state == BlackPlay)) {
        if (en_state == WhitePlay) {
            
            player_white.moveManually(player_black);
            
            //player_white.moveAuto(player_black);
        }
        else if (en_state == BlackPlay) {

            //player_black.moveManually(player_white);

            player_black.moveAuto(player_white);
        }
        else {
            /* NOP */
        }

        viewer.showPosition(player_white, player_black);
        en_state = judgeman.judgeWinLose(player_white, player_black, en_state);
    }
}