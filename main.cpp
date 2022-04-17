/* Includes */
#include <iostream>
#include "inc/typedefs.h"
#include "class/player.h"
#include "class/viewer.h"
#include "class/judgeman.h"
#include "class/gene.h"

using namespace std;

/* Defines */
#define LAYER_INPUT (30)
#define LAYER_OUTPUT (40)
#define NUM_GENE (10)

/* Structs */

/* Variables */

/* Constants */

/* Prototypes */
void vdf_evaluation(Gene *genes_white, Gene *genes_black);
void vdf_evolution(Gene *genes_white, Gene *genes_black, Gene *genes_white_next, Gene *genes_black_next);

/* Main */
main () {

    S4 s4t_i = 0;

    Gene genes_white[NUM_GENE];
    Gene genes_black[NUM_GENE];
    Gene genes_white_next[NUM_GENE];
    Gene genes_black_next[NUM_GENE];

    for (s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
        genes_white[s4t_i].vdg_init(LAYER_INPUT, LAYER_OUTPUT, White); 
        genes_black[s4t_i].vdg_init(LAYER_INPUT, LAYER_OUTPUT, Black); 
    }

    vdf_evaluation(genes_white, genes_black);
    vdf_evolution(genes_white, genes_black, genes_white_next, genes_black_next);

#if 1
    for (s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
        cout << "white[" << s4t_i << "]" << genes_white[s4t_i].s4t_count_win << "\n";
        //cout << "black[" << s4t_i << "]" << genes_black[s4t_i].s4t_count_win << "\n";       
    }
#endif

    #if 0
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

            player_black.moveAutoNN(player_white);
        }
        else {
            /* NOP */
        }

        viewer.showPosition(player_white, player_black);
        en_state = judgeman.judgeWinLose(player_white, player_black, en_state);
    }
    #endif
}

/* Sub */
void vdf_evaluation(Gene *genes_white, Gene *genes_black) {
    S4  s4t_num_white = 0;
    S4  s4t_num_black = 0;

    for (s4t_num_white = 0; s4t_num_white < NUM_GENE; s4t_num_white++) {
        for (s4t_num_black = 0; s4t_num_black < NUM_GENE; s4t_num_black++) {
            Player      player_white(White, &(genes_white[s4t_num_white]));
            Player      player_black(Black, &(genes_black[s4t_num_black]));
            Judgeman    judgeman(player_white, player_black);
            EN_STATE    en_state = WhitePlay;

            while ((en_state == WhitePlay) || (en_state == BlackPlay)) {
                if (en_state == WhitePlay) {
                    player_white.moveAutoNN(player_black);
                }
                else if (en_state == BlackPlay) {
                    player_black.moveAutoNN(player_white);
                }
                else {
                    /* NOP */
                }
                en_state = judgeman.judgeWinLose(player_white, player_black, en_state);
            }

            if (en_state == WhiteWin) {
                genes_white[s4t_num_white].s4t_count_win++;
            }
            else if (en_state == BlackWin) {
                genes_black[s4t_num_black].s4t_count_win++;
            }
            else {
                /* NOP */
            }
        }
    }
}

void vdf_evolution(
    Gene *genes_white,
    Gene *genes_black,
    Gene *genes_white_next,
    Gene *genes_black_next)
{

};