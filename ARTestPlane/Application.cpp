/**
 * Application.cpp
 * Created By: Michael Feist
 */
#include "Application.h"

#include <osg/AutoTransform>
#include <osg/Texture2D>
#include <osg/TexMat>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

#include "Client.h"

#include "RigidBody.h"

osgViewer::Viewer viewer;
osg::Vec4 backGroundColor(0.f, 0.f, 0.f, 0.f);

osg::AutoTransform* planeMatrix;
osg::AutoTransform* cameraMatrix;

const int PLANELENGTH = 10;

osg::Geode *createPlane() {
	// vertex array
	osg::Vec3Array *vertexArray = new osg::Vec3Array();
	vertexArray->push_back(osg::Vec3(0, PLANELENGTH, 0));
	vertexArray->push_back(osg::Vec3(0, 0, 0));
	vertexArray->push_back(osg::Vec3(PLANELENGTH, 0, 0));
	vertexArray->push_back(osg::Vec3(PLANELENGTH, PLANELENGTH, 0));

	// face array
	// give indices of vertices in counter-clockwise order
	osg::DrawElementsUInt *faceArray = new osg::DrawElementsUInt(
		osg::PrimitiveSet::QUADS, 0
	);
	faceArray->push_back(0);
	faceArray->push_back(1);
	faceArray->push_back(2);
	faceArray->push_back(3);

	// normal array
	// give the normals on the cube's faces
	osg::Vec3Array *normalArray = new osg::Vec3Array();
	normalArray->push_back(osg::Vec3(0, 0, +1));

	// normal index
	// assign each vertex a normal (similar to assigning colors)
	osg::TemplateIndexArray<unsigned int, osg::Array::UIntArrayType, 24, 4> *normalIndexArray;
	normalIndexArray = new osg::TemplateIndexArray<
		unsigned int, osg::Array::UIntArrayType, 24, 4
	>();
	normalIndexArray->push_back(0);
	normalIndexArray->push_back(0);
	normalIndexArray->push_back(0);
	normalIndexArray->push_back(0);

	// texture coordinates
	osg::Vec2Array *texCoords = new osg::Vec2Array();
	texCoords->push_back(osg::Vec2(0.0, 1.0));
	texCoords->push_back(osg::Vec2(0.0, 0.0));
	texCoords->push_back(osg::Vec2(1.0, 0.0));
	texCoords->push_back(osg::Vec2(1.0, 1.0));

	osg::Geometry *geometry = new osg::Geometry();
	geometry->setVertexArray(vertexArray);
	geometry->setNormalArray(normalArray);
	geometry->setNormalIndices(normalIndexArray);
	geometry->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
	geometry->setTexCoordArray(0, texCoords);
	geometry->addPrimitiveSet(faceArray);

	osg::Geode *geode = new osg::Geode();
	geode->addDrawable(geometry);
	return geode;
}

int Application::run()
{
	ClientHandler* theClient = 0;
	Client::createClient(&theClient);

	osg::Group* rootNode = new osg::Group();
	planeMatrix = new osg::AutoTransform();
	cameraMatrix = new osg::AutoTransform();

	RigidBody *planeBody = new RigidBody();
	planeBody->setTransform(planeMatrix);

	theClient->addRigidBody(65537, planeBody);
	//theClient->addRigidBody(10, cameraMatrix);

	rootNode->addChild(planeMatrix);
	//rootNode->addChild(cameraMatrix);

	osg::Node* model = osgDB::readNodeFile("cow.osg");
	//rootNode->addChild(model);

	//osg::Geode *plane = createPlane();
	planeMatrix->addChild(model);
	/*
	osg::Image *image_checker = osgDB::readImageFile("Images/checker.jpg");
	if (!image_checker) {
		printf("Couldn't load texture.\n");
		//return NULL;
	}
	
	// checker_texture
	osg::Texture2D *checker_texture = new osg::Texture2D();
	checker_texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
	checker_texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
	checker_texture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	checker_texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP);
	checker_texture->setImage(image_checker);

	// Bind Texture
	osg::StateSet *planeStateSet = plane->getOrCreateStateSet();
	planeStateSet->ref();
	planeStateSet->setTextureAttributeAndModes(
		0, checker_texture, osg::StateAttribute::ON
	);

	plane->setStateSet(planeStateSet);
	*/
	viewer.setSceneData(rootNode);
	viewer.getCamera()->setClearColor(backGroundColor);

	viewer.setRunMaxFrameRate(60.f);

	viewer.setUpViewInWindow(100, 100, 800, 600);

	viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	viewer.realize();
	
	//Loop
	while( !viewer.done() )
	{
		viewer.frame();
	}

	Client::deleteClient(&theClient);

	return 0;
}
