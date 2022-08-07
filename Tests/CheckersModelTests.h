#pragma once

#include <gtest/gtest.h>

#include <memory>
using namespace std;

#include "../Core/framework.h"

class CheckersModelTests : public ::testing::Test
{
protected:
	void SetUp() override {
		board = make_shared<Board>(true);
		checkBoard = board->Get();
	}

	shared_ptr<Board> board;
	vector<int> checkBoard;
};

TEST_F(CheckersModelTests, CreateBoardTest)
{
	EXPECT_EQ(board->IsCreated(), true);
}

TEST_F(CheckersModelTests, LoadTest)
{
	for (int row = 0; row < 8; row++)
		for (int col = 0; col < 8; col++)
		{
			auto canMove = board->CanMove(row, col);
			int index = row * 8 + col;
			auto cell = checkBoard[index];
			if (canMove)
			{
				EXPECT_GE(cell, -1);
				EXPECT_LE(cell,  1);
			}
			else
			{
				EXPECT_EQ(cell, 0);
			}
		}
}

TEST_F(CheckersModelTests, CheckMoveTest)
{
	EXPECT_EQ(checkBoard[16], 1);
	EXPECT_EQ(checkBoard[25], 0);

	board->MoveFigure(16, 25);

	checkBoard = board->Get();

	EXPECT_EQ(checkBoard[16], 0);
	EXPECT_EQ(checkBoard[25], 1);
}

TEST_F(CheckersModelTests, CheckEatenTest)
{
	EXPECT_EQ(checkBoard[16], 1);
	EXPECT_EQ(checkBoard[25], 0);

	board->MoveFigure(18, 27);
	board->MoveFigure(41, 34);
	board->Eaten(27, 41);
	board->MoveFigure(27, 41);

	checkBoard = board->Get();

	EXPECT_EQ(checkBoard[41], 1);
	EXPECT_EQ(checkBoard[34], 0);
	EXPECT_EQ(checkBoard[27], 0);
}
