#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
using namespace std;

#include "../Rules/Rules.h"

class BoardView
{
public:
	BoardView(const vector<int> & board,
			  function<bool(int)> & canITouch,
			  function<int(int, int)> & eaten,
			  function<tuple<bool, bool>(int, int)> & moveFigure,
			  function<void()> & endOfTurn,
			  bool isWhite_)
		: CanITouch { canITouch }, Eaten { eaten }, MoveFigure { moveFigure }, EndOfTurn { endOfTurn }
	{
		LoadSprites();
		InitBoard(board, isWhite_);
	}

	void InitBoard(const vector<int> & board, bool isWhite_) {
		isWhite = isWhite_;
		int f = 0;
		for (int row = 0; row < 8; row++)
			for (int col = 0; col < 8; col++)
			{
				int cell = board[ ToIndex(row, col) ];
				if (!cell) continue;
				int x = abs(cell) - 1;
				int y = cell > 0 ? 0 : 1;
				int c = isWhite ? col : 7 - col;
				int r = isWhite ? 7 - row : row;
				Vector2f pos = { static_cast<float>(size * c), static_cast<float>(size * r) };
				sFigures[f].setTextureRect( IntRect(size * x,size * y,size,size) );
				sFigures[f].setPosition( pos );
				++f;
			}
	}

	void Draw(RenderWindow & window) {
		sBoard.setPosition(0, 0);
		window.draw(sBoard);

		for (auto & figure : sFigures)
			figure.move(offset_f);
		for (auto & figure : sFigures)
			window.draw(figure);
		for (auto & figure : sFigures)
			figure.move(-offset_f);
	}

	void OnMousePress(Vector2i mousePos) {
		if (!isMove) {
			mousePos -= offset;
			for (int i = 0; i < 24; i++) {
				Vector2f mp { static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) };
				if (sFigures[i].getGlobalBounds().contains(mp))
				{
					oldPos = sFigures[i].getPosition();
					int source = ToIndex(oldPos);
					if (CanITouch(source))
					{
						isMove = true;
						hold = i;
						dx = static_cast<int>(mp.x - oldPos.x);
						dy = static_cast<int>(mp.y - oldPos.y);
					}
					break;
				}
			}
		}
	}

	void OnMouseRelease(Vector2i /*mousePos*/) {
		if (isMove)
		{
			//mousePos -= offset;
			isMove = false;
			Vector2f p = sFigures[hold].getPosition() + Vector2f(size_f / 2, size_f / 2);
			newPos = Vector2f( ClampCoord(p.x), ClampCoord(p.y) );

			auto pi = ToIndexCoords(p);
			if (CanMove(pi.x, pi.y) && newPos.x > -1 && newPos.x < 440 && newPos.y > -1 && newPos.y < 440)
			{
				int source = ToIndex(oldPos);
				int target = ToIndex(newPos);

				int eaten = Eaten(source, target);
				if (eaten > -1) {
					int figure = FigureByIndex(eaten);
					RemoveFromBoard(figure);
				}
				auto [ moving, becomeKing] = MoveFigure(source, target);

				Vector2f pos = moving ? newPos : oldPos;

				sFigures[hold].setPosition( pos );

				if (becomeKing) {
					auto rc = sFigures[hold].getTextureRect();
					rc.left += size;
					sFigures[hold].setTextureRect(rc);
				}

				if (moving) {
					EndOfTurn();
				}
			}
			else
			{
				sFigures[hold].setPosition( oldPos );
			}
		}
	}

	void Moving(Vector2i mousePos) {
		if (isMove) {
			mousePos -= offset;
			Vector2f pos = { static_cast<float>(mousePos.x - dx), static_cast<float>(mousePos.y - dy) };
			sFigures[hold].setPosition( pos );
		}
	}

	void Delete(int row, int col) {
		int index = row * 8 + col;
		int figure = FigureByIndex(index);
		RemoveFromBoard(figure);
	}

	void Move(int row_s, int col_s, int row_t, int col_t, bool becomeKing) {
		int source = row_s * 8 + col_s;
		int f_index = FigureByIndex(source);
		int c = isWhite ? col_t : 7 - col_t;
		int r = isWhite ? 7 - row_t : row_t;
		Vector2f pos = Vector2f( size_f * static_cast<float>(c), size_f * static_cast<float>(r) );
		sFigures[f_index].setPosition( pos );

		if (becomeKing) {
			auto rc = sFigures[f_index].getTextureRect();
			rc.left += size;
			sFigures[f_index].setTextureRect(rc);
		}
	}

private:
	const Vector2i offset = {28, 28 };
	const Vector2f offset_f = {28, 28 };
	const int size = 56;
	const float size_f = 56.0f;

	Texture boardTexture;
	Texture figuresTexture;
	Sprite sBoard;
	Sprite sFigures[24];

	bool isWhite = true;

	bool isMove = false;
	int hold = 0;
	int dx = 0;
	int dy = 0;
	Vector2f oldPos = { 0, 0 };
	Vector2f newPos = { 0, 0 };

	function<bool(int)> CanITouch;
	function<int(int, int)> Eaten;
	function<tuple<bool, bool>(int, int)> MoveFigure;
	function<void()> EndOfTurn;

	void LoadSprites() {
		if (!boardTexture.loadFromFile("images/board.png"))
			cerr << "Error: can't load images/board.png" << endl;
		if (!figuresTexture.loadFromFile("images/figures.png"))
			cerr << "Error: can't load images/figures.png" << endl;

		sBoard.setTexture(boardTexture);
		sBoard.setPosition(0, 0);
		for (auto & figure : sFigures)
			figure.setTexture(figuresTexture);
	}

	void RemoveFromBoard(int f) {
		sFigures[f].setPosition(-100,-100);
	}

	static bool CanMove(int row, int col) {
		return (row + col) % 2 == 0;
	}

	int ToIndex(Vector2f screenCoords) {
		auto pi = ToIndexCoords(screenCoords);
		return ToIndex(pi.y, pi.x);
	}

	Vector2i ToIndexCoords(Vector2f screenCoords) {
		int bx = ToRowCol(screenCoords.x);
		int by = ToRowCol(screenCoords.y);
		int c = isWhite ? bx : 7 - bx;
		int r = isWhite ? 7 - by : by;
		return { c, r };
	}

	static int ToIndex(int row, int col) {
		return row * 8 + col;
	}

	Vector2f ToPos(int index) const {
		int x = index % 8;
		int y = index / 8;
		int c = isWhite ? x : 7 - x;
		int r = isWhite ? 7 - y : y;
		return { static_cast<float>(c) * size_f, static_cast<float>(r) * size_f };
	}

	int FigureByIndex(int index) {
		Vector2f pos = ToPos(index);

		for (int f = 0; f < 24; f++) {
			auto cp = sFigures[f].getPosition();
			if (cp == pos)
				return f;
		}
		return -1;
	}

	int ToRowCol(float coord) const {
		return static_cast<int>(coord / size_f);
	}

	float ClampCoord(float coord) const {
		return static_cast<float>(size * ToRowCol(coord));
	}

};
