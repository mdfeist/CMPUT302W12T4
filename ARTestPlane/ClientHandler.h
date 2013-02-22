#pragma once

#include <map>
#include <osg/AutoTransform>

#include "NatNetTypes.h"
#include "NatNetClient.h"

class ClientHandler : public NatNetClient
{
public:
	ClientHandler(void);
	ClientHandler(int iType);
	~ClientHandler(void);

	bool addRigidBody(int id, osg::AutoTransform* transform);
	osg::AutoTransform* getRigidBodyTransformation(int id);
	void transformRigidBody(int id, osg::Vec3 pos, osg::Vec4 rot);

private:
	std::map<int, osg::AutoTransform*> _rigidBodies;

	void init();
};

