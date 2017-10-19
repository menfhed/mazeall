#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;



#define TILE_ON_RIGHT   TileMap[y][x+1]
#define TILE_ON_LEFT    TileMap[y][x-1]
#define TILE_FROM_ABOVE TileMap[y-1][x]
#define TILE_FROM_BELOW TileMap[y+1][x]
#define CURRENT_PLACE   TileMap[y][x]
#define PREVIUS_PLACE   TileMap[prev_y][prev_x]

#define FONT_COLOR         242, 244, 0, 255
#define BACKGROUND_COLOR  191, 113, 48, 255

const int H = 12;
const int W = 40;


String TileMap[H] = {
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B         0000                BBBB     B",
"B                                B     B",
"BBB                              B     B",
"B              BB                BB    B",
"B              BB                      B",
"B    B         BB         BB           B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};


String ReservMap[H] = {
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B         0000                BBBB     B",
"B                                B     B",
"BBB                              B     B",
"B              BB                BB    B",
"B              BB                      B",
"B    B         BB         BB           B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};

class Player {

public:

int x,y;
int prev_x, prev_y;
FloatRect rect;
Sprite sprite;
bool OVER;
bool WIN;
int move;
enum { UP, DOWN, LEFT, RIGHT, STOP };
int B_count;

    Player(Texture &image, Font &font)
   {
	sprite.setTexture(image);
	x = 1;
	y = 1;
	OVER = false;
	WIN  = false;
	prev_x = x;
	prev_y = y;
	rect = FloatRect(x * 32,y * 32, 40, 50);
	move = STOP;
	B_count = 0;
   }


   void update()
   {
	 if ( x < 1 ) x = 1;
	 if ( y < 1 ) y = 1;


	 Collision( move );

	 rect.left = x * 32;
	 rect.top  = y * 32;

     sprite.setPosition(rect.left, rect.top );
   }

   void Collision(int direction)
   {
	   if ( CURRENT_PLACE == 'B' )
	   {
		   if ( direction == UP )
		   {
			   if ( TILE_FROM_ABOVE == 'B' )
			   {
				   move = STOP;
				   y = prev_y;
			   }
			   else y++;
		   }
		   if ( direction == DOWN )
		   {
			   if ( TILE_FROM_BELOW == 'B' )
			   {
				   move = STOP;
				   y = prev_y;
			   }
			   else y--;
		   }
		   if ( direction == LEFT )
		   {
			   if ( TILE_ON_LEFT == 'B' )
			   {
				   move = STOP;
				   x = prev_x;
			   }
			   else x++;
		   }
		   if ( direction == RIGHT )
		   {
			   if ( TILE_ON_RIGHT == 'B' )
			   {
				   move = STOP;
				   x = prev_x;
			   }
			   else x--;
		   }
	   }
	   if ( CURRENT_PLACE == '0' )
	   {
		   CURRENT_PLACE = ' ';
	   }
   }

   void RemapTile ()
   {
 	   if ( move != STOP )
 	   {
 		 move = STOP;
 		 PREVIUS_PLACE = 'B';
 		 TheGameIsOver();
 	   }
   }
   void TheGameIsOver ()
   {
	   	   if ( B_count >= ( H * W ) - 2 )
	   {
		   WIN = true;
	   }
	   	   else
	   		   if ( ( TILE_FROM_ABOVE == 'B') &&
	   			    ( TILE_FROM_BELOW == 'B') &&
				    ( TILE_ON_LEFT    == 'B') &&
				    ( TILE_ON_RIGHT   == 'B') )
	   		   {
	   			   OVER = true;
	   		   }

   }
};


int main()
{
    RenderWindow window( VideoMode(W*32, H*32), "Game!");
    View view;
	view.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));
    window.setVerticalSyncEnabled (true);
    Texture t;
    Texture tileSet;
    String s = "_TEBE GAMOVER_";

    // Текст
    Font font;
    font.loadFromFile("res/kokilab.ttf");
    t.loadFromFile("res/pers.png");

    Text text;
	text.setFont(font);
	text.setString(s);
	text.setCharacterSize( 32 * 2 );
	text.setPosition(view.getCenter().x-((int)s.getSize()*32/2), view.getCenter().y-text.getCharacterSize());
	text.setFillColor(Color(FONT_COLOR));
	text.setOutlineColor(Color(0,0,0,255));
	text.setStyle(Text::Bold);

    Player p(t, font);

    // Для текстуры плитки
    tileSet.loadFromFile("res/tile.png");
    Sprite tile(tileSet);

    FloatRect TileRect;
    TileRect = FloatRect(0, 0, 32, 32);

    Clock clock;

    bool IsKeyPressedOneTime = false;

	RectangleShape rectangle( Vector2f(32,32));


    while (window.isOpen())
    {
		clock.restart();
		float time = clock.getElapsedTime().asMicroseconds();


		Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
	    if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			if ( IsKeyPressedOneTime == false )
			{
				p.prev_x = p.x;
				p.prev_y = p.y;
				p.x--;
				p.move = p.LEFT;
			}
				IsKeyPressedOneTime = true;
		}
	    if (Keyboard::isKeyPressed(Keyboard::Right))
	    {
	    	if ( IsKeyPressedOneTime == false )
	    	{
	    		p.prev_x = p.x;
				p.prev_y = p.y;
	    		p.x++;
	    		p.move = p.RIGHT;
	    	}
				IsKeyPressedOneTime = true;
	    }

	    if (Keyboard::isKeyPressed(Keyboard::Up))
		{
	    	if ( IsKeyPressedOneTime == false )
			{
	    		p.prev_x = p.x;
				p.prev_y = p.y;
				p.y--;
				p.move = p.UP;
			}
	    		IsKeyPressedOneTime = true;

		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			if ( IsKeyPressedOneTime == false )
			{
				p.prev_x = p.x;
				p.prev_y = p.y;
				p.y++;
				p.move = p.DOWN;
			}
				IsKeyPressedOneTime = true;
		}

		if ( event.type == Event::KeyReleased)
		{
			IsKeyPressedOneTime = false;
		}


		window.clear(Color(BACKGROUND_COLOR));

		p.update();

		for (int i=0; i<H; i++)
			 for (int j=0; j<W; j++)
			  {
				if ( TileMap[i][j]=='B' )
				{
					tile.setTextureRect( IntRect(32,0,32,32) );
					p.B_count++;
				}

				if ( TileMap[i][j]==' ' )
				{
					tile.setTextureRect( IntRect(0,0,32,32) );
				}

				if ( TileMap[i][j]=='0' ) continue;

				tile.setPosition( j*32, i*32 ) ;
				window.draw(tile);
			 }

		window.draw(p.sprite);

		if ( p.OVER == true )
		{
			window.draw(text);
		}
		if ( p.WIN == true )
		{
			text.setString("!!! YOU WIN !!!");
			window.draw(text);
		}
        window.display();
        p.RemapTile();

        p.B_count = 0;
    }

    return 0;
}




