#pragma once

class EndGameRule
{
public:
	static int ReachEndGame(vector<int> & board) {
		int white = 0;
		int black = 0;
		for (auto cell : board)
		{
			if (cell > 0)
				white++;
			else if (cell < 0)
				black++;
		}

		if (white > 0 && black > 0)
			return 0;

		return white > black ? 1 : (white < black ? -1 : 0);
	}

};
