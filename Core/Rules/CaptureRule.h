#pragma once

class CaptureRule
{
public:
	static int CanCapture(int source, int target, vector<int> & board, bool isWhite) {
		int eaten = -1;
		int diff = target - source;
		int sign = isWhite ? 1 : -1;
		diff *= sign;

		int waySign = diff > 0 ? 1 : -1;

		diff = abs(diff);
		if (diff == 14) {
			int idx = source + 7 * waySign * sign;
			if (board[idx] * sign < 0) {
				eaten = idx;
			}
		}
		else if (diff == 18)
		{
			int idx = source + 9 * waySign * sign;
			if (board[idx] * sign < 0) {
				eaten = idx;
			}
		}

		return eaten;
	}

//	void foo() {
//		if (isWhite)
//		{
//			int diff = target - source;
//			if (diff == 7 || diff == 9)
//				return -1;
//			int sign = diff > 0 ? 1 : -1;
//			diff = abs(diff);
//			if (diff == 14) {
//				int idx = source + 7 * sign;
//				if (board[idx] < 0) {
//					eaten = idx;
//				} else
//					return -1;
//			}
//			else if (diff == 18)
//			{
//				int idx = source + 9 * sign;
//				if (board[idx] < 0) {
//					eaten = idx;
//				} else
//					return -1;
//			}
//			else
//				return -1;
//		}
//		else
//		{
//			int diff = source - target;
//			if (diff == 7 || diff == 9)
//				return -1;
//			int sign = diff > 0 ? 1 : -1;
//			diff = abs(diff);
//			if (diff == 14) {
//				int idx = source - 7 * sign;
//				if (board[idx] > 0) {
//					eaten = idx;
//				} else
//					return -1;
//			}
//			else if (diff == 18)
//			{
//				int idx = source - 9 * sign;
//				if (board[idx] > 0) {
//					eaten = idx;
//				} else
//					return -1;
//			}
//			else
//				return -1;
//		}
//	}

};

