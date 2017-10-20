#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generator.h"

using namespace sf;



#define TILE_ON_RIGHT   grid[y][x+1]
#define TILE_ON_LEFT    grid[y][x-1]
#define TILE_FROM_ABOVE grid[y-1][x]
#define TILE_FROM_BELOW grid[y+1][x]
#define CURRENT_PLACE   grid[y][x]
#define PREVIUS_PLACE   grid[prev_y][prev_x]


//#define TILE_ON_RIGHT   grid[x][y+1]
//#define TILE_ON_LEFT    grid[x][y-1]
//#define TILE_FROM_ABOVE grid[x-1][y]
//#define TILE_FROM_BELOW grid[x+1][y]
//#define CURRENT_PLACE   grid[x][y]
//#define PREVIUS_PLACE   grid[prev_x][prev_y]

#define FONT_COLOR         242, 244, 0, 255
#define BACKGROUND_COLOR  191, 113, 48, 255

const int H = 12;
const int W = 40;

extern int **grid;
extern int **grid2;

//===================================================================





class Player {

public:

int x,y;
int xX, yY;
int prev_x, prev_y;
FloatRect rect;
Sprite sprite;
//Text text;
bool OVER;
bool WIN;
//int dir;
int move;
enum { UP, DOWN, LEFT, RIGHT, STOP };
int B_count;

    Player(Texture &image, Font &font)
   {
	sprite.setTexture(image);
	x = 1;
	y = 1;
	xX = 10;
	yY = 10;
	OVER = false;
	WIN  = false;
	prev_x = x;
	prev_y = y;
	rect = FloatRect(x * 32,y * 32, 40, 50);
	move = STOP;
	B_count = 0;
	main_gen( xX, yY, 40, 6, 2, 1000);
	// init map
//	TileMap = (String**)malloc(sizeof(String*) * yY);
//	for( int i = 0; i < yY; i++)
//	{
//		TileMap [i] = (String*)malloc(sizeof(String) * xX);
//	}

   }


   void update()
   {
	 if ( x < 1 ) x = 1;
//	 if ( x > 38 ) x = 38;
	 if ( y < 1 ) y = 1;
//	 if ( y > 10 ) y = 10;


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

    Texture t;
    Texture tileSet;
    String s = "_TEBE GAMOVER_";

    // Текст
    Font font;
    font.loadFromFile("res/kokilab.ttf");
    t.loadFromFile("res/pers.png");

    //music
    Music music;//создаем объект музыки
    music.openFromFile("res/sound.ogg");//загружаем файл
//    music.play();//воспроизводим музыку

    Text text;
	text.setFont(font);
	text.setString(s);
	text.setCharacterSize( 32 * 2 );
//	text.setPosition(W/2*32-32, H/2*32-32 );
//
	text.setFillColor(Color(FONT_COLOR));
	text.setOutlineColor(Color(0,0,0,255));
	text.setStyle(Text::Bold);

    Player p(t, font);

	RenderWindow window( VideoMode( p.xX * 32, p.yY * 32), "Game!");
	View view;
	view.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));
    window.setVerticalSyncEnabled (true);
//    window.setKeyRepeatEnabled(false);

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

//		time = time/700;
//
//		if (time>20) time = 20;
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

		for (int i = 0; i < p.xX; i++)
			 for (int j = 0; j < p.yY; j++)
			  {
				if ( grid[i][j]== 1 )
				{
//					printf("g1");
					tile.setTextureRect( IntRect(32,0,32,32) );
					p.B_count++;
				}

				if ( grid[i][j]== 0 )
				{
//					printf("g2");
					tile.setTextureRect( IntRect(0,0,32,32) );
				}

			//	if ( TileMap[i][j]=='0' ) continue;

				tile.setPosition( j*32, i*32 ) ;
				window.draw(tile);
			 }

		window.draw(p.sprite);

		if ( p.OVER == true )
		{
			window.draw(text);
			music.stop();
		}
		if ( p.WIN == true )
		{
			text.setPosition(view.getCenter().x-((int)s.getSize()*32/2), view.getCenter().y-text.getCharacterSize());
			text.setString("!!! YOU WIN !!!");
			window.draw(text);
			music.stop();
		}
        window.display();
        p.RemapTile();
//        p.TheGameIsOver();

        p.B_count = 0;
    }

    return 0;
}




