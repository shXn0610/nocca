/* Includes */
#include <iostream>
#include "..\inc\typedefs.h"
#include "..\class\judgeman.h"

using namespace std;

/* Variables */

/* prototypes */

/* Public */
Judgeman::Judgeman(Player player_white, Player player_black) {
	S4 s4t_i = 0;

	for (s4t_i = 0; s4t_i < 15; s4t_i++) {
		Judgeman::s4_positionWhite_save[s4t_i] = player_white.as4_position[s4t_i]; 
		Judgeman::s4_positionBlack_save[s4t_i] = player_black.as4_position[s4t_i]; 
	}
};

Judgeman::~Judgeman(void) {
	/* NOP */
};

EN_STATE Judgeman::judgeWinLose(Player player_white, Player player_black, EN_STATE en_state) {
	S4		s4t_i;
	S4		s4t_j;
	S4		s4t_k;
	S4		s4t_num_white;
	S4		s4t_num_black;
	S4		s4t_count;
	S4		s4t_flag;
	S4		as4_diff_player_white[15];
	S4		as4_diff_player_black[15];

	/* Calc Diff */
	for (s4t_i = 0; s4t_i < 15; s4t_i++) {
		as4_diff_player_white[s4t_i] = player_white.as4_position[s4t_i] - this->s4_positionWhite_save[s4t_i];
		as4_diff_player_black[s4t_i] = player_black.as4_position[s4t_i] - this->s4_positionBlack_save[s4t_i];
	}

	switch(en_state) {
		case WhitePlay:
			/* Check Difference */
			s4t_count = 0;

			for (s4t_i = 0; s4t_i < 15; s4t_i++) {
				if (as4_diff_player_white[s4t_i] == 0) {
					s4t_count++;
				}
				else {
					break;
				}
			}
			
			if (s4t_count == 15) {
				/* White doesn't move. So Black wins. */
				//cout << "Black wins. White doesn't move.\n";
				return BlackWin;
			}
			else {
				/* NOP */
			}

			/* Check that the block moves over 2 squares. */
			for (s4t_i = 0; s4t_i < 5; s4t_i++) {
				if ((as4_diff_player_white[s4t_i * 3 + 0] > 1) ||
					(as4_diff_player_white[s4t_i * 3 + 0] < (-1)) ||
					(as4_diff_player_white[s4t_i * 3 + 1] > 1) ||
					(as4_diff_player_white[s4t_i * 3 + 1] < (-1)))
				{
					/* White cheated. */
					//cout << "Black wins. White moves over 2 squares.\n";
					return BlackWin;
				}

				else {
					/* NOP */
				}
			}

			/* Check that the block is out of board. */
			for (s4t_i = 0; s4t_i < 5; s4t_i++) {
				if ((player_white.as4_position[3 * s4t_i + 0] < 0) ||
					(player_white.as4_position[3 * s4t_i + 0] > 4) ||
					(player_white.as4_position[3 * s4t_i + 1] < 0) ||
					(player_white.as4_position[3 * s4t_i + 2] > 2))
				{
				/* White mistaked */
				//cout << "Black wins. White is out of the board.\n";
				return BlackWin;
				}
				else {
					/* NOP */
				}
			}

			/* Check the space */
			s4t_flag = 0;
			s4t_count = 0;

			for (s4t_num_white = 0; s4t_num_white < 5; s4t_num_white++) {
				if (player_white.as4_position[3 * s4t_num_white + 2] == 0) {
					s4t_count++;
				}
				else {
					for (s4t_i = 0; s4t_i < 5; s4t_i++) {
						if (((player_white.as4_position[3 * s4t_i + 0] ==  player_white.as4_position[3 * s4t_num_white + 0]) &&
							 (player_white.as4_position[3 * s4t_i + 1] ==  player_white.as4_position[3 * s4t_num_white + 1]) &&
							 (player_white.as4_position[3 * s4t_i + 2] ==  (player_white.as4_position[3 * s4t_num_white + 2] - 1))) ||
							((player_black.as4_position[3 * s4t_i + 0] ==  player_white.as4_position[3 * s4t_num_white + 0]) &&
						     (player_black.as4_position[3 * s4t_i + 1] ==  player_white.as4_position[3 * s4t_num_white + 1]) &&
							 (player_black.as4_position[3 * s4t_i + 2] ==  (player_white.as4_position[3 * s4t_num_white + 2] - 1)))
						) {
							s4t_flag = 1;
						}
						else {
							/* NOP */
						}
					}
				}
			}
			for (s4t_num_black = 0; s4t_num_black < 5; s4t_num_black++) {
				if (player_black.as4_position[3 * s4t_num_black + 2] == 0) {
					s4t_count++;
				}
				else {
					for (s4t_i = 0; s4t_i < 5; s4t_i++) {
						if (((player_white.as4_position[3 * s4t_i + 0] ==  player_black.as4_position[3 * s4t_num_black + 0]) &&
							 (player_white.as4_position[3 * s4t_i + 1] ==  player_black.as4_position[3 * s4t_num_black + 1]) &&
							 (player_white.as4_position[3 * s4t_i + 2] ==  (player_black.as4_position[3 * s4t_num_black + 2] - 1))) ||
							((player_black.as4_position[3 * s4t_i + 0] ==  player_black.as4_position[3 * s4t_num_black + 0]) &&
						     (player_black.as4_position[3 * s4t_i + 1] ==  player_black.as4_position[3 * s4t_num_black + 1]) &&
							 (player_black.as4_position[3 * s4t_i + 2] ==  (player_black.as4_position[3 * s4t_num_black + 2] - 1)))
						) {
							s4t_flag = 1;
						}
						else {
							/* NOP */
						}
					}
				}
			}

			if ((s4t_count != 10) && (s4t_flag == 0)) {
				/* White makes space. */
				//cout << "Black wins. White makes space.\n";
				return BlackWin;
			}
			else {
				/* NOP */
			}

			/* Judge Win or Lose 1 */
			for (s4t_i = 0; s4t_i < 5; s4t_i++) {
				if (player_white.as4_position[s4t_i * 3 + 1] == 6) {
					/* White Wins */
					//cout << "White Wins. White reaches the end line.\n";
					return WhiteWin;
				}
				else {
					/* NOP */
				}
			}

			/* Judge Win or Lose 2 */
			s4t_count = 0;

			/* 黒の上に白があるか数える */
			for (s4t_num_black = 0; s4t_num_black < 5; s4t_num_black++) {
				
				s4t_flag = 0;
			
				for (s4t_k = (player_black.as4_position[s4t_num_black * 3 + 2] + 1); s4t_k < 3; s4t_k++) {
					for (s4t_num_white = 0; s4t_num_white < 5; s4t_num_white++) {
						if ((player_white.as4_position[s4t_num_white * 3 + 0] == player_black.as4_position[s4t_num_black * 3 + 0]) &&
							(player_white.as4_position[s4t_num_white * 3 + 1] == player_black.as4_position[s4t_num_black * 3 + 1]) &&
							(player_white.as4_position[s4t_num_white * 3 + 2] == s4t_k))
						{
							s4t_flag = 1;
						}
						else {
							/* NOP */
						}
					}
				}

				if (s4t_flag == 1) {
					s4t_count++;
				}
				else {
					/* NOP */
				}	
			}

			if (s4t_count == 5) {
				//cout << "White overwelms Black.\n";
				return WhiteWin;
			}
			else {
				/* NOP */
			}

			/* Update Position */
			for (s4t_i = 0; s4t_i < 15; s4t_i++) {
				Judgeman::s4_positionWhite_save[s4t_i] = player_white.as4_position[s4t_i]; 
				Judgeman::s4_positionBlack_save[s4t_i] = player_black.as4_position[s4t_i]; 
			}

			//cout << "White moved.\n\n";
			return BlackPlay;

			break;

		case BlackPlay:
			/* Check Difference */
			s4t_count = 0;

			for (s4t_i = 0; s4t_i < 15; s4t_i++) {
				if (as4_diff_player_black[s4t_i] == 0) {
					s4t_count++;
				}
				else {
					break;
				}
			}
			
			if (s4t_count == 15) {
				/* Black doesn't move. So White wins. */
				//cout << "White wins. Black doesn't move.\n";
				return WhiteWin;
			}
			else {
				/* NOP */
			}

			/* Check that the block moves over 2 squares. */
			for (s4t_i = 0; s4t_i < 5; s4t_i++) {
				if ((as4_diff_player_black[s4t_i * 3 + 0] > 1) ||
					(as4_diff_player_black[s4t_i * 3 + 0] < (-1)) ||
					(as4_diff_player_black[s4t_i * 3 + 1] > 1) ||
					(as4_diff_player_black[s4t_i * 3 + 1] < (-1)))
				{
					/* Black cheated. */
					//cout << "White wins. Black moves over 2 squares.\n";
					return WhiteWin;
				}

				else {
					/* NOP */
				}
			}

			/* Check that the block is out of board. */
			for (s4t_i = 0; s4t_i < 5; s4t_i++) {
				if ((player_black.as4_position[3 * s4t_i + 0] < 0) ||
					(player_black.as4_position[3 * s4t_i + 0] > 4) ||
					(player_black.as4_position[3 * s4t_i + 1] > 5) ||
					(player_black.as4_position[3 * s4t_i + 2] > 2))
				{
				/* Black mistaked */
				//cout << "White wins. Black is out of the board.\n";
				return WhiteWin;
				}
				else {
					/* NOP */
				}
			}

			/* Check the space */
			s4t_flag = 0;
			s4t_count = 0;

			for (s4t_num_white = 0; s4t_num_white < 5; s4t_num_white++) {
				if (player_white.as4_position[3 * s4t_num_white + 2] == 0) {
					s4t_count++;
				}
				else {
					for (s4t_i = 0; s4t_i < 5; s4t_i++) {
						if (((player_white.as4_position[3 * s4t_i + 0] ==  player_white.as4_position[3 * s4t_num_white + 0]) &&
							 (player_white.as4_position[3 * s4t_i + 1] ==  player_white.as4_position[3 * s4t_num_white + 1]) &&
							 (player_white.as4_position[3 * s4t_i + 2] ==  (player_white.as4_position[3 * s4t_num_white + 2] - 1))) ||
							((player_black.as4_position[3 * s4t_i + 0] ==  player_white.as4_position[3 * s4t_num_white + 0]) &&
						     (player_black.as4_position[3 * s4t_i + 1] ==  player_white.as4_position[3 * s4t_num_white + 1]) &&
							 (player_black.as4_position[3 * s4t_i + 2] ==  (player_white.as4_position[3 * s4t_num_white + 2] - 1)))
						) {
							s4t_flag = 1;
						}
						else {
							/* NOP */
						}
					}
				}
			}
			for (s4t_num_black = 0; s4t_num_black < 5; s4t_num_black++) {
				if (player_black.as4_position[3 * s4t_num_black + 2] == 0) {
					s4t_count++;
				}
				else {
					for (s4t_i = 0; s4t_i < 5; s4t_i++) {
						if (((player_white.as4_position[3 * s4t_i + 0] ==  player_black.as4_position[3 * s4t_num_black + 0]) &&
							 (player_white.as4_position[3 * s4t_i + 1] ==  player_black.as4_position[3 * s4t_num_black + 1]) &&
							 (player_white.as4_position[3 * s4t_i + 2] ==  (player_black.as4_position[3 * s4t_num_black + 2] - 1))) ||
							((player_black.as4_position[3 * s4t_i + 0] ==  player_black.as4_position[3 * s4t_num_black + 0]) &&
						     (player_black.as4_position[3 * s4t_i + 1] ==  player_black.as4_position[3 * s4t_num_black + 1]) &&
							 (player_black.as4_position[3 * s4t_i + 2] ==  (player_black.as4_position[3 * s4t_num_black + 2] - 1)))
						) {
							s4t_flag = 1;
						}
						else {
							/* NOP */
						}
					}
				}
			}

			if ((s4t_count != 10) && (s4t_flag == 0)) {
				/* White makes space. */
				//cout << "White wins. Black makes space.\n";
				return WhiteWin;
			}
			else {
				/* NOP */
			}

			/* Judge Win or Lose 1 */
			for (s4t_i = 0; s4t_i < 5; s4t_i++) {
				if (player_black.as4_position[s4t_i * 3 + 1] == (-1)) {
					/* Black Wins */
					//cout << "Black Wins. Black reaches the end line.\n";
					return BlackWin;
				}
				else {
					/* NOP */
				}
			}

			/* Judge Win or Lose 2 */
			s4t_count = 0;

			/* 黒の上に白があるか数える */
			for (s4t_num_white = 0; s4t_num_white < 5; s4t_num_white++) {
				
				s4t_flag = 0;
			
				for (s4t_k = (player_white.as4_position[s4t_num_white * 3 + 2] + 1); s4t_k < 3; s4t_k++) {
					for (s4t_num_black = 0; s4t_num_black < 5; s4t_num_black++) {
						if ((player_black.as4_position[s4t_num_black * 3 + 0] == player_white.as4_position[s4t_num_white * 3 + 0]) &&
							(player_black.as4_position[s4t_num_black * 3 + 1] == player_white.as4_position[s4t_num_white * 3 + 1]) &&
							(player_black.as4_position[s4t_num_black * 3 + 2] == s4t_k))
						{
							s4t_flag = 1;
						}
						else {
							/* NOP */
						}
					}
				}

				if (s4t_flag == 1) {
					s4t_count++;
				}
				else {
					/* NOP */
				}	
			}

			if (s4t_count == 5) {
				//cout << "Black overwelms White.\n";
				return BlackWin;
			}
			else {
				/* NOP */
			}

			/* Update Position */
			for (s4t_i = 0; s4t_i < 15; s4t_i++) {
				Judgeman::s4_positionWhite_save[s4t_i] = player_white.as4_position[s4t_i]; 
				Judgeman::s4_positionBlack_save[s4t_i] = player_black.as4_position[s4t_i]; 
			}

			//cout << "Black moved.\n\n";
			return WhitePlay;
			break;

		default:
			break;

	}
	return Error;
}
/* Private */
