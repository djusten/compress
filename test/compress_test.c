// Copyright (C) 2020  Diogo Justen. All rights reserved.

#include <stdlib.h>
#include <unity.h>
#include <compress.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_compress_zeros_special(void)
{
  const uint8_t pixels[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF
                           };
  uint_fast16_t width = 5;
  uint_fast16_t height = 4;

  uint8_t expectedRet[] = { 0x80, 0x01 };

  uint32_t size;
  uint8_t *compressed = Compress(pixels, width, height, &size);

  TEST_ASSERT_EQUAL_INT(0x02, size);
  TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);

  free(compressed);
}

void test_compress_one_zero(void)
{
  const uint8_t pixels[] = { 0x0, 0x0, 0x0, 0xff };
  uint_fast16_t width = 1;
  uint_fast16_t height = 1;

  uint8_t expectedRet[] = { 0x0 };

  uint32_t size;
  uint8_t *compressed = Compress(pixels, width, height, &size);

  TEST_ASSERT_EQUAL_INT(0x01, size);
  TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);

  free(compressed);
}

void test_compress_three_zeros(void)
{
  const uint8_t pixels[] = { 0x0, 0x0, 0x0, 0xff };
  uint_fast16_t width = 3;
  uint_fast16_t height = 1;

  const uint8_t expectedRet[] = { 0x0 };

  uint32_t size;
  uint8_t *compressed = Compress(pixels, width, height, &size);

  TEST_ASSERT_EQUAL_INT(0x01, size);
  TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);

  free(compressed);
}

void test_compress_one_fd(void)
{
  const uint8_t pixels[] = { 0x1, 0xFF, 0xFF, 0xFF};
  uint_fast16_t width = 1;
  uint_fast16_t height = 1;

  uint8_t expectedRet[] = { 0x80, 0x80 };

  uint32_t size;
  uint8_t *compressed = Compress(pixels, width, height, &size);

  TEST_ASSERT_EQUAL_INT(0x02, size);
  TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);

  free(compressed);
}

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_compress_zeros_special);

  RUN_TEST(test_compress_one_zero);
//  RUN_TEST(test_compress_three_zeros);

  RUN_TEST(test_compress_one_fd);

  //test 0xff 0xff
  return UNITY_END();
}
