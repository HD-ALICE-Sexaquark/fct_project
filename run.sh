#!/bin/bash

CURRENT_DIR=${PWD}

# define build dir
BUILD_DIR=$(readlink -f ./G4_B2a_MK_build)

cd ${BUILD_DIR}

./exampleB2a

cd ${CURRENT_DIR}