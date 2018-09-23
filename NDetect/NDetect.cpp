#include "pch.h"
#include "CaptureEngine.h"

//
// NOTE: remember to include WPCAP and HAVE_REMOTE among your
// preprocessor definitions.
//

CaptureEngine cap;

int main(int argc, char **argv)
{

	/*
		TODO
			Make Capture Packets through CaptureEngine Class
			Make run in a mode that displays only the interfaces
			Code a way to pass down the arguments of the program into the capture
				Select Interface from args
			Show captured packets as Source/Dest IPS, MACs, and Ports
			Show Data in ACSII

	*/

	cap.SelectInterface();
	// Capture Mode: 1 = Promiscuous, 0 = Normal
	// Promiscuous means that all packets, even those not destined for the
	// host computer are captured. This provides 
	cap.Capture(1);

}