//
// OpenSceneGraph Quick Start Guide
// http://www.lulu.com/content/767629
// http://www.openscenegraph.com/osgwiki/pmwiki.php/Documentation/QuickStartGuide
//

// Viewer Example, A minimal OSG viewer

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

int
main( int, char ** )
{
    // Create a Viewer.
    osgViewer::Viewer viewer;

    // Load a model and add it to the Viewer.
    viewer.setSceneData( osgDB::readNodeFile( "cow.osg" ) );
    if (!viewer.getSceneData())
    {
        osg::notify( osg::FATAL ) << "Unable to load data file. Exiting." << std::endl;
        return 1;
    }

    // TBD. Waiting for this file to get a permanent location after
    //   the dimain name shuffle. THis is a better example than the
    //   cow because it shows off the .net loader.
    //viewer.setSceneData( osgDB::readNodeFile(
    //    "http://www.openscenegraph.org/downloads/data/Earth/model.ive" ) );

    // Display, and main loop.
    return viewer.run();
}
