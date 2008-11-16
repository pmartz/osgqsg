//
// OpenSceneGraph Quick Start Guide
// http://www.lulu.com/content/767629
// http://www.openscenegraph.com/osgwiki/pmwiki.php/Documentation/QuickStartGuide
//

// FindNode Example, Simple NodeVisitor-derived class for finding a named Node

#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osg/Camera>
#include <osg/StateSet>
#include <osg/ShadeModel>
#include <osgDB/ReadFile>
#include <string>

// Derive a class from NodeVisitor to find a node with a
//   specific name.
class FindNamedNode : public osg::NodeVisitor
{
public:
    FindNamedNode( const std::string& name )
      : osg::NodeVisitor( // Traverse all children.
                osg::NodeVisitor::TRAVERSE_ALL_CHILDREN ),
        _name( name ) {}

    // This method gets called for every node in the scene
    //   graph. Check each node to see if its name matches
    //   out target. If so, save the node's address.
    virtual void apply( osg::Node& node )
    {
        if (node.getName() == _name)
            _node = &node;

        // Keep traversing the rest of the scene graph.
        traverse( node );
    }

    osg::Node* getNode() { return _node.get(); }

protected:
    std::string _name;
    osg::ref_ptr<osg::Node> _node;
};


int
main( int, char ** )
{
    osg::ref_ptr<osg::Node> sg =
            osgDB::readNodeFile( "State.osg" );
    if (!sg.valid())
    {
        osg::notify( osg::FATAL ) << "Unable to load data file. Exiting." << std::endl;
        return 1;
    }

    // Find the node who's name is "Flat".
    FindNamedNode fnn( "Flat" );
    sg->accept( fnn );
    if (fnn.getNode() != NULL)
    {
        // We found the node. MGet the ShadeModel attribute
        //   from its StateSet and set it to SMOOTH shading.
        osg::StateSet* ss = fnn.getNode()->getOrCreateStateSet();
        osg::ShadeModel* sm = dynamic_cast<osg::ShadeModel*>(
                ss->getAttribute(
                        osg::StateAttribute::SHADEMODEL ) );
        sm->setMode( osg::ShadeModel::SMOOTH );
    }


    // Create the viewer and set its scene data to our scene
    //   graph created above.
    osgViewer::Viewer viewer;
    viewer.setSceneData( sg.get() );

    // Loop and render. OSG calls RotateCB::operator()
    //   during the update traversal.
    viewer.run();
}
