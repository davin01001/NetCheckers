#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <tuple>
using namespace std;

#include "../Views/BoardView.h"
#include "../Rules/Rules.h"

class Board
{
public:
	explicit Board(bool isWhite_) {
		Init(isWhite_);
	};

	void Init(bool isWhite_) {
		isWhite = isWhite_;
		board = boardInitialization;
	}

	[[nodiscard]] bool IsCreated() const {
		return board.size() == 64 && board[16] == 1 && board[25] == 0;
	}

	[[nodiscard]] vector<int> Get() const {
		return board;
	}

	bool CanITouch(int source) {
		bool iw = board[source] > 0;
		return isWhite == iw;
	}

	int Eaten(int source, int target) {
		int currentSource = board[source];
		int currentTarget = board[target];

		if (currentTarget != 0)
			return -1;

		bool iw = currentSource > 0;
		bool isKing = abs(currentSource) > 1;

		int eaten;
		if (isKing)
		{
			bool isMoved = MoveKingRule::CanMove(source, target, board, iw);
			if (isMoved)
				return -1;
			eaten = CaptureKingRule::CanCapture(source, target, board, iw);
		}
		else
		{
			bool isMoved = MoveRule::CanMove(source, target, board, iw);
			if (isMoved)
				return -1;
			eaten = CaptureRule::CanCapture(source, target, board, iw);
		}

		return eaten;
	}

	tuple<bool, bool> MoveFigure(int source, int target) {
		int currentSource = board[source];
		int currentTarget = board[target];

		if (currentTarget != 0)
			return { false, false };

		bool iw = currentSource > 0;
		bool isKing = abs(currentSource) > 1;

		int eaten = -1;
		if (isKing)
		{
			bool isMoved = MoveKingRule::CanMove(source, target, board, iw);
			if (!isMoved) {
				eaten = CaptureKingRule::CanCapture(source, target, board, iw);
				if (eaten == -1)
					return { false, false };
			}
		}
		else
		{
			bool isMoved = MoveRule::CanMove(source, target, board, iw);
			if (!isMoved) {
				eaten = CaptureRule::CanCapture(source, target, board, iw);
				if (eaten == -1)
					return  { false, false };
			}
		}

		if (eaten != -1) {
			board[eaten] = 0;
			lastMove += "-" + ToChessNote(eaten);
		}

		swap(board[source], board[target]);
		lastMove += ToChessNote(source) + ToChessNote(target);

		bool becomeKing = false;
		if (abs(currentSource) == 1) {
			becomeKing = BecomeKingRule::CanBecomeKing(target, iw);
			if (becomeKing) {
				board[target] = currentSource * 2;
			}
		}

		return { true, becomeKing };
	}

	static bool CanMove(int row, int col) {
		return (row + col) % 2 == 0;
	}

	[[nodiscard]] string LastMove() const {
		return lastMove;
	}

	void ClearLastMove() {
		lastMove = "";
	}

	void Delete(int row, int col) {
		int index = row * 8 + col;
		board[index] = 0;
	}

	bool Move(int row_s, int col_s, int row_t, int col_t) {
		int source = row_s * 8 + col_s;
		int target = row_t * 8 + col_t;
		swap(board[source], board[target]);

		bool becomeKing = false;
		if (abs(board[target]) == 1) {
			bool iw = board[target] > 0;
			becomeKing = BecomeKingRule::CanBecomeKing(target, iw);
			if (becomeKing) {
				board[target] *= 2;
			}
		}
		return becomeKing;
	}

private:
	vector<int> boardInitialization = {
		 1,  0,  1,  0,  1,  0,  1,  0,
		 0,  1,  0,  1,  0,  1,  0,  1,
		 1,  0,  1,  0,  1,  0,  1,  0,
		 0,  0,  0,  0,  0,  0,  0,  0,
		 0,  0,  0,  0,  0,  0,  0,  0,
		 0, -1,  0, -1,  0, -1,  0, -1,
		-1,  0, -1,  0, -1,  0, -1,  0,
		 0, -1,  0, -1,  0, -1,  0, -1
	};
	vector<int> board;
	bool isWhite = true;
	string lastMove;

	static string ToChessNote(int index) {
		int col = index % 8;
		int row = index / 8;
		stringstream ss;
		ss << static_cast<char>('a' + col);
		ss << static_cast<char>('1' + row);
		return ss.str();
	}

};
