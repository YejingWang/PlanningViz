#
# Created By: YejingWang 2021/08/11
#

cmake_minimum_required(VERSION  3.8.0)

IF (UNIX)
	set(CMAKE_C_COMPILER "/usr/bin/clang")
	set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -I/usr/include/libcxxabi")
	set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
ENDIF()

add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)

# top project
project (PlanningViz VERSION 1.0.0 LANGUAGES C CXX)

set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_AUTOMOC TRUE)

IF (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0501)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
ENDIF()

add_definitions(-DNOMINMAX)
add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

# global settings
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

set(SRC_ROOT "${CMAKE_CURRENT_LIST_DIR}/../Source")
file(GLOB_RECURSE srcs "${SRC_ROOT}/*.hpp" "${SRC_ROOT}/*.cpp")
source_group(TREE "${SRC_ROOT}" FILES ${srcs})
	
set(QT_ROOT "${CMAKE_CURRENT_LIST_DIR}/../3rdparty/Qt/qt-5.13.0")
include_directories("${QT_ROOT}/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/../3rdparty/")

add_executable(${PROJECT_NAME} ${srcs})

IF(MSVC)
	target_link_libraries(PlanningViz debug "${QT_ROOT}/lib/Qt5Cored.lib")
    target_link_libraries(PlanningViz debug "${QT_ROOT}/lib/Qt5Guid.lib")
    target_link_libraries(PlanningViz debug "${QT_ROOT}/lib/Qt5Widgetsd.lib")
    target_link_libraries(PlanningViz optimized "${QT_ROOT}/lib/Qt5Core.lib")
    target_link_libraries(PlanningViz optimized "${QT_ROOT}/lib/Qt5Gui.lib")
    target_link_libraries(PlanningViz optimized "${QT_ROOT}/lib/Qt5Widgets.lib")
			
	add_custom_command(TARGET PlanningViz 
				PRE_BUILD
				COMMAND echo "executing prebuild command"
				COMMAND ${CMAKE_COMMAND} -E copy_directory ${QT_ROOT}/bin ${CMAKE_BINARY_DIR}/Debug
				COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Debug/platforms
				COMMAND ${CMAKE_COMMAND} -E copy_directory ${QT_ROOT}/bin/platforms ${CMAKE_BINARY_DIR}/Debug/platforms
				COMMAND ${CMAKE_COMMAND} -E copy_directory ${QT_ROOT}/bin ${CMAKE_BINARY_DIR}/Release
				COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Release/platforms
				COMMAND ${CMAKE_COMMAND} -E copy_directory ${QT_ROOT}/bin/platforms ${CMAKE_BINARY_DIR}/Release/platforms
				)
ENDIF()