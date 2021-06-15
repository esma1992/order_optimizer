//
// Created by knapp on 15.06.21.
//

#include <iostream>
#include <gtest/gtest.h>
#include "../src/order_optimizer/src/subscriber_function.cpp"

// Declare a test
TEST(TestSuite, testCase1)
{
double *dist = new double[4];
     dist[0]= 2.3;
dist[1]= 4.5;
dist[2]= 3.6;
dist[3]= 5.2;
bool sptSet[4] = {false, true, false, false};

OrderOptimizer obj;
int min_distance = obj.min_distance(dist, sptSet, 4);
EXPECT_EQ(0, min_distance);
}

// Run all the tests that were declared with TEST()
int StartGoogleTest(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}


