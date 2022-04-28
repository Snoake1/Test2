#include "tests.h"
#include "tests_out.h"
#include <gtest/gtest.h>

int main(int argc, char * argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
