#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GameWindow.h"
#include "GameLogic.h"
#include "Bot.h"
#include <memory>

/*
###########################################################################################################
#
#       Welcome to GameWindow.h! This file was auto-generated, along with GameWindow.ui, but most
#       functionality was programmed by me. The class's public section was auto-generated, along
#       with the `Ui::GameWindowClass ui;` allocation in `private.` Everything else was programmed
#       by me.
#
###########################################################################################################
*/

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private:
    void PlaceTurn(int x, int y);
    void UpdateWin(bool reset = false);

    Ui::GameWindowClass ui;
    std::unique_ptr<Game> game;
    std::unique_ptr<Bot> bot;

    // This is to check whether the game is multiplayer or not. Primarily used in the `PlaceTurn()` function, to know whether or not to call on the bot for their turn.
    bool multiplayer;

    // This allows me to easily iterate through all the buttons to enable, disable, or label them.
    QPushButton* buttons[3][3];
private slots:
    // These functions DO have a specific naming scheme required by Qt. that is `on_{elementName}_{action}()`

    void on_actionNewGame_triggered();

    // I defined these functions here since they're short and repetitive
    void on_button00_clicked() { PlaceTurn(0, 0); }
    void on_button10_clicked() { PlaceTurn(1, 0); }
    void on_button20_clicked() { PlaceTurn(2, 0); }
    void on_button01_clicked() { PlaceTurn(0, 1); }
    void on_button11_clicked() { PlaceTurn(1, 1); }
    void on_button21_clicked() { PlaceTurn(2, 1); }
    void on_button02_clicked() { PlaceTurn(0, 2); }
    void on_button12_clicked() { PlaceTurn(1, 2); }
    void on_button22_clicked() { PlaceTurn(2, 2); }
};
