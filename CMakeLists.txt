cmake_minimum_required (VERSION 2.8)

include(gtest.cmake)
include_directories(SYSTEM
    ./
)

# if(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fsanitize=address -O1 -Wall -Wextra -Wno-unused-command-line-argument -Wshadow -Wnon-virtual-dtor -pedantic")
# endif(CMAKE_COMPILER_IS_GNUCXX)

# enum your files
add_library(my_library STATIC json.cpp json.hpp) # Создание статической библиотеки с именем my_library
add_executable(executable test.cpp) # Создает исполняемый файл с именем executable
add_executable(json json.cpp )# Создает исполняемый файл с именем json

find_package (Threads)
target_link_libraries(executable -fsanitize=address gtest ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(executable my_library)# Подключаем библиотеки к исполняемому файлу
target_link_libraries(json my_library)# Подключаем библиотеки к исполняемому файлу
