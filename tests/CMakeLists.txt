include(GoogleTest)

# cmake Build System Test
add_executable(cmake_build_test test_build.cpp)
target_link_libraries(cmake_build_test PRIVATE showcasegl gtest_main)
gtest_discover_tests(cmake_build_test)

# app Test
add_executable(showcasegl_application_test test_application.cpp)
target_link_libraries(showcasegl_application_test PRIVATE showcasegl gtest_main)
gtest_discover_tests(showcasegl_application_test)

# shader Test
add_executable(showcasegl_shader_test test_shader.cpp)
target_link_libraries(showcasegl_shader_test PRIVATE showcasegl gtest_main)
gtest_discover_tests(showcasegl_shader_test)