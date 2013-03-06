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

	RigidBody *cameraBody = new RigidBody();
	cameraBody->setTransform(cameraMatrix);

	//theClient->addRigidBody(65537, planeBody);
	theClient->addRigidBody(65537, cameraBody);

	rootNode->addChild(planeMatrix);
	planeMatrix->setPosition(osg::Vec3(-5.f, 23.f, 9.f));
	planeMatrix->setScale(0.5);
	//rootNode->addChild(cameraMatrix);

	osg::Node* model = osgDB::readNodeFile("cow.osg");
	planeMatrix->addChild(model);

	osg::Geode *plane = createPlane();
	planeMatrix->addChild(plane);
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
	//viewer.setSceneData(rootNode);
	//viewer.getCamera()->setClearColor(backGroundColor);

	osg::Camera* cam = new osg::Camera();
	cam->setClearColor(backGroundColor);
	cam->addChild(rootNode);

	cam->setProjectionMatrixAsPerspective(45.0, 1.0, 0.5, 1000.f);

	//planeMatrix->addChild(cam);

	viewer.setCamera(cam);

	viewer.setRunMaxFrameRate(60.f);

	viewer.setUpViewInWindow(100, 100, 800, 600);

	//viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	viewer.realize();
	
	int c = 0; 

	//Loop
	while( !viewer.done() )
	{
		c++;

		osg::Quat quat = cameraMatrix->getRotation();

		osg::Matrixf matrix = cam->getViewMatrix();
		matrix.setTrans(cameraMatrix->getPosition());
		matrix.setRotate(quat);
		cam->setViewMatrix(osg::Matrixf::inverse(matrix));

		//matrix.setTrans(planeMatrix->getPosition());
		//matrix.setRotate(planeMatrix->getRotation());

		/*
		cam->setViewMatrixAsLookAt(planeMatrix->getPosition(), 
		osg::Vec3(0.f, 0.f, 0.f), 
		osg::Vec3(0.f, 1.f, 0.f));
		*/
		osg::Vec3 eye;
		osg::Vec3 center;
		osg::Vec3 up;

		cam->getViewMatrixAsLookAt(eye, center, up);
		
		if (c % 10 == 0) {
			printf("Eye: %f %f %f\nCenter: %f %f %f\nUp: %f %f %f\n",
				eye.x(), eye.y(), eye.z(), center.x(), center.y(), center.z(),
				up.x(), up.y(), up.z());
		}
		/*
		cam->setViewMatrixAsLookAt(planeMatrix->getPosition(), 
		osg::Vec3(0.f, 0.f, 0.f), 
		osg::Vec3(0.f, 1.f, 0.f));
		*/
		viewer.frame();
	}

	Client::deleteClient(&theClient);

	return 0;
}
