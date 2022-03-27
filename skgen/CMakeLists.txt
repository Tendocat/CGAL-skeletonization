include_directories("${CMAKE_CURRENT_SOURCE_DIR}/inc/")

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${EXECUTABLE_NAME} ${LINK_EXTERNAL_LIBRARIES})
