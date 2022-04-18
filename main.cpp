/* Includes */
#include <iostream>
#include <time.h>
#include "inc/typedefs.h"
#include "class/player.h"
#include "class/viewer.h"
#include "class/judgeman.h"
#include "class/gene.h"

using namespace std;

/* Defines */
#define LAYER_INPUT (30)
#define LAYER_OUTPUT (40)
#define NUM_GENE (50)
#define ALPHA (0.25f)
#define GENERATION (1000)

/* Structs */

/* Variables */

/* Constants */

/* Prototypes */
void vdf_evaluation(Gene *genes_white, Gene *genes_black);
void vdf_evolution(Gene *genes_white, Gene *genes_black, Gene *genes_white_parent, Gene *genes_black_parent);
void vdf_InitCount(Gene *genes_white, Gene *genes_black);
void vdf_SelectParent(Gene *genes_white, Gene *genes_black, Gene *genes_white_parent, Gene *genes_black_parent);
void vdf_BLXalpha(Gene *genes_white, Gene *genes_black, Gene *genes_white_parent, Gene *genes_black_parent);

/* Main */
main () {

    S4 s4t_i = 0;

    Gene genes_white[NUM_GENE];
    Gene genes_black[NUM_GENE];
    Gene genes_white_parent[2];
    Gene genes_black_parent[2];

    for (s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
        genes_white[s4t_i].vdg_init(LAYER_INPUT, LAYER_OUTPUT, White); 
        genes_black[s4t_i].vdg_init(LAYER_INPUT, LAYER_OUTPUT, Black);  
    }
    for (s4t_i = 0; s4t_i < 2; s4t_i++) {
        genes_white_parent[s4t_i].vdg_init(LAYER_INPUT, LAYER_OUTPUT, White); 
        genes_black_parent[s4t_i].vdg_init(LAYER_INPUT, LAYER_OUTPUT, Black);  
    }

    for (s4t_i = 0; s4t_i < GENERATION; s4t_i++) {
        vdf_InitCount(genes_white, genes_black);
        vdf_evaluation(genes_white, genes_black);
        vdf_evolution(genes_white, genes_black, genes_white_parent, genes_black_parent);

        if (((s4t_i + 1) % 100) == 0) {
            cout << (s4t_i + 1) << "steps has done.\n";
        }
        else {
            /* NOP */
        }
    }

#if 1
    for (s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
        cout << "white[" << s4t_i << "]" << genes_white[s4t_i].s4t_count_win << "\n";      
    }
    for (s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
        //cout << "black[" << s4t_i << "]" << genes_black[s4t_i].s4t_count_win << "\n";       
    }
#endif
}

/* Sub */
void vdf_InitCount(Gene *genes_white, Gene *genes_black) {
    S4 s4t_i = 0;

    for (s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
        genes_white[s4t_i].s4t_count_win = 0;
        genes_black[s4t_i].s4t_count_win = 0;
    }
}

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
                    player_black.moveAuto(player_white);
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
    Gene *genes_white_parent,
    Gene *genes_black_parent)
{
    vdf_SelectParent(genes_white, genes_black, genes_white_parent, genes_black_parent);
    vdf_BLXalpha(genes_white, genes_black, genes_white_parent, genes_black_parent);
};

void vdf_SelectParent(
    Gene *genes_white,
    Gene *genes_black,
    Gene *genes_white_parent,
    Gene *genes_black_parent)
{
    S4 s4t_i = 0;
    S4 as4t_index_white[2] = {0};
    S4 as4t_index_black[2] = {0};
    /* Select Top */
    S4 s4t_value_white = 0;
    S4 s4t_value_black = 0;
    /* Roulette Selection */
    struct timespec ts;
    S4 s4t_sum_white = 0;
    S4 s4t_sum_black = 0;
    S4 s4t_arrow_white = 0;
    S4 s4t_arrow_black = 0;
    S4 s4t_roulette_white = 0;
    S4 s4t_roulette_black = 0;

    /* Select Top */
    for (s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
        if (s4t_value_white < genes_white[s4t_i].s4t_count_win) {
            s4t_value_white = genes_white[s4t_i].s4t_count_win;
            as4t_index_white[0] = s4t_i;
        }
        else {
            /* NOP */
        }
        if (s4t_value_black < genes_black[s4t_i].s4t_count_win) {
            s4t_value_black = genes_black[s4t_i].s4t_count_win;
            as4t_index_black[0] = s4t_i;
        }
        else {
            /* NOP */
        }
    }

    for (s4t_i = 0; s4t_i < (LAYER_INPUT * LAYER_OUTPUT); s4t_i++) {
        genes_white_parent[0].pf4t_gene[s4t_i] = genes_white[as4t_index_white[0]].pf4t_gene[s4t_i];
        genes_black_parent[0].pf4t_gene[s4t_i] = genes_black[as4t_index_black[0]].pf4t_gene[s4t_i];
    }


    /* Roulette Selection */
    for (s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
        s4t_sum_white += genes_white[s4t_i].s4t_count_win;
        s4t_sum_black += genes_black[s4t_i].s4t_count_win;
    }

	clock_gettime(CLOCK_MONOTONIC, &ts);
	srand(ts.tv_nsec);

    s4t_arrow_white = (S4)(((float)rand() / (float)RAND_MAX) * s4t_sum_white);
    s4t_arrow_black = (S4)(((float)rand() / (float)RAND_MAX) * s4t_sum_black);

    for (s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
        s4t_roulette_white += genes_white[s4t_i].s4t_count_win;
        if (s4t_roulette_white >= s4t_arrow_white) {
            as4t_index_white[1] = s4t_i;
            break;
        }
        else {
            /* NOP */
        }
    }

    for (s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
        s4t_roulette_black += genes_black[s4t_i].s4t_count_win;
        if (s4t_roulette_black >= s4t_arrow_black) {
            as4t_index_black[1] = s4t_i;
            break;
        }
        else {
            /* NOP */
        }
    }

    for (s4t_i = 0; s4t_i < (LAYER_INPUT * LAYER_OUTPUT); s4t_i++) {
        genes_white_parent[1].pf4t_gene[s4t_i] = genes_white[as4t_index_white[1]].pf4t_gene[s4t_i];
        genes_black_parent[1].pf4t_gene[s4t_i] = genes_black[as4t_index_black[1]].pf4t_gene[s4t_i];
    }
};

void vdf_BLXalpha(
    Gene *genes_white,
    Gene *genes_black,
    Gene *genes_white_parent,
    Gene *genes_black_parent)
{
    S4 s4t_num = 0;
    S4 s4t_i = 0;

    F4 f4t_weight_max_white = 0.0f;
    F4 f4t_weight_min_white[LAYER_INPUT * LAYER_OUTPUT] = {0.0f};
    F4 f4t_weight_diff_white[LAYER_INPUT * LAYER_OUTPUT] = {0.0f};
    F4 f4t_weight_max_black = 0.0f;
    F4 f4t_weight_min_black[LAYER_INPUT * LAYER_OUTPUT] = {0.0f};
    F4 f4t_weight_diff_black[LAYER_INPUT * LAYER_OUTPUT] = {0.0f};
    F4 f4t_tmp = 0.0f;
    struct timespec ts;

    for (s4t_i = 0; s4t_i < (LAYER_INPUT * LAYER_OUTPUT); s4t_i++) {
        if (genes_white_parent[0].pf4t_gene[s4t_i] >= genes_white_parent[1].pf4t_gene[s4t_i]) {
            f4t_tmp = genes_white_parent[0].pf4t_gene[s4t_i] - genes_white_parent[1].pf4t_gene[s4t_i];
            f4t_weight_max_white = genes_white_parent[0].pf4t_gene[s4t_i] + f4t_tmp * ALPHA;
            f4t_weight_min_white[s4t_i] = genes_white_parent[1].pf4t_gene[s4t_i] - f4t_tmp * ALPHA;
        }
        else {
            f4t_tmp = genes_white_parent[1].pf4t_gene[s4t_i] - genes_white_parent[0].pf4t_gene[s4t_i];
            f4t_weight_max_white = genes_white_parent[1].pf4t_gene[s4t_i] + f4t_tmp * ALPHA;
            f4t_weight_min_white[s4t_i] = genes_white_parent[0].pf4t_gene[s4t_i] - f4t_tmp * ALPHA;
        }
        f4t_weight_diff_white[s4t_i] = f4t_weight_max_white - f4t_weight_min_white[s4t_i];

        if (genes_black_parent[0].pf4t_gene[s4t_i] >= genes_black_parent[1].pf4t_gene[s4t_i]) {
            f4t_tmp = genes_black_parent[0].pf4t_gene[s4t_i] - genes_black_parent[1].pf4t_gene[s4t_i];
            f4t_weight_max_black = genes_black_parent[0].pf4t_gene[s4t_i] + f4t_tmp * ALPHA;
            f4t_weight_min_black[s4t_i] = genes_black_parent[1].pf4t_gene[s4t_i] - f4t_tmp * ALPHA;
        }
        else {
            f4t_tmp = genes_black_parent[1].pf4t_gene[s4t_i] - genes_black_parent[0].pf4t_gene[s4t_i];
            f4t_weight_max_black = genes_black_parent[1].pf4t_gene[s4t_i] + f4t_tmp * ALPHA;
            f4t_weight_min_black[s4t_i] = genes_black_parent[0].pf4t_gene[s4t_i] - f4t_tmp * ALPHA;
        }
        f4t_weight_diff_black[s4t_i] = f4t_weight_max_black - f4t_weight_min_black[s4t_i];
    }

    for (s4t_num = 0; s4t_num < 1; s4t_num++) {
        for (s4t_i = 0; s4t_i < (LAYER_INPUT * LAYER_OUTPUT); s4t_i++) {
            genes_white[s4t_num].pf4t_gene[s4t_i] = genes_white_parent[s4t_num].pf4t_gene[s4t_i];
            genes_black[s4t_num].pf4t_gene[s4t_i] = genes_black_parent[s4t_num].pf4t_gene[s4t_i];
        }
    }

    for (s4t_num = 2; s4t_num < NUM_GENE; s4t_num++) {
        for (s4t_i = 0; s4t_i < (LAYER_INPUT * LAYER_OUTPUT); s4t_i++) {
            clock_gettime(CLOCK_MONOTONIC, &ts);
            srand(ts.tv_nsec);
            genes_white[s4t_num].pf4t_gene[s4t_i] = f4t_weight_min_white[s4t_i] + ((float)rand() / (float)RAND_MAX) * f4t_weight_diff_white[s4t_i];
            genes_black[s4t_num].pf4t_gene[s4t_i] = f4t_weight_min_black[s4t_i] + ((float)rand() / (float)RAND_MAX) * f4t_weight_diff_black[s4t_i];
        }
    }
};


