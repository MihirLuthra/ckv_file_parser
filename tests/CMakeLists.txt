set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

file(COPY sample_ckv_files DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(test_ckv test_ckv.cpp)

target_link_libraries(test_ckv PRIVATE ckv_file_parser)
