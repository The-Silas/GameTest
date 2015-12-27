
function MainMenu_Load()
	
	//load text menu
	CreateText(0,"Infiltration")
	SetTextSize(0,textsize +10)
	SetTextAlignment(0,1)
	SetTextPosition(0, width/2, 250)
	
	CreateText ( 1, "Start a game" )
	SetTextSize ( 1, textsize )
	SetTextAlignment(1, 1)
	SetTextPosition (1, width/2 , 450 )
	
	CreateText ( 2, "Settings")
	SetTextSize (2,textsize)
	SetTextPosition(2, width/2, 450 + textsize)
	SetTextAlignment(2,1)
	
	LoadImage( 1, "street.png" )
	CreateSprite ( 1, 1 )
	SetSpritePosition ( 1, 0, 0 )
	SetSpriteVisible(1,1)
	
	createMarines(10)
	
	
endfunction
	
function MainMenu_Loop()
	
	SetTextColor ( 1, Random ( 1, 255 ), Random ( 1, 255 ), Random ( 1, 255 ), 255 )
	
	
	
endfunction
