#!/bin/bash

BUILD_DIR=build

# Check for the -hard argument
if [ "$1" == "-hard" ]; then
    echo "Running in hard mode: deleting and rebuilding..."
    rm -rf $BUILD_DIR
    mkdir -p $BUILD_DIR
    cd $BUILD_DIR
    cmake ..
    make
    ./ChristmasVM
else
    echo "Running in normal mode: building and running..."
    mkdir -p $BUILD_DIR
    cd $BUILD_DIR
    if [ ! -f "Makefile" ]; then
        cmake ..
    fi
    make
    ./ChristmasVM
fi
