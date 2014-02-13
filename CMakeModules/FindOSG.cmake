# This is part of the Findosg* suite used to find OpenSceneGraph components.
# Each component is separate and you must opt in to each module. You must 
# also opt into OpenGL and OpenThreads (and Producer if needed) as these 
# modules won't do it for you. This is to allow you control over your own 
# system piece by piece in case you need to opt out of certain components
# or change the Find behavior for a particular module (perhaps because the
# default FindOpenGL.cmake module doesn't work with your system as an
# example).
# If you want to use a more convenient module that includes everything,
# use the FindOpenSceneGraph.cmake instead of the Findosg*.cmake modules.
# 
# Locate osg
# This module defines
# OSG_LIBRARY
# OSG_FOUND, if false, do not try to link to osg
# OSG_INCLUDE_DIR, where to find the headers
#
# $OSGDIR is an environment variable that would
# correspond to the ./configure --prefix=$OSGDIR
# used in building osg.

# Header files are presumed to be included like
# #include <osg/PositionAttitudeTransform>
# #include <osgUtil/SceneView>

# For Windows, I have attempted to incorporate the environmental variables
# and registry entries used by Mike E. Weiblen's (mew) OSG installer. 
# 
# On OSX, this will prefer the Framework version (if found) over others.
# People will have to manually change the cache values of 
# the library to override this selection or set the CMake environment
# CMAKE_INCLUDE_PATH to modify the search paths.
#
# I originally had implemented some really nasty hacks to do OS X
# framework detection. CMake per my request has introduced native support
# for this so the code has been simplified. But for this to work,
# you must be using the new CMake code (introduced just before Jan 1st, 2006).

MACRO( FIND_OSG_INCLUDE THIS_OSG_INCLUDE_DIR THIS_OSG_INCLUDE_FILE )
    FIND_PATH( ${THIS_OSG_INCLUDE_DIR}
        NAMES ${THIS_OSG_INCLUDE_FILE}
        PATHS
            ${OSG_SOURCE_DIR}
            ${OSGDIR}
            ${OSG_DIR}
            ${OSG_ROOT}
            /usr/local/
            /usr/
            /sw/ # Fink
            /opt/local/ # DarwinPorts
            /opt/csw/ # Blastwave
            /opt/
            "C:/Program Files/OpenSceneGraph/"
            ~/Library/Frameworks
            /Library/Frameworks
            ENV OSG_SOURCE_DIR
            ENV OSGDIR
            ENV OSG_DIR
            ENV OSG_ROOT
        PATH_SUFFIXES
            include
    )
ENDMACRO( FIND_OSG_INCLUDE THIS_OSG_INCLUDE_DIR THIS_OSG_INCLUDE_FILE )

FIND_OSG_INCLUDE( OSG_INCLUDE_DIR osg/PositionAttitudeTransform )
FIND_OSG_INCLUDE( OSG_GEN_INCLUDE_DIR osg/Config )

MACRO(FIND_OSG_LIBRARY MYLIBRARY MYLIBRARYNAME)
    FIND_LIBRARY( ${MYLIBRARY}
        NAMES ${MYLIBRARYNAME}
        PATHS
            "C:/Program Files/OpenSceneGraph"
            ${OSG_BUILD_DIR}
            ${OSGDIR}
            ${OSG_DIR}
            ${OSG_ROOT}
            ~/Library/Frameworks
            /Library/Frameworks
            /usr/local
            /usr
            /sw
            /opt/local
            /opt/csw
            /opt
            /usr/freeware/lib64
            ENV OSG_BUILD_DIR
            ENV OSGDIR
            ENV OSG_DIR
            ENV OSG_ROOT
        PATH_SUFFIXES
            lib
            Build/lib
            build/lib
            bld/lib
    )
ENDMACRO(FIND_OSG_LIBRARY LIBRARY LIBRARYNAME)

FIND_OSG_LIBRARY(OSG_LIBRARY osg)
FIND_OSG_LIBRARY(OSGUTIL_LIBRARY osgUtil)
FIND_OSG_LIBRARY(OSGDB_LIBRARY osgDB)
FIND_OSG_LIBRARY(OSGTEXT_LIBRARY osgText)
FIND_OSG_LIBRARY(OSGTERRAIN_LIBRARY osgTerrain)
FIND_OSG_LIBRARY(OSGFX_LIBRARY osgFX)
FIND_OSG_LIBRARY(OSGSIM_LIBRARY osgSim)
FIND_OSG_LIBRARY(OSGVIEWER_LIBRARY osgViewer)

SET( OSG_FOUND "NO" )
IF( OSG_LIBRARY AND OSG_INCLUDE_DIR )
    SET( OSG_FOUND "YES")
    SET( OSG_INCLUDE_DIRS ${OSG_INCLUDE_DIR} ${OSG_GEN_INCLUDE_DIR} )
    GET_FILENAME_COMPONENT( OSG_LIBRARIES_DIR ${OSG_LIBRARY} PATH )
ENDIF( OSG_LIBRARY AND OSG_INCLUDE_DIR )

