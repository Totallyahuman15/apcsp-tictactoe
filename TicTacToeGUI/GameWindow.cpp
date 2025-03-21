#include "stdafx.h"
#include "GameWindow.h"
#include "Settings.h"

/*
########################################################################################################################################################################
#
#		This is GameWindow.cpp. This handles all user input recieved from GameWindow.ui. GameWindow.ui was the auto-generated form file which was created on solution
#		creation.
#
########################################################################################################################################################################
*/

// Constructor - This mainly just initializes some variables, but it also opens the Settings.ui dialog box to set some game rules.
GameWindow::GameWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	buttons[0][0] = ui.button00;
	buttons[1][0] = ui.button10;
	buttons[2][0] = ui.button20;
	buttons[0][1] = ui.button01;
	buttons[1][1] = ui.button11;
	buttons[2][1] = ui.button21;
	buttons[0][2] = ui.button02;
	buttons[1][2] = ui.button12;
	buttons[2][2] = ui.button22;

	// This is the settings dialog box. All variable names within the class are defined in Settings.h
	Settings settings(this);
	
	if (settings.exec())
	{
		PlayerTypes player;
		PlayerTypes botRole;
		if (settings.xRButton->isChecked())
		{
			player = PlayerTypes::X;
			botRole = PlayerTypes::O;
		}
		else if (settings.oRButton->isChecked())
		{
			player = PlayerTypes::O;
			botRole = PlayerTypes::X;
		}
		else
		{
			std::srand(std::time(nullptr));
			if (std::rand() % 2)
			{
				player = PlayerTypes::X;
				botRole = PlayerTypes::O;
			}
			else
			{
				player = PlayerTypes::O;
				botRole = PlayerTypes::X;
			}
		}

		// This instantiates the game class I've created and defined in GameLogic.h
		game = std::make_unique<Game>(player);

		multiplayer = !settings.botCheckBox->isChecked();

		// This instantiates the bot class I've created and defined in Bot.h
		if (!multiplayer && botRole == PlayerTypes::X)
		{
			bot = std::make_unique<Bot>(botRole, *game);
			std::tuple<int, int, int> botMove = bot->Move(*game, botRole);
			PlaceTurn(std::get<1>(botMove), std::get<2>(botMove));
		}
	}
	else
		// If the dialog box is canceled/ignored, the program will automatically close upon its first heartbeat. If this isn't called, the game will begin without any
		// logic.
		QTimer::singleShot(0, this, &QWidget::close);
}

// Qt handles most clean-up, including the objects' references. All other pointers are `std::unique_ptr`s and are destroyed once they've fallen out-of-scope.
GameWindow::~GameWindow()
{
}

// The function's name and parameters are pretty self-explanitory
void GameWindow::PlaceTurn(int x, int y)
{
	QString piece;

	switch (game->GetTurn())
	{
	case PlayerTypes::X: { piece = "X"; break; }
	case PlayerTypes::O: piece = "O";
	}

	// Once the user selects a slot, the button will mark their piece and disable, so it cannot be placed there again.
	buttons[x][y]->setText(piece);
	buttons[x][y]->setEnabled(false);
	game->SubmitTurn(x, y);
	// If there is a winner, all the buttons are disabled to prevent playing the game after it's been won.
	if (game->GetWinner() != PlayerTypes::NONE)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				buttons[x][y]->setEnabled(false);
			}
		}
		UpdateWin();
		return;
	}
	else if (game->IsCat())
	{
		UpdateWin();
		return;
	}

	// This checks whos turn it is, and—assuming it's singleplayer—will call the bot to make a decision.
	if (game->GetHumanRole() != game->GetTurn() && !multiplayer && (game->GetWinner() == PlayerTypes::NONE || !game->IsCat()))
	{
		std::tuple<int, int, int> botMove = bot->Move(*game, game->GetTurn());
		PlaceTurn(std::get<1>(botMove), std::get<2>(botMove));
	}
}

// This updates the label at the top to show the user a terminal state (aka win, lose, or draw)
void GameWindow::UpdateWin(bool reset)
{
	QString winner;

	switch (game->GetWinner())
	{
	case PlayerTypes::X: { winner = "X"; break; }
	case PlayerTypes::O: { winner = "O"; break; }
	default: winner = "Cat!";
	}

	if (reset)
		ui.winnerLabel->clear();
	else
		ui.winnerLabel->setText("Winner: " + winner);
}

// This does the same thing as the constructor, just without initializing variables.
void GameWindow::on_actionNewGame_triggered()
{
	Settings settings(this);
	if (settings.exec())
	{
		PlayerTypes player;
		PlayerTypes botRole;
		if (settings.xRButton->isChecked())
		{
			player = PlayerTypes::X;
			botRole = PlayerTypes::O;
		}
		else if (settings.oRButton->isChecked())
		{
			player = PlayerTypes::O;
			botRole = PlayerTypes::X;
		}
		else
		{
			std::srand(std::time(nullptr));
			if (std::rand() % 2)
			{
				player = PlayerTypes::X;
				botRole = PlayerTypes::O;
			}
			else
			{
				player = PlayerTypes::O;
				botRole = PlayerTypes::X;
			}
		}

		// Re-instantiates game, essentially resetting it
		game = std::make_unique<Game>(player);

		multiplayer = !settings.botCheckBox->isChecked();

		// Reset window - sets all buttons to active and removes their mark, setting the board up for another game.
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				buttons[y][x]->setEnabled(true);
				buttons[y][x]->setText("");
			}
		}
		UpdateWin(true);

		if (!multiplayer && botRole == PlayerTypes::X)
		{
			// Same thing here as game's reinstantiation
			bot = std::make_unique<Bot>(botRole, *game);
			std::tuple<int, int, int> botMove = bot->Move(*game, botRole);
			PlaceTurn(std::get<1>(botMove), std::get<2>(botMove));
		}
	}
}
