#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC


#include <SFML/Graphics.hpp>
#include "Helper.h"
#include <vector>
using namespace sf;
using namespace std;

int main()
{
	const int hexWidth = 64;
	const int windowWidth = 1200;
	const int windowHeight = 800;

	RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "v 0.1");
	window.setFramerateLimit(30);


	//board
	Texture txtBoard;
	txtBoard.loadFromFile("pic/board1.gif");
	Sprite spBoard = Sprite(txtBoard);
	Vector2f boardCenter(txtBoard.getSize().x / 2, txtBoard.getSize().y / 2);

	View view = View(boardCenter, Vector2f(windowWidth, windowHeight));
	window.setView(view);

	//menu
	bool menuActive = false;
	Texture txtMenu;
	txtMenu.loadFromFile("pic/menu.jpg");
	Sprite spMenu = Sprite(txtMenu);

	Texture txtExtras;
	txtExtras.loadFromFile("pic/extrasheet.png");
	Sprite moveBtn(txtExtras, IntRect(30, 0, 53, 25));
	moveBtn.setPosition(spMenu.getPosition().x + 20, spMenu.getPosition().y + 20);

	//units
	Vector2f unitSize(78, 78);
	Vector2f unitScale(0.5, 0.5);
	Texture unitSheet;
	unitSheet.loadFromFile("pic/sheet.jpg");
	Sprite generalBeuregard(unitSheet, IntRect(0, 0, unitSize.x, unitSize.y));
	generalBeuregard.setPosition(Vector2f(36, 44));
	generalBeuregard.setScale(unitScale);

	bool showOutline = false;
	RectangleShape unitOutline(sf::Vector2f(unitSize.x * unitScale.x + 10, unitSize.y *unitScale.y + 10));
	unitOutline.setFillColor(sf::Color::Yellow);
	unitOutline.setPosition(generalBeuregard.getPosition().x - 5, generalBeuregard.getPosition().y - 5);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}

			//zoom
			if (event.type == Event::MouseWheelMoved) {

				if (event.mouseWheel.delta > 0)
					view.zoom(0.5f);
				else
					view.zoom(2);

				window.setView(view);
			}

			//navigate
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Left) {
					view.move(Vector2f(-100, 0));
				}
				else if (event.key.code == Keyboard::Right) {
					view.move(Vector2f(100, 0));
				}
				else if (event.key.code == Keyboard::Up) {
					view.move(Vector2f(0, -100));
				}
				else if (event.key.code == Keyboard::Down) {
					view.move(Vector2f(0, 100));
				}
				else if (event.key.code == Keyboard::M) {
					menuActive = !menuActive;
				}

				window.setView(view);
			}

			//mouse clicks
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				Vector2i localPosition = sf::Mouse::getPosition(window);
				Vector2f mappedPosition = window.mapPixelToCoords(localPosition);

				if (menuActive) {

				}
				else
				{
					FloatRect generalRect = generalBeuregard.getGlobalBounds();

					bool contains = generalRect.contains(mappedPosition.x, mappedPosition.y);
					if (contains) {
						showOutline = !showOutline;
					}
					else {
						showOutline = false;
					}
				}

			}

		}

		window.clear();
		window.draw(spBoard);
		if (showOutline) {
			window.draw(unitOutline);
		}
		window.draw(generalBeuregard);

		if (menuActive) {
			window.draw(spMenu);
			window.draw(moveBtn);
		}

		window.display();
	}

	return 0;
}