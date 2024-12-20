cmake_minimum_required(VERSION 3.14)

# задаем используемый стандарт С++
set(CMAKE_CXX_STANDARD 11)

# TODO: переименовать проект
project(tuple_printer)

set(exe_name ${PROJECT_NAME})

# описываем основную библиотеку, т.е. библиотеку, содержащую все cpp-файлы, кроме main.cpp
# TODO: отредактировать список cpp-файлов
# add_library(corelib OBJECT Ground.cpp Shelter.cpp Man.cpp Bullet.cpp Enemy.cpp Intro.cpp GamePlay.cpp Ending.cpp)

# описываем исполняемый файл основной программы: это main.cpp + основная библиотека
add_executable(${exe_name} main.cpp)
# target_link_libraries(${exe_name} corelib)
