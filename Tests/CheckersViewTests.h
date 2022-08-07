#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;
#include <gtest/gtest.h>

#include <memory>
#include <functional>
using namespace std;

#include "../Core/framework.h"

class CheckersViewTests : public ::testing::Test
{
protected:
	void SetUp() override {
		board = make_shared<Board>(true);
		checkBoard = board->Get();

		function<bool(int)> cit ([&](int source) { return board->CanITouch(source); });
		function<int(int, int)> e ([&](int source, int target) { return board->Eaten(source, target); });
		function<tuple<bool, bool>(int, int)> mf ([&](int source, int target) { return board->MoveFigure(source, target); });
		function<void()> eot ([&]() { return false; });
		view = make_unique<BoardView>(board->Get(), cit, e, mf, eot, true);
	}

	shared_ptr<Board> board;
	shared_ptr<BoardView> view;
	vector<int> checkBoard;
};

TEST_F(CheckersViewTests, CreateWindowTest)
{
	RenderWindow window(VideoMode(320, 480), "Checkers");

	bool wasOpen = window.isOpen();
	if (wasOpen)
		window.close();

	EXPECT_EQ(wasOpen, true);
}

TEST_F(CheckersViewTests, MouseTest)
{
	Vector2i pos1 = { 60, 334 };
	Vector2i pos2 = { 114, 281 };

	EXPECT_EQ(checkBoard[16], 1);
	EXPECT_EQ(checkBoard[25], 0);

	view->OnMousePress(pos1);
	view->Moving(pos1);
	view->Moving(pos2);
	view->OnMouseRelease(pos2);

	checkBoard = board->Get();

	EXPECT_EQ(checkBoard[16], 0);
	EXPECT_EQ(checkBoard[25], 1);
}
