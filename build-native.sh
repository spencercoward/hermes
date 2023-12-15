#!/bin/bash
# written by scoward

if ! command -v cmake &> /dev/null
then
    echo "cmake could not be found on PATH"
    exit
fi

# where we build the main part of the repo
PROJECT_NAME=Hermes
BLD_DIR=hermes-build
export ROOT_DIR=$PWD

# quick check if setup has been run
if [ ! -d "./external/install/lib" ]
then
   ./setup
fi

# check if we already have a build dir
#if [ ! -d "./hermes-build" ]
#then
#   mkdir hermes-build
#fi

#PRJ_BLD_DIR=$BLD_DIR/$PROJECT_NAME
PRJ_BLD_DIR=$BLD_DIR
PRJ_INSTALL_DIR=$PWD/external/install

 
echo "*****************************************************************************"
echo "Executing cmake configure steps for $PROJECT_NAME"
echo "CMAKE_GENERATOR             = $CMAKE_GENERATOR"
echo "BLD_DIR                     = $BLD_DIR"
echo "PRJ_BLD_DIR                 = $PRJ_BLD_DIR"
echo "PRJ_INSTALL_DIR             = $PRJ_INSTALL_DIR"
echo "POCO_SRC_DIR                = $POCO_SRC_DIR"
echo "POCO_BLD_DIR                = $POCO_BLD_DIR"
echo "GRPC_SRC_DIR                = $GRPC_SRC_DIR"
echo "GRPC_BLD_DIR                = $GRPC_BLD_DIR"
echo "PWD                         = $PWD"
echo "*****************************************************************************"


TIMEFORMAT='
*********************************************************
${PROJECT_NAME} configure elapsed time is %2lE
*********************************************************
'

if [ ! -d "$PRJ_BLD_DIR/CMakeFiles" ]; then
   time (cmake -S . -DCMAKE_TOOLCHAIN_FILE=$TC_DIR \
          -B $PRJ_BLD_DIR \
          -G "$CMAKE_GENERATOR" \
          $ARCHITECTURE \
          -DCMAKE_BUILD_TYPE=$CONFIG_OPT \
          -DCMAKE_PREFIX_PATH=$PRJ_INSTALL_DIR \
          -DCMAKE_INSTALL_PREFIX=$PRJ_INSTALL_DIR
        )
fi

#pushd hermes-build
#cmake ..
#cmake --build . -j 24

# written by scoward