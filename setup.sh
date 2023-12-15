#!/bin/bash
# written by scoward

echo ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
echo // written by scoward
echo ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BUILD_TYPE=Debug
HERMES_CMAKE_CONFIGURE_COMMAND="cmake .. -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=$BUILD_TYPE"
HERMES_CMAKE_BUILD_COMMAND="cmake --build . -j 24"
HERMES_CMAKE_INSTALL_COMMAND="cmake --install . --prefix "../../../install""

# setup the location for cloning external libs
mkdir external
pushd external

# create a location to clone things to
mkdir sources

# create a location to install the libs to so we dont have to keep building them after initial setup
mkdir install

# start cloning things
pushd sources

git clone --recursive --depth 1 https://github.com/pocoproject/poco.git

git clone --recursive --depth 1 https://github.com/zeromq/libzmq.git

git clone --recursive --depth 1 https://github.com/google/flatbuffers.git

# build the libs
pushd poco
mkdir hermes-build
pushd hermes-build

$HERMES_CMAKE_CONFIGURE_COMMAND
$HERMES_CMAKE_BUILD_COMMAND
$HERMES_CMAKE_INSTALL_COMMAND

popd
popd

pushd libzmq
mkdir hermes-build
pushd hermes-build

$HERMES_CMAKE_CONFIGURE_COMMAND
$HERMES_CMAKE_BUILD_COMMAND
$HERMES_CMAKE_INSTALL_COMMAND

popd
popd

pushd flatbuffers
mkdir hermes-build
pushd hermes-build

$HERMES_CMAKE_CONFIGURE_COMMAND
$HERMES_CMAKE_BUILD_COMMAND
$HERMES_CMAKE_INSTALL_COMMAND

popd
popd


echo Done setting up
echo 
echo ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
echo // written by scoward
echo ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

# written by scoward