#!/bin/bash
# written by scoward

echo ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
echo // written by scoward
echo ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BUILD_TYPE=Debug
HERMES_CMAKE_CONFIGURE_COMMAND="cmake -S . -B hermes-build -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_INSTALL_PREFIX=$PWD/external/install" 
HERMES_CMAKE_BUILD_COMMAND="cmake --build hermes-build -j 24"
HERMES_CMAKE_INSTALL_COMMAND="cmake --install hermes-build "

# setup the location for cloning external libs
mkdir -p external/sources
mkdir -p external/install

# start cloning things
pushd external/sources

git clone --recursive --depth 1 https://github.com/pocoproject/poco.git
git clone --recursive --depth 1 https://github.com/zeromq/libzmq.git
git clone --recursive --depth 1 https://github.com/google/flatbuffers.git

# build the libs
pushd poco

$HERMES_CMAKE_CONFIGURE_COMMAND
$HERMES_CMAKE_BUILD_COMMAND
$HERMES_CMAKE_INSTALL_COMMAND

popd

pushd libzmq

$HERMES_CMAKE_CONFIGURE_COMMAND
$HERMES_CMAKE_BUILD_COMMAND
$HERMES_CMAKE_INSTALL_COMMAND

popd

pushd flatbuffers

$HERMES_CMAKE_CONFIGURE_COMMAND
$HERMES_CMAKE_BUILD_COMMAND
$HERMES_CMAKE_INSTALL_COMMAND

popd

echo Done setting up
echo 
echo ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
echo // written by scoward
echo ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

# written by scoward