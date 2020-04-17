add_executable(test_app
    bitstream_test.c
)

target_link_libraries(test_app
    bit_stream
    Unity
)

add_test(bitstream_test test_app)
