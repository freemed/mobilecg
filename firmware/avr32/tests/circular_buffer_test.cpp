#include "gtest/gtest.h"
#include "../application/circular_buffer.hpp"

TEST(CircularBufferTest, SanityCheck)
{
	CircularBuffer<4> cbuf;
	char buf[5] = "    ";
	EXPECT_FALSE(cbuf.popBytes(buf, 1));
	EXPECT_TRUE(cbuf.pushBytes("a", 1));
	EXPECT_TRUE(cbuf.popBytes(buf, 1));
	EXPECT_FALSE(cbuf.popBytes(buf, 1));
	EXPECT_EQ(buf[0], 'a');
}

TEST(CircularBufferTest, OverflowTest)
{
	CircularBuffer<4> cbuf;
	char buf[5] = "    ";
	EXPECT_TRUE(cbuf.pushBytes("a", 1));
	EXPECT_TRUE(cbuf.pushBytes("bc", 2));
	EXPECT_FALSE(cbuf.pushBytes("d", 1));
	EXPECT_FALSE(cbuf.popBytes(buf, 4));
	EXPECT_TRUE(cbuf.popBytes(buf, 3));
	EXPECT_STREQ(buf, "abc ");
	EXPECT_FALSE(cbuf.popBytes(buf, 1));
}

TEST(CircularBufferTest, BurnInTest)
{
	CircularBuffer<4> cbuf;
	char buf[5] = "    ";
	for(int i = 0; i < 10; i++)
	{
		char x = i;
		EXPECT_TRUE(cbuf.pushBytes(&x, 1));
		EXPECT_TRUE(cbuf.popBytes(buf, 1));
		EXPECT_FALSE(cbuf.popBytes(buf, 1));
		EXPECT_EQ(buf[0], x);
	}
	for(int i = 0; i < 10; i++)
	{
		char x[4] = {i, i % 17, i % 7, 0};
		EXPECT_TRUE(cbuf.pushBytes(x, 3));
		EXPECT_TRUE(cbuf.popBytes(buf, 3));
		EXPECT_FALSE(cbuf.popBytes(buf, 2));
		EXPECT_EQ(buf[0], x[0]);
		EXPECT_EQ(buf[1], x[1]);
		EXPECT_EQ(buf[2], x[2]);
	}
	for(int i = 0; i < 10; i++)
	{
		char x[4] = {i, i % 17, i % 7, 0};
		EXPECT_TRUE(cbuf.pushBytes(x, 2));
		EXPECT_TRUE(cbuf.pushBytes(x+2, 1));
		EXPECT_TRUE(cbuf.popBytes(buf, 1));
		EXPECT_TRUE(cbuf.popBytes(buf+1, 1));
		EXPECT_TRUE(cbuf.popBytes(buf+2, 1));
		EXPECT_FALSE(cbuf.popBytes(buf, 2));
		EXPECT_EQ(buf[0], x[0]);
		EXPECT_EQ(buf[1], x[1]);
		EXPECT_EQ(buf[2], x[2]);
	}
}
