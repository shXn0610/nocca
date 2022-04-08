/* Includes */
#include <iostream>
#include <time.h>
#include "..\inc\typedefs.h"
#include "..\class\player.h"

using namespace std;

/* Variables */

/* prototypes */

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

	//cout << "Constructor is called.\n";
	//cout << "\n";
};

Player::~Player() {

	//cout << "Destructor is called.\n";
	//cout << "\n";

};

void Player::showPosition(void) {
	S4 s4t_i;
	for (s4t_i = 0; s4t_i < 15; s4t_i++) {
		cout << Player::as4_position[s4t_i] << " ";
	}
	cout << "\n";
}

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
		cout << "w*(0 ~ 4) : ";
    	cin >> s4t_num;
	}
	else {
		cout << "b*(0 ~ 4) : ";
    	cin >> s4t_num;
	}

    cout << "x(-1 ~ 1) : ";
    cin >> s4t_dx;
    cout << "y(-1 ~ 1) : ";
    cin >> s4t_dy;
    cout << "\n";

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
		cout << "w*(0 ~ 4) : " << s4t_num << "\n";
    	cout << "x(-1 ~ 1) : " << s4t_x << "\n";
    	cout << "y(-1 ~ 1) : " << s4t_y << "\n\n";
	}
	else if (this->en_color == Black) {
		cout << "b*(0 ~ 4) : " << s4t_num << "\n";
    	cout << "x(-1 ~ 1) : " << s4t_x << "\n";
    	cout << "y(-1 ~ 1) : " << s4t_y << "\n\n";
	}
	else {
		/* NOP */
	}

	return 0;
}

/* Private */
