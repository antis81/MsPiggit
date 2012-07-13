cmake_minimum_required(VERSION 2.8)
project(MsPiggit)

set (MSPIGGIT_VERSION_MAJOR 0)
set (MSPIGGIT_VERSION_MINOR 1)
set (MSPIGGIT_VERSION_REV   0)

set (MSPIGGIT_VERSION_STRING "${MSPIGGIT_VERSION_MAJOR}.${MSPIGGIT_VERSION_MINOR}.${MSPIGGIT_VERSION_REV}")

#include_directories( model ui )
file( GLOB_RECURSE MSPIGGIT_SRC *.cpp )
file( GLOB_RECURSE MSPIGGIT_HEADERS *.h)

file( GLOB MSPIGGIT_UI ui/*.ui)
file( GLOB MSPIGGIT_RESOURCE resources/*.qrc )

# enable warnings
add_definitions( -Wall )

set( CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Wall -O2 -g" )
set( CMAKE_CXX_FLAGS_RELEASE "-Wall -O2" )
set( CMAKE_CXX_FLAGS_DEBUG "-Wall -g3 -ggdb -O0" CACHE STRING "Debug options." FORCE )

# Build Release by default
IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF ()

find_package(Qt4 4.3 REQUIRED)
include( ${QT_USE_FILE} )

include_directories(AFTER ${CMAKE_CURRENT_SOURCE_DIR}/../libs/libqgit2)

qt4_wrap_ui( MSPIGGIT_UI_HEADERS ${MSPIGGIT_UI} )
qt4_wrap_cpp( MSPIGGIT_MOC_HEADERS ${MSPIGGIT_SRC} )
qt4_add_resources( MSPIGGIT_RESOURCE_SRC ${MSPIGGIT_RESOURCE} )

include_directories( ${PROJECT_SOURCE_DIR} ${CMAKE_BINARY_DIR} )

add_executable( MsPiggit ${MSPIGGIT_SRC} )
