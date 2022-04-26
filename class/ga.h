#ifndef GA_H
#define GA_H

/* Incluldes */
#include "..\inc\typedefs.h"
#include "gene.h"

/* Defines */

/* Macro Functions */

/* Variables */

/* Constants */

/* Class */
class GA {
public:
	GA(void);
	~GA(void);
	void startGA();
	
	void evaluation(Gene *gene_white, Gene *gene_black);
	void evolution(Gene *gene_white, Gene *gene_black, Gene *gene_white_parent, Gene *gene_black_parent);
	void selectParent(Gene *gene_white, Gene *gene_black, Gene *gene_white_parent, Gene *gene_black_parent);
	void BLXalpha(Gene *gene_white, Gene *gene_black, Gene *gene_white_parent, Gene *gene_black_parent);
	
private:
    
};

/* Prototypes */

#endif /* #ifndef GA_H */