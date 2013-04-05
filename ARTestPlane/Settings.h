/**
 * Settings.h
 * Created By: Michael Feist
 */

#ifndef SETTINGS_H
#define SETTINGS_H

namespace Settings {

	// Opens the properties file
	int open();

	// Client
	void getClientIPAddress(char *ip);
	
	// Server
	void getServerIPAddress(char *ip);
	void getConnectionType(int *type);
	void getCommandPort(int *port);
	void getDataPort(int *port);

	// Camera
	void getCameraRigidBodyID(int *id);
};

#endif // SETTINGS_H