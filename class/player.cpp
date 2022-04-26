/* Includes */
#include <iostream>
#include <time.h>
#include "player.h"

using namespace std;

/* Variables */

/* prototypes */

/* Public */
Player::Player(EN_COLOR en_color) {
    this->color = en_color;
};

Player::~Player() {

};

void Player::moveManually(Board &board) {
    S4 s4t_idx = 0;
	S4 s4t_dx = 0;
	S4 s4t_dy = 0;

    switch (this->color) {
        case WHITE:
			cout << "w*(0 ~ 4) : ";
			cin >> s4t_idx;
            break;
        case BLACK:
			cout << "b*(0 ~ 4) : ";
			cin >> s4t_idx;
            break;
        default:
            break;
    }

	cout << "x(-1 ~ 1) : ";
	cin >> s4t_dx;
	cout << "y(-1 ~ 1) : ";
	cin >> s4t_dy;
	cout << "\n";

    board.updateBoard(s4t_idx, s4t_dx, s4t_dy, this->color);
}

void Player::moveAuto(Board &board) {
    S4 s4t_idx = 0;

    struct timespec ts;
    S4 s4t_temp;
	S4 s4t_dx = 0;
	S4 s4t_dy = 0;

    S4 s4t_count = 0;
    S4 s4t_flag = 0;
    S4 s4t_step = 0;
    S4 s4t_x_updated = 0;
    S4 s4t_y_updated = 0;
    S4 s4t_z_updated = 0;

    while (1) {
        clock_gettime(CLOCK_MONOTONIC, &ts);
        srand(ts.tv_nsec);
				
		/* Choice Block */
		s4t_idx = rand() % 5;

		/* Choice x and y */
		s4t_temp = rand() % 14;

		if (this->color == WHITE) {
			if ((s4t_temp == 0) || (s4t_temp == 1) || (s4t_temp == 2)) {
				s4t_dx = -1;
				s4t_dy = 1;
			}
			else if ((s4t_temp == 3) || (s4t_temp == 4) || (s4t_temp == 5)) {
				s4t_dx = 0;
				s4t_dy = 1;
			}
			else if ((s4t_temp == 6) || (s4t_temp == 7) || (s4t_temp == 8)) {
				s4t_dx = 1;
				s4t_dy = 1;
			}
			else if (s4t_temp == 9) {
				s4t_dx = -1;
				s4t_dy = 0;
			}
			else if (s4t_temp == 10) {
				s4t_dx = 1;
				s4t_dy = 0;
			}
			else if (s4t_temp == 11) {
				s4t_dx = -1;
				s4t_dy = -1;
			}
			else if (s4t_temp == 12) {
				s4t_dx = 0;
				s4t_dy = -1;
			}
			else if (s4t_temp == 13) {
				s4t_dx = 1;
				s4t_dy = -1;
			}
			else {
				/* NOP */
			}
		}
		else if (this->color == BLACK) {
			if ((s4t_temp == 0) || (s4t_temp == 1) || (s4t_temp == 2)) {
				s4t_dx = -1;
				s4t_dy = -1;
			}
			else if ((s4t_temp == 3) || (s4t_temp == 4) || (s4t_temp == 5)) {
				s4t_dx = 0;
				s4t_dy = -1;
			}
			else if ((s4t_temp == 6) || (s4t_temp == 7) || (s4t_temp == 8)) {
				s4t_dx = 1;
				s4t_dy = -1;
			}
			else if (s4t_temp == 9) {
				s4t_dx = -1;
				s4t_dy = 0;
			}
			else if (s4t_temp == 10) {
				s4t_dx = 1;
				s4t_dy = 0;
			}
			else if (s4t_temp == 11) {
				s4t_dx = -1;
				s4t_dy = 1;
			}
			else if (s4t_temp == 12) {
				s4t_dx = 0;
				s4t_dy = 1;
			}
			else if (s4t_temp == 13) {
				s4t_dx = 1;
				s4t_dy = 1;
			}
			else {
				/* NOP */
			}
		}
		else {
			/* NOP */
		}

        if ((board.bl_checkMove(s4t_idx, s4t_dx, s4t_dy, this->color)) &&
            (board.bl_checkBlockOn(s4t_idx, this->color))) {
                
            if (this->color == WHITE) {
                /* Calculate X and Y */
                s4t_x_updated = board.blocks[s4t_idx].s4_x + s4t_dx;
                s4t_y_updated = board.blocks[s4t_idx].s4_y + s4t_dy;

                /* Calculate Z */
                s4t_count = 0;
                for (S4 s4t_i = 0; s4t_i < 10; s4t_i++) {
                    if ((s4t_x_updated == board.blocks[s4t_i].s4_x) &&
                        (s4t_y_updated == board.blocks[s4t_i].s4_y)
                    ) {
                        s4t_count++;
                    }
                    else {
                        /* NOP */
                    }
                }

                s4t_z_updated = s4t_count;

                s4t_flag = 0;
                for (S4 s4t_i = 0; s4t_i < 10; s4t_i++) {
                    if(((s4t_x_updated >= 0) && (s4t_x_updated <= 4)) &&
                    ((s4t_y_updated >= 0) && (s4t_y_updated <= 6)) &&
                    ((s4t_z_updated >= 0) && (s4t_z_updated <= 2))
                    ) {
                        /* NOP */
                    }
                    else {
                        s4t_flag = 1;
                        break;
                    }
                }
            }
            else if (this->color == BLACK) {
                /* Calculate X and Y */
                s4t_x_updated = board.blocks[s4t_idx + 5].s4_x + s4t_dx;
                s4t_y_updated = board.blocks[s4t_idx + 5].s4_y + s4t_dy;

                /* Calculate Z */
                s4t_count = 0;
                for (S4 s4t_i = 0; s4t_i < 10; s4t_i++) {
                    if ((s4t_x_updated == board.blocks[s4t_i].s4_x) &&
                        (s4t_y_updated == board.blocks[s4t_i].s4_y)
                    ) {
                        s4t_count++;
                    }
                    else {
                        /* NOP */
                    }
                }

                s4t_z_updated = s4t_count;

                s4t_flag = 0;
                for (S4 s4t_i = 0; s4t_i < 10; s4t_i++) {
                    if(((s4t_x_updated >= 0) && (s4t_x_updated <= 4)) &&
                       ((s4t_y_updated >= (-1)) && (s4t_y_updated <= 5)) &&
                       ((s4t_z_updated >= 0) && (s4t_z_updated <= 2))
                    ) {
                        /* NOP */
                    }
                    else {
                        s4t_flag = 1;
                        break;
                    }
                }
	        }
	        else {
	    	    /* NOP */
    	    }

            if (s4t_flag == 0) {
                break;
            }
            else {
                /* NOP */
            }
        } 
        else {
            /* NOP */
        }
    } 

    board.updateBoard(s4t_idx, s4t_dx, s4t_dy, this->color);
}

void Player::moveAutoGA(Board &board, Gene &gene) {
    S4 s4t_idx = 0;
	S4 s4t_dx = 0;
	S4 s4t_dy = 0;
    F4 af4t_input[30];
    F4 af4t_output[40];

    F4 f4t_value_max = 0.0f;
    S4 s4t_idx_max = 0;
    S4 s4t_tmp = 0;

    /* Initialize input */
    for (S4 s4t_i = 0; s4t_i < 10; s4t_i++) {
        af4t_input[3 * s4t_i + 0] = (F4)(board.blocks[s4t_i].s4_x);
        af4t_input[3 * s4t_i + 1] = (F4)(board.blocks[s4t_i].s4_y);
        af4t_input[3 * s4t_i + 2] = (F4)(board.blocks[s4t_i].s4_z);
    }
    /* Initialize output */
    for (S4 s4t_i = 0; s4t_i < 40; s4t_i++) {
        af4t_output[s4t_i] = 0.0f;
    }

    /* Calc output */
    for (S4 s4t_i = 0; s4t_i < 40; s4t_i++) {
        for (S4 s4t_j = 0; s4t_j < 30; s4t_j++) {
            af4t_output[s4t_i] += (gene.ppf4_weight[s4t_i][s4t_j] * af4t_input[s4t_j]);
        }
    }

    f4t_value_max = af4t_output[0];
    for (S4 s4t_i = 1; s4t_i < 40; s4t_i++) {
        if (af4t_output[s4t_i] > f4t_value_max) {
            f4t_value_max = af4t_output[s4t_i];
            s4t_idx_max = s4t_i;
        }
        else {
            /* NOP */
        }
    }

    s4t_idx = s4t_idx_max / 8;
    s4t_tmp = s4t_idx_max % 8;

    switch(s4t_tmp) {
		case 0:
			s4t_dx = 1;
			s4t_dy = 1;
			break;
		case 1:
			s4t_dx = 0;
			s4t_dy = 1;
			break;
		case 2:
			s4t_dx = -1;
			s4t_dy = 1;
			break;
		case 3:
			s4t_dx = 1;
			s4t_dy = 0;
			break;
		case 4:
			s4t_dx = -1;
			s4t_dy = 0;
			break;
		case 5:
			s4t_dx = 1;
			s4t_dy = -1;
			break;
		case 6:
			s4t_dx = 0;
			s4t_dy = -1;
			break;
		case 7:
			s4t_dx = -1;
			s4t_dy = -1;
			break;
		default:
			break;
	}

    board.updateBoard(s4t_idx, s4t_dx, s4t_dy, this->color);
}
/* Sub */