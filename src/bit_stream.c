// Copyright (C) 2020  Diogo Justen. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include "bit_stream.h"

#define BITS_USED_NON_ZERO 9
#define BITS_USED_SPECIAL_CODE 16
#define SPECIAL_CODE_MASK 0x8000
#define NON_ZERO_MASK 0x100

bool BitStreamAdd(BitStream *bitStream, const uint8_t pixel, int numOccurrences)
{
  uint8_t bitsUsed = 0;
  uint32_t pixelBitStream = 0;

  if (!BitStreamConvert(pixel, numOccurrences, &pixelBitStream, &bitsUsed))
  {
    printf("Unable to convert bit stream");
    return false;
  }

  BitStreamPrint(pixelBitStream, bitsUsed);

  //TODO use mask to shift using blocks
  for (int i = bitsUsed - 1; i >= 0; i--)
  {
    if (bitStream->outputBitSize == 0)
    {
      bitStream->size++;
      bitStream->data = realloc(bitStream->data, bitStream->size);
    }

    uint8_t bit = (pixelBitStream >> i) & 1U;
    bitStream->outputValue |= (bit << (7 - bitStream->outputBitSize++));

    (bitStream->data)[bitStream->size - 1] = bitStream->outputValue;
    if (bitStream->outputBitSize == 8)
    {
      bitStream->outputValue = 0;
      bitStream->outputBitSize = 0;
    }
  }

  return true;
}

bool BitStreamConvert(const uint8_t pixel, int numOccurrences,
                      uint32_t *bitStream, uint8_t *bitsUsed)
{
  *bitStream = 0;

  if (pixel != 0)
  {
    if (numOccurrences > 1)
    {
      printf("Invalid pixel and numOccurrences\n");
      return false;
    }

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
