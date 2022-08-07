#pragma once

class MoveRule
{
public:

	static bool CanMove(int source, int target, vector<int> & board, bool isWhite) {
		int diff = target - source;
		int sign = isWhite ? 1 : -1;
		diff *= sign;

		return (diff == 7 || diff == 9);
	}

};
