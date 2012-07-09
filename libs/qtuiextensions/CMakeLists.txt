cmake_minimum_required(VERSION 2.8)
project(QtUiExtensions)

find_package( Qt4 4.3 REQUIRED )

# Build Release by default
IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF ()

file( GLOB UIEXT_SRC *.cpp )

add_library( QtUiExtensions ${UIEXT_SRC} )
