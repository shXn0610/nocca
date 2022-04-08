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

	S4 s4t_x = 0;
	S4 s4t_y = 0;
	S4 s4t_z = 0;
	S4 s4t_i;
	S4 s4t_state;

	for (s4t_y = 5; s4t_y >= 0; s4t_y--) {
		for (s4t_x = 0; s4t_x < 15; s4t_x++) {

			s4t_state = 1;

			for (s4t_i = 0; s4t_i < 5; s4t_i++) {
				if ((player_white.as4_position[s4t_i * 3 + 0] == (s4t_x % 5)) &&
					(player_white.as4_position[s4t_i * 3 + 1] == s4t_y) &&
					(player_white.as4_position[s4t_i * 3 + 2] == s4t_z))
				{
					cout << "w" << s4t_i;
					cout << " ";
					s4t_state = 0;
					break;
				}
				else if ((player_black.as4_position[s4t_i * 3 + 0] == (s4t_x % 5)) &&
						 (player_black.as4_position[s4t_i * 3 + 1] == s4t_y) &&
						 (player_black.as4_position[s4t_i * 3 + 2] == s4t_z))
				{
					cout << "b" << s4t_i;
					cout << " ";
					s4t_state = 0;
					break;
				}
				else {
					/*  NOP */
				}
			}
			if (s4t_state == 1) {
				cout << "--";
				cout << " ";
			}
			else {
				/* NOP */
			}
			/* spacer */
			if ((s4t_x == 4) || (s4t_x == 9)) {
				cout << "    ";
				s4t_z++;
			}
			else {
				/* NOP */
			}
			/* return */
			if (s4t_x == 14) {
				cout << "\n";
				s4t_z = 0;
			}
			else {
				/* NOP */
			}
		}
	}

	cout << "\n";
}
/* Private */
