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
	switch (Gene::en_color) {
		case White:
			free(pf4t_gene_white);
			break;
		case Black:
			free(pf4t_gene_black);
			break;
		default:
			break;
	}
};

void Gene::vdg_init(S4 s4_layer_input, S4 s4_layer_output, EN_COLOR en_color) {
	S4 s4t_i = 0;
	S4 s4t_num_genes = 0;
	Gene::en_color = en_color;
	struct timespec ts;

	s4t_num_genes = s4_layer_input * s4_layer_output;

	switch (en_color) {

		case White:
			Gene::pf4t_gene_white = (F4*)malloc(sizeof(F4) * s4t_num_genes);

			for (s4t_i = 0; s4t_i < s4t_num_genes; s4t_i++) {
				clock_gettime(CLOCK_MONOTONIC, &ts);
				srand(ts.tv_nsec);
				Gene::pf4t_gene_white[s4t_i] = ((float)rand() / (float)RAND_MAX) - 0.5f;
			}

			break;
		case Black:
			Gene::pf4t_gene_black = (F4*)malloc(sizeof(F4) * s4t_num_genes);

			for (s4t_i = 0; s4t_i < s4t_num_genes; s4t_i++) {
				clock_gettime(CLOCK_MONOTONIC, &ts);
				srand(ts.tv_nsec);
				Gene::pf4t_gene_black[s4t_i] = ((float)rand() / (float)RAND_MAX) - 0.5f;
			}

			break;
		default:
			break;
	}
};

/* Private */
