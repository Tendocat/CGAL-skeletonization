include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/")

file(GLOB_RECURSE SOURCES "src/*.cpp")


add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${LINK_EXTERNAL_LIBRARIES})

if(MSVC)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different           # which executes "cmake - E copy_if_different..."
            "${CMAKE_SOURCE_DIR}/${PATH_TO_EXTERNAL_LIBS}/pmp.dll"                  # <--this is in-file
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)                 # <--this is out-file path
endif()