//
// OpenSceneGraph Quick Start Guide
// http://www.lulu.com/content/767629
// http://www.openscenegraph.com/osgwiki/pmwiki.php/Documentation/QuickStartGuide
//

// Texture Mapping Example, Texture mapped tree, blending, alpha test

#include <osg/ref_ptr>
#include <osgDB/Registry>
#include <osgDB/WriteFile>
#include <osg/Notify>
#include <iostream>

using std::endl;

osg::ref_ptr<osg::Node> createSceneGraph();

int
main( int argc, char** argv)
{
    osg::ref_ptr<osg::Node> root = createSceneGraph();
    if (!root.valid())
    {
        osg::notify(osg::FATAL) << "Failed in createSceneGraph()." << endl;
        return 1;
    }

    std::string out( "TextureMapping.osg" );
    if ( !(osgDB::writeNodeFile( *(root.get()), out )) )
    {
        osg::notify(osg::FATAL) << "Failed in osgDB::writeNodeFile()." << endl;
        return 1;
    }

    osg::notify(osg::ALWAYS) << "Successfully wrote \"" << out << "\". Execute \"osgviewer " << out << "\" to view." << endl;
}
