find_package(Catch2 3 CONFIG REQUIRED)

add_executable(gbcemu_tests test_placeholder.cpp)
target_link_libraries(gbcemu_tests
    PRIVATE
        gbcemu_warnings
        gbcemu_options
        Catch2::Catch2WithMain
)

add_test(NAME gbcemu_tests COMMAND gbcemu_tests)
