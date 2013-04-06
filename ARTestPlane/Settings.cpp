/**
* Settings.cpp
* Created By: Michael Feist
*/

#include "Settings.h"
#include "pugixml.hpp"

#include "NatNetTypes.h"

#include <stdio.h>
#include <vector>

// NatNetSDK
char clientIPAddress[128] = "192.168.1.31";
char serverIPAddress[128] = "192.168.1.30";

int iConnectionType = ConnectionType_Multicast;

int iCommandPort = 1510;
int iDataPort = 1511;

// Camera Info
int iCameraRigidBodyID = 65537;
float fCameraFOV = 27.0f;
float fCameraAspectRatio = 1.77777f;
float fCameraOffsetX = 0.f, fCameraOffsetY = 0.f, fCameraOffsetZ = 0.f;

// Holds Models
std::vector<Settings::Model3D*> modelArray;

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
			pugi::xml_attribute cameraAspectRatio = camera.attribute("AspectRatio");

			pugi::xml_attribute cameraOffsetX = camera.attribute("OffsetX");
			pugi::xml_attribute cameraOffsetY = camera.attribute("OffsetY");
			pugi::xml_attribute cameraOffsetZ = camera.attribute("OffsetZ");

			if (cameraID) {
				iCameraRigidBodyID = cameraID.as_int();
				printf("Camera RigidBody ID: %d\n", iCameraRigidBodyID);
			} else {
				printf("No Camera RigidBody Defined\n");
			}

			if (cameraFOV) {
				fCameraFOV = cameraFOV.as_float(); 
				printf("Camera FOV: %.2f\n", fCameraFOV);
			} else {
				printf("No Camera FOV Defined\n");
			}

			if (cameraAspectRatio) {
				fCameraAspectRatio = cameraAspectRatio.as_float();
				printf("Camera Aspect Ratio: %.2f\n", fCameraAspectRatio);
			} else {
				printf("No Camera Aspect Ratio Defined\n");
			}

			if (cameraOffsetX) {
				fCameraOffsetX = cameraOffsetX.as_float();
				printf("Camera Offset X: %.2f\n", fCameraOffsetX);
			} else {
				printf("No Camera OffsetX Defined\n");
			}

			if (cameraOffsetY) {
				fCameraOffsetY = cameraOffsetY.as_float();
				printf("Camera Offset Y: %.2f\n", fCameraOffsetY);
			} else {
				printf("No Camera OffsetY Defined\n");
			}

			if (cameraOffsetZ) {
				fCameraOffsetZ = cameraOffsetZ.as_float();
				printf("Camera Offset Z: %.2f\n", fCameraOffsetZ);
			} else {
				printf("No Camera OffsetZ Defined\n");
			}

		} else {
			printf("No Camera Defined\n");
		}

		printf("\nModels:\n");

		// Models
		pugi::xml_node models = settings.child("Models");

		for (pugi::xml_node model = models.child("Model"); model; model = model.next_sibling()) {
			pugi::xml_attribute modelID = model.attribute("RigidBodyID");
			pugi::xml_attribute modelFile = model.attribute("file");
			pugi::xml_attribute modelTexture = model.attribute("texture");

			Model3D *newModel = new Model3D;

			printf("Loading new Model:\n");

			if (modelID) {
				newModel->rigidbody = modelID.as_int();
				printf("\tRigidbody ID: %d\n", newModel->rigidbody);
			} else {
				printf("\tNo Rigidbody ID\n");
			}

			if (modelFile) {
				strncpy_s(newModel->filePath, modelFile.value(), 1024);
				printf("\tModel File Path: %s\n", newModel->filePath);
			} else {
				printf("\tNo File Path\n");
			}

			if (modelTexture) {
				strncpy_s(newModel->texturePath, modelTexture.value(), 1024);
				printf("\tModel Texture: %s\n", newModel->texturePath);
			} else {
				printf("\tNo Texture\n");
			}

			modelArray.push_back(newModel);
		}

		printf("\n");
	}

	return 0;
}

void Settings::saveCameraInfo(float fov, float aspect, 
	float offsetX, float offsetY, float offsetZ) {

	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("Properties.xml");

	if (result.status) {
		printf("Load Properties Result: %s\n", result.description());
	} else {
		printf("Properties File Found\n");

		// Get Settings
		pugi::xml_node settings = doc.child("Settings");

		if (settings) {

			// Get Camera Information
			pugi::xml_node camera = settings.child("Camera");

			if (camera) {
				pugi::xml_attribute cameraFOV = camera.attribute("FOV");
				pugi::xml_attribute cameraAspectRatio = camera.attribute("AspectRatio");

				pugi::xml_attribute cameraOffsetX = camera.attribute("OffsetX");
				pugi::xml_attribute cameraOffsetY = camera.attribute("OffsetY");
				pugi::xml_attribute cameraOffsetZ = camera.attribute("OffsetZ");


				if (cameraFOV) {
					cameraFOV.set_value(fov); 
				} else {
					printf("No Camera FOV Defined\n");
				}

				if (cameraAspectRatio) {
					cameraAspectRatio.set_value(aspect);
				} else {
					printf("No Camera Aspect Ratio Defined\n");
				}

				if (cameraOffsetX) {
					cameraOffsetX.set_value(offsetX);
				} else {
					printf("No Camera OffsetX Defined\n");
				}

				if (cameraOffsetY) {
					cameraOffsetY.set_value(offsetY);
				} else {
					printf("No Camera OffsetY Defined\n");
				}

				if (cameraOffsetZ) {
					cameraOffsetZ.set_value(offsetZ);
				} else {
					printf("No Camera OffsetZ Defined\n");
				}

				printf("Saving camera properties ...\n");
				doc.save_file("Properties.xml");
				printf("Camera properties saved\n");
			} else {
				printf("No Camera Defined in Properties.xml\n");
			}
		} else {
			printf("No Settings Defined in Properties.xml\n");
		}
	}
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

void Settings::getCommandPort(unsigned int *port) {
	(*port) = iCommandPort;
}

void Settings::getDataPort(unsigned int *port) {
	(*port) = iDataPort;
}

void Settings::getCameraRigidBodyID(int *id) {
	(*id) = iCameraRigidBodyID;
}

void Settings::getCameraFOV(float *fov) {
	(*fov) = fCameraFOV;
}

void Settings::getCameraAspectRatio(float *ratio) {
	(*ratio) = fCameraAspectRatio;
}

void Settings::getCameraOffsets(float *x, float *y, float *z) {
	(*x) = fCameraOffsetX;
	(*y) = fCameraOffsetY;
	(*z) = fCameraOffsetZ;
}

int Settings::getNumberOfModels() {
	return modelArray.size();
}

Settings::Model3D* Settings::getModelAt(unsigned int index) {
	if (index < modelArray.size())
		return modelArray.at(index);

	return 0;
}