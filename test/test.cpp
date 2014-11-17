#include <gtest/gtest.h>
#include "../cpo_utils.h"

TEST(Equal, Tolerance) {
	EXPECT_TRUE(equal(1.0, 1.1, 0.1));
	EXPECT_TRUE(equal(-10.0, -11.0, 0.1));
	EXPECT_TRUE(equal(-10.0, 10.0, 2.0));
	EXPECT_FALSE(equal(1.0, 1.2, 0.1));
	EXPECT_FALSE(equal(-10.0, -12.0, 0.1));
}

TEST(BinarySearch, FindExistingValue) {
	blitz::Array<double, 1> ar(10);
	ar = 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
	EXPECT_EQ(0, binary_search(ar, 0.0));
	EXPECT_EQ(1, binary_search(ar, 1.0));
	EXPECT_EQ(2, binary_search(ar, 2.0));
	EXPECT_EQ(3, binary_search(ar, 3.0));
	EXPECT_EQ(4, binary_search(ar, 4.0));
	EXPECT_EQ(5, binary_search(ar, 5.0));
	EXPECT_EQ(6, binary_search(ar, 6.0));
	EXPECT_EQ(7, binary_search(ar, 7.0));
	EXPECT_EQ(8, binary_search(ar, 8.0));
	EXPECT_EQ(8, binary_search(ar, 9.0));
}

TEST(BinarySearch, FindValue) {
	blitz::Array<double, 1> ar(10);
	ar = 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
	EXPECT_EQ(0, binary_search(ar, 0.01));
	EXPECT_EQ(0, binary_search(ar, 0.99));
	EXPECT_EQ(1, binary_search(ar, 1.01));
	EXPECT_EQ(1, binary_search(ar, 1.99));
	EXPECT_EQ(6, binary_search(ar, 6.1));
	EXPECT_EQ(6, binary_search(ar, 6.5));
	EXPECT_EQ(7, binary_search(ar, 7.2));
	EXPECT_EQ(8, binary_search(ar, 8.01));
	EXPECT_EQ(8, binary_search(ar, 8.99));
}
