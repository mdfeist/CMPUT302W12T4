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
#include "GenericInput.h"

#include "XBoxThread.h"

#include "Settings.h"

osgViewer::Viewer viewer;
osg::Vec4 backGroundColor(0.f, 0.f, 0.f, 0.f);

osg::AutoTransform* planeMatrix;
osg::AutoTransform* cameraMatrix;

int Application::run()
{
	Settings::open();

	XBoxThread::startThread();

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
	//planeMatrix->setPosition(osg::Vec3(-5.f, -5.5f, -5.f));
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
	GenericInput::setFOV(27.0f);
	GenericInput::setAspect(1.77777f);

	GenericInput::setCameraOffsetX(0.f);
	GenericInput::setCameraOffsetY(0.f);
	GenericInput::setCameraOffsetZ(0.f);

	viewer.addEventHandler(kboard);

	//viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	viewer.realize();
	
	int c = 0; 

	//Loop
	while( !viewer.done() )
	{
		c++;

		cam->setProjectionMatrixAsPerspective(GenericInput::getFOV(), 
			GenericInput::getAspect(), 0.5, 1000.f);


		osg::Quat quat = cameraMatrix->getRotation();

		float y = (float)atan2(2.f * quat.x() * quat.w() + 2.f * quat.y() * quat.z(), 1.f - 2.f * (quat.z()*quat.z()  + quat.w()*quat.w()));     // Yaw 
		float x = (float)asin(2.f * ( quat.w() * quat.z() - quat.w() * quat.y() ) );
		float z = (float)atan2(2.f * quat.x() * quat.y() + 2.f * quat.z() * quat.w(), 1 - 2.f * (quat.y()*quat.y() + quat.z()*quat.z()));
		
		//planeMatrix->setPosition(osg::Vec3(kboard->x, kboard->y, kboard->z));

		osg::Matrixf matrix = cam->getViewMatrix();
		matrix.setRotate(osg::Quat(quat.x(), -quat.y(), -quat.z(), quat.w()));
		matrix.setTrans(osg::Vec3(-cameraMatrix->getPosition().x(), 
			cameraMatrix->getPosition().y(), 
			cameraMatrix->getPosition().z()));
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
			printf("X: %f Y: %f Z: %f\n", x, y, z);
			printf("FOV: %f\nAspect: %f\n",
				GenericInput::getFOV(), GenericInput::getAspect());
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
