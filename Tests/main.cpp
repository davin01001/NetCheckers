#include <gtest/gtest.h>

#include "CheckersModelTests.h"
#include "CheckersViewTests.h"
#include "CheckersNetTests.h"

int main(int argc, char * argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
