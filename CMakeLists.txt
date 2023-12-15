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
find_package(flatbuffers REQUIRED)

#find cppzmq
find_package(cppzmq)

add_executable(${PROJECT_NAME})

cmake_print_variables(PROJECT_NAME)

target_sources(${PROJECT_NAME}
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hermes.cpp
)

target_link_libraries(hermes PUBLIC Poco::Foundation Poco::Net cppzmq libzmq-static flatbuffers::flatbuffers)

target_include_directories(${PROJECT_NAME}
                           PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")

# written by scoward