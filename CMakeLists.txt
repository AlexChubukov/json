cmake_minimum_required (VERSION 2.8)

include(gtest.cmake)
include_directories(SYSTEM
    ./
)

# if(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fsanitize=address -O1 -Wall -Wextra -Wno-unused-command-line-argument -Wshadow -Wnon-virtual-dtor -pedantic")
# endif(CMAKE_COMPILER_IS_GNUCXX)

# enum your files
add_library(my_library STATIC json.hpp) # Создание статической библиотеки с именем my_library
add_executable(json test.cpp) # Создает исполняемый файл с именем json
target_link_libraries(json my_library)# Подключаем библиотеки к исполняемому файлу

find_package (Threads)
target_link_libraries(executable -fsanitize=address gtest ${CMAKE_THREAD_LIBS_INIT})
