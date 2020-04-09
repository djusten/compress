#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "compress.h"

int main(int argc, char *argv[])
{
  //uint8_t pixels[] = { 9, 2, 3, 4, 2, 9, 54, 6, 1, 1, 2, 7 };
  //uint8_t pixels[] = { 1, 2, 3, 255, 1, 2, 3, 255, 1, 2, 3, 255 };
  uint8_t pixels[] = { 0x00, 0x00, 0x00, 0xFD, 0x00, 0xFF, 0xFF, 0xFF,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF
                     };

  uint32_t size = 0;
  //uint8_t *compressedImage = Compress(pixels, 3, 3, &size);
  uint8_t *compressedImage = Compress(pixels, 5, 5, &size);
  if (!compressedImage)
  {
    printf("Unable to compress image\n");
    return -1;
  }

  free(compressedImage);

  printf("\n");

  return 0;
}


