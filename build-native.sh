#!/bin/bash
# written by scoward

if ! command -v cmake &> /dev/null
then
    echo "cmake could not be found on PATH"
    exit
fi

CMAKE_GENERATOR=""
POCO_CMAKE_DEFINES=""

if [[ "$OSTYPE" == "linux-gnu" ]]; then
  CMAKE_GENERATOR="Unix Makefiles"
  ARCHITECTURE=""
fi

# where we build the main part of the repo
PROJECT_NAME=Hermes
BLD_DIR=hermes-build
export ROOT_DIR=$PWD

################################################

# Help

################################################

Help()
{
   # Display Help
   echo "CMake builder script"
   echo
   echo "Syntax: scriptTemplate [option]"
   echo "options:"
   echo "-h | --help        Print this Help."
   echo "-j | --jobs        Configure the jobs to use for build (defaults to 1)"
   echo "-t | --toolchain   Specify Toolchain to be used (Available Toolchain files can be found under cmake)."
   echo "-c | --config      Specify config - Release or Debug."
   echo "-C | --credentials Specify Credentials for cloning"
   echo "-g | --generator  Specify the generator used for cmake. cmake --help for all options"
   echo "-f | --force      Force a reconfigure on a specific item"
   echo "-v | --version    Build sw with version number built in"
   echo

   exit
}

# Get the options
SHORT=h,t:,j:,c:,C:,v:,g:,f:
LONG=help,toolchain:,jobs:,config:,credentials:,version:,generator:,force:
OPTS=$(getopt -a -n configure-cmake --options $SHORT --longoptions $LONG -- "$@")
VALID_ARGUMENTS=$# # Returns the count of arguments that are in short or long options
eval set -- "$OPTS"

ToolChain=""
CONFIG_OPT=""

while :
  do
   case $1 in
      -h | --help ) # display Help
         Help
         shift 2
         ;;
      -j | --jobs )
         JOBS="-j $2"
         shift 2
         ;;
      -t | --toolchain )
         ToolChain=$2
         echo "ToolChain = ${ToolChain}"
         shift 2
         ;;
      -c | --config )
         CONFIG_OPT=$2
         echo "config = ${CONFIG_OPT}"
         shift 2
         ;;
      -C | --credentials )
         JENKINS_CRED="$2"
         shift 2
         ;;
      -v | --version )
         VERSION=$2
         echo "version = ${VERSION}"
         shift 2
         ;;
      -g | --generator )
         CMAKE_GENERATOR="$2"
         shift 2
         ;;
      -f | --force )
         FORCE="$2"
         shift 2
         ;;
      --)
         shift;
         break
         ;;
      *) # Invalid option
         echo "Error: Invalid option"
         Help
         ;;
   esac
done

# Verify valid Toolchain and determine directory layout
TARGET_PLATFORM=""
TC_DIR="${PWD}/cmake/tc-${ToolChain}.cmake"

if [ ! -f $TC_DIR ]; then
  echo "$TC_DIR does not exist. Using default."
  TC_DIR=""
  BLD_DIR="build/host"
else
  TARGET_PLATFORM=$(cut -d "-" -f 2 <<< "$ToolChain")
  BLD_DIR="build/${TARGET_PLATFORM}/$(cut -d "-" -f 1 <<< "$ToolChain")"
  ARCHITECTURE=""
fi

if [[ "$OSTYPE" == "linux-gnu" ]]; then # No default config for linux
  if [ -z $CONFIG_OPT ]; then
    CONFIG=""
    echo "CONFIG is $CONFIG"
  else
    CONFIG="--config $CONFIG_OPT"
    echo "CONFIG is $CONFIG"
  fi
else # Default config to debug for windows/vxworks if not specified
  if [ -z $CONFIG_OPT ]; then
    CONFIG="--config Debug"
    echo "CONFIG is $CONFIG"
  else
    CONFIG="--config $CONFIG_OPT"
    echo "CONFIG is $CONFIG"
  fi
fi

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
configure elapsed time is %2lE
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

TIMEFORMAT='
*********************************************************
build elapsed time is %2lE
*********************************************************
'
time (cmake --build $PRJ_BLD_DIR -j 24)

#pushd hermes-build
#cmake ..
#cmake --build . -j 24

# written by scoward