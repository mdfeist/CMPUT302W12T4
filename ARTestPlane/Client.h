/**
 * Client.h
 * Original code from NatNetSDK2.2 SampleClient.
 * Modified By: Michael Feist
 */

#include "ClientHandler.h"

/*
 * The Client handles the start up process
 * of the NatNetSDK.
 */
namespace Client
{
	// Creates a new connection to the OptiTrack System
	int createClient(ClientHandler** theClient);
	// Cleans up the connection
	int deleteClient(ClientHandler** theClient);
};