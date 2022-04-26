/* Includes */
#include <iostream>
#include "board.h"

using namespace std;

/* Variables */

/* prototypes */

/* Public */
Board::Board() {
    S4 s4t_i = 0;

    /* initialize white blocks */
    for (s4t_i = 0; s4t_i < 5; s4t_i++) {
        this->blocks[s4t_i].s4_x = s4t_i;
        this->blocks[s4t_i].s4_y = 0;
        this->blocks[s4t_i].s4_z = 0;
        this->blocks[s4t_i].en_color = WHITE;
    }
    /* initialize black blocks */
    for (s4t_i = 5; s4t_i < 10; s4t_i++) {
        this->blocks[s4t_i].s4_x = s4t_i % 5;
        this->blocks[s4t_i].s4_y = 5;
        this->blocks[s4t_i].s4_z = 0;
        this->blocks[s4t_i].en_color = BLACK;
    }

    /* initialize pre-blocks */
        for (s4t_i = 0; s4t_i < 10; s4t_i++) {
        this->blocks_pre[s4t_i].s4_x = this->blocks[s4t_i].s4_x;
        this->blocks_pre[s4t_i].s4_y = this->blocks[s4t_i].s4_y;
        this->blocks_pre[s4t_i].s4_z = this->blocks[s4t_i].s4_z;
    }

    /* initialize differences of blocks */
        for (s4t_i = 0; s4t_i < 10; s4t_i++) {
        this->blocks_diff[s4t_i].s4_x = this->blocks[s4t_i].s4_x - this->blocks_pre[s4t_i].s4_x;
        this->blocks_diff[s4t_i].s4_y = this->blocks[s4t_i].s4_y - this->blocks_pre[s4t_i].s4_y;
        this->blocks_diff[s4t_i].s4_z = this->blocks[s4t_i].s4_z - this->blocks_pre[s4t_i].s4_z;
    }
};

Board::~Board() {

};

void Board::showBoard(void) {
	S4 s4t_x;
	S4 s4t_y;
	S4 s4t_z;
	S4 s4t_i;
	S4 s4t_j;

	for (s4t_y = 5; s4t_y >= 0; s4t_y--) {
		for (s4t_z = 0; s4t_z < 3; s4t_z++) {
			for (s4t_x = 0; s4t_x < 5; s4t_x++) {
				for (s4t_i = 0; s4t_i < 5; s4t_i++) {
					if ((blocks[s4t_i].s4_x == s4t_x) &&
						(blocks[s4t_i].s4_y == s4t_y) &&
						(blocks[s4t_i].s4_z == s4t_z)
					) {
						//cout << "w" << s4t_i << " ";
						break;
					}
				}
				for (s4t_j = 5; s4t_j < 10; s4t_j++) {
					if ((blocks[s4t_j].s4_x == s4t_x) &&
						(blocks[s4t_j].s4_y == s4t_y) &&
						(blocks[s4t_j].s4_z == s4t_z)
					) {
						//cout << "b" << s4t_j % 5 << " ";
						break;
					}
					else {
						/*  NOP */
					}
				}
				if ((s4t_i == 5) && (s4t_j == 10)) {
					//cout << "-- ";
				}
				else {
					/* NOP */
				}
			}

			/* spacer */
			//cout << "    ";
		}
		//cout << "\n";
	}

	//cout << "\n";
}

void Board::updateBoard(S4 s4_idx, S4 s4_dx, S4 s4_dy, EN_COLOR en_color) {

	if ((bl_checkMove(s4_idx, s4_dx, s4_dy, en_color)) && (bl_checkBlockOn(s4_idx, en_color))) {
		vdg_updateBoard(s4_idx, s4_dx, s4_dy, en_color);
	}
	else {
		/* NOP */
	}
}

bool Board::bl_checkMove(S4 s4_idx, S4 s4_dx, S4 s4_dy, EN_COLOR en_color) {

	switch (en_color) {
		case (WHITE):
			if (((s4_idx >= 0) && (s4_idx <= 4)) &&
				((s4_dx >= -1) && (s4_dx <= 1)) &&
				((s4_dy >= -1) && (s4_dy <= 1)) &&
				(!((s4_dx == 0) && (s4_dy == 0)))
			) {
				return true;
			}
			else {
				return false;
			}
			break;
		case (BLACK):
			if (((s4_idx >= 0) && (s4_idx <= 4)) &&
				((s4_dx >= -1) && (s4_dx <= 1)) &&
				((s4_dy >= -1) && (s4_dy <= 1)) &&
				(!((s4_dx == 0) && (s4_dy == 0)))
			) {
				return true;
			}
			else {
				return false;
			}
			break;
		default:
			break;
	}

	return false;
};

bool Board::bl_checkBlockOn(S4 s4_idx, EN_COLOR en_color) {
	S4 s4t_x = 0;
	S4 s4t_y = 0;
	S4 s4t_z = 0;

	if (en_color == WHITE) {
		s4t_x = this->blocks[s4_idx].s4_x;
		s4t_y = this->blocks[s4_idx].s4_y;
		s4t_z = this->blocks[s4_idx].s4_z + 1;
	}
	else if (en_color == BLACK) {
		s4t_x = this->blocks[s4_idx + 5].s4_x;
		s4t_y = this->blocks[s4_idx + 5].s4_y;
		s4t_z = this->blocks[s4_idx + 5].s4_z + 1;
	}
	else {
		/* NOP */
	}

	for (S4 s4t_i = 0; s4t_i < 10; s4t_i++) {
		if ((s4t_x == this->blocks[s4t_i].s4_x) &&
			(s4t_y == this->blocks[s4t_i].s4_y) &&
			(s4t_z == this->blocks[s4t_i].s4_z)) {
			return false;
		}
		else {
			/* NOP */
		}
	}

	return true;
};

void Board::vdg_updateBoard(S4 s4_idx, S4 s4_dx, S4 s4_dy, EN_COLOR en_color) {
	S4 s4t_x_updated = 0;
	S4 s4t_y_updated = 0;
	S4 s4t_z_updated = 0;
	S4 s4t_count = 0;

	
	if (en_color == WHITE) {

		#if 1
		//cout << "w* : " << s4_idx << "\n";
		//cout << "dx : " << s4_dx << "\n";
		//cout << "dy : " << s4_dy << "\n"; 
		//cout << "\n";
		#endif

		/* Calculate X and Y */
		s4t_x_updated = this->blocks[s4_idx].s4_x + s4_dx;
		s4t_y_updated = this->blocks[s4_idx].s4_y + s4_dy;

		/* Calculate Z */
		for (S4 s4t_i = 0; s4t_i < 10; s4t_i++) {
			if ((s4t_x_updated == this->blocks[s4t_i].s4_x) &&
				(s4t_y_updated == this->blocks[s4t_i].s4_y)
			) {
				s4t_count++;
			}
			else {
				/* NOP */
			}
		}

		s4t_z_updated = s4t_count;

		/* Update */
		this->blocks[s4_idx].s4_x = s4t_x_updated;
		this->blocks[s4_idx].s4_y = s4t_y_updated;
		this->blocks[s4_idx].s4_z = s4t_z_updated;
	}
	else if (en_color == BLACK) {

		#if 1
		//cout << "b* : " << s4_idx << "\n";
		//cout << "dx : " << s4_dx << "\n";
		//cout << "dy : " << s4_dy << "\n"; 
		//cout << "\n";
		#endif

		/* Calculate X and Y */
		s4t_x_updated = this->blocks[s4_idx + 5].s4_x + s4_dx;
		s4t_y_updated = this->blocks[s4_idx + 5].s4_y + s4_dy;

		/* Calculate Z */
		for (S4 s4t_i = 0; s4t_i < 10; s4t_i++) {
			if ((s4t_x_updated == this->blocks[s4t_i].s4_x) &&
				(s4t_y_updated == this->blocks[s4t_i].s4_y)
			) {
				s4t_count++;
			}
			else {
				/* NOP */
			}
		}

		s4t_z_updated = s4t_count;

		/* Update */
		this->blocks[s4_idx + 5].s4_x = s4t_x_updated;
		this->blocks[s4_idx + 5].s4_y = s4t_y_updated;
		this->blocks[s4_idx + 5].s4_z = s4t_z_updated;

	}
	else {
		/* NOP */
	}

};

EN_STATE Board::judgeWinLose(EN_STATE en_state) {
	EN_STATE en_result;
	en_result = en_state;

	calcDiff();
	updateBlocksPre();
	en_result = checkDiff(en_state);
	if (en_result == WHITE_WIN) {
		return WHITE_WIN;
	}
	else if (en_result == BLACK_WIN) {
		return BLACK_WIN;
	}
	else {
		/* NOP */
	}

	en_result = checkOutOfBoard(en_state);
	if (en_result == WHITE_WIN) {
		return WHITE_WIN;
	}
	else if (en_result == BLACK_WIN) {
		return BLACK_WIN;
	}
	else {
		/* NOP */
	}

	en_result = checkReachEndline(en_state);
	if (en_result == WHITE_WIN) {
		return WHITE_WIN;
	}
	else if (en_result == BLACK_WIN) {
		return BLACK_WIN;
	}
	else {
		/* NOP */
	}

	en_result = checkOverwhelm(en_state);
	if (en_result == WHITE_WIN) {
		return WHITE_WIN;
	}
	else if (en_result == BLACK_WIN) {
		return BLACK_WIN;
	}
	else {
		/* NOP */
	}

	switch (en_state) {
		case WHITE_PLAYING:
			return BLACK_PLAYING;
			break;
		case BLACK_PLAYING:
			return WHITE_PLAYING;
			break;
		default:
			break;
	}
	return WHITE_WIN;
}

void Board::calcDiff() {
	for (S4 s4t_i = 0; s4t_i < 10; s4t_i++) {
		this->blocks_diff[s4t_i].s4_x = this->blocks_pre[s4t_i].s4_x - this->blocks[s4t_i].s4_x;
		this->blocks_diff[s4t_i].s4_y = this->blocks_pre[s4t_i].s4_y - this->blocks[s4t_i].s4_y;
		this->blocks_diff[s4t_i].s4_z = this->blocks_pre[s4t_i].s4_z - this->blocks[s4t_i].s4_z;
	}
}

void Board::updateBlocksPre() {
	for (S4 s4t_i = 0; s4t_i < 10; s4t_i++) {
		this->blocks_pre[s4t_i].s4_x = this->blocks[s4t_i].s4_x;
		this->blocks_pre[s4t_i].s4_y = this->blocks[s4t_i].s4_y;
		this->blocks_pre[s4t_i].s4_z = this->blocks[s4t_i].s4_z;
	}
}

EN_STATE Board::checkDiff(EN_STATE en_state) {
	S4 s4t_flag = 0;

	for (S4 s4t_i = 0; s4t_i < 10; s4t_i++) {
		if ((this->blocks_diff[s4t_i].s4_x != 0) ||
			(this->blocks_diff[s4t_i].s4_y != 0) ||
			(this->blocks_diff[s4t_i].s4_z != 0)
		) {
			s4t_flag = 1;
			break;
		}
		else {
			/* NOP */
		}
	}

	if (s4t_flag == 0) {
		if (en_state == WHITE_PLAYING) {
			//cout << "White didn't move.\n";
			return BLACK_WIN;
		}
		else if (en_state == BLACK_PLAYING) {
			//cout << "Black didn't mobe.\n";
			return WHITE_WIN;
		}
		else {
			/* NOP */
		}
	}
	else {
		if (en_state == WHITE_PLAYING) {
			return WHITE_PLAYING;
		}
		else if (en_state == BLACK_PLAYING) {
			return BLACK_PLAYING;
		}
		else {
			/* NOP */
		}
	}

	return WHITE_WIN;
}

EN_STATE Board::checkOutOfBoard(EN_STATE en_state) {
	S4 s4t_flag = 0;
	EN_STATE en_result = en_state;

	if (en_state == WHITE_PLAYING) {
		for (S4 s4t_i = 0; s4t_i < 10; s4t_i++) {
			if(((this->blocks[s4t_i].s4_x >= 0) && (this->blocks[s4t_i].s4_x <= 4)) &&
			   ((this->blocks[s4t_i].s4_y >= 0) && (this->blocks[s4t_i].s4_y <= 6)) &&
			   ((this->blocks[s4t_i].s4_z >= 0) && (this->blocks[s4t_i].s4_z <= 2))
			) {
				/* NOP */
			}
			else {
				s4t_flag = 1;
				break;
			}
		}
		if (s4t_flag == 1) {
			//cout << "White is out of the board.\n";
			en_result = BLACK_WIN;
		}
		else {
			/* NOP */
		}
	}
	else if (en_state == BLACK_PLAYING) {
		for (S4 s4t_i = 0; s4t_i < 10; s4t_i++) {
			if(((this->blocks[s4t_i].s4_x >= 0) && (this->blocks[s4t_i].s4_x <= 4)) &&
			   ((this->blocks[s4t_i].s4_y >= (-1)) && (this->blocks[s4t_i].s4_y <= 5)) &&
			   ((this->blocks[s4t_i].s4_z >= 0) && (this->blocks[s4t_i].s4_z <= 2))
			) {
				/* NOP */
			}
			else {
				s4t_flag = 1;
				break;
			}
		}
		if (s4t_flag == 1) {
			//cout << "Black is out of the board.\n";
			en_result = WHITE_WIN;
		}
		else {
			/* NOP */
		}
	}
	else {
		/* NOP */
	}

	return en_result;
}

EN_STATE Board::checkReachEndline(EN_STATE en_state) {
	EN_STATE en_result = en_state;

	if (en_state == WHITE_PLAYING) {
		for (S4 s4t_i = 0; s4t_i < 5; s4t_i++) {
			if (this->blocks[s4t_i].s4_y == 6) {
				en_result = WHITE_WIN;

				//cout << "White reached the endline.\n";
			}
			else {
				/* NOP */
			}
		}
	}
	else if (en_state == BLACK_PLAYING) {
		for (S4 s4t_i = 5; s4t_i < 10; s4t_i++) {
			if (this->blocks[s4t_i].s4_y == (-1)) {
				en_result = BLACK_WIN;

				//cout << "Black reached the endline.\n";
			}
			else {
				/* NOP */
			}
		}
	}
	else {
		/* NOP */
	}

	return en_result;
}

EN_STATE Board::checkOverwhelm(EN_STATE en_state) {
	EN_STATE en_result = en_state;
	S4 s4t_count = 0;

	if (en_state == WHITE_PLAYING) {
		for (S4 s4t_idx_black = 5; s4t_idx_black < 10; s4t_idx_black++) {
			for (S4 s4t_idx_white = 0; s4t_idx_white < 5; s4t_idx_white++) {
				if ((this->blocks[s4t_idx_white].s4_x == this->blocks[s4t_idx_black].s4_x) &&
					(this->blocks[s4t_idx_white].s4_y == this->blocks[s4t_idx_black].s4_y) &&
					(this->blocks[s4t_idx_white].s4_z >  this->blocks[s4t_idx_black].s4_z)
				) {
					s4t_count++;
					}
				else {
					/* NOP */
				}		
			}
		}
		if (s4t_count == 5) {
			//cout << "White overwhelmed black.\n";
			en_result = WHITE_WIN;
		}
		else {
			/* NOP */
		}
	}
	else if (en_state == BLACK_PLAYING) {
		for (S4 s4t_idx_white = 0; s4t_idx_white < 5; s4t_idx_white++) {
			for (S4 s4t_idx_black = 5; s4t_idx_black < 10; s4t_idx_black++) {
				if ((this->blocks[s4t_idx_black].s4_x == this->blocks[s4t_idx_white].s4_x) &&
					(this->blocks[s4t_idx_black].s4_y == this->blocks[s4t_idx_white].s4_y) &&
					(this->blocks[s4t_idx_black].s4_z >  this->blocks[s4t_idx_white].s4_z)
				) {
					s4t_count++;
					}
				else {
					/* NOP */
				}		
			}
		}
		if (s4t_count == 5) {
			//cout << "Black overwhelmed white.\n";
			en_result = WHITE_WIN;
		}
		else {
			/* NOP */
		}
	}
	else {
		/* NOP */
	}

	return en_result;
}