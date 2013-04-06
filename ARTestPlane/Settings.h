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
		float rotationX;
		float rotationY;
		float rotationZ;
		float modelScale;
		int flipX;
		int flipY;
		int flipZ;
	} Model3D;

	// Opens the properties file
	int open();

	// Saves the given camera info to
	// the properties file
	void saveCameraInfo(float fov, float aspect, 
		float offsetX, float offsetY, float offsetZ);

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
	void getCameraOffsets(float *x, float *y, float *z);

	// Models
	int getNumberOfModels();
	Model3D* getModelAt(unsigned int index);
};

#endif // SETTINGS_H