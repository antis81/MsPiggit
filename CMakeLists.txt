cmake_minimum_required(VERSION 2.8)
project(MsPiggit)

set (MSPIGGIT_VERSION_MAJOR 0)
set (MSPIGGIT_VERSION_MINOR 1)
set (MSPIGGIT_VERSION_REV   0)

set (MSPIGGIT_VERSION_STRING "${MSPIGGIT_VERSION_MAJOR}.${MSPIGGIT_VERSION_MINOR}.${MSPIGGIT_VERSION_REV}")

set ( MSPIGGIT_RES_DIR core/resources )

#include_directories( model ui )
file( GLOB_RECURSE MSPIGGIT_SRC core/*.cpp )
file( GLOB_RECURSE MSPIGGIT_H core/*.h)

file( GLOB_RECURSE MSPIGGIT_UIS core/*.ui )
file( GLOB MSPIGGIT_RESOURCE ${MSPIGGIT_RES_DIR}/*.qrc )

# setup include directories
set( LIBS libs )
set( QGIT2_INCLUDEDIR ${LIBS}/libqgit2/include )
set( GIT2_INCLUDEDIR ${LIBS}/libqgit2/libgit2/include )
include_directories( core ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${QGIT2_INCLUDEDIR} ${GIT2_INCLUDEDIR} )

# enable warnings
set( CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Wall -O2 -g" )
set( CMAKE_CXX_FLAGS_RELEASE "-Wall -O2" )
set( CMAKE_CXX_FLAGS_DEBUG "-Wall -g3 -ggdb -O0" CACHE STRING "Debug options." FORCE )

# Build Debug by default
IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF ()

find_package(Qt4 4.6 REQUIRED)
include( ${QT_USE_FILE} )

#--------------------------------------------------------------------------------
# This sets the windows build that will need the special winmain@16 call. Qt provides
# this for us in the qtmain.lib file. Using this cmake code will ensure we have it
# linked into our build. Not needed on Unix/OS X/Linux which is why we have the
# IF(WIN32) conditional.
IF (WIN32)
    SET (QT_USE_QTMAIN TRUE)
ENDIF (WIN32)

qt4_add_resources( MSPIGGIT_RESOURCE_SRC ${MSPIGGIT_RESOURCE} )
qt4_wrap_ui( MSPIGGIT_UI_H ${MSPIGGIT_UIS} )
qt4_wrap_cpp( MSPIGGIT_MOC_CPP ${MSPIGGIT_H} )

#--------------------------------------------------------------------------------
# For Apple set the icns file containing icons
IF(APPLE)
  # set how it shows up in the Info.plist file
  SET(MACOSX_BUNDLE_ICON_FILE ${PROJECT_NAME}.icns)
  # set where in the bundle to put the icns file
  SET_SOURCE_FILES_PROPERTIES(${MSPIGGIT_RES_DIR}/icons/${PROJECT_NAME}.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
  # include the icns file in the target
  SET(MSPIGGIT_SRC ${MSPIGGIT_SRC} ${MSPIGGIT_RES_DIR}/icons/${PROJECT_NAME}.icns)
ENDIF(APPLE)

add_subdirectory (libs/libqgit2)
add_subdirectory (libs/qtuiextensions)

add_executable( MsPiggit
                MACOSX_BUNDLE WIN32
                ${MSPIGGIT_SRC}
                ${MSPIGGIT_MOC_CPP}
                ${MSPIGGIT_UI_H}
                ${MSPIGGIT_RESOURCE_SRC}
)

target_link_libraries( MsPiggit qgit2 QtUiExtensions ${QT_LIBRARIES} )

#--------------------------------------------------------------------------------
# installation stuff below
#--------------------------------------------------------------------------------
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${MSPIGGIT_VERSION_STRING}")
set(CPACK_PACKAGE_VERSION "${MSPIGGIT_VERSION_STRING}")
set(CPACK_PACKAGE_CONTACT "Nils Fenner <nilsfenner@web.de>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A platform independent Git user interface based on Qt.")

SET(plugin_dest_dir bin)
SET(qtconf_dest_dir bin)
SET(APPS "\${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}")
IF(APPLE)
  SET( CPACK_BUNDLE_NAME "${PROJECT_NAME}-${MSPIGGIT_VERSION_STRING}" )
  SET(plugin_dest_dir ${PROJECT_NAME}.app/Contents/MacOS)
  SET(qtconf_dest_dir ${PROJECT_NAME}.app/Contents/Resources)
  SET(APPS "\${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app")
ENDIF(APPLE)
IF(WIN32)
  SET(APPS "\${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}.exe")
ENDIF(WIN32)

#--------------------------------------------------------------------------------
# Install the MsPiggit application, on Apple, the bundle is at the root of the
# install tree, and on other platforms it'll go into the bin directory.
INSTALL(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION . COMPONENT Runtime
    RUNTIME DESTINATION bin COMPONENT Runtime
    )

#--------------------------------------------------------------------------------
# Install needed Qt plugins by copying directories from the qt installation
# One can cull what gets copied by using 'REGEX "..." EXCLUDE'
INSTALL(DIRECTORY "${QT_PLUGINS_DIR}/imageformats" DESTINATION ${plugin_dest_dir}/plugins COMPONENT Runtime)

#--------------------------------------------------------------------------------
# install a qt.conf file
# this inserts some cmake code into the install script to write the file
INSTALL(CODE "
    file(WRITE \"\${CMAKE_INSTALL_PREFIX}/${qtconf_dest_dir}/qt.conf\" \"\")
    " COMPONENT Runtime)


#--------------------------------------------------------------------------------
# Use BundleUtilities to get all other dependencies for the application to work.
# It takes a bundle or executable along with possible plugins and inspects it
# for dependencies.  If they are not system dependencies, they are copied.

# directories to look for dependencies
SET( DIRS ${QT_LIBRARY_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/${LIBS}/libqgit2 ${CMAKE_CURRENT_BINARY_DIR}/${LIBS}/libqgit2/libgit2)

INSTALL( CODE "
    file(GLOB_RECURSE QTPLUGINS
      \"\${CMAKE_INSTALL_PREFIX}/${plugin_dest_dir}/plugins/*${CMAKE_SHARED_LIBRARY_SUFFIX}\")
    include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\${QTPLUGINS}\" \"${DIRS}\")
    " COMPONENT Runtime
)


# To Create a package, one can run "cpack -G DragNDrop CPackConfig.cmake" on Mac OS X
# where CPackConfig.cmake is created by including CPack
# And then there's ways to customize this as well
set(CPACK_BINARY_DRAGNDROP ON)
include(InstallRequiredSystemLibraries)
include(CPack)

