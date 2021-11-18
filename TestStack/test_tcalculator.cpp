#include "../mp2-lab3-stack/TCalculator.h"
#include "gtest.h"

//can evaluate simple expression

TEST(TCalculator, can_create_calculator)
{
	ASSERT_NO_THROW(TCalculator(""));
}



