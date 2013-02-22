#include "ClientHandler.h"

ClientHandler::ClientHandler(void) : NatNetClient()
{
	
}

ClientHandler::ClientHandler(int iType) : NatNetClient(iType)
{

}


void ClientHandler::init()
{
}

ClientHandler::~ClientHandler(void)
{
	this->NatNetClient::~NatNetClient();
}

bool ClientHandler::addRigidBody(int id, osg::AutoTransform* transform)
{
	std::pair<std::map<int,osg::AutoTransform*>::iterator,bool> ret;
	ret = _rigidBodies.insert ( std::pair<int, osg::AutoTransform*>(id, transform) );

	if (ret.second == false)
		return false;

	return true;
}

osg::AutoTransform* ClientHandler::getRigidBodyTransformation(int id)
{
	std::map<int, osg::AutoTransform*>::iterator ret;
	ret = _rigidBodies.find(id);

	if ( ret == _rigidBodies.end())
		return 0;

	return ret->second;
}

void ClientHandler::transformRigidBody(int id, osg::Vec3 pos, osg::Vec4 rot)
{
	std::map<int, osg::AutoTransform*>::iterator ret;
	ret = _rigidBodies.find(id);

	if ( ret == _rigidBodies.end())
		return;

	ret->second->setRotation(rot);
	ret->second->setPosition(pos);
}
