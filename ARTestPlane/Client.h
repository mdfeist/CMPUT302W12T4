#include <osg/AutoTransform>

namespace Client
{
	int initClient();
	int cleanClient();

	void addRigidBody(int id, osg::AutoTransform* transform);
};