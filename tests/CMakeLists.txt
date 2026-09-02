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

# test to ensure application works

add_executable(showcasegl_application_test
    application_test.cpp
)
target_link_libraries(showcasegl_application_test
    PRIVATE showcasegl
)
add_test(
    NAME showcasegl_application_test
    COMMAND showcasegl_application_test
)