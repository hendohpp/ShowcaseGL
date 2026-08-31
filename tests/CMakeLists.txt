# test to ensure build system works
add_executable(cmake_build_test
    build_test.cpp
)
target_link_libraries(cmake_build_test
    PRIVATE showcasegl
)
add_test(
    NAME cmake_build_test
    COMMAND cmake_build_test
)