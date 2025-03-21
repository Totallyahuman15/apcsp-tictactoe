#include "stdafx.h"
#include "Settings.h"

Settings::Settings(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}

Settings::~Settings()
{}

void Settings::on_botCheckBox_stateChanged(int state)
{
	/*
	#########################################################################################################
	#
	#		The variables here are merely options for the game. The `botCheckBox` toggles the bot on and off
	#		(as well as toggle the radio buttons on and off). The `randomRButton` is the radio button that
	#		specifies the human player will be randomly chosen either X or O. The `xRButton` and `oRButton`
	#		set the user's role as X and O respectively.
	#
	#########################################################################################################
	*/

	randomRButton->setEnabled(!randomRButton->isEnabled());
	xRButton->setEnabled(!xRButton->isEnabled());
	oRButton->setEnabled(!oRButton->isEnabled());
}
