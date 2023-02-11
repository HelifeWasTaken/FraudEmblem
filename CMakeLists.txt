project(fraudEmblem)
cmake_minimum_required(VERSION 3.15)

add_subdirectory(Inferdum)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

file(
    GLOB SRC

    src/*.cpp
    src/component/*.cpp
    src/state/*.cpp
    main.cpp

    include/*.hpp
    include/component/*.hpp
    include/state/*.hpp

    Inferdum/include/Kat/*.h
    Inferdum/include/Kat/entt/entt.hpp
)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC kat)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC Inferdum/include/Kat)

target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-window sfml-system sfml-audio)
