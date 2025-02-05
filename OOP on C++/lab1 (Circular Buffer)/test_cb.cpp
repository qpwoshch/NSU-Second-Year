#include <iostream>
#include "CircularBuffer.h"
#include <gtest/gtest.h>

TEST(CircularBufferTest, CreationAndDistructionEmptyBuffer) {
CircularBuffer buf;

}

TEST(CircularBufferTest, CreationAndCopy) {
CircularBuffer buf(5);
CircularBuffer buf2(4, 'R');
CircularBuffer buf_copy(buf2);
EXPECT_EQ(buf_copy.toString(), "RRRR");
}

TEST(CircularBufferTest, CreationWithException) {
EXPECT_THROW(CircularBuffer buf(0), std::logic_error);
EXPECT_THROW(CircularBuffer buf1(0, 'r'), std::logic_error);
}


TEST(CircularBufferTest, PushBack) {
CircularBuffer buf(5);
buf.push_back('o');
buf.push_back('n');
buf.push_back('e');
buf.push_back('t');
buf.push_back('w');
buf.push_back('r');
EXPECT_EQ(buf.toString(), "netwr");
}

TEST(CircularBufferTest, PushFront) {
CircularBuffer buf(5);
buf.push_front('o');
buf.push_front('n');
buf.push_front('e');
buf.push_front('t');
buf.push_front('w');
buf.push_front('r');
EXPECT_EQ(buf.toString(), "rwten");
}

TEST(CircularBufferTest, Back) {
CircularBuffer buf(3);
buf.push_back('a');
buf.push_back('b');
buf.push_back('c');
buf.push_back('d');
buf.push_back('e');
buf.push_back('f');
EXPECT_EQ(buf.back(), 'f');
const CircularBuffer& const_buf = buf;
EXPECT_EQ(const_buf.back(), 'f');
}

TEST(CircularBufferTest, Front) {
CircularBuffer buf(3);
buf.push_front('a');
buf.push_front('b');
buf.push_front('c');
buf.push_front('d');
EXPECT_EQ(buf.front(), 'd');
const CircularBuffer& const_buf = buf;
EXPECT_EQ(const_buf.front(), 'd');
}


TEST(CircularBufferTest, Operator) {
CircularBuffer buf(3);
buf.push_front('a');
buf.push_front('b');
buf.push_front('c');
buf.push_front('d');
EXPECT_EQ(buf[1], 'c');
const CircularBuffer& const_buf = buf;
EXPECT_EQ(const_buf[2], 'b');
}



TEST(CircularBufferTest, AccessByIndex) {
CircularBuffer buf(4);
buf.push_front('a');
buf.push_back('b');
buf.push_front('c');
buf.push_back('d');
buf.push_front('e');
buf.push_front('f');
buf.push_front('g');
buf.push_back('h');
EXPECT_EQ(buf.at(2), 'c');
EXPECT_EQ(buf.at(-3), 'e');
const CircularBuffer& const_buf = buf;
EXPECT_EQ(const_buf.at(1), 'e');
EXPECT_EQ(const_buf.at(-2), 'c');
}

TEST(CircularBufferTest, linerize) {
CircularBuffer buf(5);
buf.push_front('a');
buf.push_front('b');
buf.push_front('c');
buf.push_back('1');
buf.push_front('2');
buf.push_back('3');
buf.push_front('4');
buf.push_front('f');
buf.push_front('g');
buf.push_back('h');
buf.linearize();
EXPECT_EQ(buf.LinerizeToString(), "f4cbh");
}

TEST(CircularBufferTest, linerizeExeption) {
CircularBuffer buf(5);
EXPECT_THROW(buf.linearize(), std::out_of_range);
}

TEST(CircularBufferTest, IsLinerize) {
CircularBuffer buf(5);
buf.push_front('a');
buf.push_front('b');
buf.push_front('c');
buf.push_back('1');
buf.push_front('2');
buf.push_back('3');
buf.push_front('4');
buf.push_front('f');
buf.push_front('g');
buf.push_back('h');
EXPECT_FALSE(buf.is_linearized());
buf.linearize();
EXPECT_TRUE(buf.is_linearized());
}

TEST(CircularBufferTest, Rotate) {
CircularBuffer buf(5);
buf.push_front('g');
buf.push_front('0');
buf.push_front('F');
buf.push_back('t');
buf.push_back('5');
buf.push_front('R');
buf.push_back('8');
buf.rotate(3);
EXPECT_EQ(buf.toString(), "0gt8F");
buf.rotate(-2);
EXPECT_EQ(buf.toString(), "8F0gt");
}

TEST(CircularBufferTest, size) {
CircularBuffer buf(20, 'r');
EXPECT_EQ(buf.size(), 20);
CircularBuffer buf1(5);
EXPECT_EQ(buf1.size(), 0);
}

TEST(CircularBufferTest, IsEmpty) {
CircularBuffer buf(20, 'r');
EXPECT_FALSE(buf.empty());
CircularBuffer buf1(5);
EXPECT_TRUE(buf1.empty());
}

TEST(CircularBufferTest, IsFull) {
CircularBuffer buf(20, 'r');
EXPECT_TRUE(buf.full());
CircularBuffer buf1(5);
EXPECT_FALSE(buf1.full());
}

TEST(CircularBufferTest, reserve) {
CircularBuffer buf(20);
buf.push_front('r');
EXPECT_EQ(buf.reserve(), 19);
}

TEST(CircularBufferTest, capacity) {
CircularBuffer buf(20);
buf.push_front('r');
EXPECT_EQ(buf.capacity(), 20);
}

TEST(CircularBufferTest, resize) {
CircularBuffer buf(8);
buf.push_back('F');
buf.resize(7, 'f');
EXPECT_EQ(buf.toString(), "Fffffff");
CircularBuffer buf1(8, 'a');
buf1.resize(2, 'f');
EXPECT_EQ(buf1.toString(), "aa");
}

TEST(CircularBufferTest, resizeExeption) {
CircularBuffer buf(8, 'a');
EXPECT_THROW(buf.resize(-2), std::logic_error);
EXPECT_THROW(buf.resize(10), std::logic_error);
}

TEST(CircularBufferTest, recapacity) {
CircularBuffer buf(8, 'a');
buf.set_capacity(6);
EXPECT_EQ(buf.toString(), "aaaaaa");
CircularBuffer buf1(8, 'a');
buf1.set_capacity(10);
EXPECT_EQ(buf1.toString(), "aaaaaaaa");
}

TEST(CircularBufferTest, recapacityExeption) {
CircularBuffer buf(8, 'a');
EXPECT_THROW(buf.set_capacity(-2), std::logic_error);
}

TEST(CircularBufferTest, OperatorEquality) {
CircularBuffer buf(8, 'a');
CircularBuffer buf1(9, 'b');
CircularBuffer buf2(9, 'b');
buf=buf1;
EXPECT_EQ(buf.toString(), "bbbbbbbbb");
}



TEST(CircularBufferTest, swap) {
CircularBuffer buf(8, 'a');
CircularBuffer buf1(9, 'b');
buf.swap(buf1);
EXPECT_EQ(buf.toString(), "bbbbbbbbb");
EXPECT_EQ(buf1.toString(), "aaaaaaaa");
}

TEST(CircularBufferTest, popBack) {
CircularBuffer buf(8, 'a');
buf.push_back('q');
buf.push_back('w');
buf.pop_back();
EXPECT_EQ(buf.toString(), "aaaaaaq");
}

TEST(CircularBufferTest, popBackExeption) {
CircularBuffer buf(5);
EXPECT_THROW(buf.pop_back(), std::logic_error);
}

TEST(CircularBufferTest, popFront) {
CircularBuffer buf(8, 'a');
buf.push_front('q');
buf.push_front('w');
buf.pop_front();
EXPECT_EQ(buf.toString(), "qaaaaaa");
}

TEST(CircularBufferTest, popFrontExeption) {
CircularBuffer buf(5);
EXPECT_THROW(buf.pop_front(), std::logic_error);
}

TEST(CircularBufferTest, insert) {
CircularBuffer buf(8, 'a');
buf.insert(5, 'A');
EXPECT_EQ(buf.toString(), "aaaaaAaa");
buf.insert(-12, 'r');
EXPECT_EQ(buf.toString(), "aaaarAaa");
buf.insert(9, 'V');
EXPECT_EQ(buf.toString(), "aVaarAaa");
}



TEST(CircularBufferTest, erase) {
CircularBuffer buf(8, 'a');
buf.push_front('A');
buf.push_front('A');
buf.push_back('B');
buf.erase(2, 4);
EXPECT_EQ(buf.toString(), "AaaaaB");
buf.erase(0, 6);
EXPECT_EQ(buf.toString(), "");
}

TEST(CircularBufferTest, eraseExeption) {
CircularBuffer buf(8, 'a');
EXPECT_THROW(buf.erase(6, 2), std::logic_error);
}

TEST(CircularBufferTest, clear) {
CircularBuffer buf(8, 'a');
buf.clear();
EXPECT_EQ(buf.toString(), "");
}

TEST(CircularBufferTest, operatorComparison) {
CircularBuffer buf(8, 'a');
CircularBuffer buf2(8, 'a');
CircularBuffer buf4(8, 'b');
CircularBuffer buf3(9, 'a');
EXPECT_TRUE(buf==buf2);
EXPECT_FALSE(buf==buf3);
EXPECT_FALSE(buf==buf4);
EXPECT_TRUE(buf!=buf3);
EXPECT_FALSE(buf!=buf2);
}