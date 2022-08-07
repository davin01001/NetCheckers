#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class WaitingView
{
public:
	static bool Show(int width, int height, NetServer * server, Font & font) {
		const Color bg { 0, 0, 90 };
		RenderWindow waitingWindow(VideoMode(500, 200), "Checkers", Style::Close | Style::Titlebar);
		Vector2i pos { static_cast<int>(width / 2 - waitingWindow.getSize().x / 2),
		               static_cast<int>(height / 2 - waitingWindow.getSize().y / 2) };
		waitingWindow.setPosition(pos);

		Text messageText("Waiting for your opponent", font);
		messageText.setPosition(60, 70);

		bool isExit = false;
		while (waitingWindow.isOpen())
		{
			Event e {};
			while (waitingWindow.pollEvent(e))
				if (e.type == Event::Closed) {
					waitingWindow.close();
					isExit = true;
				}

			waitingWindow.clear(bg);
			waitingWindow.draw(messageText);
			waitingWindow.display();

			this_thread::sleep_for(100ms);

			string msg = server->GetMessage();
			if (!msg.empty())
				waitingWindow.close();
		}

		return isExit;
	}
};