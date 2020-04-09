// Copyright (C) 2020  Diogo Justen. All rights reserved.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint8_t *Filter(const uint8_t *pixels, uint_fast16_t width, uint32_t length)
{
  uint8_t *validPixels = malloc(length);
  if (!validPixels)
  {
    printf("Unable to allocate memory\n");
    return NULL;
  }

  int offsetSrc = 0;
  int offsetDest = 0;

  for (offsetDest = 0; offsetDest < length; offsetDest += width)
  {
    memcpy(validPixels + offsetDest, pixels + offsetSrc, width);

    //round up to next index multiple of 4
    offsetSrc += (offsetDest | 0x3) + 1;
  }

  return validPixels;
}
