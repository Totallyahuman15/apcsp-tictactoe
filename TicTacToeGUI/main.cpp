#include "stdafx.h"
#include "GameWindow.h"
#include <QtWidgets/QApplication>

/*
##########################################################################################################################
#
#		Hello! For this project I've used the library Qt 6.8.2. This library—paired with its Visual Studio tools—
#		auto-generates some files. These files include: Form Files (*.ui) (generate blank), header files (*.h) for each
#		form file (generate mostly blank), source files (*.cpp) for each form file (generate mostly blank), and this main
#		file here. Almost all functionality of this app was programmed by me—the rest being auto-generated on solution
#		creation.
#		
#		I used Microsoft Visual Studio Community 2022 to program this software and will provide a link to a GitHub
#		containing the solution file, in the case I've missed anything, or you are confused on the organization of this
#		project.
#		
#		Here is the link: https://github.com/Totallyahuman15/apcsp-tictactoe
#
##########################################################################################################################
*/


// This was auto-generated. All it does is run the game window :)
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GameWindow w;
	w.show();
	return a.exec();
}
