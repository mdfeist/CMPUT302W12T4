#include "Settings.h"
#include "pugixml.hpp"

#include "NatNetTypes.h"

#include <stdio.h>

char clientIPAddress[128] = "";
char serverIPAddress[128] = "";

int iConnectionType = ConnectionType_Multicast;

int iCommandPort = 1510;
int iDataPort = 1511;

int iCameraRigidBodyID = 65537;
float fCameraFOV = 27.0f;

int Settings::open() {

	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("Properties.xml");
	
	if (result.status) {
		printf("Load Settings Result: %s\n", result.description());
	} else {
		printf("Settings File Found\n");

		// Get Settings
		pugi::xml_node settings = doc.child("Settings");

		if (settings) {
			
			// Get Client Information
			pugi::xml_node client = settings.child("Client");

			if (client) {
				pugi::xml_attribute clientIP = client.attribute("IP");

				if (clientIP) {
					strncpy_s(clientIPAddress, clientIP.value(), 128);
					printf("Client IP: %s\n", clientIPAddress);
				} else {
					printf("No Client IP\n");
				}
			}

			// Get Sever Information
			pugi::xml_node server = settings.child("Server");

			if (server) {
				pugi::xml_attribute serverIP = server.attribute("IP");
				pugi::xml_attribute connectionType = server.attribute("ConnectionType");
				pugi::xml_attribute commandPort = server.attribute("CommandPort");
				pugi::xml_attribute dataPort = server.attribute("DataPort");

				// Get Server IP
				if (serverIP) {
					strncpy_s(serverIPAddress, serverIP.value(), 128);
					printf("Sever IP: %s\n", serverIPAddress);
				} else {
					printf("No Server IP\n");
				}

				// Get Server connection type
				if (connectionType) {
					if (!strncmp(connectionType.value(), "Multicast", 128)) {
						printf("Connection Type: Multicast\n");
						iConnectionType = ConnectionType_Multicast;
					} else if (!strncmp(connectionType.value(), "Unicast", 128)) {
						printf("Connection Type: Unicast\n");
						iConnectionType = ConnectionType_Unicast;
					} else {
						printf("Sever has undefined connection type, using default Multicast.\n");
						iConnectionType = ConnectionType_Multicast;
					}
				}

				// Get Command Port
				if (commandPort) {
					iCommandPort = commandPort.as_int();
					printf("Command Port: %d\n", iCommandPort);
				} else {
					printf("No Command Port\n");
				}

				// Get Data Port
				if (dataPort) {
					iDataPort = dataPort.as_int();
					printf("Data Port: %d\n", iDataPort);
				} else {
					printf("No Data Port\n");
				}
			}

		} else {
			printf("No Settings Attribute\n");
		}

		printf("\nCamera\n");

		// Get Camera Information
		pugi::xml_node camera = settings.child("Camera");

		if (camera) {
			pugi::xml_attribute cameraID = camera.attribute("RigidBodyID");
			pugi::xml_attribute cameraFOV = camera.attribute("FOV");

			if (cameraID) {
				iCameraRigidBodyID = cameraID.as_int();
				printf("Camera RigidBody ID: %d\n", iCameraRigidBodyID);
			} else {
				printf("No Camera RigidBody Defined\n");
			}

			if (cameraFOV) {
				fCameraFOV = cameraFOV.as_float(); 
			} else {
				printf("No Camera FOV Defined\n");
			}

		} else {
			printf("No Camera Defined\n");
		}

		printf("\n");
	}

	return 0;
}

void Settings::getClientIPAddress(char *ip) {
	strncpy_s(ip, 128, clientIPAddress, 128);
}

void Settings::getServerIPAddress(char *ip) {
	strncpy_s(ip, 128, serverIPAddress, 128);
}

void Settings::getConnectionType(int *type) {
	(*type) = iConnectionType;
}

void Settings::getDataPort(int *port) {
	(*port) = iDataPort;
}

void Settings::getCameraRigidBodyID(int *id) {
	(*id) = iCameraRigidBodyID;
}