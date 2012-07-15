cmake_minimum_required(VERSION 2.8)
project(libQtUiExtensions)

set( CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Wall -O2 -g" )
set( CMAKE_CXX_FLAGS_RELEASE "-Wall -O2" )
set( CMAKE_CXX_FLAGS_DEBUG "-Wall -g3 -ggdb -O0" CACHE STRING "Debug options." FORCE )

# Build Release by default
IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF ()

find_package( Qt4 4.3 REQUIRED )
include( ${QT_USE_FILE} )

qt4_wrap_ui( MSPIGGIT_UI_HEADERS ${MSPIGGIT_UI} )
qt4_wrap_cpp( MSPIGGIT_MOC_HEADERS ${MSPIGGIT_SRC} )
qt4_add_resources( MSPIGGIT_RESOURCE_SRC ${MSPIGGIT_RESOURCE} )


file( GLOB UIEXT_SRC *.cpp )

add_library( QtUiExtensions STATIC ${UIEXT_SRC} )

target_link_libraries( QtUiExtensions )
