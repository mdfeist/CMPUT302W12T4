/**
 * ClientHandler.h
 * Created By: Michael Feist
 */

#pragma once

#include <map>

#include "RigidBody.h"

#include "NatNetTypes.h"
#include "NatNetClient.h"

class ClientHandler : public NatNetClient
{
public:
	ClientHandler(void);
	ClientHandler(int iType);
	~ClientHandler(void);

	bool addRigidBody(int id, RigidBody* rigidBody);
	RigidBody* getRigidBody(int id);
	void transformRigidBody(int id, osg::Vec3 pos, osg::Vec4 rot);

private:
	std::map<int, RigidBody*> _rigidBodies;

	void init();
};

