/**
 * Client.cpp
 * Original code from NatNetSDK2.2 SampleClient.
 * Modified By: Michael Feist
 */

#include "Client.h"

#include <Windows.h>
#include <stdio.h>
#include <math.h>

#include <tchar.h>
#include <conio.h>

#include <osg/AutoTransform>

#include "NatNetTypes.h"
#include "NatNetClient.h"

#include "Settings.h"

#pragma warning( disable : 4996 )

// receives data from the server
void __cdecl DataHandler(sFrameOfMocapData* data, void* pUserData);
// receives NatNet error mesages
void __cdecl MessageHandler(int msgType, char* msg);
// Establish a NatNet Client connection
int initClient(ClientHandler** theClient, int iConnectionType);
// Resets the NatNet Client connection
void resetClient(ClientHandler** theClient);

unsigned int MyServersDataPort = 1511;
unsigned int MyServersCommandPort = 1510;

char szMyIPAddress[128] = "";
char szServerIPAddress[128] = "";

int Client::createClient(ClientHandler** theClient )
{
	int iResult;
    int iConnectionType = ConnectionType_Multicast;

	Settings::getConnectionType(&iConnectionType);
	Settings::getCommandPort(&MyServersCommandPort);
	Settings::getDataPort(&MyServersDataPort);
	Settings::getServerIPAddress(szServerIPAddress);
	Settings::getClientIPAddress(szMyIPAddress);

	printf("Command port of server: %d\n", MyServersCommandPort);
	printf("Data port of server: %d\n", MyServersDataPort);
    printf("Connecting to server at %s...\n", szServerIPAddress);
	printf("Connecting from %s...\n", szMyIPAddress);

    // Create NatNet Client
    iResult = initClient(theClient, iConnectionType);
    if(iResult != ErrorCode_OK)
    {
        printf("Error initializing client.  See log for details.  Exiting");
        return 1;
    }
    else
    {
        printf("Client initialized and ready.\n");
    }

#ifdef _DEBUG
	// send/receive test request
	printf("[SampleClient] Sending Test Request\n");
	void* response;
	int nBytes;
	iResult = (*theClient)->SendMessageAndWait("TestRequest", &response, &nBytes);
	if (iResult == ErrorCode_OK)
	{
		printf("[SampleClient] Received: %s", (char*)response);
	}

	// Retrieve Data Descriptions from server
	printf("\n\n[SampleClient] Requesting Data Descriptions...");
	sDataDescriptions* pDataDefs = NULL;
	int nBodies = (*theClient)->GetDataDescriptions(&pDataDefs);
	if(!pDataDefs)
	{
		printf("[SampleClient] Unable to retrieve Data Descriptions.");
		//return 1;
	}
	else
	{
        printf("[SampleClient] Received %d Data Descriptions:\n", pDataDefs->nDataDescriptions );
        for(int i=0; i < pDataDefs->nDataDescriptions; i++)
        {
            printf("Data Description # %d (type=%d)\n", i, pDataDefs->arrDataDescriptions[i].type);
            if(pDataDefs->arrDataDescriptions[i].type == Descriptor_MarkerSet)
            {
                // MarkerSet
                sMarkerSetDescription* pMS = pDataDefs->arrDataDescriptions[i].Data.MarkerSetDescription;
                printf("MarkerSet Name : %s\n", pMS->szName);
                for(int i=0; i < pMS->nMarkers; i++)
                    printf("%s\n", pMS->szMarkerNames[i]);

            }
            else if(pDataDefs->arrDataDescriptions[i].type == Descriptor_RigidBody)
            {
                // RigidBody
                sRigidBodyDescription* pRB = pDataDefs->arrDataDescriptions[i].Data.RigidBodyDescription;
                printf("RigidBody Name : %s\n", pRB->szName);
                printf("RigidBody ID : %d\n", pRB->ID);
                printf("RigidBody Parent ID : %d\n", pRB->parentID);
                printf("Parent Offset : %3.2f,%3.2f,%3.2f\n", pRB->offsetx, pRB->offsety, pRB->offsetz);
            }
            else if(pDataDefs->arrDataDescriptions[i].type == Descriptor_Skeleton)
            {
                // Skeleton
                sSkeletonDescription* pSK = pDataDefs->arrDataDescriptions[i].Data.SkeletonDescription;
                printf("Skeleton Name : %s\n", pSK->szName);
                printf("Skeleton ID : %d\n", pSK->skeletonID);
                printf("RigidBody (Bone) Count : %d\n", pSK->nRigidBodies);
                for(int j=0; j < pSK->nRigidBodies; j++)
                {
                    sRigidBodyDescription* pRB = &pSK->RigidBodies[j];
                    printf("  RigidBody Name : %s\n", pRB->szName);
                    printf("  RigidBody ID : %d\n", pRB->ID);
                    printf("  RigidBody Parent ID : %d\n", pRB->parentID);
                    printf("  Parent Offset : %3.2f,%3.2f,%3.2f\n", pRB->offsetx, pRB->offsety, pRB->offsetz);
                }
            }
            else
            {
                printf("Unknown data type.");
                // Unknown
            }
        }      
	}
#endif

	// Ready to receive marker stream!
	printf("\nClient is connected to server and listening for data...\n");

	return ErrorCode_OK;
}

int Client::deleteClient(ClientHandler** theClient)
{
	// Done - clean up.
	(*theClient)->Uninitialize();

	return ErrorCode_OK;
}


// Establish a NatNet Client connection
int initClient(ClientHandler** theClient, int iConnectionType)
{
    // release previous server
    if((*theClient) != 0)
    {
        (*theClient)->Uninitialize();
        delete (*theClient);
    }

    // create NatNet client
    (*theClient) = new ClientHandler(iConnectionType);

    // print version info
    unsigned char ver[4];
    (*theClient)->NatNetVersion(ver);
    printf("NatNet Sample Client (NatNet ver. %d.%d.%d.%d)\n", ver[0], ver[1], ver[2], ver[3]);

    // Set callback handlers
    (*theClient)->SetMessageCallback(MessageHandler);
    (*theClient)->SetVerbosityLevel(Verbosity_Debug);
    (*theClient)->SetDataCallback( DataHandler, (*theClient) );	// this function will receive data from the server

    // Init Client and connect to NatNet server
    // to use NatNet default port assigments
    //int retCode = (*theClient)->Initialize(szMyIPAddress, szServerIPAddress);
    // to use a different port for commands and/or data:
    int retCode = (*theClient)->Initialize(szMyIPAddress, szServerIPAddress, MyServersCommandPort, MyServersDataPort);
    if (retCode != ErrorCode_OK)
    {
        printf("Unable to connect to server.  Error code: %d. Exiting", retCode);
        return ErrorCode_Internal;
    }
    else
    {
        // print server info
        sServerDescription ServerDescription;
        memset(&ServerDescription, 0, sizeof(ServerDescription));
        (*theClient)->GetServerDescription(&ServerDescription);
        if(!ServerDescription.HostPresent)
        {
            printf("Unable to connect to server. Host not present. Exiting.");
            return 1;
        }
        printf("[SampleClient] Server application info:\n");
        printf("Application: %s (ver. %d.%d.%d.%d)\n", ServerDescription.szHostApp, ServerDescription.HostAppVersion[0],
            ServerDescription.HostAppVersion[1],ServerDescription.HostAppVersion[2],ServerDescription.HostAppVersion[3]);
        printf("NatNet Version: %d.%d.%d.%d\n", ServerDescription.NatNetVersion[0], ServerDescription.NatNetVersion[1],
            ServerDescription.NatNetVersion[2], ServerDescription.NatNetVersion[3]);
        printf("Client IP:%s\n", szMyIPAddress);
        printf("Server IP:%s\n", szServerIPAddress);
        printf("Server Name:%s\n\n", ServerDescription.szHostComputerName);
    }

    return ErrorCode_OK;

}

// DataHandler receives data from the server
void __cdecl DataHandler(sFrameOfMocapData* data, void* pUserData)
{
	ClientHandler* pClient = (ClientHandler*) pUserData;

	//printf("Received frame %d\n", data->iFrame);
	int i=0;

    // same system latency test
    float fThisTick = (float)GetTickCount();
    float fDiff = fThisTick - data->fLatency;
    double dDuration = fDiff;
    //printf("Latency (same system) (msecs): %3.2lf\n", dDuration);

	// Other Markers
	/*
	printf("Other Markers [Count=%d]\n", data->nOtherMarkers);
	for(i=0; i < data->nOtherMarkers; i++)
	{
		printf("Other Marker %d : %3.2f\t%3.2f\t%3.2f\n",
			i,
			data->OtherMarkers[i][0],
			data->OtherMarkers[i][1],
			data->OtherMarkers[i][2]);
	}
	*/
	//Cow
	//planeMatrix->setRotation(osg::Vec4(data->RigidBodies[0].qx, data->RigidBodies[0].qy, data->RigidBodies[0].qz, data->RigidBodies[0].qw));
	//planeMatrix->setPosition(osg::Vec3(data->RigidBodies[0].x, data->RigidBodies[0].y, data->RigidBodies[0].z));

	// Rigid Bodies
	//printf("Rigid Bodies [Count=%d]\n", data->nRigidBodies);
	for(i=0; i < data->nRigidBodies; i++)
	{
			
		//printf("Rigid Body [ID=%d  Error=%3.2f]\n", data->RigidBodies[i].ID, data->RigidBodies[i].MeanError);
		/*	
			printf("\tx\ty\tz\tqx\tqy\tqz\tqw\n");
			printf("\t%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\n",
				data->RigidBodies[i].x,
				data->RigidBodies[i].y,
				data->RigidBodies[i].z,
				data->RigidBodies[i].qx,
				data->RigidBodies[i].qy,
				data->RigidBodies[i].qz,
				data->RigidBodies[i].qw);
			*/
		if ( pClient->getRigidBody(data->RigidBodies[i].ID) )
		{
			
			pClient->transformRigidBody(data->RigidBodies[i].ID,
				osg::Vec3(data->RigidBodies[i].x, data->RigidBodies[i].z, data->RigidBodies[i].y),
				osg::Vec4(data->RigidBodies[i].qx, data->RigidBodies[i].qz, data->RigidBodies[i].qy, data->RigidBodies[i].qw));
		}

		/*
		printf("\tRigid body markers [Count=%d]\n", data->RigidBodies[i].nMarkers);
		for(int iMarker=0; iMarker < data->RigidBodies[i].nMarkers; iMarker++)
		{
            printf("\t\t");
            if(data->RigidBodies[i].MarkerIDs)
                printf("MarkerID:%d", data->RigidBodies[i].MarkerIDs[iMarker]);
            if(data->RigidBodies[i].MarkerSizes)
                printf("\tMarkerSize:%3.2f", data->RigidBodies[i].MarkerSizes[iMarker]);
            if(data->RigidBodies[i].Markers)
                printf("\tMarkerPos:%3.2f,%3.2f,%3.2f\n" ,
                    data->RigidBodies[i].Markers[iMarker][0],
                    data->RigidBodies[i].Markers[iMarker][1],
                    data->RigidBodies[i].Markers[iMarker][2]);
        }
		*/
	}

    // skeletons
    /*
	printf("Skeletons [Count=%d]\n", data->nSkeletons);
    for(i=0; i < data->nSkeletons; i++)
    {
        sSkeletonData skData = data->Skeletons[i];
        printf("Skeleton [ID=%d  Bone count=%d]\n", skData.skeletonID, skData.nRigidBodies);
        for(int j=0; j< skData.nRigidBodies; j++)
        {
            sRigidBodyData rbData = skData.RigidBodyData[j];
            printf("Bone %d\t%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\n",
                    rbData.ID, rbData.x, rbData.y, rbData.z, rbData.qx, rbData.qy, rbData.qz, rbData.qw );
    
            printf("\tRigid body markers [Count=%d]\n", rbData.nMarkers);
            for(int iMarker=0; iMarker < data->RigidBodies[i].nMarkers; iMarker++)
            {
                printf("\t\t");
                if(rbData.MarkerIDs)
                    printf("MarkerID:%d", rbData.MarkerIDs[iMarker]);
                if(rbData.MarkerSizes)
                    printf("\tMarkerSize:%3.2f", rbData.MarkerSizes[iMarker]);
                if(rbData.Markers)
                    printf("\tMarkerPos:%3.2f,%3.2f,%3.2f\n" ,
                    data->RigidBodies[i].Markers[iMarker][0],
                    data->RigidBodies[i].Markers[iMarker][1],
                    data->RigidBodies[i].Markers[iMarker][2]);
            }
        }
    }
	*/
}

// MessageHandler receives NatNet error/debug messages
void __cdecl MessageHandler(int msgType, char* msg)
{
	//printf("\n%s\n", msg);
}

void resetClient(ClientHandler** theClient)
{
	int iSuccess;

	printf("\n\nre-setting Client\n\n.");

	iSuccess = (*theClient)->Uninitialize();
	if(iSuccess != 0)
		printf("error un-initting Client\n");

	iSuccess = (*theClient)->Initialize(szMyIPAddress, szServerIPAddress);
	if(iSuccess != 0)
		printf("error re-initting Client\n");


}