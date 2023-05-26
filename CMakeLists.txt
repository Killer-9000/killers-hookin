cmake_minimum_required ( VERSION 3.20 )

# Set the project name
project ( killerhookin )

# Specify the C++ standard
set ( CMAKE_CXX_STANDARD 23 )
set ( CMAKE_CXX_STANDARD_REQUIRED True )
set ( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

add_subdirectory("${CMAKE_SOURCE_DIR}/src/KillerHookin/Features/")

file(GLOB_RECURSE sources "${CMAKE_SOURCE_DIR}/src/KillerHookin/*")

file(GLOB imgui_sources
	${CMAKE_SOURCE_DIR}/src/imgui/*.h
	${CMAKE_SOURCE_DIR}/src/imgui/*.cpp
	${CMAKE_SOURCE_DIR}/src/imgui/backends/imgui_impl_win32.h
	${CMAKE_SOURCE_DIR}/src/imgui/backends/imgui_impl_win32.cpp
	${CMAKE_SOURCE_DIR}/src/imgui/backends/imgui_impl_dx9.h
	${CMAKE_SOURCE_DIR}/src/imgui/backends/imgui_impl_dx9.cpp
	${CMAKE_SOURCE_DIR}/src/imgui/backends/imgui_impl_opengl3.h
	${CMAKE_SOURCE_DIR}/src/imgui/backends/imgui_impl_opengl3.cpp
)

list(APPEND sources ${imgui_sources})

include_directories (
	${CMAKE_SOURCE_DIR}/src
	${CMAKE_SOURCE_DIR}/src/KillerHookin
	${CMAKE_SOURCE_DIR}/src/imgui
)

# Finally add our executable
add_library ( killerhookin SHARED
	${sources}
)

add_subdirectory(./src/minhook)

target_link_libraries(killerhookin
	PUBLIC
		minhook
)