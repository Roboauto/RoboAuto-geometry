find_package(Threads REQUIRED)
include(ExternalProject)

ExternalProject_Add(
		gtest
		URL https://github.com/google/googletest/archive/master.zip
		PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
		# Disable install step
		INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest source_dir binary_dir)

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

set_target_properties(libgtest PROPERTIES
		"IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
		"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
		)

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock prope rties
set_target_properties(libgmock PROPERTIES
		"IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
		"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
		)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
		"${source_dir}/googlemock/include")

find_package(Qt5Core)
find_package(Qt5Charts)

add_executable(RoboAuto_geometry_tests testMain.cpp PolygonTest.h LineTest.h VectorTest.h CircleTest.h)

target_link_libraries(RoboAuto_geometry_tests libgtest libgmock)

target_link_libraries(RoboAuto_geometry_tests Qt5::Widgets Qt5::Charts)