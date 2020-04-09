// Copyright (C) 2020  Diogo Justen. All rights reserved.

#ifndef BIT_STREAM_H__
#define BIT_STREAM_H__

#include <stdint.h>
#include <stdbool.h>

bool BitStreamConvert(const uint8_t pixel, int numOccurrences,
                      uint32_t *bitStream, uint8_t *bitsUsed);
void BitStreamPrint(uint32_t bitStream, uint8_t bitsUsed);

#endif //BIT_STREAM_H__
