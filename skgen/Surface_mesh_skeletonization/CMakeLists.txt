# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


cmake_minimum_required(VERSION 3.1...3.15)
project( Surface_mesh_skeletonization_Examples )

find_package(CGAL)

if ( CGAL_FOUND )

	find_package(Eigen3)

	if(EIGEN3_FOUND)
		include( ${EIGEN3_USE_FILE} )

		add_subdirectory(detail_MCF_Skeleton)
		add_subdirectory(direct_MCF_Skeleton)
		file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	else()
		message(STATUS "These programs require the Eigen library (3.2 or greater), and will not be compiled.")
	endif()
else()
	message(STATUS "This program requires the CGAL library, and will not be compiled.")
endif()

# COPY exec to current path

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD        # Adds a post-build event to MyTest
#	COMMAND ${CMAKE_COMMAND} -E copy_if_different           # which executes "cmake - E copy_if_different..."
#		"${CMAKE_SOURCE_DIR}/${PATH_TO_EXTERNAL_LIBS}/pmp.dll"                  # <--this is in-file
#		$<TARGET_FILE_DIR:${PROJECT_NAME}>)               