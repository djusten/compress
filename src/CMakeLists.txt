# Copyright (C) 2020  Diogo Justen. All rights reserved.

add_library(bit_stream STATIC
    ./bit_stream.c
)
target_include_directories(bit_stream PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

#---------------#

add_library(compress STATIC
    ./compress.c
)
target_include_directories(compress PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(compress
    bit_stream
)

#---------------#

add_executable(compress_service
  ./main.c
)

target_link_libraries(compress_service
    compress
)
