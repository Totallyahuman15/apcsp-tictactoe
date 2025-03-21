#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

/*
##############################################################################################################
#
#		Welcome to GameLogic.h! This was 100% user-generated! I've made this class to enhance my program's
#		readability and scalibility! Nothing really more to preface here. Let's dive in!
#
##############################################################################################################
*/

// This just assigns numbers to names so I don't have to remember the code for each player type.
enum PlayerTypes
{
	NONE = 0,
	X = 1,
	O = 2
};

// This is the Board variable type. It stores the board's data within a 2D array of PlayerTypes. All of these functions are self-explanatory and short, so I won't be
// explaining them.
struct Board
{
	using enum PlayerTypes;
	PlayerTypes board[3][3] = {
		{ NONE, NONE, NONE },
		{ NONE, NONE, NONE },
		{ NONE, NONE, NONE }
	};

	void PlacePiece(int x, int y, PlayerTypes piece)
	{
		board[y][x] = piece;
	}
	bool IsTaken(int x, int y)
	{
		return board[y][x] != NONE;
	}
	void UndoPlace(int x, int y)
	{
		board[y][x] = NONE;
	}
};

// Here's the meat! This is the main Game class used to translate the user's interpreted inputs into memory. It also handles the base game's logic.
class Game
{
public:
	Game(PlayerTypes humanRole = PlayerTypes::NONE);
	void SubmitTurn(int x, int y);
	void UndoTurn(int x, int y);
	// These functions are self-explanatory and are extremely short.
	PlayerTypes GetTurn() { return turn; }
	PlayerTypes GetWinner() { return winner; }
	PlayerTypes GetHumanRole() { return human; }
	bool IsCat();
	bool IsTaken(int x, int y) { return currentBoard.IsTaken(x, y); }
private:
	// These internal variables help the game remember important details and allow it to properly run the game's logic

	PlayerTypes human;
	PlayerTypes turn = PlayerTypes::X;
	PlayerTypes winner = PlayerTypes::NONE;
	Board currentBoard;
};

#endif
