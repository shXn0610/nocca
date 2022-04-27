/* Includes */
#include <iostream>
#include <time.h>
#include "ga.h"
#include "gene.h"
#include "nocca.h"

using namespace std;

/* Defines */
#define INPUT_LAYER (30)
#define OUTPUT_LAYER (40)
#define NUM_GENE (250)
#define GENERATION (100)
#define ALPHA (0.70f)

/* Variables */

/* prototypes */

/* Public */
GA::GA() {
    /* NOP */
};

GA::~GA() {
    /* NOP */
};

void GA::startGA() {
    Gene gene_white[NUM_GENE];
    Gene gene_black[NUM_GENE];
    Gene gene_white_parent[2];
    Gene gene_black_parent[2];

    S4 s4t_sum = 0;
    S4 s4t_ave = 0;

    for (S4 s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
        gene_white[s4t_i].initWeight(INPUT_LAYER, OUTPUT_LAYER);
        gene_black[s4t_i].initWeight(INPUT_LAYER, OUTPUT_LAYER);
    }
    for (S4 s4t_i = 0; s4t_i < 2; s4t_i++) {
        gene_white_parent[s4t_i].initWeight(INPUT_LAYER, OUTPUT_LAYER);
        gene_black_parent[s4t_i].initWeight(INPUT_LAYER, OUTPUT_LAYER);
    }

    for (S4 s4t_j = 0; s4t_j < GENERATION; s4t_j++) {
        evaluation(gene_white, gene_black);
        evolution(gene_white, gene_black, gene_white_parent, gene_black_parent);

        if (((s4t_j + 1) % 5) == 0) {
            s4t_sum = 0;
            s4t_ave = 0;
            for (S4 s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
                s4t_sum += gene_white[s4t_i].s4_count_win;
            }
            s4t_ave = (S4)(((F4)s4t_sum / NUM_GENE / NUM_GENE) * 100);
            cout << (s4t_j + 1) << "step:";
            cout << "average win rate = " << s4t_ave << "%\n";
        }
        else {
            /* NOP */
        }
    }

    cout << "end.\n";

    for (S4 s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
        gene_white[s4t_i].clearWeight(INPUT_LAYER, OUTPUT_LAYER);
        gene_black[s4t_i].clearWeight(INPUT_LAYER, OUTPUT_LAYER);
    }  
}

void GA::evaluation(Gene *gene_white, Gene *gene_black) {
    Nocca nocca;
    EN_STATE en_state = WHITE_PLAYING;

    /* Initialize count of win */
    for (S4 s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
        gene_white[s4t_i].s4_count_win = 0;
        gene_black[s4t_i].s4_count_win = 0;
    }

    for (S4 s4t_white = 0; s4t_white < NUM_GENE; s4t_white++) {
        for (S4 s4t_black = 0; s4t_black < NUM_GENE; s4t_black++) {
            en_state = nocca.startGameGA(&(gene_white[s4t_white]), &(gene_black[s4t_black]));

            if (en_state == WHITE_WIN) {
                gene_white[s4t_white].s4_count_win++;
            }
            else if (en_state == BLACK_WIN) {
                gene_black[s4t_black].s4_count_win++;
            }
            else {
                /* NOP */
            }
        }
    }
}

void GA::evolution(
    Gene *gene_white,
    Gene *gene_black,
    Gene *gene_white_parent,
    Gene *gene_black_parent)
{
    selectParent(gene_white, gene_black, gene_white_parent, gene_black_parent);
    BLXalpha(gene_white, gene_black, gene_white_parent, gene_black_parent);
}

void GA::selectParent(
    Gene *gene_white,
    Gene *gene_black,
    Gene *gene_white_parent,
    Gene *gene_black_parent)
{
    S4 as4t_index_white[2] = {0, 0};
    S4 as4t_index_black[2] = {0, 0};
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
    for (S4 s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
        if (s4t_value_white <= gene_white[s4t_i].s4_count_win) {
            s4t_value_white = gene_white[s4t_i].s4_count_win;
            as4t_index_white[0] = s4t_i;
        }
        else {
            /* NOP */
        }
        if (s4t_value_black <= gene_black[s4t_i].s4_count_win) {
            s4t_value_black = gene_black[s4t_i].s4_count_win;
            as4t_index_black[0] = s4t_i;
        }
        else {
            /* NOP */
        }
    }
    
    for (S4 s4t_i = 0; s4t_i < OUTPUT_LAYER; s4t_i++) {
        for (S4 s4t_j = 0; s4t_j < INPUT_LAYER; s4t_j++) {
            gene_white_parent[0].ppf4_weight[s4t_i][s4t_j] = gene_white[as4t_index_white[0]].ppf4_weight[s4t_i][s4t_j] ;
            gene_black_parent[0].ppf4_weight[s4t_i][s4t_j] = gene_black[as4t_index_black[0]].ppf4_weight[s4t_i][s4t_j] ;
        }
    }

    /* Roulette Selection */
    for (S4 s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
        s4t_sum_white += (gene_white[s4t_i].s4_count_win + 1);
        s4t_sum_black += (gene_black[s4t_i].s4_count_win + 1);
    }

    while(1) {
        s4t_roulette_white = 0;
        s4t_roulette_black = 0;
        clock_gettime(CLOCK_MONOTONIC, &ts);
	    srand(ts.tv_nsec);

        s4t_arrow_white = (S4)(((float)(rand() - 1) / (float)(RAND_MAX)) * s4t_sum_white) + 1;
        s4t_arrow_black = (S4)(((float)(rand() - 1) / (float)(RAND_MAX)) * s4t_sum_black) + 1;

        for (S4 s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
            s4t_roulette_white += (gene_white[s4t_i].s4_count_win + 1);
            if (s4t_roulette_white >= s4t_arrow_white) {
                as4t_index_white[1] = s4t_i;
                break;
            }
            else {
                /* NOP */
            }
        }

        for (S4 s4t_i = 0; s4t_i < NUM_GENE; s4t_i++) {
            s4t_roulette_black += (gene_black[s4t_i].s4_count_win + 1);
            if (s4t_roulette_black >= s4t_arrow_black) {
                as4t_index_black[1] = s4t_i;
                break;
            }
            else {
                /* NOP */
            }
        }

        if ((as4t_index_white[0] == as4t_index_white[1]) || (as4t_index_black[0] == as4t_index_black[1])) {
            /* NOP */
        }
        else {
            break;
        }
    }

    for (S4 s4t_i = 0; s4t_i < OUTPUT_LAYER; s4t_i++) {
        for (S4 s4t_j = 0; s4t_j < INPUT_LAYER; s4t_j++) {
            gene_white_parent[1].ppf4_weight[s4t_i][s4t_j] = gene_white[as4t_index_white[1]].ppf4_weight[s4t_i][s4t_j] ;
            gene_black_parent[1].ppf4_weight[s4t_i][s4t_j] = gene_black[as4t_index_black[1]].ppf4_weight[s4t_i][s4t_j] ;
        }
    }    
}

void GA::BLXalpha(
    Gene *gene_white,
    Gene *gene_black,
    Gene *gene_white_parent,
    Gene *gene_black_parent)
{
    S4 s4t_num = 0;

    F4 f4t_weight_max_white = 0.0f;
    F4 f4t_weight_min_white[OUTPUT_LAYER][INPUT_LAYER];
    F4 f4t_weight_diff_white[OUTPUT_LAYER][INPUT_LAYER];
    F4 f4t_weight_max_black = 0.0f;
    F4 f4t_weight_min_black[OUTPUT_LAYER][INPUT_LAYER];
    F4 f4t_weight_diff_black[OUTPUT_LAYER][INPUT_LAYER];
    F4 f4t_weight_tmp = 0.0f;

    F4 f4t_bias_max_white = 0.0f;
    F4 f4t_bias_min_white[OUTPUT_LAYER];
    F4 f4t_bias_diff_white[OUTPUT_LAYER];
    F4 f4t_bias_max_black = 0.0f;
    F4 f4t_bias_min_black[OUTPUT_LAYER];
    F4 f4t_bias_diff_black[OUTPUT_LAYER];
    F4 f4t_bias_tmp = 0.0f;

    struct timespec ts;

    for (S4 s4t_i = 0; s4t_i < OUTPUT_LAYER; s4t_i++) {
        for (S4 s4t_j = 0; s4t_j < INPUT_LAYER; s4t_j++) {
            if (gene_white_parent[0].ppf4_weight[s4t_i][s4t_j] >= gene_white_parent[1].ppf4_weight[s4t_i][s4t_j]) {
                f4t_weight_tmp = gene_white_parent[0].ppf4_weight[s4t_i][s4t_j] - gene_white_parent[1].ppf4_weight[s4t_i][s4t_j];
                f4t_weight_max_white = gene_white_parent[0].ppf4_weight[s4t_i][s4t_j] + f4t_weight_tmp * ALPHA;
                f4t_weight_min_white[s4t_i][s4t_j] = gene_white_parent[1].ppf4_weight[s4t_i][s4t_j] - f4t_weight_tmp * ALPHA;
            }
            else {
                f4t_weight_tmp = gene_white_parent[1].ppf4_weight[s4t_i][s4t_j] - gene_white_parent[0].ppf4_weight[s4t_i][s4t_j];
                f4t_weight_max_white = gene_white_parent[1].ppf4_weight[s4t_i][s4t_j] + f4t_weight_tmp * ALPHA;
                f4t_weight_min_white[s4t_i][s4t_j] = gene_white_parent[0].ppf4_weight[s4t_i][s4t_j] - f4t_weight_tmp * ALPHA;
            }
            f4t_weight_diff_white[s4t_i][s4t_j] = f4t_weight_max_white - f4t_weight_min_white[s4t_i][s4t_j];

            if (gene_black_parent[0].ppf4_weight[s4t_i][s4t_j] >= gene_black_parent[1].ppf4_weight[s4t_i][s4t_j]) {
                f4t_weight_tmp = gene_black_parent[0].ppf4_weight[s4t_i][s4t_j] - gene_black_parent[1].ppf4_weight[s4t_i][s4t_j];
                f4t_weight_max_black = gene_black_parent[0].ppf4_weight[s4t_i][s4t_j] + f4t_weight_tmp * ALPHA;
                f4t_weight_min_black[s4t_i][s4t_j] = gene_black_parent[1].ppf4_weight[s4t_i][s4t_j] - f4t_weight_tmp * ALPHA;
            }
            else {
                f4t_weight_tmp = gene_black_parent[1].ppf4_weight[s4t_i][s4t_j] - gene_black_parent[0].ppf4_weight[s4t_i][s4t_j];
                f4t_weight_max_black = gene_black_parent[1].ppf4_weight[s4t_i][s4t_j] + f4t_weight_tmp * ALPHA;
                f4t_weight_min_black[s4t_i][s4t_j] = gene_black_parent[0].ppf4_weight[s4t_i][s4t_j] - f4t_weight_tmp * ALPHA;
            }
            f4t_weight_diff_black[s4t_i][s4t_j] = f4t_weight_max_black - f4t_weight_min_black[s4t_i][s4t_j];
        }

        if (gene_white_parent[0].pf4_bias[s4t_i] >= gene_white_parent[1].pf4_bias[s4t_i]) {
            f4t_bias_tmp = gene_white_parent[0].pf4_bias[s4t_i] - gene_white_parent[1].pf4_bias[s4t_i];
            f4t_bias_max_white = gene_white_parent[0].pf4_bias[s4t_i] + f4t_bias_tmp * ALPHA;
            f4t_bias_min_white[s4t_i] = gene_white_parent[1].pf4_bias[s4t_i] - f4t_bias_tmp * ALPHA;
        }
        else {
            f4t_bias_tmp = gene_white_parent[1].pf4_bias[s4t_i] - gene_white_parent[0].pf4_bias[s4t_i];
            f4t_bias_max_white = gene_white_parent[1].pf4_bias[s4t_i] + f4t_bias_tmp * ALPHA;
            f4t_bias_min_white[s4t_i] = gene_white_parent[0].pf4_bias[s4t_i] - f4t_bias_tmp * ALPHA;
        }
        f4t_bias_diff_white[s4t_i] = f4t_bias_max_white - f4t_bias_min_white[s4t_i];

        if (gene_black_parent[0].pf4_bias[s4t_i] >= gene_black_parent[1].pf4_bias[s4t_i]) {
            f4t_bias_tmp = gene_black_parent[0].pf4_bias[s4t_i] - gene_black_parent[1].pf4_bias[s4t_i];
            f4t_bias_max_black = gene_black_parent[0].pf4_bias[s4t_i] + f4t_bias_tmp * ALPHA;
            f4t_bias_min_black[s4t_i] = gene_black_parent[1].pf4_bias[s4t_i] - f4t_bias_tmp * ALPHA;
        }
        else {
            f4t_bias_tmp = gene_black_parent[1].pf4_bias[s4t_i] - gene_black_parent[0].pf4_bias[s4t_i];
            f4t_bias_max_black = gene_black_parent[1].pf4_bias[s4t_i] + f4t_bias_tmp * ALPHA;
            f4t_bias_min_black[s4t_i] = gene_black_parent[0].pf4_bias[s4t_i] - f4t_bias_tmp * ALPHA;
        }
        f4t_bias_diff_black[s4t_i] = f4t_bias_max_black - f4t_bias_min_black[s4t_i];

    }

    for (s4t_num = 0; s4t_num < 2; s4t_num++) {
        for (S4 s4t_i = 0; s4t_i < OUTPUT_LAYER; s4t_i++) {
            for (S4 s4t_j = 0; s4t_j < INPUT_LAYER; s4t_j++) {
                gene_white[s4t_num].ppf4_weight[s4t_i][s4t_j] = gene_white_parent[s4t_num].ppf4_weight[s4t_i][s4t_j];
                gene_black[s4t_num].ppf4_weight[s4t_i][s4t_j] = gene_black_parent[s4t_num].ppf4_weight[s4t_i][s4t_j];
            }

            gene_white[s4t_num].pf4_bias[s4t_i] = gene_white_parent[s4t_num].pf4_bias[s4t_i];
            gene_black[s4t_num].pf4_bias[s4t_i] = gene_black_parent[s4t_num].pf4_bias[s4t_i];
        }
    }

    for (s4t_num = 2; s4t_num < NUM_GENE; s4t_num++) {
        for (S4 s4t_i = 0; s4t_i < OUTPUT_LAYER; s4t_i++) {
            for (S4 s4t_j = 0; s4t_j < INPUT_LAYER; s4t_j++) {
                clock_gettime(CLOCK_MONOTONIC, &ts);
                srand(ts.tv_nsec);
                gene_white[s4t_num].ppf4_weight[s4t_i][s4t_j] = f4t_weight_min_white[s4t_i][s4t_j] + ((float)rand() / (float)RAND_MAX) * f4t_weight_diff_white[s4t_i][s4t_j];
                gene_black[s4t_num].ppf4_weight[s4t_i][s4t_j] = f4t_weight_min_black[s4t_i][s4t_j] + ((float)rand() / (float)RAND_MAX) * f4t_weight_diff_black[s4t_i][s4t_j];
            }

            gene_white[s4t_num].pf4_bias[s4t_i] = f4t_bias_min_white[s4t_i] + ((float)rand() / (float)RAND_MAX) * f4t_bias_diff_white[s4t_i];
            gene_black[s4t_num].pf4_bias[s4t_i] = f4t_bias_min_black[s4t_i] + ((float)rand() / (float)RAND_MAX) * f4t_bias_diff_black[s4t_i];

        }
    }
}
/* Sub */