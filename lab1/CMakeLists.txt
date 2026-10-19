set(exe_name lab1)
set(test_name lab1_tests)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_library(lab1_core OBJECT BigInt.cpp)

add_executable(${exe_name} main.cpp)
target_link_libraries(${exe_name} lab1_core)

add_executable(${test_name} BigInt_test.cpp)
target_link_libraries(${test_name} lab1_core gtest_main)

include(GoogleTest)
gtest_discover_tests(${test_name})