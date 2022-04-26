#ifndef GENE_H
#define GENE_H

/* Incluldes */
#include "..\inc\typedefs.h"

/* Defines */

/* Macro Functions */

/* Variables */

/* Constants */

/* Class */
class Gene {
public:
	Gene(void);
	~Gene(void);
	void initWeight(S4 s4_input_layer, S4 s4_output_layer);
	void clearWeight(S4 s4_input_layer, S4 s4_output_layer);

	S4 s4_count_win;
	F4 **ppf4_weight;
	
private:
    
};

/* Prototypes */

#endif /* #ifndef GENE_H */