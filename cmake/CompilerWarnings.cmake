option(GBCEMU_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

function(set_project_warnings target)
    set(GCC_CLANG_WARNINGS
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
        -Wsign-conversion
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2
    )
    set(MSVC_WARNINGS /W4 /permissive-)

    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        if(GBCEMU_WARNINGS_AS_ERRORS)
            list(APPEND GCC_CLANG_WARNINGS -Werror)
        endif()
        target_compile_options(${target} INTERFACE ${GCC_CLANG_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        if(GBCEMU_WARNINGS_AS_ERRORS)
            list(APPEND MSVC_WARNINGS /WX)
        endif()
        target_compile_options(${target} INTERFACE ${MSVC_WARNINGS})
    else()
        message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
    endif()
endfunction()
