#pragma once

class CaptureKingRule
{
public:
	static int CanCapture(int source, int target, vector<int> & board, bool isWhite) {
		int diff = target - source;
		int sign = isWhite ? -1 : 1;

		vector<int> movesLeft = { 7, 14, 21, 28, 35, 42, 49  };
		vector<int> movesRight = { 9, 18, 27, 36, 45, 54, 63 };

		int other = 0;
		int eaten = -1;
		for (auto ml : movesLeft)
		{
			int idx = source + ml;
			if (!Wayable(idx) || idx < 0 || idx > 63)
				break;
			if (board[idx] != 0)
			{
				if (board[idx] * sign < 0)
					break;
				other++;
				eaten = idx;
			}
			if (diff == ml)
				return other == 1 ? eaten : -1;
		}

		other = 0;
		eaten = -1;
		for (auto ml : movesLeft)
		{
			int idx = source - ml;
			if (!Wayable(idx) || idx < 0 || idx > 63)
				break;
			if (board[idx] != 0)
			{
				if (board[idx] * sign < 0)
					break;
				other++;
				eaten = idx;
			}
			if (diff == -ml)
				return other == 1 ? eaten : -1;
		}

		other = 0;
		eaten = -1;
		for (auto mr : movesRight)
		{
			int idx = source + mr;
			if (!Wayable(idx) || idx < 0 || idx > 63)
				break;
			if (board[idx] != 0)
			{
				if (board[idx] * sign < 0)
					break;
				other++;
				eaten = idx;
			}
			if (diff == mr)
				return other == 1 ? eaten : -1;
		}

		other = 0;
		eaten = -1;
		for (auto mr : movesRight)
		{
			int idx = source - mr;
			if (!Wayable(idx) || idx < 0 || idx > 63)
				break;
			if (board[idx] != 0)
			{
				if (board[idx] * sign < 0)
					break;
				other++;
				eaten = idx;
			}
			if (diff == -mr)
				return other == 1 ? eaten : -1;
		}

		return -1;
	}

private:
	static bool Wayable(int index) {
		int row = index / 8;
		int col = index % 8;
		return (row + col) % 2 == 0;
	}

};
