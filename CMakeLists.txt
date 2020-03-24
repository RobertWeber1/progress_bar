cmake_minimum_required(VERSION 2.8)

project("progress_bar" CXX)


################################################################################
# Version-file #
################

execute_process(
	COMMAND git describe --tags
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	OUTPUT_STRIP_TRAILING_WHITESPACE
	OUTPUT_VARIABLE GIT_TAG
)

execute_process(
	COMMAND git rev-parse HEAD
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	OUTPUT_STRIP_TRAILING_WHITESPACE
	OUTPUT_VARIABLE COMMIT_HASH
)

configure_file (
	"${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME}/version.h.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}/version.h"
)


################################################################################
# Library #
###########

add_library( ${PROJECT_NAME} INTERFACE )

target_include_directories( ${PROJECT_NAME}
	INTERFACE src/
	INTERFACE ${PROJECT_BINARY_DIR}/
)


################################################################################
# Unit test #
#############

add_executable( ${PROJECT_NAME}-test EXCLUDE_FROM_ALL
	test/catch.cc
	test/version.cc
	test/options.cc
)

target_include_directories( ${PROJECT_NAME}-test
	PRIVATE test/
)

target_link_libraries( ${PROJECT_NAME}-test
	PRIVATE asan
	PRIVATE ubsan
	PRIVATE ${PROJECT_NAME}
	PRIVATE gcov
)

target_compile_options( ${PROJECT_NAME}-test
	PRIVATE -std=c++1z

	PRIVATE -fsanitize=address
	PRIVATE -fsanitize=undefined

	PRIVATE -fprofile-arcs
	PRIVATE -ftest-coverage

	PRIVATE -g
	PRIVATE -O0
	PRIVATE -Wall
	PRIVATE -Wunused-variable
	PRIVATE -Wunused-parameter
	PRIVATE -Wunused-function
	PRIVATE -Wunused
	PRIVATE -Wno-system-headers
	PRIVATE -Wno-deprecated
	PRIVATE -Wwrite-strings
)

add_custom_target(coverage-${PROJECT_NAME}-test
	COMMAND lcov --capture --directory . --output-file coverage.info
	COMMAND lcov --remove coverage.info '/usr/*' './test/*' '7/*' --output-file coverage.info
	COMMAND genhtml coverage.info --output-directory coverage-report
)