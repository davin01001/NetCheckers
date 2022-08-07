#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class WinView
{
public:
	static void Show(Vector2i winPos) {
		RenderWindow winWindow(VideoMode(400, 200), "You win!", Style::Close | Style::Titlebar);
		winWindow.setPosition(Vector2i(winPos.x + 52, winPos.y + 100));
		Font font;
		if (!font.loadFromFile("fonts/Jura-Regular.ttf"))
			return;

		Text message("You are win!", font);
		message.setPosition(120, 70);

		while (winWindow.isOpen()) {
			Event e {};
			while (winWindow.pollEvent(e))
				if (e.type == Event::Closed)
					winWindow.close();

			Color bg { 0, 50, 0 };
			winWindow.clear(bg);
			winWindow.draw(message);
			winWindow.display();
		}
	}
};