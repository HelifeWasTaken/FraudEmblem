project(fraudEmblem)
cmake_minimum_required(VERSION 3.15)

add_subdirectory(Inferdum)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

file(
    GLOB SRC

    src/*.cpp
    main.cpp
)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC kat)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC Inferdum/include/Kat)
