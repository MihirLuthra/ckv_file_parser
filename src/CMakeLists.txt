configure_file(
	ckv_config.hpp.in
	${CMAKE_CURRENT_BINARY_DIR}/ckv_config.hpp
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_library(
	ckv_file_parser
	SHARED ckv.cpp
)

target_include_directories(
	ckv_file_parser
	PUBLIC

	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>

	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

install(
	TARGETS ckv_file_parser
	DESTINATION lib
	EXPORT ckv_file_parser_targets
)

install(
	FILES ckv.hpp ${CMAKE_CURRENT_BINARY_DIR}/ckv_config.hpp
	DESTINATION include
)

install(
	EXPORT ckv_file_parser_targets
	FILE ckv_file_parser_targets.cmake
	DESTINATION cmake
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/ckv_file_parser-config.cmake"

	INSTALL_DESTINATION cmake

	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/ckv_file_parser-config-version.cmake"
	VERSION "${ckv_file_parser_VERSION_MAJOR}.${ckv_file_parser_VERSION_MINOR}.${ckv_file_parser_VERSION_PATCH}"
	COMPATIBILITY AnyNewerVersion
)

install(
	FILES
	"${CMAKE_CURRENT_BINARY_DIR}/ckv_file_parser-config.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/ckv_file_parser-config-version.cmake"
	
	DESTINATION cmake
)

export(
	EXPORT ckv_file_parser_targets
	FILE ckv_file_parser_targets.cmake
)
