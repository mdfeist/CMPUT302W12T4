#include "Client.h"

#include <Windows.h>
#include <stdio.h>
#include <math.h>

#include <tchar.h>
#include <conio.h>
//#include <winsock2.h>

#include "NatNetTypes.h"
#include "NatNetClient.h"

#include "ClientHandler.h"

#pragma warning( disable : 4996 )

void _WriteHeader(FILE* fp, sDataDescriptions* pBodyDefs);
void _WriteFrame(FILE* fp, sFrameOfMocapData* data);
void _WriteFooter(FILE* fp);
void __cdecl DataHandler(sFrameOfMocapData* data, void* pUserData);			// receives data from the server
void __cdecl MessageHandler(int msgType, char* msg);		// receives NatNet error mesages
void resetClient();
int CreateClient(int iConnectionType);

unsigned int MyServersDataPort = 3130;
unsigned int MyServersCommandPort = 3131;

ClientHandler* theClient;
FILE* fp;

char szMyIPAddress[128] = "";
char szServerIPAddress[128] = "";

int Client::initClient()
{
	int iResult;
    int iConnectionType = ConnectionType_Multicast;
    //int iConnectionType = ConnectionType_Unicast;
    
    // parse command line args
    strcpy(szServerIPAddress, "");		// not specified - assume server is local machine
    printf("Connecting to server at LocalMachine\n");

    strcpy(szMyIPAddress, "");		// not specified - assume server is local machine
    printf("Connecting from LocalMachine...\n");

    // Create NatNet Client
    iResult = CreateClient(iConnectionType);
    if(iResult != ErrorCode_OK)
    {
        printf("Error initializing client.  See log for details.  Exiting");
        return 1;
    }
    else
    {
        printf("Client initialized and ready.\n");
    }


	// send/receive test request
	printf("[SampleClient] Sending Test Request\n");
	void* response;
	int nBytes;
	iResult = theClient->SendMessageAndWait("TestRequest", &response, &nBytes);
	if (iResult == ErrorCode_OK)
	{
		printf("[SampleClient] Received: %s", (char*)response);
	}

	// Retrieve Data Descriptions from server
	printf("\n\n[SampleClient] Requesting Data Descriptions...");
	sDataDescriptions* pDataDefs = NULL;
	int nBodies = theClient->GetDataDescriptions(&pDataDefs);
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

	
	// Create data file for writing received stream into
	char szFile[MAX_PATH];
	char szFolder[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szFolder);
	
	sprintf(szFile, "%s\\Client-output.pts",szFolder);
		
	fp = fopen(szFile, "w");
	if(!fp)
	{
		printf("error opening output file %s.  Exiting.", szFile);
		exit(1);
	}
	if(pDataDefs)
		_WriteHeader(fp, pDataDefs);

	// Ready to receive marker stream!
	printf("\nClient is connected to server and listening for data...\n");

	return ErrorCode_OK;
}

int Client::cleanClient()
{
	// Done - clean up.
	theClient->Uninitialize();
	_WriteFooter(fp);
	fclose(fp);

	return ErrorCode_OK;
}


// Establish a NatNet Client connection
int CreateClient(int iConnectionType)
{
    // release previous server
    if(theClient)
    {
        theClient->Uninitialize();
        delete theClient;
    }

    // create NatNet client
    theClient = new ClientHandler(iConnectionType);

    // [optional] use old multicast group
    //theClient->SetMulticastAddress("224.0.0.1");

    // print version info
    unsigned char ver[4];
    theClient->NatNetVersion(ver);
    printf("NatNet Sample Client (NatNet ver. %d.%d.%d.%d)\n", ver[0], ver[1], ver[2], ver[3]);

    // Set callback handlers
    theClient->SetMessageCallback(MessageHandler);
    theClient->SetVerbosityLevel(Verbosity_Debug);
    theClient->SetDataCallback( DataHandler, theClient );	// this function will receive data from the server

    // Init Client and connect to NatNet server
    // to use NatNet default port assigments
    int retCode = theClient->Initialize(szMyIPAddress, szServerIPAddress);
    // to use a different port for commands and/or data:
    //int retCode = theClient->Initialize(szMyIPAddress, szServerIPAddress, MyServersCommandPort, MyServersDataPort);
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
        theClient->GetServerDescription(&ServerDescription);
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
	if(fp)
		_WriteFrame(fp,data);
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
		if ( theClient->getRigidBodyTransformation(data->RigidBodies[i].ID) )
		{
			/*
			printf("Rigid Body [ID=%d  Error=%3.2f]\n", data->RigidBodies[i].ID, data->RigidBodies[i].MeanError);
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
			theClient->transformRigidBody(data->RigidBodies[i].ID,
				osg::Vec3(data->RigidBodies[i].x, data->RigidBodies[i].y, data->RigidBodies[i].z),
				osg::Vec4(data->RigidBodies[i].qx, data->RigidBodies[i].qy, data->RigidBodies[i].qz, data->RigidBodies[i].qw));
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

void Client::addRigidBody(int id, osg::AutoTransform* transform)
{
	theClient->addRigidBody(id, transform);
}

// MessageHandler receives NatNet error/debug messages
void __cdecl MessageHandler(int msgType, char* msg)
{
	printf("\n%s\n", msg);
}

/* File writing routines */
void _WriteHeader(FILE* fp, sDataDescriptions* pBodyDefs)
{
	int i=0;

    if(!pBodyDefs->arrDataDescriptions[0].type == Descriptor_MarkerSet)
        return;
        
	sMarkerSetDescription* pMS = pBodyDefs->arrDataDescriptions[0].Data.MarkerSetDescription;

	fprintf(fp, "<MarkerSet>\n\n");
	fprintf(fp, "<Name>\n%s\n</Name>\n\n", pMS->szName);

	fprintf(fp, "<Markers>\n");
	for(i=0; i < pMS->nMarkers; i++)
	{
		fprintf(fp, "%s\n", pMS->szMarkerNames[i]);
	}
	fprintf(fp, "</Markers>\n\n");

	fprintf(fp, "<Data>\n");
	fprintf(fp, "Frame#\t");
	for(i=0; i < pMS->nMarkers; i++)
	{
		fprintf(fp, "M%dX\tM%dY\tM%dZ\t", i, i, i);
	}
	fprintf(fp,"\n");

}

void _WriteFrame(FILE* fp, sFrameOfMocapData* data)
{
	fprintf(fp, "%d", data->iFrame);
	for(int i =0; i < data->MocapData->nMarkers; i++)
	{
		fprintf(fp, "\t%.5f\t%.5f\t%.5f", data->MocapData->Markers[i][0], data->MocapData->Markers[i][1], data->MocapData->Markers[i][2]);
	}
	fprintf(fp, "\n");
}

void _WriteFooter(FILE* fp)
{
	fprintf(fp, "</Data>\n\n");
	fprintf(fp, "</MarkerSet>\n");
}

void resetClient()
{
	int iSuccess;

	printf("\n\nre-setting Client\n\n.");

	iSuccess = theClient->Uninitialize();
	if(iSuccess != 0)
		printf("error un-initting Client\n");

	iSuccess = theClient->Initialize(szMyIPAddress, szServerIPAddress);
	if(iSuccess != 0)
		printf("error re-initting Client\n");


}