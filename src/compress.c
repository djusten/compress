// Copyright (C) 2020  Diogo Justen. All rights reserved.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <bit_stream.h>

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
  int sizeTotal = height == 1 ? width : (height * lineSize);

  int currentPixelIndex = 0;
  int currentLine = 0;
  int pixelCount = 1;

  //Debug and to show results
  printf("Valid pixels: ");
  printPixels(pixels, width, sizeTotal);

  BitStream bitStream =
  {
    .data = NULL,
    .size = 0,
    .outputValue = 0,
    .outputBitSize = 0
  };

  for (int nextPixelIndex = 1; nextPixelIndex <= sizeTotal;)
  {
    const uint8_t *currentPixel = pixels + currentPixelIndex;

    //last valid pixel is different from previous
    if (nextPixelIndex >= sizeTotal)
    {
      BitStreamAdd(&bitStream, *currentPixel, pixelCount);
      break;
    }

    const uint8_t *nextPixel = pixels + nextPixelIndex;
    if (*currentPixel == *nextPixel)
    {
      if (++pixelCount == MAX_ZERO_SPECIAL_CODE)
      {
        BitStreamAdd(&bitStream, *currentPixel, pixelCount);
        currentPixelIndex = nextPixelIndex;
        pixelCount = 1;
      }
    }
    else
    {
      BitStreamAdd(&bitStream, *currentPixel, pixelCount);
      currentPixelIndex = nextPixelIndex;
      pixelCount = 1;
    }

    if (++nextPixelIndex >= (currentLine * lineSize) + width)
    {
      nextPixelIndex = (nextPixelIndex | 0x3) + 1;
      currentLine++;
    }
  }

  printf("\n");

  *size = bitStream.size;
  return bitStream.data;
}
