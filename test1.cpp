#include <SFML/Graphics.hpp>

using namespace sf;


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
//int dir;
int move;
enum { UP, DOWN, LEFT, RIGHT, STOP };
int B_count;

    Player(Texture &image)
   {
	sprite.setTexture(image);
	x = 1;
	y = 1;
	prev_x = x;
	prev_y = y;
	rect = FloatRect(x * 32,y * 32, 40, 50);
	move = STOP;
	B_count = 0;
   }


   void update()
   {
//	 if ( x < 1 ) x = 1;
//	 if ( x > 38 ) x = 38;
//	 if ( y < 1 ) y = 1;
//	 if ( y > 10 ) y = 10;


	 Collision( move );

	 rect.left = x * 32;
	 rect.top  = y * 32;

     sprite.setPosition(rect.left, rect.top );
   }

   void Collision(int direction)
   {
	   if ( TileMap[y][x] == 'B' )
	   {
		   if ( direction == UP )
		   {
			   if ( TileMap[y+1][x] == 'B' )
				   y = prev_y;
			   else y++;
		   }
		   if ( direction == DOWN )
		   {
			   if ( TileMap[y-1][x] == 'B' )
				   y = prev_y;
			   else y--;
		   }
		   if ( direction == LEFT )
		   {
			   if ( TileMap[y][x+1] == 'B' )
				   x = prev_x;
			   else x++;
		   }
		   if ( direction == RIGHT )
		   {
			   if ( TileMap[y][x-1] == 'B' )
				   x = prev_y;
			   else x--;
		   }
	   }
	   if ( TileMap[y][x] == '0' )
	   {
		   TileMap[y][x] = ' ';
	   }
   }

   void RemapTile ()
   {

 	   if ( (TileMap[y+1][x] == 'B') &&
 			(TileMap[y-1][x] == 'B') &&
			(TileMap[y][x+1] == 'B') &&
			(TileMap[y][x-1] == 'B') )
	   {
 		   TileMap[y][x+1] = ' ';
	   }

	   TileMap[prev_y][prev_x] = 'B';
   }
};


int main()
{
    RenderWindow window( VideoMode(W*32, H*32), "Test!");
    Texture t;

    t.loadFromFile("res/2.png");

    Player p(t);
    Clock clock;

    bool IsKeyPressedOneTime = false;

	RectangleShape rectangle( Vector2f(32,32));




    while (window.isOpen())
    {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

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
			if (!IsKeyPressedOneTime)
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
	    	if (!IsKeyPressedOneTime)
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
	    	if (!IsKeyPressedOneTime)
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
			if (!IsKeyPressedOneTime)
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
			if ( time > 500 )
			IsKeyPressedOneTime = false;
		}

		window.clear(Color::White);
		p.update();


		 for (int i=0; i<H; i++)
			 for (int j=0; j<W ; j++)
				{
				  if (TileMap[i][j]=='B')
				  {
					  rectangle.setFillColor(Color::Black);
					  p.B_count++;
				  }

			      if (TileMap[i][j]=='0')  rectangle.setFillColor(Color::Green);

				  if (TileMap[i][j]==' ') continue;

		          rectangle.setPosition( j*32, i*32 );
		          window.draw(rectangle);
		         }
		 if ( p.B_count >= 200)
		 {
			 for (int i=0; i<H; i++)
				 for (int j=0; j<W ; j++)
				 {
					 TileMap[i][j]='0';
				 }
		 }
		window.draw(p.sprite);
        window.display();
        p.RemapTile();
        p.move = p.STOP;
        p.B_count = 0;
    }

    return 0;
}




