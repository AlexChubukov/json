cmake_minimum_required(VERSION 2.8) # Проверка версии CMake

project(json_parse) # Название проекта
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build	 tests" OFF)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall") # Устанавливаем неободимые флаги компиляции

add_library(my_library STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/son.cpp) # Создание статической библиотеки с именем my_library
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include) # показываем, где можно искать заголовочные файлы 
add_executable(json ${CMAKE_CURRENT_SOURCE_DIR}/sources/json.cpp) # Создает исполняемый файл с именем json
target_link_libraries(json my_library)# Подключаем библиотеки к исполняемому файлу



if(BUILD_TESTS)
enable_testing()
file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
target_link_libraries(check ${PROJECT_NAME} ${DEPENDS_LIBRARIES})
add_test(NAME check COMMAND check "-s" "-r" "compact" "--use-colour" "yes") 
endif()