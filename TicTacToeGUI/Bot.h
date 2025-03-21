#ifndef BOT_H
#define BOT_H

#include "GameLogic.h"

/*
###########################################################################################################
#
#		Finally, the last script—the bot! This is just a simple minimax algorithm... It's really that
#		simple!
#
###########################################################################################################
*/

class Bot
{
public:
	Bot(PlayerTypes role, Game board);
	std::tuple<int, int, int> Move(Game board, PlayerTypes role);
private:
	// These play a role in its decision-making process.
	int Minimax(Game board, int depth, bool isMax, PlayerTypes role);
	int EvalBoard(Game board, int depth, PlayerTypes role);

	// Just some memory things so the bot doesn't develop dementia! Used in `EvalBoard()` to determine who won
	PlayerTypes role;
	// The current, unmodified board to see the current game. Essential in making a decision.
	Game curBoard;
};

#endif
