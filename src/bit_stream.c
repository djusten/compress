// Copyright (C) 2020  Diogo Justen. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include "bit_stream.h"

#define BITS_USED_NON_ZERO 9
#define BITS_USED_SPECIAL_CODE 16
#define SPECIAL_CODE_MASK 0x8000
#define NON_ZERO_MASK 0x100

int BitStreamAdd(uint8_t **vectorOutput, const uint8_t pixel, int numOccurrences)
{
  uint8_t bitsUsed;
  uint32_t bitStream;

  BitStreamConvert(pixel, numOccurrences, &bitStream, &bitsUsed);
  BitStreamPrint(bitStream, bitsUsed);

  //TODO move to struct
  static uint8_t outputValue = 0;
  static uint8_t outputBitSize = 0;
  static int count = 0;

  for (int i = bitsUsed - 1; i >= 0; i--)
  {
    if (outputBitSize == 0)
    {
      count++;
      *vectorOutput = realloc(*vectorOutput, count);
    }

    uint8_t bit = (bitStream >> i) & 1U;
    outputValue |= (bit << (7 - outputBitSize++));

    (*vectorOutput)[count - 1] = outputValue;
    if (outputBitSize == 8)
    {
      outputValue = 0;
      outputBitSize = 0;
    }
  }

  return count;
}

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
