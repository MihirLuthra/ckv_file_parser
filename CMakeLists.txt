cmake_minimum_required(VERSION 3.10)
project(ckv_file_parser VERSION 1.0.0)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(doxygen)

enable_testing()
add_test(
	NAME ckv_file_parser_test
	COMMAND test_ckv
	WORKING_DIRECTORY tests
)
