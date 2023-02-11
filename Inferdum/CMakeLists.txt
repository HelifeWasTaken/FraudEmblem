project(kat)
cmake_minimum_required(VERSION 3.15)
include(FetchContent)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(_WIN32_WINT=0x0601)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -fconcepts")
endif()

set(LUA_BUILD_COMPILER OFF CACHE INTERNAL "")
set(LUA_BUILD_INTERPRETER OFF CACHE INTERNAL "")

include(FetchContent)

FetchContent_Declare(
    lua
    GIT_REPOSITORY "https://github.com/HelifeWasTaken/lua"
)

FetchContent_MakeAvailable(lua)

FetchContent_Declare(
	sfml
	GIT_REPOSITORY "https://github.com/SFML/SFML"
    GIT_TAG 2.5.x
)

FetchContent_MakeAvailable(sfml)

include_directories(${lua_SOURCE_DIR}/src)
include_directories(${sfml_SOURCE_DIR}/include)

file(
    GLOB_RECURSE SRC

    src/*.c src/*.cpp

    include/*.h include/*.hpp

    src/imgui/*.c src/imgui/*.cpp
    src/imgui/*.h src/imgui/*.hpp
)

include_directories(include src/imgui)

add_library(${PROJECT_NAME} STATIC ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

#add_executable(${PROJECT_NAME}_test App/App.cpp)

# target_link_libraries(
#         ${PROJECT_NAME}_test
#         sfml-graphics sfml-window sfml-system
#         lua::lua ${PROJECT_NAME}
# )

if (UNIX)
    target_link_libraries(${PROJECT_NAME} pthread GL dl)
else()
    target_link_libraries(${PROJECT_NAME} opengl32 m)
endif()
