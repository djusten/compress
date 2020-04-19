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

void test_compress_one_pixel(void)
{
  uint_fast16_t width = 1;
  uint_fast16_t height = 1;
  uint32_t size;

  {
    const uint8_t pixels[] = { 0x00 };
    const uint8_t expectedRet[] = { 0x00 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0x7E };
    const uint8_t expectedRet[] = { 0xBF, 0x00 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0xFF };
    const uint8_t expectedRet[] = { 0xFF, 0x80 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }
}

void test_compress_three_pixels_equal_one_row(void)
{
  uint_fast16_t width = 3;
  uint_fast16_t height = 1;
  uint32_t size;

  {
    const uint8_t pixels[] = { 0x00, 0x00, 0x00 };
    const uint8_t expectedRet[] = { 0x00 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0x81, 0x81, 0x81 };
    const uint8_t expectedRet[] = { 0xC0, 0xE0, 0x70, 0x20 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0xFF, 0xFF, 0xFF };
    const uint8_t expectedRet[] = { 0xFF, 0xFF, 0xFF, 0xE0 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }
}

void test_compress_four_pixels_equal_one_row(void)
{
  uint_fast16_t width = 4;
  uint_fast16_t height = 1;
  uint32_t size;

  {
    const uint8_t pixels[] = { 0x00, 0x00, 0x00, 0x00 };
    const uint8_t expectedRet[] = { 0x00 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0x81, 0x81, 0x81, 0x81 };
    const uint8_t expectedRet[] = { 0xC0, 0xE0, 0x70, 0x38, 0x10 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0xFF, 0xFF, 0xFF, 0xFF };
    const uint8_t expectedRet[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xF0 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }
}

void test_compress_six_pixels_equal_one_row(void)
{
  uint_fast16_t width = 6;
  uint_fast16_t height = 1;
  uint32_t size;

  {
    const uint8_t pixels[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    const uint8_t expectedRet[] = { 0x00 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0x3, 0x3, 0x3, 0x3, 0x3, 0x3 };
    const uint8_t expectedRet[] = { 0x81, 0xC0, 0xE0, 0x70, 0x38, 0x1C, 0x0C };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0x81, 0x81, 0x81, 0x81, 0x81, 0x81 };
    const uint8_t expectedRet[] = { 0xC0, 0xE0, 0x70, 0x38, 0x1C, 0x0E, 0x04 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    const uint8_t expectedRet[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }
}

void test_compress_three_pixels_different_one_row(void)
{
  uint_fast16_t width = 3;
  uint_fast16_t height = 1;
  uint32_t size;

  {
    const uint8_t pixels[] = { 0x00, 0x23, 0xDD };
    const uint8_t expectedRet[] = { 0x48, 0xFB, 0xA0 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0x81, 0x10, 0xB1 };
    const uint8_t expectedRet[] = { 0xC0, 0xC4, 0x36, 0x20 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0x11, 0xFF, 0xFF };
    const uint8_t expectedRet[] = { 0x88, 0xFF, 0xFF, 0xE0 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0xF0, 0x01, 0x00 };
    const uint8_t expectedRet[] = { 0xF8, 0x40, 0x40 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }
}

void test_compress_six_pixels_different_one_row(void)
{
  uint_fast16_t width = 6;
  uint_fast16_t height = 1;
  uint32_t size;

  {
    const uint8_t pixels[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05 };
    const uint8_t expectedRet[] = { 0x40, 0x60, 0x50, 0x38, 0x24, 0x14 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60 };
    const uint8_t expectedRet[] = { 0x88, 0x48, 0x26, 0x14, 0x0A, 0x85, 0x80 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF };
    const uint8_t expectedRet[] = { 0x07, 0xFC };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00 };
    const uint8_t expectedRet[] = { 0xFF, 0xFF, 0xC0 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }
}

void test_compress_3x2_same_pixels(void)
{
  uint_fast16_t width = 3;
  uint_fast16_t height = 2;
  uint32_t size;

  {
    const uint8_t pixels[] = { 0x00, 0x00, 0x00, 0xAA,
                               0x00, 0x00, 0x00, 0xAA
                             };
    const uint8_t expectedRet[] = { 0x00 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0x10, 0x10, 0x10, 0xAA,
                               0x10, 0x10, 0x10, 0xAA
                             };
    const uint8_t expectedRet[] = { 0x88, 0x44, 0x22, 0x11, 0x08, 0x84, 0x40 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0xFF, 0xFF, 0xFF, 0xAA,
                               0xFF, 0xFF, 0xFF, 0xAA
                             };
    const uint8_t expectedRet[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }
}

void test_compress_3x2_different_pixels(void)
{
  uint_fast16_t width = 3;
  uint_fast16_t height = 2;
  uint32_t size;

  {
    const uint8_t pixels[] = { 0x00, 0x01, 0x02, 0xAA,
                               0x03, 0x04, 0x05, 0xAA
                             };
    const uint8_t expectedRet[] = { 0x40, 0x60, 0x50, 0x38, 0x24, 0x14 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0x10, 0x20, 0x30, 0xAA,
                               0x40, 0x50, 0x60, 0xAA
                             };
    const uint8_t expectedRet[] = { 0x88, 0x48, 0x26, 0x14, 0x0A, 0x85, 0x80 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0x00, 0x00, 0x00, 0xAA,
                               0x00, 0x00, 0xFF, 0xAA
                             };
    const uint8_t expectedRet[] = { 0x07, 0xFC };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }
}

void test_compress_4x2_same_pixels(void)
{
  uint_fast16_t width = 4;
  uint_fast16_t height = 2;
  uint32_t size;

  {
    const uint8_t pixels[] = { 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00
                             };
    const uint8_t expectedRet[] = { 0x00 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0xA1, 0xA1, 0xA1, 0xA1,
                               0xA1, 0xA1, 0xA1, 0xA1
                             };
    const uint8_t expectedRet[] = { 0xD0, 0xE8, 0x74, 0x3A, 0x1D, 0x0E, 0x87, 0x43, 0xA1 };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }

  {
    const uint8_t pixels[] = { 0xFF, 0xFF, 0xFF, 0xFF,
                               0xFF, 0xFF, 0xFF, 0xFF
                             };
    const uint8_t expectedRet[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    uint8_t *compressed = Compress(pixels, width, height, &size);
    TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);
    free(compressed);
  }
}

void test_compress_16x_zeros(void)
{
  const uint8_t pixels[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                           };
  uint_fast16_t width = 8;
  uint_fast16_t height = 2;

  uint8_t expectedRet[] = { 0x00, 0x00 };

  uint32_t size;
  uint8_t *compressed = Compress(pixels, width, height, &size);

  TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
  TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);

  free(compressed);
}

void test_compress_17x_zeros(void)
{
  const uint8_t pixels[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xFF, 0xFF
                           };
  uint_fast16_t width = 6;
  uint_fast16_t height = 3;

  uint8_t expectedRet[] = { 0x00, 0x00, 0x6A, 0x80 };

  uint32_t size;
  uint8_t *compressed = Compress(pixels, width, height, &size);

  TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
  TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);

  free(compressed);
}

void test_compress_zeros_special_code_18x(void)
{
  const uint8_t pixels[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF
                           };
  uint_fast16_t width = 6;
  uint_fast16_t height = 3;

  uint8_t expectedRet[] = { 0x80, 0x00 };

  uint32_t size;
  uint8_t *compressed = Compress(pixels, width, height, &size);

  TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
  TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);

  free(compressed);
}

void test_compress_zeros_special_code_40x(void)
{
  const uint8_t pixels[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                           };
  uint_fast16_t width = 8;
  uint_fast16_t height = 5;

  uint8_t expectedRet[] = { 0x80, 0x0B };

  uint32_t size;
  uint8_t *compressed = Compress(pixels, width, height, &size);

  TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
  TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);

  free(compressed);
}

void test_compress_sample1(void)
{
  const uint8_t pixels[] = { 0x00, 0x00, 0x00, 0xFD, 0x00, 0x00, 0xFF, 0xFF,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF
                           };

  uint_fast16_t width = 6;
  uint_fast16_t height = 4;

  uint8_t expectedRet[] = { 0x1F, 0xD8, 0x00, 0x10 };

  uint32_t size;
  uint8_t *compressed = Compress(pixels, width, height, &size);

  TEST_ASSERT_EQUAL_INT(sizeof(expectedRet), size);
  TEST_ASSERT_EQUAL_HEX8_ARRAY(expectedRet, compressed, size);

  free(compressed);
}

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_compress_one_pixel);

  RUN_TEST(test_compress_three_pixels_equal_one_row);
  RUN_TEST(test_compress_four_pixels_equal_one_row);
  RUN_TEST(test_compress_six_pixels_equal_one_row);

  RUN_TEST(test_compress_three_pixels_different_one_row);
  RUN_TEST(test_compress_six_pixels_different_one_row);

  RUN_TEST(test_compress_3x2_same_pixels);
  RUN_TEST(test_compress_3x2_different_pixels);

  RUN_TEST(test_compress_4x2_same_pixels);

  RUN_TEST(test_compress_16x_zeros);
  RUN_TEST(test_compress_17x_zeros);
  RUN_TEST(test_compress_zeros_special_code_18x);
  RUN_TEST(test_compress_zeros_special_code_40x);

  RUN_TEST(test_compress_sample1);

  return UNITY_END();
}
