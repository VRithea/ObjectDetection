cmake_minimum_required(VERSION 3.10)

project(ObjectDetection VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(ObjectDetection src/Main.cpp)

target_link_libraries( ObjectDetection ${OpenCV_LIBS})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


#set(OpenCV_DIR D:/Other/Files/opencv/build)
#find_package(OpenCV REQUIRED)
 
#include_directories("D:/Other/Files/opencv/build/include")
#include_directories(${OpenCV_INCLUDE_DIRS})
#message(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")

#add_executable(${PROJECT_NAME} src/Main.cpp)

#target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
