// Copyright (C) 2020  Diogo Justen. All rights reserved.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "bit_stream.h"

#define MAX_ZERO_SPECIAL_CODE 272

void printPixels(const uint8_t *pixels, int width, int sizeTotal)
{
  const uint8_t *p = pixels;
  int lineSize = (width | 0x3) + 1;
  int currentLine = 0;
  int i;

  for (i = 0; i < sizeTotal;)
  {
    printf("%X ", *(p + i));

    if (++i >= (currentLine * lineSize) + width)
    {
      i = (i | 0x3) + 1;
      currentLine++;
    }
  }

  printf("\n");
}

uint8_t *Compress(const uint8_t *pixels, uint_fast16_t width, uint_fast16_t height, uint32_t *size)
{
  int lineSize = (width | 0x3) + 1;
  int sizeTotal = height * lineSize;

  int currentPixelIndex = 0;
  int currentLine = 0;
  int count = 1;

  //Debug and to show results
  printf("Valid pixels: ");
  printPixels(pixels, width, sizeTotal);

  uint8_t bitsUsed;
  uint32_t bitStream;

  for (int nextPixelIndex = 1; nextPixelIndex <= sizeTotal;)
  {
    const uint8_t *currentPixel = pixels + currentPixelIndex;

    //last valid pixel is different from previous
    if (nextPixelIndex >= sizeTotal)
    {
      BitStreamConvert(*currentPixel, count, &bitStream, &bitsUsed);
      BitStreamPrint(bitStream, bitsUsed);
      break;
    }

    const uint8_t *nextPixel = pixels + nextPixelIndex;
    if (*currentPixel == *nextPixel)
    {
      if (++count == MAX_ZERO_SPECIAL_CODE)
      {
        BitStreamConvert(*currentPixel, count, &bitStream, &bitsUsed);
        BitStreamPrint(bitStream, bitsUsed);
        currentPixelIndex = nextPixelIndex;
        count = 1;
      }
    }
    else
    {
      BitStreamConvert(*currentPixel, count, &bitStream, &bitsUsed);
      BitStreamPrint(bitStream, bitsUsed);
      currentPixelIndex = nextPixelIndex;
      count = 1;
    }

    if (++nextPixelIndex >= (currentLine * lineSize) + width)
    {
      nextPixelIndex = (nextPixelIndex | 0x3) + 1;
      currentLine++;
    }
  }

  printf("\n");

  return NULL;
}
