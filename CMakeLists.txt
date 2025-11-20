cmake_minimum_required(VERSION 4.0)
project(carricato_todolist)

set(CMAKE_CXX_STANDARD 20)

add_executable(carricato_todolist main.cpp
        inc/Task.h
        inc/ToDoList.h
        src/Task.cpp
        src/ToDoList.cpp
        inc/Date.h
        inc/TimeOfDay.h
        src/Date.cpp
        src/TimeOfDay.cpp
        inc/DateTime.h
        src/DateTime.cpp
        inc/Location.h
        src/Location.cpp

)
