#ifndef GENE_H
#define GENE_H

/* Incluldes */
#include "..\inc\typedefs.h"
#include "..\class\gene.h"

/* Defines */

/* Macro Functions */

/* Variables */

/* Constants */

/* Class */
class Gene {
public:
	Gene(void);
	~Gene(void);

	void vdg_init(S4 s4_layer_input, S4 s4_layer_output, EN_COLOR en_color);

	S4	s4t_count_win = 0;
	F4	*pf4t_gene = NULL;
	EN_COLOR en_color;

private:
    
};

/* Prototypes */

#endif /* #ifndef GENE_H */