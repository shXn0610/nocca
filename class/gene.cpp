/* Includes */
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "gene.h"

using namespace std;

/* Defines */
#define WEIGHT_MAX (75.0f)

/* Variables */

/* prototypes */

/* Public */
Gene::Gene() {
    s4_count_win = 0;
};

Gene::~Gene() {

};

void Gene::initWeight(S4 s4_input_layer, S4 s4_output_layer) {
    struct timespec ts;

    ppf4_weight = (F4**)malloc(sizeof(F4*) * s4_output_layer);
    
    for (S4 s4t_i = 0; s4t_i < s4_output_layer; s4t_i++) {
        ppf4_weight[s4t_i] = (F4*)malloc(sizeof(F4) * s4_input_layer);
    }

    for (S4 s4t_j = 0; s4t_j < s4_input_layer; s4t_j++) {
        for (S4 s4t_i = 0; s4t_i < s4_output_layer; s4t_i++) {
            clock_gettime(CLOCK_MONOTONIC, &ts);
            srand(ts.tv_nsec);
            ppf4_weight[s4t_i][s4t_j] = ((float)rand() / (float)RAND_MAX) * WEIGHT_MAX - 0.5f * WEIGHT_MAX;
        }
    }
}

void Gene::clearWeight(S4 s4_input_layer, S4 s4_output_layer) {

    for (S4 s4t_i = 0; s4t_i < s4_output_layer; s4t_i++) {
        free(ppf4_weight[s4t_i]);
    }

    free(ppf4_weight);
}
/* Sub */