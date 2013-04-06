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

#define PIOVER180 0.01745329252

void fromEuler(osg::Quat *quat, float pitch, float yaw, float roll);
void addModelsToScene();

ClientHandler* theClient;
osg::Group* rootNode;

osgViewer::Viewer viewer;
osg::Vec4 backGroundColor(0.f, 0.f, 0.f, 0.f);

osg::AutoTransform* cameraMatrix;

int Application::run()
{
	Settings::open();

	XBoxThread::startThread();

	theClient = 0;
	Client::createClient(&theClient);

	rootNode = new osg::Group();
	cameraMatrix = new osg::AutoTransform();

	RigidBody *cameraBody = new RigidBody();
	cameraBody->setTransform(cameraMatrix);

	theClient->addRigidBody(65537, cameraBody);

if (0) {
	osg::AutoTransform* planeMatrix = new osg::AutoTransform();

	rootNode->addChild(planeMatrix);
	planeMatrix->setScale(10.f);

	osg::Geode *plane = Objects::createPlane();
	Objects::applyTexture("./Data/checker.jpg", plane);
	planeMatrix->addChild(plane);
} else {
	addModelsToScene();
}

	osg::Camera* cam = new osg::Camera();
	cam->setClearColor(backGroundColor);
	cam->addChild(rootNode);

	viewer.setCamera(cam);

	viewer.setRunMaxFrameRate(60.f);

	viewer.setUpViewInWindow(100, 100, 800, 600);

	float fov, aspect;
	float offsetX, offsetY, offsetZ;

	Settings::getCameraFOV(&fov);
	Settings::getCameraAspectRatio(&aspect);
	Settings::getCameraOffsets(&offsetX, &offsetY, &offsetZ);

	// Keyboard input
	KeyBoardInput* kboard = new KeyBoardInput();
	GenericInput::setFOV(fov);
	GenericInput::setAspect(aspect);

	GenericInput::setCameraOffsetX(offsetX);
	GenericInput::setCameraOffsetY(offsetY);
	GenericInput::setCameraOffsetZ(offsetZ);

	viewer.addEventHandler(kboard);

	viewer.realize();
	
	// Main Loop
	while( !viewer.done() )
	{
		cam->setProjectionMatrixAsPerspective(GenericInput::getFOV(), 
			GenericInput::getAspect(), 0.5, 1000.f);

		osg::Quat rot;

		fromEuler(&rot, GenericInput::getCameraOffsetX(),
						GenericInput::getCameraOffsetY(),
						GenericInput::getCameraOffsetZ());

		osg::Matrixf rotation;
		rotation.setRotate(rot);

		osg::Matrixf matrix = cam->getViewMatrix();
		matrix.setRotate(cameraMatrix->getRotation());
		matrix.setTrans(cameraMatrix->getPosition());

		matrix = osg::Matrixf::inverse(matrix) * rotation;

		cam->setViewMatrix(matrix);
		 
		viewer.frame();
	}

	Client::deleteClient(&theClient);

	return 0;
}

void fromEuler(osg::Quat *quat, float pitch, float yaw, float roll)
{
	// Basically we create 3 Quaternions, one for pitch, one for yaw, one for roll
	// and multiply those together.
	// the calculation below does the same, just shorter
 
	float p = pitch * PIOVER180 / 2.0;
	float y = yaw * PIOVER180 / 2.0;
	float r = roll * PIOVER180 / 2.0;
 
	float sinp = sin(p);
	float siny = sin(y);
	float sinr = sin(r);
	float cosp = cos(p);
	float cosy = cos(y);
	float cosr = cos(r);
 
	quat->x() = sinr * cosp * cosy - cosr * sinp * siny;
	quat->y() = cosr * sinp * cosy + sinr * cosp * siny;
	quat->z() = cosr * cosp * siny - sinr * sinp * cosy;
	quat->w() = cosr * cosp * cosy + sinr * sinp * siny;
 
	osg::Vec4d norm = quat->asVec4() / quat->asVec4().length();

	quat->set(norm);
}

void addModelsToScene() {
	int size = Settings::getNumberOfModels();

	for (int i = 0; i < size; i++) {
		Settings::Model3D* modelInfo = Settings::getModelAt(i);
		
		osg::AutoTransform *modelMatrix = new osg::AutoTransform();

		RigidBody *modelBody = new RigidBody();
		modelBody->setTransform(modelMatrix);

		theClient->addRigidBody(modelInfo->rigidbody, modelBody);

		rootNode->addChild(modelMatrix);

		osg::Quat rotation;
		fromEuler(&rotation, modelInfo->rotationX, modelInfo->rotationY, modelInfo->rotationZ);
		modelMatrix->setRotation(rotation);
		modelMatrix->setScale(modelInfo->modelScale);

		osg::Node *model = osgDB::readNodeFile(modelInfo->filePath);
		Objects::applyTexture(modelInfo->texturePath, model);
		model->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
		modelMatrix->addChild(model);
	}
}
