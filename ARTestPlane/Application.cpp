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
#include "Objects.h"
#include "KeyBoardInput.h"

osgViewer::Viewer viewer;
osg::Vec4 backGroundColor(0.f, 0.f, 0.f, 0.f);

osg::AutoTransform* planeMatrix;
osg::AutoTransform* cameraMatrix;

const int PLANELENGTH = 10;

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
	planeMatrix->setPosition(osg::Vec3(0.f, 0.f, 4.f));
	planeMatrix->setScale(10.f);
	//rootNode->addChild(cameraMatrix);

	//osg::Node* model = osgDB::readNodeFile("cow.osg");
	//planeMatrix->addChild(model);

	osg::Geode *plane = Objects::createPlane();
	planeMatrix->addChild(plane);
	
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
	
	//viewer.setSceneData(rootNode);
	//viewer.getCamera()->setClearColor(backGroundColor);

	osg::Camera* cam = new osg::Camera();
	cam->setClearColor(backGroundColor);
	cam->addChild(rootNode);

	//planeMatrix->addChild(cam);

	viewer.setCamera(cam);

	viewer.setRunMaxFrameRate(60.f);

	viewer.setUpViewInWindow(100, 100, 800, 600);

	KeyBoardInput* kboard = new KeyBoardInput();
	kboard->setFOV(26.0f);
	kboard->setAspect(1.77f);
	viewer.addEventHandler(kboard);

	//viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	viewer.realize();
	
	int c = 0; 

	//Loop
	while( !viewer.done() )
	{
		c++;

		cam->setProjectionMatrixAsPerspective(kboard->getFOV(), 
			kboard->getAspect(), 0.5, 1000.f);


		osg::Quat quat = cameraMatrix->getRotation();

		osg::Matrixf matrix = cam->getViewMatrix();
		matrix.setTrans(osg::Vec3(-cameraMatrix->getPosition().x(), 
			cameraMatrix->getPosition().y(), 
			cameraMatrix->getPosition().z()));
		matrix.setRotate(osg::Quat(quat.x(), -quat.y(), -quat.z(), quat.w()));
		cam->setViewMatrix(osg::Matrixf::inverse(matrix));

		//matrix.setTrans(planeMatrix->getPosition());
		//matrix.setRotate(planeMatrix->getRotation());

		/*
		cam->setViewMatrixAsLookAt(osg::Vec3(10.f, 5.f, 10.f), 
		osg::Vec3(0.f, 0.f, 0.f), 
		osg::Vec3(0.f, 1.f, 0.f));
		*/
		osg::Vec3 eye;
		osg::Vec3 center;
		osg::Vec3 up;

		cam->getViewMatrixAsLookAt(eye, center, up);
		
		if (c % 10 == 0) {
			printf("FOV: %f\nAspect: %f\n",
				kboard->getFOV(), kboard->getAspect());
			/*
			printf("Eye: %f %f %f\nCenter: %f %f %f\nUp: %f %f %f\n",
				eye.x(), eye.y(), eye.z(), center.x(), center.y(), center.z(),
				up.x(), up.y(), up.z());
				*/
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
