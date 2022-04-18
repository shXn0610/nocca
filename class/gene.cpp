/* Includes */
#include <iostream>
#include <time.h>
#include "..\inc\typedefs.h"
#include "..\class\gene.h"

using namespace std;

/* Variables */

/* prototypes */

/* Public */
Gene::Gene() {
	/* NOP */
};

Gene::~Gene() {
	free(pf4t_gene);
};

void Gene::vdg_init(S4 s4_layer_input, S4 s4_layer_output, EN_COLOR en_color) {
	S4 s4t_i = 0;
	S4 s4t_num_genes = 0;
	Gene::en_color = en_color;
	struct timespec ts;

	s4t_num_genes = s4_layer_input * s4_layer_output;


	Gene::pf4t_gene = (F4*)malloc(sizeof(F4) * s4t_num_genes);

	for (s4t_i = 0; s4t_i < s4t_num_genes; s4t_i++) {
		clock_gettime(CLOCK_MONOTONIC, &ts);
		srand(ts.tv_nsec);
		Gene::pf4t_gene[s4t_i] = ((float)rand() / (float)RAND_MAX) - 0.5f;
	}

};

/* Private */
