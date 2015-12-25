
// Project: GameTest 
// Created: 2015-12-24

// set window properties

#include "Main_menu.agc"
#include "Setup.agc"

SetWindowTitle( title$ )
SetWindowSize( width, height, 0 )

// set display properties
SetVirtualResolution( 1024, 768 )
SetOrientationAllowed( 1, 1, 1, 1 )

global gamestate = 0

global menu_background

MainMenu_Load()

do
    

    Print( ScreenFPS() )
    Print( gamestate )
    if ( gamestate < 1 )
		MainMenu_Loop()
		
	endif
    Sync()
loop
