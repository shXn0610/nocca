/* Includes */
#include <iostream>
#include "..\inc\typedefs.h"
#include "..\class\viewer.h"

using namespace std;

/* Variables */

/* prototypes */

/* Public */
Viewer::Viewer(void) {
	/* NOP */
};

Viewer::~Viewer() {

};

void Viewer::showPosition(Player player_white, Player player_black) {

	S4 s4t_x;
	S4 s4t_y;
	S4 s4t_i;

	for (s4t_y = 0; s4t_y < 6; s4t_y++) {
		for (s4t_x = 0; s4t_x < 5; s4t_x++) {

			for (s4t_i = 0; s4t_i < 5; s4t_i++) {
				if ((s4t_x == player_white.as4_position[s4t_i * 3 + 0]) &&
					(s4t_y == player_white.as4_position[s4t_i * 3 + 1]))
				{
					cout << "w" << s4t_i;
					cout << " ";
				}
				else if ((s4t_x == player_black.as4_position[s4t_i * 3 + 0]) &&
					(s4t_y == player_black.as4_position[s4t_i * 3 + 1]))
				{
					cout << "b" << s4t_i;
					cout << " ";
				}
				else {
					cout << "--";
					cout << " ";
				}
			}
		}
		cout << "\n";
	}

}

/* Private */
