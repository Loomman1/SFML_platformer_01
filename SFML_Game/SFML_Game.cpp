#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
//test comment for github
//second test comment
#ifndef GL_SRGB8_ALPHA8
#define GL_SRGB8_ALPHA8 0x8C43
#endif
using namespace sf;
using namespace std;

int ground = 500;
int score = 0;
int nMonsters = 2;
double step = 0.04;
float currentFrameX = 0;
float offsetX=0, offsetY = 0;
const int h = 42;
const int w = 118;

enum eNumerator {Horizontal, Vertical};
String testString = "test";

String TileMap[h]
{
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"B                            B                                                                                      B",
	"B                            B                                                                                      B",
	"B                       0000 B                                                                                      B",
	"B                            B                                                                                      B",
	"B                            B                                        00                                            B",
	"B                            B                                                                                      B",
	"B                            B         B                                                                            B",
	"B       000            BBBBBBB         B                                                                            B",
	"BBBB                                   B                                                                            B",
	"B                                      B                                                                            B",
	"B               BB                     B    000                                           BB                        B",
	"B               BB                     B                                                  BB                        B",
	"B               BB                     B             BB                                   BB                        B",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB     BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB           B",
	"B                            B                                                                                      B",
	"B                            B                                                                                      B",
	"B                            B                                                                                      B",
	"B                            B                                                                                      B",
	"B                            B                                                                                      B",
	"B       000            BBBBBBB                                                                                BBBBBBB",
	"BBBB                                                                                                                B",
	"B                                                                                                                   B",
	"B                                                                                                                   B",
	"B                                                                                                                   B",
	"B                                                                                                       B           B",
	"B                                                                                                       B           B",
	"B               BB                                                                                      B           B",
	"B               BB                                   BB                                   BB            B           B",
	"BB       BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"B                            B                                                                                      B",
	"B                            B                                                                                      B",
	"B                            B                                                                                      B",
	"B                       0000 B                                                                                      B",
	"B                            B                                                                                      B",
	"B       000            BBBBBBB                                                                                BBBBBBB",
	"BBBB                                                                                                                B",
	"B                                                                                                                   B",
	"B               BB                                                                                                  B",
	"B               BB                                                                                                  B",
	"B               BB                                   BB                                   BB                        B",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
};
/*
class Enemy
{
public:
	float dx;
	FloatRect rect;
	Sprite s;
	float currentFrame;
	//bool life;

	Enemy(Texture& image, int x, int y)
	{
		s.setTexture(image);
		rect = FloatRect(x, y, 128, 100);
		dx = 0.05;
		currentFrame = 0;
		//life = true;
	}

	void update(float time)
	{
		rect.left += dx * time;

		Collision();
		//if (rect.top > ground)	{	rect.top = ground;	dy = 0;	onGround = true;	}

		currentFrame += 0.0005 * time;
		if (currentFrame > 10) currentFrame -= 10;
		if (dx < 0)
		{
				s.setTextureRect(IntRect(128 * int(currentFrame), 300, -128, 100));
		}
		if (dx > 0)
		{
				s.setTextureRect(IntRect(128 * int(currentFrame), 300, 128, 100));
		}
		s.setPosition(rect.left - offsetX, rect.top - offsetY);
	}

	void Collision()
	{
		for (int i = rect.top / 32; i < ((rect.top + rect.height) / 32); i++)
		{
			for (int j = rect.left / 32; j < ((rect.left + rect.width) / 32); j++)
			{
				if (TileMap[i][j] == 'B')
				{
					if (dx > 0) { rect.left = j * 32 - rect.width; dx = -0.05; }
					else
					if (dx < 0) { rect.left = j * 32 + 64; dx = 0.05; }
				
				}
			}
		}
	}
};
*/

 
class Player
{
public:
	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite s;
	float CurrFrame;

	Player(Texture& image)
	{
		s.setTexture(image);
		s.setTextureRect(IntRect(0, 0, 248, 268));	//Cut top left image
		s.setScale(0.4f, 0.4f);
		rect = FloatRect(64, 64, 99, 107);

		dx = dy = 0;
		CurrFrame = 0;
	}

	void update(float time)
	{
		rect.left += dx * time;
		Collision(Horizontal);

		if (!onGround) dy = dy + 0.000023 * time;
		rect.top += dy * time;
		onGround = false;

		Collision(Vertical);
		//if (rect.top > ground)	{	rect.top = ground;	dy = 0;	onGround = true;	}

		currentFrameX += 0.001 * time;
			if (currentFrameX > 10) currentFrameX -= 10;
		if (dx < 0)
		{
			
			if (currentFrameX < 4)
				s.setTextureRect(IntRect(248 * int(currentFrameX) + 248, 0, -248, 268));
			else
				if (currentFrameX < 8)
					s.setTextureRect(IntRect(248 * int(currentFrameX) - 4 * 248 + 248, 268, -248, 268));
				else
					s.setTextureRect(IntRect(248 * int(currentFrameX) - 8 * 248 + 248, 268 * 2, -248, 268));
		}
		if (dx > 0)
		{
				if (currentFrameX < 4)
					s.setTextureRect(IntRect(248 * int(currentFrameX), 0, 248, 268));
				else
					if (currentFrameX < 8)
						s.setTextureRect(IntRect(248 * int(currentFrameX) - 4 * 248, 268, 248, 268));
					else
						s.setTextureRect(IntRect(248 * int(currentFrameX) - 8 * 248, 268 * 2, 248, 268));

		}
		s.setPosition(rect.left - offsetX, rect.top - offsetY);
		dx = 0;
	}

	void Collision(eNumerator dir)
	{
		for (int i = rect.top / 32; i < ((rect.top + rect.height) / 32); i++)
		{
			for (int j = rect.left / 32; j < ((rect.left + rect.width) / 32); j++)
			{
				if (TileMap[i][j] == 'B')
				{
					if (dir == Horizontal)
					{
						if (dx > 0) rect.left = j * 32 - rect.width;
						if (dx < 0) rect.left = j * 32 + 32;
					}
					if (dir == Vertical)
					{	
						if (dy > 0) { rect.top = i * 32 - rect.height; dy = 0; onGround = true; }
						if (dy < 0) { rect.top = i * 32 + 32; dy = 0; }
					}
				}

				if (TileMap[i][j] == '0')
				{
					score++;
					TileMap[i][j] = ' ';
				}
			}

		}
	}
};

int main()
{
	bool exit = false;
	bool sRgb = false;

	/*ContextSettings contextSettings;
	contextSettings.depthBits = 24;
	contextSettings.sRgbCapable = sRgb;*/

	//std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	// for (std::size_t i = 0; i < modes.size(); ++i)
	// {
	//     sf::VideoMode mode = modes[i];
	//     std::cout << "Mode #" << i << ": "
	//               << mode.width << "x" << mode.height << " - "
	//               << mode.bitsPerPixel << " bpp" << std::endl;
	// }

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	RenderWindow window(VideoMode(1920, 1080, desktop.bitsPerPixel), "MyGame"); //, Style::Default, contextSettings
	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(3000);
	
	//window.create(sf::VideoMode(1024, 768, desktop.bitsPerPixel), "SFML window");

	Texture bgt;
	bgt.setSrgb(sRgb);
	if (!bgt.loadFromFile("resources/sky.jpg"))
		return EXIT_FAILURE;

	Sprite bg;
	bg.setTexture(bgt);

	Texture t;
	t.setSrgb(sRgb);
	if (!t.loadFromFile("resources/MyBoy.png"))
		return EXIT_FAILURE;
	Texture t1;
	t1.setSrgb(sRgb);
	if (!t1.loadFromFile("resources/Jungle.png"))
		return EXIT_FAILURE;
	Texture t2;
	t2.setSrgb(sRgb);
	if (!t2.loadFromFile("resources/FishTiles.png"))
		return EXIT_FAILURE;
	Texture MonsterTexture;
	MonsterTexture.setSrgb(sRgb);
	if (!MonsterTexture.loadFromFile("resources/monster.png"))
		return EXIT_FAILURE;

	Player p(t);
	//Enemy e(MonsterTexture, 3400, 800);/////////////////////

	Clock clock;
	RectangleShape rectangle;

	clock.restart();
	while (window.isOpen())
	{
		Sleep(2);
		float time = clock.getElapsedTime().asMicroseconds()*0.01;
		clock.restart();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			p.dx = -step;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.dx = step;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (p.onGround) { p.dy = -step*2.5; p.onGround = false; }
		}
		/*if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			s.move(0, step* time);
		}*/

		p.update(time);
		/*
		for(int i=0;i<nMonsters;i++)
		*/
		//e.update(time);//////////////////////////////////////
		
		if(p.rect.left> 1920 / 2-128)
		offsetX = p.rect.left-1920/2+64;
		if (p.rect.top > 1080 / 2)
		offsetY = p.rect.top-1080/2+64;
		window.clear(Color::White);
		window.draw(bg);
		//window.clear(Color::White);
		Vector2f vecSize;
		vecSize.x = 32;
		vecSize.y = 32;
		
		
		for (int i = 0; i < h; i++)  //Horizontal
		{
			for (int j = 0; j < w; j++)   //Vertical
			{
				if (TileMap[i][j] == 'B')	//Wall
				{	
					rectangle.setTexture(&t1);
					rectangle.setTextureRect(IntRect(40, 35, 112, 99));
					//rectangle.setFillColor(Color::Black);
				}
			
				if (TileMap[i][j] == '0')	//Chicken-bonus
				{
					rectangle.setTexture(&t2);
					rectangle.setTextureRect(IntRect(430, 904, 34, 22));
				}

				if (TileMap[i][j] == ' ') continue;	//empty
				rectangle.setSize(vecSize);
				rectangle.setPosition(j*32 - offsetX, i*32 - offsetY);
				window.draw(rectangle);
			}

		}
		window.draw(p.s);
		//window.draw(e.s);
		window.display();
	}
}

