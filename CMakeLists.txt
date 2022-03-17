cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(sqcheck)


include_directories("externals/pmp-library/src/")
include_directories("externals/pmp-library/external/eigen/")
include_directories("externals/pmp-library/external/glew/include/")
include_directories("externals/pmp-library/external/glfw/include/")
include_directories("externals/pmp-library/external/imgui/")

include_directories(include)

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

set(TARGET sqcheck)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${TARGET})
