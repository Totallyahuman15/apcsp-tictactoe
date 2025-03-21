#include "stdafx.h"
#include "Bot.h"

// Just initializes variables
Bot::Bot(PlayerTypes role, Game board)
	: role(role), curBoard(board)
{
}

// Determines the best possible move, and calls on the minimax algorithm
std::tuple<int, int, int> Bot::Move(Game board, PlayerTypes role)
{
	int bestVal = -1000;
	int bestX = -1;
	int bestY = -1;

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (!board.IsTaken(x, y))
			{
				board.SubmitTurn(x, y);
				int moveVal = Minimax(board, 0, false, role);
				board.UndoTurn(x, y);
				if (moveVal > bestVal)
				{
					bestX = x;
					bestY = y;
					bestVal = moveVal;
				}
			}
		}
	}

	return std::tuple<int, int, int>(bestVal, bestX, bestY); // Returns its desired move
}

// The meat of this script! It's the main brain!
int Bot::Minimax(Game board, int depth, bool isMax, PlayerTypes role)
{
	// This determines if there is a winner—which'll heavily bias it's choice to one that will win!
	int score = EvalBoard(board, depth, role);
	if (board.GetWinner() != PlayerTypes::NONE || board.IsCat()) return score;

	if (isMax) // Tries to get the bot the highest score possible!
	{
		int best = std::numeric_limits<int>::min(); // Set to -inf to not set a minimum requirement and potentially make stupid decisions
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				if (!board.IsTaken(x, y))
				{
					board.SubmitTurn(x, y);
					best = std::max(best, Minimax(board, depth + 1, false, role)); // Calls recursively to see ALL possible outcomes
					board.UndoTurn(x, y);
				}
			}
		}
		return best;
	}
	else // This tries to get the bot the lowest score, so it doesn't make decisions that'll loose it the game!
	{
		int best = std::numeric_limits<int>::max(); // Set to +inf for the same reason above!
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				if (!board.IsTaken(x, y))
				{
					board.SubmitTurn(x, y);
					best = std::min(best, Minimax(board, depth + 1, true, role));
					board.UndoTurn(x, y);
				}
			}
		}
		return best;
	}
}

int Bot::EvalBoard(Game board, int depth, PlayerTypes role)
{
	if (board.GetWinner() == role) // If the bot has one, give it a score of ten. We subtract by the depth in order to prioritize faster wins!
		return 10 - depth;
	else if (board.GetWinner() != role && board.GetWinner() != PlayerTypes::NONE) // Same as above, but flipped so because the higher the score, the worse the opponent did!
		return depth - 10;
	else
		return 0; // Don't influence it if nothing happened/cat game
}
