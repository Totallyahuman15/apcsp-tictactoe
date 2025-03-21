#include "stdafx.h"
#include "GameLogic.h"

// This simply initializes the human's role 
Game::Game(PlayerTypes humanRole)
	: human(humanRole), currentBoard()
{
}

// This utilizes the Board variable to place a piece of the current player's turn. It also checks to see if there's a winner.
void Game::SubmitTurn(int x, int y)
{
	if (!currentBoard.IsTaken(x, y))
	{
		currentBoard.PlacePiece(x, y, turn);
	}
	else
		return;

	// Row Win
	for (int y = 0; y < 3; y++)
	{
		if (currentBoard.board[y][0] == turn && currentBoard.board[y][1] == turn && currentBoard.board[y][2] == turn)
		{
			winner = turn;
		}
	}

	// Column Win
	for (int x = 0; x < 3; x++)
	{
		if (currentBoard.board[0][x] == turn && currentBoard.board[1][x] == turn && currentBoard.board[2][x] == turn)
		{
			winner = turn;
		}
	}

	// Diagonal Win
	if (currentBoard.board[0][0] == turn && currentBoard.board[1][1] == turn && currentBoard.board[2][2] == turn)
	{
		winner = turn;
	}
	else if (currentBoard.board[0][2] == turn && currentBoard.board[1][1] == turn && currentBoard.board[2][0] == turn)
	{
		winner = turn;
	}

	// Makes sure to switch it to the other's turn.
	switch (turn)
	{
	case PlayerTypes::X: { turn = PlayerTypes::O; break; }
	case PlayerTypes::O: turn = PlayerTypes::X;
	}
}

// This does exactly as advertised. Used in the bot's minimax algorithm
void Game::UndoTurn(int x, int y)
{
	currentBoard.UndoPlace(x, y);

	switch (turn)
	{
	case PlayerTypes::X: { turn = PlayerTypes::O; break; }
	case PlayerTypes::O: turn = PlayerTypes::X;
	}
}

bool Game::IsCat()
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (currentBoard.board[y][x] == PlayerTypes::NONE) return false;
		}
	}

	return true;
}
