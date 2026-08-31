option(ENABLE_CLANG_TIDY "enable clang-tidy targets" OFF)

set(CLANG_TIDY_BIN "clang-tidy"
    CACHE STRING "clang-tidy binary"
)

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE
        NAMES ${CLANG_TIDY_BIN} clang-tidy
    )

    if(NOT CLANG_TIDY_EXE)
        message(FATAL_ERROR
            "clang-tidy not found"
        )
    endif()

    file(GLOB_RECURSE TIDY_FILES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    )

    set(CLANG_TIDY_EXTRA_ARGS)

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy")
        list(APPEND CLANG_TIDY_EXTRA_ARGS
            "--config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy"
        )
    endif()

    add_custom_target(tidy
        COMMAND "${CLANG_TIDY_EXE}"
            ${CLANG_TIDY_EXTRA_ARGS}
            -p "${CMAKE_BINARY_DIR}"
            --quiet
            ${TIDY_FILES}
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        VERBATIM
    )
endif()
