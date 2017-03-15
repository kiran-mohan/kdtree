cmake_minimum_required(VERSION 2.8.3)
project(kdtree)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter")
endif()

find_package(catkin REQUIRED)

include_directories(include
  ${catkin_INCLUDE_DIRS}
)

add_library(kdtree src/kdtree.cpp)
target_link_libraries(kdtree ${catkin_LIBRARIES})

add_executable(kdtree_node src/kdtree_node.cpp)
target_link_libraries(kdtree_node ${catkin_LIBRARIES} kdtree)

if(false)
if (CATKIN_ENABLE_TESTING)
  add_subdirectory(test)
endif()
endif()
