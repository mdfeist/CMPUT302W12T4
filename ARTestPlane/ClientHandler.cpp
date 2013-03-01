/**
 * ClientHandler.cpp
 * Created By: Michael Feist
 */

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

bool ClientHandler::addRigidBody(int id, RigidBody* rigidBody)
{
	std::pair<std::map<int,RigidBody*>::iterator,bool> ret;
	ret = _rigidBodies.insert ( std::pair<int, RigidBody*>(id, rigidBody) );

	if (ret.second == false)
		return false;

	return true;
}

RigidBody* ClientHandler::getRigidBody(int id)
{
	std::map<int, RigidBody*>::iterator ret;
	ret = _rigidBodies.find(id);

	if ( ret == _rigidBodies.end())
		return 0;

	return ret->second;
}

void ClientHandler::transformRigidBody(int id, osg::Vec3 pos, osg::Vec4 rot)
{
	std::map<int, RigidBody*>::iterator ret;
	ret = _rigidBodies.find(id);

	if ( ret == _rigidBodies.end())
		return;

	ret->second->addFrame(pos, rot);
}
