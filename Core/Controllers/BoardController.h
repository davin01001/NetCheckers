#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
using namespace std;
using namespace chrono_literals;

#include "../Rules/Rules.h"
#include "../Views/WinView.h"
#include "../Views/LoseView.h"
#include "../Views/WaitingView.h"

class BoardController
{
public:
	explicit BoardController(const string & ip_) {
		font = new Font();
		if (!font->loadFromFile("fonts/Jura-Regular.ttf"))
			return;
		auto desktop = VideoMode::getDesktopMode();

		if (!ip_.empty())
			ip = ip_;

		client = new NetClient();
		if (client->Setup(ip, port)) {
			isWhite = false;
			myTurn = false;
			client->SetMessage("Go");
		} else {
			delete client;
			client = nullptr;

			server = new NetServer();
			if (!server->Setup(port))
				return;

			isWhite = true;
			myTurn = true;

			if (WaitingView::Show(static_cast<int>(desktop.width), static_cast<int>(desktop.height),
								  server, *font))
				return;
		}

		window = new RenderWindow(VideoMode(504, 504), "Checkers", Style::Close | Style::Titlebar);
		Vector2i pos { static_cast<int>(desktop.width / 2 - window->getSize().x / 2),
		               static_cast<int>(desktop.height / 2 - window->getSize().y / 2) };
		window->setPosition(pos);

		board = make_shared<Board>(isWhite);
		function<bool(int)> cit ([&](int source) { return board->CanITouch(source); });
		function<int(int, int)> e ([&](int source, int target) { return board->Eaten(source, target); });
		function<tuple<bool, bool>(int, int)> mf ([&](int source, int target) { return board->MoveFigure(source, target); });
		function<void()> eot ([&]() { return EndOfTurn(); });
		view = make_unique<BoardView>(board->Get(), cit, e, mf, eot, isWhite);

		turnCircle = new CircleShape(10);
		Color red { 150, 0, 0 };
		turnCircle->setFillColor(red);
		turnCircle->setPosition(4, 4);
	}

	~BoardController() {
		delete turnCircle;
		delete window;
		delete server;
		delete client;
	}

	BoardController(const BoardController &) = delete;
	BoardController(BoardController &&) = delete;

	[[nodiscard]] bool Created() const {
		return window != nullptr;
	}

	bool IsAlive() {
		return window->isOpen();
	}

	void ProcessEvents() {
		mousePos = Mouse::getPosition(*window);

		Event e {};
		while (window->pollEvent(e))
		{
			if (e.type == Event::Closed)
				window->close();

			if (e.type == Event::MouseButtonPressed)
				if (e.mouseButton.button == Mouse::Left)
					if (myTurn)
						view->OnMousePress(mousePos);

			if (e.type == Event::MouseButtonReleased)
				if (e.mouseButton.button == Mouse::Left)
					if (myTurn)
					{
						view->OnMouseRelease(mousePos);
						auto finalBoard = board->Get();
						winLose = EndGameRule::ReachEndGame(finalBoard);
					}
		}
	}

	void Update() {
		view->Moving(mousePos);
	}

	void Render() {
		window->clear(Color::Magenta);
		view->Draw(*window);
		if (myTurn)
			window->draw(*turnCircle);
		window->display();

		if (winLose != 0) {
			if (isWhite == winLose > 0)
				WinView::Show(window->getPosition());
			else
				LoseView::Show(window->getPosition());
			winLose = 0;
			board->Init(isWhite);
			view->InitBoard(board->Get(), isWhite);
		}
	}

	void Idle() {
		this_thread::sleep_for(100ms);

		if (!myTurn) {
			string message;
			if (server != nullptr) {
				message = server->GetMessage();
			} else {
				message = client->GetMessage();
			}

			if (!message.empty()) {
				ProcessMessage(message);
				auto finalBoard = board->Get();
				winLose = EndGameRule::ReachEndGame(finalBoard);
				myTurn = !myTurn;
			}
		}
	}

	void EndOfTurn() {
		string lastMove = board->LastMove();
		board->ClearLastMove();
		if (server != nullptr) {
			server->SetMessage(lastMove + "\n");
		} else {
			client->SetMessage(lastMove);
		}
		myTurn = !myTurn;
	}

private:
	RenderWindow * window = nullptr;
	Font * font;
	CircleShape * turnCircle;
	unique_ptr<BoardView> view;
	shared_ptr<Board> board;
	Vector2i mousePos;

	string ip = "127.0.0.1";
	const int port = 11999;
	NetClient * client;
	NetServer * server;

	int winLose = 0;
	bool isWhite = true;
	bool myTurn = false;

	void ProcessMessage(string & message) {
		if (message[0] == '-') {
			int col = message[1] - 'a';
			int row = message[2] - '1';
			board->Delete(row, col);
			view->Delete(row, col);
			message = message.substr(3);
		}
		int col_s = message[0] - 'a';
		int row_s = message[1] - '1';
		int col_t = message[2] - 'a';
		int row_t = message[3] - '1';
		bool becomeKing = board->Move(row_s, col_s, row_t, col_t);
		view->Move(row_s, col_s, row_t, col_t, becomeKing);
	}

};
