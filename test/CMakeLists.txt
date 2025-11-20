cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(./lib/googletest)

set(gtest_SOURCE_DIR "./lib/googletest")
include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
)

set(TEST_SOURCE_FILES
        DateTest.cpp
        TimeOfDayTest.cpp
        DateTimeTest.cpp
        LocationTest.cpp
        TaskTest.cpp
        ToDoListTest.cpp
        mainTest.cpp
)

add_executable(mainTest ${TEST_SOURCE_FILES})

target_include_directories(mainTest PRIVATE
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
)
target_link_libraries(mainTest
        gtest
        gtest_main
        carricato_todolist_lib
)

include(GoogleTest)
gtest_discover_tests(mainTest)