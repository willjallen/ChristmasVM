@echo off
SET BUILD_DIR=build

REM Check for the -hard argument
IF "%1" == "-hard" (
    echo Running in hard mode: deleting and rebuilding...
    rmdir /s /q %BUILD_DIR%
    mkdir %BUILD_DIR%
    cd %BUILD_DIR%
    cmake ..
    cmake --build . 
) ELSE (
    echo Running in normal mode: building and running...
    if not exist %BUILD_DIR% mkdir %BUILD_DIR%
    cd %BUILD_DIR%
    if not exist "Makefile" (
        cmake ..
    )
    cmake --build .
    cd Debug
    FunVM.exe ../../programs/demo.funasm
)
