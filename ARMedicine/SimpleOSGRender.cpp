/**
* SimpleOSGRender.cpp
* 
* A simple test for OSG
*
* Created By: Michael Feist
*/

#include "SimpleOSGRender.h"

#include "Util.h"

#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osgDB/ReadFile> 
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>

osg::Geode* createPyramid()
{
	osg::Geode* pyramidGeode = new osg::Geode();
	osg::Geometry* pyramidGeometry = new osg::Geometry();

	pyramidGeode->addDrawable(pyramidGeometry); 

	//Declare an array of vertices. Each vertex will be represented by
	//a triple -- an instances of the vec3 class. An instance of
	//osg::Vec3Array can be used to store these triples. Since
	//osg::Vec3Array is derived from the STL vector class, we can use the
	//push_back method to add array elements. Push back adds elements to
	//the end of the vector, thus the index of first element entered is
	//zero, the second entries index is 1, etc.
	//Using a right-handed coordinate system with 'z' up, array
	//elements zero..four below represent the 5 points required to create
	//a simple pyramid.

	osg::Vec3Array* pyramidVertices = new osg::Vec3Array;
	pyramidVertices->push_back( osg::Vec3( 0, 0, 0) ); // front left
	pyramidVertices->push_back( osg::Vec3(10, 0, 0) ); // front right
	pyramidVertices->push_back( osg::Vec3(10,10, 0) ); // back right
	pyramidVertices->push_back( osg::Vec3( 0,10, 0) ); // back left
	pyramidVertices->push_back( osg::Vec3( 5, 5,10) ); // peak

	//Associate this set of vertices with the geometry associated with the
	//geode we added to the scene.

	pyramidGeometry->setVertexArray( pyramidVertices );

	//Next, create a primitive set and add it to the pyramid geometry.
	//Use the first four points of the pyramid to define the base using an
	//instance of the DrawElementsUint class. Again this class is derived
	//from the STL vector, so the push_back method will add elements in
	//sequential order. To ensure proper backface cullling, vertices
	//should be specified in counterclockwise order. The arguments for the
	//constructor are the enumerated type for the primitive
	//(same as the OpenGL primitive enumerated types), and the index in
	//the vertex array to start from.

	osg::DrawElementsUInt* pyramidBase =
		new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	pyramidBase->push_back(3);
	pyramidBase->push_back(2);
	pyramidBase->push_back(1);
	pyramidBase->push_back(0);
	pyramidGeometry->addPrimitiveSet(pyramidBase);

	//Repeat the same for each of the four sides. Again, vertices are
	//specified in counter-clockwise order.

	osg::DrawElementsUInt* pyramidFaceOne =
		new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	pyramidFaceOne->push_back(0);
	pyramidFaceOne->push_back(1);
	pyramidFaceOne->push_back(4);
	pyramidGeometry->addPrimitiveSet(pyramidFaceOne);

	osg::DrawElementsUInt* pyramidFaceTwo =
		new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	pyramidFaceTwo->push_back(1);
	pyramidFaceTwo->push_back(2);
	pyramidFaceTwo->push_back(4);
	pyramidGeometry->addPrimitiveSet(pyramidFaceTwo);

	osg::DrawElementsUInt* pyramidFaceThree =
		new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	pyramidFaceThree->push_back(2);
	pyramidFaceThree->push_back(3);
	pyramidFaceThree->push_back(4);
	pyramidGeometry->addPrimitiveSet(pyramidFaceThree);

	osg::DrawElementsUInt* pyramidFaceFour =
		new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	pyramidFaceFour->push_back(3);
	pyramidFaceFour->push_back(0);
	pyramidFaceFour->push_back(4);
	pyramidGeometry->addPrimitiveSet(pyramidFaceFour);

	//Declare and load an array of Vec4 elements to store colors.

	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) ); //index 0 red
	colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f) ); //index 1 green
	colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f) ); //index 2 blue
	colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f) ); //index 3 white
	colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) ); //index 4 red

	//The next step is to associate the array of colors with the geometry,
	//assign the color indices created above to the geometry and set the
	//binding mode to _PER_VERTEX.

	pyramidGeometry->setColorArray(colors);
	pyramidGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	// Since the mapping from vertices to texture coordinates is 1:1, 
	// we don't need to use an index array to map vertices to texture
	// coordinates. We can do it directly with the 'setTexCoordArray' 
	// method of the Geometry class. 
	// This method takes a variable that is an array of two dimensional
	// vectors (osg::Vec2). This variable needs to have the same
	// number of elements as our Geometry has vertices. Each array element
	// defines the texture coordinate for the cooresponding vertex in the
	// vertex array.

	osg::Vec2Array* texcoords = new osg::Vec2Array(5);
	(*texcoords)[0].set(0.00f,0.0f); // tex coord for vertex 0 
	(*texcoords)[1].set(0.25f,0.0f); // tex coord for vertex 1 
	(*texcoords)[2].set(0.50f,0.0f); // ""
	(*texcoords)[3].set(0.75f,0.0f); // "" 
	(*texcoords)[4].set(0.50f,1.0f); // ""
	pyramidGeometry->setTexCoordArray(0,texcoords);

	return pyramidGeode;
}

void SimpleOSGRender::render()
{
	osgViewer::Viewer viewer;
	osg::Group* root = new osg::Group();
	osg::Geode* pyramidGeode = createPyramid();

	viewer.setUpViewInWindow(30, 30, 640, 480); 

	//Add the pyramid geode to the root node of the scene graph.
	root->addChild(pyramidGeode);

	osg::Texture2D* KLN89FaceTexture = new osg::Texture2D;

	// protect from being optimized away as static state:
	KLN89FaceTexture->setDataVariance(osg::Object::DYNAMIC); 

	// load an image by reading a file: 
	osg::Image* klnFace = osgDB::readImageFile(Util::openfilename().c_str());
	if (!klnFace)
	{
		std::cout << " couldn't find texture, quiting." << std::endl;
		return;
	}

	// Assign the texture to the image we read from file: 
	KLN89FaceTexture->setImage(klnFace);

	// Create a new StateSet with default settings: 
	osg::StateSet* stateOne = new osg::StateSet();

	// Assign texture unit 0 of our new StateSet to the texture 
	// we just created and enable the texture.
	stateOne->setTextureAttributeAndModes
		(0,KLN89FaceTexture,osg::StateAttribute::ON);
	// Associate this state set with the Geode that contains
	// the pyramid: 
	pyramidGeode->setStateSet(stateOne);
	// switch off lighting as we haven't assigned any normals.
	root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	//The final step is to set up and enter a simulation loop.

	viewer.setSceneData( root );
	//viewer.run();

	viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	viewer.realize();

	while( !viewer.done() )
	{
		viewer.frame();
	}
}