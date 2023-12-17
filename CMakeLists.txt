# written by scoward
include(CMakePrintHelpers)

cmake_minimum_required(VERSION 3.20.0)
project(hermes)

# find poco
find_package(Poco REQUIRED COMPONENTS Net Foundation Util XML JSON Zip)

# find zmq
if(NOT TARGET libzmq-static)
  find_package(ZeroMQ REQUIRED)
endif()

# find flatbuffers
if(NOT TARGET flatbuffers)
  find_package(flatbuffers REQUIRED)
endif()

#find cppzmq
if(NOT TARGET cppzmq)
  find_package(cppzmq)
endif()

add_executable(${PROJECT_NAME})

cmake_print_variables(PROJECT_NAME)

target_sources(${PROJECT_NAME}
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hermes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/publisher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/subscriber.cpp
)

target_link_libraries(hermes PUBLIC Poco::Foundation Poco::Util Poco::Net cppzmq libzmq-static flatbuffers::flatbuffers)

target_include_directories(${PROJECT_NAME}
                           PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")

# written by scoward