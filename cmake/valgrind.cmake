find_program(VALGRIND_BIN valgrind)

if (NOT VALGRIND_BIN)
    message(STATUS "valgrind not found")
    return()
endif()

set(MEMORYCHECK_COMMAND
    "${VALGRIND_BIN}"
    CACHE FILEPATH "valgrind executable"
)

set(MEMORYCHECK_COMMAND_OPTIONS
    "--leak-check=full"
    "--show-leak-kinds=definite,indirect"
    "--track-origins=yes"
    "--error-exitcode=1"
    CACHE STRING "valgrind options"
)

# targets only cpu-bound tests instead of graphical tests
add_custom_target(valgrind
    COMMAND ${CMAKE_CTEST_COMMAND}
        --test-dir "${CMAKE_BINARY_DIR}"
        -T memcheck
        --output-on-failure
    DEPENDS 
        cmake_build_test
    USES_TERMINAL
)