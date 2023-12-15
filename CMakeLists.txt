# written by scoward
cmake_minimum_required(VERSION 3.20.0)
project(hermes)

# setup some variables to use for finding packages
set(EXTERNAL_LIB_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/external/install")
set(EXTERNAL_INCLUDE_DIR "${EXTERNAL_LIB_PREFIX}/include")
set(EXTERNAL_LIB_DIR "${EXTERNAL_LIB_PREFIX}/lib")

# setup all the prefix dirs that we are going to want to use with hermes
set(HERMES_PREFIXES ${EXTERNAL_LIB_DIR}/cmake/Poco ${EXTERNAL_LIB_DIR}/cmake/flatbuffers ${EXTERNAL_LIB_DIR}/cmake/ZeroMQ)
set(CMAKE_PREFIX_PATH ${HERMES_PREFIXES})

# need to find these poco packages separately because im having issues just finding poco
find_package(PocoJSON REQUIRED)
find_package(PocoXML REQUIRED)

# find poco
find_package(Poco REQUIRED COMPONENTS Net Foundation Util XML JSON Zip)
# find zmq
find_package(ZeroMQ REQUIRED)
# find flatbuffers
find_package(flatbuffers REQUIRED)



include_directories(include)

set(SOURCES src/hermes.cpp)

add_executable(hermes ${SOURCES})
target_link_libraries(hermes PUBLIC Poco::Foundation Poco::Net zmq flatbuffers)

# written by scoward