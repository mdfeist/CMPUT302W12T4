/**
 * ClientHandler.h
 * Created By: Michael Feist
 */

#pragma once

#include <map>

#include "RigidBody.h"

#include "NatNetTypes.h"
#include "NatNetClient.h"

/*
 * The ClientHandler Class handles multiple
 * RigidBody's. You are able to add, get,
 * and update RigidBody's according to 
 * their given id.
 */
class ClientHandler : public NatNetClient
{
public:
	ClientHandler(void);
	ClientHandler(int iType);
	~ClientHandler(void);

	// Add a RigidBody to the ClientHandler
	bool addRigidBody(int id, RigidBody* rigidBody);
	// Get RigidBody based on it's id
	RigidBody* getRigidBody(int id);
	// Updates the RigidBody's transformation based on it's id
	void transformRigidBody(int id, osg::Vec3 pos, osg::Vec4 rot);

private:
	std::map<int, RigidBody*> _rigidBodies;

	void init();
};

