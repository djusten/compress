#include <unity.h>
#include <bit_stream.h>

void setUp(void) {
}

void tearDown(void) {
}

void test_StreamConvert(void)
{
  const uint8_t pixel = 0;
  int numOccurrences = 1;

  uint32_t bitStream = 0;
  uint8_t bitsUsed = 0;

  TEST_ASSERT_TRUE(BitStreamConvert(pixel, numOccurrences, &bitStream, &bitsUsed));
  TEST_ASSERT_EQUAL_INT(bitStream, 0x00);
  TEST_ASSERT_EQUAL_INT(bitsUsed, 0x01);
}

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_StreamConvert);

  return UNITY_END();
}
