#!/bin/bash
# written by scoward

# quick check if setup has been run
if [ ! -d "./external/install/lib" ]
then
   ./setup
fi

# check if we already have a build dir
if [ ! -d "./hermes-build" ]
then
   mkdir hermes-build
fi

pushd hermes-build

cmake ..
cmake --build . -j 24

# written by scoward