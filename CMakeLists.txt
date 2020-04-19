# Copyright (C) 2020  Diogo Justen. All rights reserved.

cmake_minimum_required(VERSION 3.0)
project(compress_service)

#################################### Flags ####################################

add_compile_options (-Wall -Werror -O3)

################################# Source files #################################

add_subdirectory(external)
add_subdirectory(src)

enable_testing()
add_subdirectory(test)
