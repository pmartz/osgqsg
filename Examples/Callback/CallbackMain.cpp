//
// OpenSceneGraph Quick Start Guide
// http://www.lulu.com/content/767629
// http://www.openscenegraph.com/osgwiki/pmwiki.php/Documentation/QuickStartGuide
//

// Callback Example, Using an update callback to modify the scene graph

#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osg/Camera>
#include <osg/NodeCallback>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osg/Notify>

// Derive a class from NodeCallback to manipulate a
//   MatrixTransform object's matrix.
class RotateCB : public osg::NodeCallback
{
public:
    RotateCB() : _angle( 0. ) {}

    virtual void operator()( osg::Node* node,
            osg::NodeVisitor* nv )
    {
        // Normally, check to make sure we have an update
        //   visitor, not necessary in this simple example.
        osg::MatrixTransform* mtLeft =
                dynamic_cast<osg::MatrixTransform*>( node );
        osg::Matrix mR, mT;
        mT.makeTranslate( -6., 0., 0. );
        mR.makeRotate( _angle, osg::Vec3( 0., 0., 1. ) );
        mtLeft->setMatrix( mR * mT );

        // Increment the angle for the next from.
        _angle += 0.01;

        // Continue traversing so that OSG can process
        //   any other nodes with callbacks.
        traverse( node, nv );
    }

protected:
    double _angle;
};

// Create the scene graph. This is a Group root node with two
//   MatrixTransform children, which multiply parent a single
//   Geode loaded from the cow.osg model file.
osg::Node*
createScene()
{
    // Load the cow model.
    osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile( "cow.osg" );
    if (!cow.valid())
    {
        osg::notify( osg::FATAL ) << "Unable to load data file. Exiting." << std::endl;
        return( NULL );
    }
    // Data variance is STATIC because we won't modify it.
    cow->setDataVariance( osg::Object::STATIC );

    // Create a MatrixTransform to display the cow on the left.
    osg::ref_ptr<osg::MatrixTransform> mtLeft =
            new osg::MatrixTransform;
    mtLeft->setName( "Left Cow\nDYNAMIC" );
    // Set data variance to DYNAMIC to let OSG know that we
    //   will modify this node during the update traversal.
    mtLeft->setDataVariance( osg::Object::DYNAMIC );
    // Set the update callback.
    mtLeft->setUpdateCallback( new RotateCB );
    osg::Matrix m;
    m.makeTranslate( -6.f, 0.f, 0.f );
    mtLeft->setMatrix( m );
    mtLeft->addChild( cow.get() );

    // Create a MatrixTransform to display the cow on the right.
    osg::ref_ptr<osg::MatrixTransform> mtRight =
            new osg::MatrixTransform;
    mtRight->setName( "Right Cow\nSTATIC" );
    // Data variance is STATIC because we won't modify it.
    mtRight->setDataVariance( osg::Object::STATIC );
    m.makeTranslate( 6.f, 0.f, 0.f );
    mtRight->setMatrix( m );
    mtRight->addChild( cow.get() );

    // Create the Group root node.
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->setName( "Root Node" );
    // Data variance is STATIC because we won't modify it.
    root->setDataVariance( osg::Object::STATIC );
    root->addChild( mtLeft.get() );
    root->addChild( mtRight.get() );

    return( root.release() );
}

int
main( int, char ** )
{
    // Create the viewer and set its scene data to our scene
    //   graph created above.
    osgViewer::Viewer viewer;
    viewer.setSceneData( createScene() );
    if (!viewer.getSceneData())
        return( 1 );

    // Set the clear color to something other than chalky blue.
    viewer.getCamera()->setClearColor(
            osg::Vec4( 1., 1., 1., 1. ) );

    // Loop and render. OSG calls RotateCB::operator()
    //   during the update traversal.
    return( viewer.run() );
}
