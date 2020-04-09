// Copyright (C) 2020  Diogo Justen. All rights reserved.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "filter.h"
#include "bit_stream.h"

void printPixels(const uint8_t *pixels, int size)
{
  int i;
  const uint8_t *p = pixels;

  for (i = 0; i < size; i++)
  {
    printf("%x ", *p);
    p++;
  }
  printf("\n");
}

int CountPixel(const uint8_t *pValidPixels, int remainingPixels)
{
  if (remainingPixels <= 1)
  {
    printf("Error\n");
    return 0;
  }

  uint8_t pixel = *pValidPixels;
  //current pixel different from the next
  if (pixel != *(pValidPixels + 1))
  {
    return 1;
  }

  /* To discuss later
   * "...<width> has a typical value of 256 to 4096..."
   * uint8_t blankBlock[256] = { 0 };
   * memset(blankBlock, 0, sizeof(blankBlock);
   * memcmp(blankBlock, pValidPixels);
   * if equal than return 256
   */

  int i = 0;
  int pixelCount = 1;

  while ((i < (remainingPixels - 1)) && (pixel == *(pValidPixels + 1)))
  {
    pValidPixels++;
    pixelCount++;
    i++;
  }

  return pixelCount;
}

uint8_t *Compress(const uint8_t *pixels, uint_fast16_t width, uint_fast16_t height, uint32_t *size)
{
  uint32_t validPixelsSize = width * height;
  uint8_t *validPixels = Filter(pixels, width, validPixelsSize);

  //Debug and to show results
  printf("Valid pixels: ");
  printPixels(validPixels, validPixelsSize);

  const uint8_t *pValidPixels = validPixels;
  int remainingPixels;
  for (remainingPixels = validPixelsSize; remainingPixels > 0;)
  {
    int numSamePixel = CountPixel(pValidPixels, remainingPixels);
    if (numSamePixel <= 0)
    {
      printf("Unable to count pixel %x\n", *pValidPixels);
      free(validPixels);
      return NULL;
    }

    //Debug
    //printf("Pixel: %x Samples: %dx\n", *pValidPixels, numSamePixel);

    uint8_t bitsUsed;
    uint32_t bitStream;

    BitStreamConvert(*pValidPixels, numSamePixel, &bitStream, &bitsUsed);

    //Debug Only
    BitStreamPrint(bitStream, bitsUsed);

    pValidPixels += numSamePixel;
    remainingPixels -= numSamePixel;
  }

  *size = validPixelsSize;
  return validPixels;
}
