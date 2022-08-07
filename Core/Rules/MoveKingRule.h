#pragma once

class MoveKingRule
{
public:
	static bool CanMove(int source, int target, vector<int> & board, bool isWhite) {
		int diff = target - source;

		if (abs(diff) == 7 || abs(diff) == 9)
			return true;

		vector<int> movesLeft = { 7, 14, 21, 28, 35, 42, 49  };
		vector<int> movesRight = { 9, 18, 27, 36, 45, 54, 63 };

		bool other = false;
		for (auto ml : movesLeft)
		{
			int idx = source + ml;
			if (board[idx] != 0)
				other = true;
			if (diff == ml)
				return !other;
		}

		other = false;
		for (auto ml : movesLeft)
		{
			int idx = source - ml;
			if (board[idx] != 0)
				other = true;
			if (diff == -ml)
				return !other;
		}

		other = false;
		for (auto mr : movesRight)
		{
			int idx = source + mr;
			if (board[idx] != 0)
				other = true;
			if (diff == mr)
				return !other;
		}

		other = false;
		for (auto mr : movesRight)
		{
			int idx = source - mr;
			if (board[idx] != 0)
				other = true;
			if (diff == -mr)
				return !other;
		}

		return false;
	}

};
