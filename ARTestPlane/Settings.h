/**
 * Settings.h
 * Created By: Michael Feist
 */

#ifndef SETTINGS_H
#define SETTINGS_H

namespace Settings {

	typedef struct Model3D {
		int rigidbody;
		char filePath[1024];
		char texturePath[1024];
	} Model3D;

	// Opens the properties file
	int open();

	// Client
	void getClientIPAddress(char *ip);
	
	// Server
	void getServerIPAddress(char *ip);
	void getConnectionType(int *type);
	void getCommandPort(unsigned int *port);
	void getDataPort(unsigned int *port);

	// Camera
	void getCameraRigidBodyID(int *id);
	void getCameraFOV(float *fov);
	void getCameraAspectRatio(float *ratio);

	// Models
	int getNumberOfModels();
	Model3D* getModelAt(unsigned int index);
};

#endif // SETTINGS_H