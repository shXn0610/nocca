/* Includes */
#include <iostream>
#include "nocca.h"

using namespace std;

/* Variables */

/* prototypes */

/* Public */
Nocca::Nocca() {

};

Nocca::~Nocca() {

};

void Nocca::startGamePvP() {
    Player      player_white(WHITE);
    Player      player_black(BLACK);
    Board       board;
    EN_STATE    en_state = WHITE_PLAYING;

    board.showBoard();

	while ((en_state == WHITE_PLAYING) || (en_state == BLACK_PLAYING)) {

		if (en_state == WHITE_PLAYING) {
			player_white.moveManually(board);
		}
		else if (en_state == BLACK_PLAYING) {
			player_black.moveManually(board);
		}
		else {
			/* NOP */
		}

		board.showBoard();
        en_state = board.judgeWinLose(en_state);
	}

}

void Nocca::startGamePvC() {
    Player      player_white(WHITE);
    Player      player_black(BLACK);
    Board       board;
    EN_STATE    en_state = WHITE_PLAYING;

    board.showBoard();

	while ((en_state == WHITE_PLAYING) || (en_state == BLACK_PLAYING)) {

		if (en_state == WHITE_PLAYING) {
			player_white.moveManually(board);
		}
		else if (en_state == BLACK_PLAYING) {
			player_black.moveAuto(board);
		}
		else {
			/* NOP */
		}

		board.showBoard();
        en_state = board.judgeWinLose(en_state);
	}

}

void Nocca::startGameCvC() {
    Player      player_white(WHITE);
    Player      player_black(BLACK);
    Board       board;
    EN_STATE    en_state = WHITE_PLAYING;

    board.showBoard();

	while ((en_state == WHITE_PLAYING) || (en_state == BLACK_PLAYING)) {

		if (en_state == WHITE_PLAYING) {
			player_white.moveAuto(board);
		}
		else if (en_state == BLACK_PLAYING) {
			player_black.moveAuto(board);
		}
		else {
			/* NOP */
		}

		board.showBoard();
        en_state = board.judgeWinLose(en_state);
	}

}

EN_STATE Nocca::startGameGA(Gene *gene_white, Gene *gene_black) {
    Player      player_white(WHITE);
    Player      player_black(BLACK);
    Board       board;
    EN_STATE    en_state = WHITE_PLAYING;

    //board.showBoard();

	while ((en_state == WHITE_PLAYING) || (en_state == BLACK_PLAYING)) {

		if (en_state == WHITE_PLAYING) {
			player_white.moveAutoGA(board, *gene_white);
			//player_white.moveAuto(board);
		}
		else if (en_state == BLACK_PLAYING) {
			//player_black.moveAutoGA(board, *gene_black);
			player_black.moveAuto(board);
		}
		else {
			/* NOP */
		}

		//board.showBoard();
        en_state = board.judgeWinLose(en_state);
	}

	return en_state;
}
/* Sub */