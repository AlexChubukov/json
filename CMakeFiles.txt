cmake_minimum_required(VERSION 2.8) # Проверка версии CMake

project(json_parse) # Название проекта
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall") # Устанавливаем необъодиыме флаги компиляции
set(JSON_EXE json.cpp) # Установка переменной со списком исходников для исполняемого файла

# include_directories("include/") # показываем, где можно искать заголовочные файлы 

add_library(my_library STATIC sources/son.cpp include/Json.h) # Создание статической библиотеки с именем my_library

add_executable(json sources/json.cpp) # Создает исполняемый файл с именем json

target_link_libraries(json my_library)# Подключаем библиотеки к исполняемому файлу