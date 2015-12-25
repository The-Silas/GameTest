
// Project: GameTest 
// Created: 2015-12-24

// set window properties
SetWindowTitle( "GameTest" )
SetWindowSize( 1024, 768, 0 )

// set display properties
SetVirtualResolution( 1024, 768 )
SetOrientationAllowed( 1, 1, 1, 1 )



do
    

    Print( ScreenFPS() )
    Sync()
loop
