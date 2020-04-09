# Copyright (C) 2020  Diogo Justen. All rights reserved.

cmake_minimum_required(VERSION 3.0)
project(compress_service)

#################################### Flags ####################################

add_compile_options (-Wall -Werror -O3)

################################# Source files #################################

add_executable(compress_service
  ./src/bit_stream.c
  ./src/compress.c
  ./src/filter.c
  ./src/main.c
)
