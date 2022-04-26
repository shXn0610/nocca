#ifndef NOCCA_H
#define NOCCA_H

/* Incluldes */
#include "..\inc\typedefs.h"
#include "player.h"
#include "board.h"
#include "gene.h"

/* Defines */

/* Macro Functions */

/* Variables */

/* Constants */

/* Class */
class Nocca {
	public:
		Nocca(void);
		~Nocca(void);

    	void startGamePvP(void);
		void startGamePvC(void);
		void startGameCvC(void);
		EN_STATE startGameGA(Gene *gene_white, Gene *gene_black);

	private:
    
};

/* Prototypes */

#endif /* #ifndef NOCCA_H */