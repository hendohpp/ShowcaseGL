option(ENABLE_CLANG_FORMAT "enable clang-format targets" OFF)

set(CLANG_FORMAT_BIN "clang-format"
    CACHE STRING "clang-format binary"
)

if(ENABLE_CLANG_FORMAT)
    find_program(CLANG_FORMAT_EXE
        NAMES ${CLANG_FORMAT_BIN} clang-format
    )

    if(NOT CLANG_FORMAT_EXE)
        message(FATAL_ERROR
            "clang-format not found"
        )
    endif()

    file(GLOB_RECURSE FORMAT_FILES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.hpp"
    )

    add_custom_target(format
        COMMAND "${CLANG_FORMAT_EXE}"
            -i
            -style=file
            ${FORMAT_FILES}
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        VERBATIM
    )

    add_custom_target(format-check
        COMMAND "${CLANG_FORMAT_EXE}"
            --dry-run
            --Werror
            -style=file
            ${FORMAT_FILES}
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        VERBATIM
    )
endif()
