cmake_minimum_required(VERSION 3.14)
project(Game LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include(FetchContent)
# FetchContent_Declare(raylib
#     GIT_REPOSITORY https://github.com/raysan5/raylib.git
#     GIT_TAG 5.0
# )
# FetchContent_MakeAvailable(raylib)

set(RAYLIB_PATH "C:/raylib") 

include_directories(${RAYLIB_PATH}/include) # Include the directory with raylib.h
link_directories(${RAYLIB_PATH}/lib)

include_directories(include)

file(GLOB_RECURSE SOURCES "source/*.cpp")

add_executable(main ${SOURCES})

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/resource
            ${CMAKE_BINARY_DIR}/resource   
)

target_link_libraries(main raylib -lopengl32 -lgdi32 -lwinmm)