cmake_minimum_required(VERSION 3.12) # 3.12 for C++20


project(SKGen)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif()

# Check compiler and add corresponding flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_USE_MATH_DEFINES -DNOMINMAX -D_CRT_SECURE_NO_WARNINGS")
    add_compile_options(/wd4267) # conversion from size_t
    add_compile_options(/wd4244) # conversion from double to float
    add_compile_options(/wd4305) # truncation from double to float
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-Wall -O3 -DGLEW_STATIC -pthread")
else()
    message(FATAL_ERROR "Compiler not supported for this project, however you can modify the CMakeLists.txt file to fit your needs.")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(PATH_TO_EXTERNAL_LIBS "./externals/pmp-library/build/Debug")
else()
    set(PATH_TO_EXTERNAL_LIBS "./externals/pmp-library/build/")
endif()

# Make sure OpenGL is accessible
find_package(OpenGL REQUIRED)
if(NOT OpenGL_FOUND)
    message(FATAL_ERROR "OpenGL could not be found")
endif()

# And, on unix/linux systems make sure X11 is accessible
if(UNIX)
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
endif()

message(STATUS "Looking into ${PATH_TO_EXTERNAL_LIBS}")

# Make sure glew is accessible
find_library(LIB_GLEW
        NAMES glew
        PATHS ${PATH_TO_EXTERNAL_LIBS})
if(NOT LIB_GLEW)
    message(FATAL_ERROR "Glew library could not be found")
endif()

# Make sure glw3 is accessible
find_library(LIB_GLFW
        NAMES glfw3
        PATHS ${PATH_TO_EXTERNAL_LIBS})
if(NOT LIB_GLFW)
    message(FATAL_ERROR "Glfw library could not be found")
endif()

# Make sure pmp is accessible
find_library(LIB_PMP
        NAMES pmp
        PATHS ${PATH_TO_EXTERNAL_LIBS})
if(NOT LIB_PMP)
    message(FATAL_ERROR "pmp library could not be found")
endif()

# Make sure pmp-vis (visualisation part of pmp) is accessible
find_library(LIB_PMP_VIS
        NAMES pmp_vis
        PATHS ${PATH_TO_EXTERNAL_LIBS})
if(NOT LIB_PMP_VIS)
    message(FATAL_ERROR "pmp_vis library could not be found")
endif()

# Make sure imgui is accessible
find_library(LIB_IMGUI
        NAMES imgui
        PATHS ${PATH_TO_EXTERNAL_LIBS})
if(NOT LIB_IMGUI)
    message(FATAL_ERROR "imgui library could not be found")
endif()

# Make sure stb-image is accessible
find_library(LIB_STB_IMAGE
        NAMES stb_image
        PATHS ${PATH_TO_EXTERNAL_LIBS})
if(NOT LIB_STB_IMAGE)
    message(FATAL_ERROR "stb_image library could not be found")
endif()

# List the external libraries depending on the OS (e.g. opengl32 required on windows, but is called GL on *nix systems)
if(WIN32)
    set(LINK_EXTERNAL_LIBRARIES ${LIB_PMP_VIS} ${LIB_GLFW} ${LIB_GLEW} opengl32  ${LIB_PMP} ${LIB_IMGUI} ${LIB_STB_IMAGE})
else()
    set(LINK_EXTERNAL_LIBRARIES ${LIB_PMP_VIS} GL ${LIB_GLEW} ${LIB_GLFW} ${LIB_PMP} ${LIB_IMGUI} ${LIB_STB_IMAGE} ${CMAKE_DL_LIBS} ${X11_LIBRARIES})
endif()

include_directories("externals/pmp-library/src/")
include_directories("externals/pmp-library/external/eigen/")
include_directories("externals/pmp-library/external/glew/include/")
include_directories("externals/pmp-library/external/glfw/include/")
include_directories("externals/pmp-library/external/imgui/")

add_subdirectory(skgen)
add_subdirectory(skgen/Surface_mesh_skeletonization)

add_custom_target(BuildAll)
add_dependencies(BuildAll SKGen direct_skeletonizer detailed_skeletonizer)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif()
