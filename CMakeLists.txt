cmake_minimum_required(VERSION 4.0)
project(carricato_todolist)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(test)

set(APP_SOURCE_FILES
        src/Date.cpp
        inc/Date.h
        inc/TimeOfDay.h
        src/TimeOfDay.cpp
        src/DateTime.cpp
        inc/DateTime.h
        src/Location.cpp
        inc/Location.h
        src/Task.cpp
        inc/Task.h
        src/ToDoList.cpp
        inc/ToDoList.h
)

add_library(carricato_todolist_lib STATIC ${APP_SOURCE_FILES})

target_include_directories(carricato_todolist_lib PUBLIC
        ${CMAKE_SOURCE_DIR}/inc
)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE carricato_todolist_lib)