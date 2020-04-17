add_executable(bitstream_test
    bitstream_test.c
)

target_link_libraries(bitstream_test
    bit_stream
    Unity
)

#------

add_executable(compress_test
    compress_test.c
)

target_link_libraries(compress_test
    compress
    Unity
)

#------

add_test(bitstream_suite_test bitstream_test)
add_test(compress_suite_test compress_test)
