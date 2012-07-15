cmake_minimum_required(VERSION 2.8)
project(MsPiggit)

set (MSPIGGIT_VERSION_MAJOR 0)
set (MSPIGGIT_VERSION_MINOR 1)
set (MSPIGGIT_VERSION_REV   0)

set (MSPIGGIT_VERSION_STRING "${MSPIGGIT_VERSION_MAJOR}.${MSPIGGIT_VERSION_MINOR}.${MSPIGGIT_VERSION_REV}")

#include_directories( model ui )
file( GLOB_RECURSE MSPIGGIT_SRC core/*.cpp )
file( GLOB_RECURSE MSPIGGIT_H core/*.h)

file( GLOB_RECURSE MSPIGGIT_UIS core/*.ui )
file( GLOB MSPIGGIT_RESOURCE core/resources/*.qrc )

# setup include directories
set( LIBS libs )
set( QGIT2_INCLUDEDIR ${LIBS}/libqgit2/include )
set( GIT2_INCLUDEDIR ${LIBS}/libqgit2/libgit2/include )
include_directories( core ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${QGIT2_INCLUDEDIR} ${GIT2_INCLUDEDIR} )

# enable warnings
set( CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Wall -O2 -g" )
set( CMAKE_CXX_FLAGS_RELEASE "-Wall -O2" )
set( CMAKE_CXX_FLAGS_DEBUG "-Wall -g3 -ggdb -O0" CACHE STRING "Debug options." FORCE )

# Build Release by default
IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF ()

find_package(Qt4 4.3 REQUIRED)
include( ${QT_USE_FILE} )

qt4_add_resources( MSPIGGIT_RESOURCE_SRC ${MSPIGGIT_RESOURCE} )
qt4_wrap_ui( MSPIGGIT_UI_H ${MSPIGGIT_UIS} )
qt4_wrap_cpp( MSPIGGIT_MOC_CPP ${MSPIGGIT_H} )

add_subdirectory (libs/libqgit2)
add_subdirectory (libs/qtuiextensions)

add_executable( MsPiggit ${MSPIGGIT_SRC} ${MSPIGGIT_MOC_CPP} ${MSPIGGIT_UI_H} ${MSPIGGIT_RESOURCE_SRC} )
target_link_libraries( MsPiggit qgit2 QtUiExtensions ${QT_LIBRARIES} )
#INSTALL_TARGETS( ./bin MsPiggit)


#Packaging options
set(CPACK_GENERATOR "RPM;TGZ")
set(CPACK_PACKAGE_NAME "MsPiggit")
set(CPACK_PACKAGE_FILE_NAME "MsPiggit-${LIBQGIT2_VERSION_STRING}")
set(CPACK_PACKAGE_VERSION "${MSPIGGIT_VERSION_MAJOR}.${MSPIGGIT_VERSION_MINOR}.${MSPIGGIT_VERSION_REV}")
set(CPACK_PACKAGE_CONTACT "Nils Fenner <nilsfenner@web.de>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A platform independent Git user interface based on Qt.")
include(InstallRequiredSystemLibraries)
include(CPack)
