/* Includes */
#include <iostream>
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

void Player::showPosition1(void) {
	S4 s4t_i;
	for (s4t_i = 0; s4t_i < 15; s4t_i++) {
		cout << Player::as4_position[s4t_i] << " ";
	}
	cout << "\n";
}

void Player::showPosition2(void) {

}

S4 Player::moveManually(Player player_enemy, S4 s4_num, S4 s4_x, S4 s4_y) {
	S4	s4t_i;
	S4	s4t_j;

	S4	s4t_x;
	S4	s4t_y;
	S4	s4t_z;
	S4	s4t_count;

	S4	s4t_x_updated;
	S4	s4t_y_updated;
	S4	s4t_z_updated;

	/* Check Error */
	if ((0 <= s4_num) && (s4_num < 5)) {
		/* NOP */
	}
	else {
		return 0;
	}

	if ((-1 <= s4_x) && (s4_x <= 1)) {
		/* NOP */
	}
	else {
		return 0;
	}

	if ((-1 <= s4_y) && (s4_y <= 1)) {
		/* NOP */
	}
	else {
		return 0;
	}

	/* Check the Blocks on itself*/
	s4t_x = this->as4_position[s4_num * 3 + 0];
	s4t_y = this->as4_position[s4_num * 3 + 1];
	s4t_z = this->as4_position[s4_num * 3 + 2] + 1;

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
	s4t_x_updated = this->as4_position[s4_num * 3 + 0] + s4_x;
	s4t_y_updated = this->as4_position[s4_num * 3 + 1] + s4_y;
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
	this->as4_position[s4_num * 3 + 0] = s4t_x_updated;
	this->as4_position[s4_num * 3 + 1] = s4t_y_updated;
	this->as4_position[s4_num * 3 + 2] = s4t_z_updated;

	/* Check Win-Loss and Error*/

	return 1;
}

/* Private */
