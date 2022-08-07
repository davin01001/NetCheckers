#pragma once

class BecomeKingRule
{
public:
	static bool CanBecomeKing(int index, bool isWhite) {
		return (isWhite ? index > 55 : index < 8);
	}
};
