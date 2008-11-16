//
// OpenSceneGraph Quick Start Guide
// http://www.lulu.com/content/767629
// http://www.openscenegraph.com/osgwiki/pmwiki.php/Documentation/QuickStartGuide
//

// State Example, Modifying state attributes and modes

#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/StateSet>
#include <osg/StateAttribute>
#include <osg/ShadeModel>
#include <osg/CullFace>
#include <osg/PolygonMode>
#include <osg/LineWidth>

// Create a pair of quadrilateral primitives with color
//   per vertex and return them as a single Drawable.
osg::ref_ptr<osg::Drawable>
createDrawable()
{
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
    geom->setVertexArray( v.get() );
    v->push_back( osg::Vec3( -1.15f, -.5f, -.85f ) );
    v->push_back( osg::Vec3( .85f, -.5f, -.85f ) );
    v->push_back( osg::Vec3( .85f, -.5f, 1.15f ) );
    v->push_back( osg::Vec3( -1.15f, -.5f, 1.15f ) );
    v->push_back( osg::Vec3( -.85f, .5f, -1.15f ) );
    v->push_back( osg::Vec3( -.85f, .5f, .85f ) );
    v->push_back( osg::Vec3( 1.15f, .5f, .85f ) );
    v->push_back( osg::Vec3( 1.15f, .5f, -1.15f ) );

    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
    geom->setColorArray( c.get() );
    geom->setColorBinding( osg::Geometry::BIND_PER_VERTEX );
    c->push_back( osg::Vec4( 1.f, 0.33f, 0.f, 1.f ) );
    c->push_back( osg::Vec4( 0.f, 1.f, 0.f, 1.f ) );
    c->push_back( osg::Vec4( 0.f, 0.33f, 1.f, 1.f ) );
    c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f ) );
    c->push_back( osg::Vec4( 1.f, 0.f, 0.f, 1.f ) );
    c->push_back( osg::Vec4( 1.f, .66f, 1.f, 1.f ) );
    c->push_back( osg::Vec4( 0.f, 0.f, 1.f, 1.f ) );
    c->push_back( osg::Vec4( 0.f, .66f, 0.f, 1.f ) );

    geom->addPrimitiveSet(
        new osg::DrawArrays( osg::PrimitiveSet::QUADS, 0, 8 ) );

    return geom.get();
}

osg::ref_ptr<osg::Node>
createSceneGraph()
{
    // Create the root node Group.
    osg::ref_ptr<osg::Group> root = new osg::Group;
    {
        // Disable lighting in the root node's StateSet. Make
        //   it PROTECTED to prevent osgviewer from enabling it.
        osg::StateSet* state = root->getOrCreateStateSet();
        state->setMode( GL_LIGHTING,
            osg::StateAttribute::OFF |
            osg::StateAttribute::PROTECTED );
    }

    // Create the leaf node Geode and attach the Drawable.
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( createDrawable().get() );

    osg::Matrix m;
    {
        // Upper-left: Render the drawable with default state.
        osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
        m.makeTranslate( -2.f, 0.f, 2.f );
        mt->setMatrix( m );
        root->addChild( mt.get() );
        mt->addChild( geode.get() );
    }
    {
        // Upper-right Set shade model to FLAT.
        osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
        mt->setName( "Flat" );
        m.makeTranslate( 2.f, 0.f, 2.f );
        mt->setMatrix( m );
        root->addChild( mt.get() );
        mt->addChild( geode.get() );

        osg::StateSet* state = mt->getOrCreateStateSet();
        osg::ShadeModel* sm = new osg::ShadeModel();
        sm->setMode( osg::ShadeModel::FLAT );
        state->setAttribute( sm );
    }
    {
        // Lower-left: Enable back face culling.
        osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
        m.makeTranslate( -2.f, 0.f, -2.f );
        mt->setMatrix( m );
        root->addChild( mt.get() );
        mt->addChild( geode.get() );

        osg::StateSet* state = mt->getOrCreateStateSet();
        osg::CullFace* cf = new osg::CullFace(); // Default: BACK
        state->setAttributeAndModes( cf );
    }
    {
        // Lower-right: Set polygon mode to LINE in draw3's StateSet.
        osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
        m.makeTranslate( 2.f, 0.f, -2.f );
        mt->setMatrix( m );
        root->addChild( mt.get() );
        mt->addChild( geode.get() );

        osg::StateSet* state = mt->getOrCreateStateSet();
        osg::PolygonMode* pm = new osg::PolygonMode(
            osg::PolygonMode::FRONT_AND_BACK,
            osg::PolygonMode::LINE );
        state->setAttributeAndModes( pm );

        // Also set the line width to 3.
        osg::LineWidth* lw = new osg::LineWidth( 3.f );
        state->setAttribute( lw );
    }

    return root.get();
}
