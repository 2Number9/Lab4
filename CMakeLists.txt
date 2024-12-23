cmake_minimum_required(VERSION 3.14)

# задаем используемый стандарт С++
set(CMAKE_CXX_STANDARD 17)

# TODO: переименовать проект
project(Csv_Parser)

set(exe_name ${PROJECT_NAME})

# описываем исполняемый файл основной программы: это main.cpp + основная библиотека
add_executable(${exe_name} main.cpp)