/* Includes */
#include <iostream>
#include <time.h>
#include "..\inc\typedefs.h"
#include "..\class\player.h"
#include "..\class\gene.h"

using namespace std;

/* Variables */

/* prototypes */
void 	vdg_InitInput(Player player_this, Player player_enemy, S4 *pas4t_input);
void 	vdg_InitOutput(F4 *paf4t_output);
void 	vdg_Predict(Player player_this, S4 *pas4t_input, F4 *paf4t_output);
S4		s4t_DecodeOutput(F4 *paf4t_output);

/* Public */
Player::Player(EN_COLOR en_color) {
	S4		s4t_i;

	Player::en_color = en_color;

	if (en_color == White) {
		for (s4t_i = 0; s4t_i < 5; s4t_i++) {
			Player::as4_position[s4t_i * 3 + 0] = s4t_i;
			Player::as4_position[s4t_i * 3 + 1] = 0;
			Player::as4_position[s4t_i * 3 + 2] = 0;
		}
	}
	else if (en_color == Black) {
		for (s4t_i = 0; s4t_i < 5; s4t_i++) {
			Player::as4_position[s4t_i * 3 + 0] = s4t_i;
			Player::as4_position[s4t_i * 3 + 1] = 5;
			Player::as4_position[s4t_i * 3 + 2] = 0;
		}
	}
	else {
		/* NOP */
	}

	/* Initialize weight */
	srand(time(NULL));
	for (s4t_i = 0; s4t_i < 1200; s4t_i++) {
		Player::af4_weight[s4t_i] = ((float)rand() / (float)RAND_MAX) - 0.5f;
	}
};

Player::Player(EN_COLOR en_color, Gene *gene) {
	S4		s4t_i;

	Player::en_color = en_color;

	if (en_color == White) {
		for (s4t_i = 0; s4t_i < 5; s4t_i++) {
			Player::as4_position[s4t_i * 3 + 0] = s4t_i;
			Player::as4_position[s4t_i * 3 + 1] = 0;
			Player::as4_position[s4t_i * 3 + 2] = 0;
		}

		srand(time(NULL));
		for (s4t_i = 0; s4t_i < 1200; s4t_i++) {
			Player::af4_weight[s4t_i] = gene->pf4t_gene_white[s4t_i];
		}
	}
	else if (en_color == Black) {
		for (s4t_i = 0; s4t_i < 5; s4t_i++) {
			Player::as4_position[s4t_i * 3 + 0] = s4t_i;
			Player::as4_position[s4t_i * 3 + 1] = 5;
			Player::as4_position[s4t_i * 3 + 2] = 0;
		}
		srand(time(NULL));
		for (s4t_i = 0; s4t_i < 1200; s4t_i++) {
			Player::af4_weight[s4t_i] = gene->pf4t_gene_black[s4t_i];
		}
	}
	else {
		/* NOP */
	}

};


Player::~Player() {

};

S4 Player::moveManually(Player player_enemy) {
	S4	s4t_i;
	S4	s4t_j;

	S4	s4t_num;
	S4	s4t_dx;
	S4	s4t_dy;

	S4	s4t_x;
	S4	s4t_y;
	S4	s4t_z;
	S4	s4t_count;

	S4	s4t_x_updated;
	S4	s4t_y_updated;
	S4	s4t_z_updated;

	if (this->en_color == White) {
		//cout << "w*(0 ~ 4) : ";
    	cin >> s4t_num;
	}
	else {
		//cout << "b*(0 ~ 4) : ";
    	cin >> s4t_num;
	}

    //cout << "x(-1 ~ 1) : ";
    cin >> s4t_dx;
    //cout << "y(-1 ~ 1) : ";
    cin >> s4t_dy;
    //cout << "\n";

	/* Check Error */
	if ((0 <= s4t_num) && (s4t_num < 5)) {
		/* NOP */
	}
	else {
		return 0;
	}

	if ((-1 <= s4t_dx) && (s4t_dx <= 1)) {
		/* NOP */
	}
	else {
		return 0;
	}

	if ((-1 <= s4t_dy) && (s4t_dy <= 1)) {
		/* NOP */
	}
	else {
		return 0;
	}

	if ((s4t_dx == 0) && (s4t_dy == 0)) {
		return 0;
	}
	else {
		/* NOP */
	}

	/* Check the Blocks on itself*/
	s4t_x = this->as4_position[s4t_num * 3 + 0];
	s4t_y = this->as4_position[s4t_num * 3 + 1];
	s4t_z = this->as4_position[s4t_num * 3 + 2] + 1;

	for (S4 s4t_i = 0; s4t_i < 5; s4t_i++) {
		if ((s4t_x == this->as4_position[s4t_i * 3 + 0]) &&
			(s4t_y == this->as4_position[s4t_i * 3 + 1]) &&
			(s4t_z == this->as4_position[s4t_i * 3 + 2]))
		{
			return 0;
		}
		else {
			/* NOP */
		}
	}

	for (S4 s4t_i = 0; s4t_i < 5; s4t_i++) {
		if ((s4t_x == player_enemy.as4_position[s4t_i * 3 + 0]) &&
			(s4t_y == player_enemy.as4_position[s4t_i * 3 + 1]) &&
			(s4t_z == player_enemy.as4_position[s4t_i * 3 + 2]))
		{
			return 0;
		}
		else {
			/* NOP */
		}
	}

	/* Update Position of Z */
	s4t_x_updated = this->as4_position[s4t_num * 3 + 0] + s4t_dx;
	s4t_y_updated = this->as4_position[s4t_num * 3 + 1] + s4t_dy;
	s4t_count = 0;

	for (S4 s4t_i = 0; s4t_i < 5; s4t_i++) {
		if ((s4t_x_updated == this->as4_position[s4t_i * 3 + 0]) &&
			(s4t_y_updated == this->as4_position[s4t_i * 3 + 1]))
		{
			s4t_count++;
		}
		else {
			/* NOP */
		}
	}

	for (S4 s4t_i = 0; s4t_i < 5; s4t_i++) {
		if ((s4t_x_updated == player_enemy.as4_position[s4t_i * 3 + 0]) &&
			(s4t_y_updated == player_enemy.as4_position[s4t_i * 3 + 1]))
		{
			s4t_count++;
		}
		else {
			/* NOP */
		}
	}

	if (s4t_count == 3) {
		return 0;
	}
	else {
		s4t_z_updated = s4t_count;
	}

	/* Update Position of X and Y */
	this->as4_position[s4t_num * 3 + 0] = s4t_x_updated;
	this->as4_position[s4t_num * 3 + 1] = s4t_y_updated;
	this->as4_position[s4t_num * 3 + 2] = s4t_z_updated;

	return 1;
}

S4 Player::moveAuto(Player player_enemy) {
	S4	s4t_i;
	S4	s4t_j;

	S4	s4t_num;
	S4	s4t_temp;
	S4	s4t_count;
	S4	s4t_flag;

	S4	s4t_x;
	S4	s4t_y;
	S4	s4t_z;

	S4	s4t_x_updated;
	S4	s4t_y_updated;
	S4	s4t_z_updated;

	while (1) {

		srand(time(NULL));
				
		/* Choice Block */
		s4t_num = rand() % 5;

		/* Choice x and y */
		s4t_temp = rand() % 14;

		if (this->en_color == White) {
			if ((s4t_temp == 0) || (s4t_temp == 1) || (s4t_temp == 2)) {
				s4t_x = -1;
				s4t_y = 1;
			}
			else if ((s4t_temp == 3) || (s4t_temp == 4) || (s4t_temp == 5)) {
				s4t_x = 0;
				s4t_y = 1;
			}
			else if ((s4t_temp == 6) || (s4t_temp == 7) || (s4t_temp == 8)) {
				s4t_x = 1;
				s4t_y = 1;
			}
			else if (s4t_temp == 9) {
				s4t_x = -1;
				s4t_y = 0;
			}
			else if (s4t_temp == 10) {
				s4t_x = 1;
				s4t_y = 0;
			}
			else if (s4t_temp == 11) {
				s4t_x = -1;
				s4t_y = -1;
			}
			else if (s4t_temp == 12) {
				s4t_x = 0;
				s4t_y = -1;
			}
			else if (s4t_temp == 13) {
				s4t_x = 1;
				s4t_y = -1;
			}
			else {
				/* NOP */
			}

		}
		else if (this->en_color == Black) {
			if ((s4t_temp == 0) || (s4t_temp == 1) || (s4t_temp == 2)) {
				s4t_x = -1;
				s4t_y = -1;
			}
			else if ((s4t_temp == 3) || (s4t_temp == 4) || (s4t_temp == 5)) {
				s4t_x = 0;
				s4t_y = -1;
			}
			else if ((s4t_temp == 6) || (s4t_temp == 7) || (s4t_temp == 8)) {
				s4t_x = 1;
				s4t_y = -1;
			}
			else if (s4t_temp == 9) {
				s4t_x = -1;
				s4t_y = 0;
			}
			else if (s4t_temp == 10) {
				s4t_x = 1;
				s4t_y = 0;
			}
			else if (s4t_temp == 11) {
				s4t_x = -1;
				s4t_y = 1;
			}
			else if (s4t_temp == 12) {
				s4t_x = 0;
				s4t_y = 1;
			}
			else if (s4t_temp == 13) {
				s4t_x = 1;
				s4t_y = 1;
			}
			else {
				/* NOP */
			}
		}
		else {
			/* NOP */
		}

		/* Check the Blocks on itself */
		s4t_flag = 0;

		for (S4 s4t_i = 0; s4t_i < 5; s4t_i++) {
			if (((this->as4_position[s4t_num * 3 + 0]		== this->as4_position[s4t_i * 3 + 0]) &&
				 (this->as4_position[s4t_num * 3 + 1]		== this->as4_position[s4t_i * 3 + 1]) &&
				 ((this->as4_position[s4t_num * 3 + 2] + 1) == this->as4_position[s4t_i * 3 + 2])) ||
				 ((this->as4_position[s4t_num * 3 + 0]		== player_enemy.as4_position[s4t_i * 3 + 0]) &&
				 (this->as4_position[s4t_num * 3 + 1]		== player_enemy.as4_position[s4t_i * 3 + 1]) &&
				 ((this->as4_position[s4t_num * 3 + 2] + 1) == player_enemy.as4_position[s4t_i * 3 + 2])))
			{
				s4t_flag = 1;
				break;
			}
			else {
				/* NOP */
			}
		}

		if (s4t_flag == 1) {
			continue;
		}
		else {
			/* NOP */
		}

		/* Update Position of x and y */
		s4t_x_updated = this->as4_position[s4t_num * 3 + 0] + s4t_x;
		s4t_y_updated = this->as4_position[s4t_num * 3 + 1] + s4t_y;

		/* Check that block is out of the board. */
		if (this->en_color == White) {
			if ((s4t_x_updated < 0) ||
				(s4t_x_updated > 4) ||
				(s4t_y_updated < 0))
			{
				continue;
			}
			else {
				/* NOP */
			}
		}
		else if (this->en_color == Black) {
			if ((s4t_x_updated < 0) ||
				(s4t_x_updated > 4) ||
				(s4t_y_updated > 5))
			{
				continue;
			}
			else {
				/* NOP */
			}
		}
		else {
			/* NOP */
		}

		/* Update Position of z */
		s4t_count = 0;

		for (S4 s4t_i = 0; s4t_i < 5; s4t_i++) {
			if ((s4t_x_updated == this->as4_position[s4t_i * 3 + 0]) &&
				(s4t_y_updated == this->as4_position[s4t_i * 3 + 1]))
			{
				s4t_count++;
			}
			else {
				/* NOP */
			}
		}

		for (S4 s4t_i = 0; s4t_i < 5; s4t_i++) {
			if ((s4t_x_updated == player_enemy.as4_position[s4t_i * 3 + 0]) &&
				(s4t_y_updated == player_enemy.as4_position[s4t_i * 3 + 1]))
			{
				s4t_count++;
			}
			else {
				/* NOP */
			}
		}

		if (s4t_count == 3) {
			continue;
		}
		else {
			s4t_z_updated = s4t_count;
		}

		/* Update Position of X and Y */
		this->as4_position[s4t_num * 3 + 0] = s4t_x_updated;
		this->as4_position[s4t_num * 3 + 1] = s4t_y_updated;
		this->as4_position[s4t_num * 3 + 2] = s4t_z_updated;

		break;
	}

	if (this->en_color == White) {
		//cout << "w*(0 ~ 4) : " << s4t_num << "\n";
    	//cout << "x(-1 ~ 1) : " << s4t_x << "\n";
    	//cout << "y(-1 ~ 1) : " << s4t_y << "\n\n";
	}
	else if (this->en_color == Black) {
		//cout << "b*(0 ~ 4) : " << s4t_num << "\n";
    	//cout << "x(-1 ~ 1) : " << s4t_x << "\n";
    	//cout << "y(-1 ~ 1) : " << s4t_y << "\n\n";
	}
	else {
		/* NOP */
	}

	return 0;
}

S4 Player::moveAutoNN(Player player_enemy) {
	S4		as4t_input[30];
	F4		af4t_output[40];
	S4		s4t_output = 0;

	S4		s4t_i = 0; 
	S4		s4t_count = 0;

	S4		s4t_num = 0;
	S4		s4t_tmp = 0;
	S4		s4t_dx = 0;
	S4		s4t_dy = 0;
	S4		s4t_x_updated = 0;
	S4		s4t_y_updated = 0;
	S4		s4t_z_updated = 0;

	/* Initialize */
	vdg_InitInput(*this, player_enemy, as4t_input);
	vdg_InitOutput(af4t_output);

	/* Predict */
	vdg_Predict(*this, as4t_input, af4t_output);
	s4t_output = s4t_DecodeOutput(af4t_output);

	s4t_num = s4t_output / 8;
	s4t_tmp = s4t_output % 8;

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

	/* Upadate */
	s4t_x_updated = this->as4_position[3 * s4t_num + 0] + s4t_dx;
	s4t_y_updated = this->as4_position[3 * s4t_num + 1] + s4t_dy;

	/* Update Position of z */
	s4t_count = 0;

	for (S4 s4t_i = 0; s4t_i < 5; s4t_i++) {
		if ((s4t_x_updated == this->as4_position[s4t_i * 3 + 0]) &&
			(s4t_y_updated == this->as4_position[s4t_i * 3 + 1]))
		{
			s4t_count++;
		}
		else {
			/* NOP */
		}
	}

	for (S4 s4t_i = 0; s4t_i < 5; s4t_i++) {
		if ((s4t_x_updated == player_enemy.as4_position[s4t_i * 3 + 0]) &&
			(s4t_y_updated == player_enemy.as4_position[s4t_i * 3 + 1]))
		{
			s4t_count++;
		}
		else {
			/* NOP */
		}
	}

	s4t_z_updated = s4t_count;
	
	/* Update Position of X and Y */
	this->as4_position[s4t_num * 3 + 0] = s4t_x_updated;
	this->as4_position[s4t_num * 3 + 1] = s4t_y_updated;
	this->as4_position[s4t_num * 3 + 2] = s4t_z_updated;

	return 0;
}
/* Private */
void vdg_InitInput(Player player_this, Player player_enemy, S4 *pas4t_input) {
	S4	s4t_i = 0;

	for (s4t_i = 0; s4t_i < 30; s4t_i++) {
		if (s4t_i < 15) {
			pas4t_input[s4t_i] = player_this.as4_position[s4t_i];
		}
		else {
			pas4t_input[s4t_i] = player_enemy.as4_position[s4t_i - 15];
		}
	}
}

void vdg_InitOutput(F4 *paf4t_output) {
	S4	s4t_i = 0;

	for (s4t_i = 0; s4t_i < 30; s4t_i++) {
		paf4t_output[s4t_i] = 0.0f;
	}
}

void vdg_Predict(Player player_this, S4 *pas4t_input, F4 *paf4t_output) {
	S4		s4t_i = 0;
	S4		s4t_j = 0;

	for (s4t_j = 0; s4t_j < 40; s4t_j++) {
		for (s4t_i = 0; s4t_i < 30; s4t_i++) {
			paf4t_output[s4t_j] += player_this.af4_weight[30 * s4t_j + s4t_i] * pas4t_input[s4t_i];
		}
	}

}

S4 s4t_DecodeOutput(F4 *paf4t_output) {
	S4	s4t_max_index = 0;
	F4	f4t_max_value = 0;

	S4	s4t_i = 0;

	f4t_max_value = paf4t_output[0];

	for (s4t_i = 1; s4t_i < 30; s4t_i++) {
		if (f4t_max_value < paf4t_output[s4t_i]) {
			f4t_max_value = paf4t_output[s4t_i];
			s4t_max_index = s4t_i;
		}
		else {
			/* NOP */
		}
	}	

	return s4t_max_index;
}