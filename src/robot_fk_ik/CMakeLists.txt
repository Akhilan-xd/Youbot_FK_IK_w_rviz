cmake_minimum_required(VERSION 2.8.3)
project(youbot_kdl)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system)
find_package(Eigen3 REQUIRED)
find_package(orocos_kdl)
find_package(kdl_parser)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  /usr/local/include
  /usr/include/eigen3
  ${Eigen_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIR}
  ${orocos_kdl_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(youbot_kdl
   src/KDLInterface.cpp
 )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(youbot_kdl ${${PROJECT_NAME}_EXPORTED_TARGETS} )

## Declare a C++ executable
add_executable(youbot_kdl_node src/youbot_kdl.cpp src/KDLInterface.cpp)

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(youbot_kdl_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(youbot_kdl_node
  orocos-kdl
  ${orocos-kdl_LIBRARIES}
  ${kdl_parser_LIBRARIES}
)