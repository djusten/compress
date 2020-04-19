// Copyright (C) 2020  Diogo Justen. All rights reserved.

#include <stdlib.h>
#include <unity.h>
#include <bit_stream.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_stream_one_pixel(void)
{
  int numOccurrences = 1;
  uint32_t bitStream = 0;
  uint8_t bitsUsed = 0;

  uint8_t pixel = 0x00;
  TEST_ASSERT_TRUE(BitStreamConvert(pixel, numOccurrences, &bitStream, &bitsUsed));
  TEST_ASSERT_EQUAL_HEX(0x00, bitStream);
  TEST_ASSERT_EQUAL_INT(1, bitsUsed);

  pixel = 0x9E;
  TEST_ASSERT_TRUE(BitStreamConvert(pixel, numOccurrences, &bitStream, &bitsUsed));
  TEST_ASSERT_EQUAL_HEX(0b110011110, bitStream);
  TEST_ASSERT_EQUAL_INT(9, bitsUsed);

  pixel = 0xFF;
  TEST_ASSERT_TRUE(BitStreamConvert(pixel, numOccurrences, &bitStream, &bitsUsed));
  TEST_ASSERT_EQUAL_HEX(0b111111111, bitStream);
  TEST_ASSERT_EQUAL_INT(9, bitsUsed);
}

void test_stream_four_pixels(void)
{
  int numOccurrences = 4;
  uint32_t bitStream = 0;
  uint8_t bitsUsed = 0;

  uint8_t pixel = 0x00;
  TEST_ASSERT_TRUE(BitStreamConvert(pixel, numOccurrences, &bitStream, &bitsUsed));
  TEST_ASSERT_EQUAL_HEX(0x00, bitStream);
  TEST_ASSERT_EQUAL_INT(4, bitsUsed);

  pixel = 0x9E;
  TEST_ASSERT_FALSE(BitStreamConvert(pixel, numOccurrences, &bitStream, &bitsUsed));

  pixel = 0xFF;
  TEST_ASSERT_FALSE(BitStreamConvert(pixel, numOccurrences, &bitStream, &bitsUsed));
}

void test_stream_twenty_pixels(void)
{
  int numOccurrences = 20;
  uint32_t bitStream = 0;
  uint8_t bitsUsed = 0;

  uint8_t pixel = 0x00;
  TEST_ASSERT_TRUE(BitStreamConvert(pixel, numOccurrences, &bitStream, &bitsUsed));
  TEST_ASSERT_EQUAL_HEX(0b1000000000000001, bitStream);
  TEST_ASSERT_EQUAL_INT(16, bitsUsed);

  pixel = 0x9E;
  TEST_ASSERT_FALSE(BitStreamConvert(pixel, numOccurrences, &bitStream, &bitsUsed));

  pixel = 0xFF;
  TEST_ASSERT_FALSE(BitStreamConvert(pixel, numOccurrences, &bitStream, &bitsUsed));
}

void test_stream_add_one_pixel(void)
{
  int numOccurrences = 1;

  {
    BitStream bitStream =
    {
      .data = NULL,
      .size = 0,
      .outputValue = 0,
      .outputBitSize = 0
    };

    uint8_t pixel = 0x00;
    uint8_t expected[] = { 0x00 };
    TEST_ASSERT_TRUE(BitStreamAdd(&bitStream, pixel, numOccurrences));
    TEST_ASSERT_EQUAL_INT(sizeof(expected), bitStream.size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, bitStream.data, bitStream.size);
    free(bitStream.data);
  }

  {
    BitStream bitStream =
    {
      .data = NULL,
      .size = 0,
      .outputValue = 0,
      .outputBitSize = 0
    };

    uint8_t pixel = 0x55;
    uint8_t expected[] = { 0xAA, 0x80 };
    TEST_ASSERT_TRUE(BitStreamAdd(&bitStream, pixel, numOccurrences));
    TEST_ASSERT_EQUAL_INT(sizeof(expected), bitStream.size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, bitStream.data, bitStream.size);
    free(bitStream.data);
  }

  {
    BitStream bitStream =
    {
      .data = NULL,
      .size = 0,
      .outputValue = 0,
      .outputBitSize = 0
    };

    uint8_t pixel = 0xFF;
    uint8_t expected[] = { 0xFF, 0x80 };
    TEST_ASSERT_TRUE(BitStreamAdd(&bitStream, pixel, numOccurrences));
    TEST_ASSERT_EQUAL_INT(sizeof(expected), bitStream.size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, bitStream.data, bitStream.size);
    free(bitStream.data);
  }
}

void test_stream_add_four_pixels(void)
{
  int numOccurrences = 4;

  {
    BitStream bitStream =
    {
      .data = NULL,
      .size = 0,
      .outputValue = 0,
      .outputBitSize = 0
    };

    uint8_t pixel = 0x00;
    uint8_t expected[] = { 0x00 };
    TEST_ASSERT_TRUE(BitStreamAdd(&bitStream, pixel, numOccurrences));
    TEST_ASSERT_EQUAL_INT(sizeof(expected), bitStream.size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, bitStream.data, bitStream.size);
    free(bitStream.data);
  }

  {
    BitStream bitStream =
    {
      .data = NULL,
      .size = 0,
      .outputValue = 0,
      .outputBitSize = 0
    };

    uint8_t pixel = 0x55;
    TEST_ASSERT_FALSE(BitStreamAdd(&bitStream, pixel, numOccurrences));
  }

  {
    BitStream bitStream =
    {
      .data = NULL,
      .size = 0,
      .outputValue = 0,
      .outputBitSize = 0
    };

    uint8_t pixel = 0xFF;
    TEST_ASSERT_FALSE(BitStreamAdd(&bitStream, pixel, numOccurrences));
  }
}

void test_stream_add_twenty_pixels(void)
{
  int numOccurrences = 20;

  {
    BitStream bitStream =
    {
      .data = NULL,
      .size = 0,
      .outputValue = 0,
      .outputBitSize = 0
    };

    uint8_t pixel = 0x00;
    uint8_t expected[] = { 0x80, 0x01 };
    TEST_ASSERT_TRUE(BitStreamAdd(&bitStream, pixel, numOccurrences));
    TEST_ASSERT_EQUAL_INT(sizeof(expected), bitStream.size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, bitStream.data, bitStream.size);
    free(bitStream.data);
  }

  {
    BitStream bitStream =
    {
      .data = NULL,
      .size = 0,
      .outputValue = 0,
      .outputBitSize = 0
    };

    uint8_t pixel = 0x8D;
    TEST_ASSERT_FALSE(BitStreamAdd(&bitStream, pixel, numOccurrences));
  }

  {
    BitStream bitStream =
    {
      .data = NULL,
      .size = 0,
      .outputValue = 0,
      .outputBitSize = 0
    };

    uint8_t pixel = 0xFF;
    TEST_ASSERT_FALSE(BitStreamAdd(&bitStream, pixel, numOccurrences));
  }
}

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_stream_one_pixel);
  RUN_TEST(test_stream_four_pixels);
  RUN_TEST(test_stream_twenty_pixels);

  RUN_TEST(test_stream_add_one_pixel);
  RUN_TEST(test_stream_add_four_pixels);
  RUN_TEST(test_stream_add_twenty_pixels);

  return UNITY_END();
}
