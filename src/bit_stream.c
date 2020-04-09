// Copyright (C) 2020  Diogo Justen. All rights reserved.

#include <stdio.h>
#include "bit_stream.h"

#define BITS_USED_NON_ZERO 9
#define BITS_USED_SPECIAL_CODE 16
#define SPECIAL_CODE_MASK 0x8000
#define NON_ZERO_MASK 0x100

/*
 * To discuss
 * Does not support to convert long sequence of 0's > (18 + 2 * 127). e.g. a black image.
 */
bool BitStreamConvert(const uint8_t pixel, int numOccurrences,
                      uint32_t *bitStream, uint8_t *bitsUsed)
{
  *bitStream = 0;

  if (pixel != 0)
  {
    /*
     * "...input bytes (with values 1 to 255) shall be encoded by a BIT with the
     * value 1 followed by the eight bits of the input..."
     * Always 9 bits used
     */
    *bitsUsed = BITS_USED_NON_ZERO;
    *bitStream = pixel | NON_ZERO_MASK;
    return true;
  }

  //18 or more must use special code
  if (numOccurrences < 18)
  {
    *bitsUsed = numOccurrences;
    *bitStream = 0;
    return true;
  }

  //special code for zeros
  *bitStream = ((numOccurrences - 18) / 2) | SPECIAL_CODE_MASK;
  *bitsUsed = (numOccurrences % 2 == 0) ? BITS_USED_SPECIAL_CODE : BITS_USED_SPECIAL_CODE + 1;

  return true;
}

void BitStreamPrint(uint32_t bitStream, uint8_t bitsUsed)
{
  int i;

  //Only to debug and print with space
  static int tmp = 1;

  for (i = bitsUsed - 1; i >= 0; i--)
  {
    printf("%d", (bitStream >> i) & 1U);

    //Only to debug and print with space
    if (tmp++ % 8 == 0)
    {
      printf(" ");
    }
  }
}
