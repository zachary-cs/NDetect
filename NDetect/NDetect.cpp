#include "pch.h"
#include "CaptureEngine.h"
//
// NOTE: remember to include WPCAP and HAVE_REMOTE among your
// preprocessor definitions.
//


// Handles all the Packet Capture Logic
CaptureEngine ce;

int main(int argc, char **argv)
{
	// Thread test integration

	/*
		TODO
			Code a way to pass down the arguments of the program into the capture
				Select Interface from args
			Show captured packets as Source/Dest IPS, MACs, and Ports
			Separate the CaptureEngine into its own thread
			Create a data structure to hold each packet

	*/

	// Displays the Interfaces available to capture packets.
	ce.SelectInterface();
	
	// CaptureEngine::Capture(int mode)
	// Mode: 1 = Promiscuous, 0 = Normal
	// Normal mode means only packets to and from the host machine are captured.
	// Promiscuous means that all packets, even those not destined for the
	// host computer are captured. This provides access to all packets that the
	// network card can see. 
	ce.Capture(0);

}