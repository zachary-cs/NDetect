#include "pch.h"
#include "CaptureEngine.h"
#include <string>

//
// NOTE: remember to include WPCAP and HAVE_REMOTE among your
// preprocessor definitions.
//


// Handles all the Packet Capture Logic
CaptureEngine captureEngine;

// Thread holder
std::thread programThreads[10];
int threadCount = 0;

// Mutual Exclusion
// Used to give one thread exclusive operation, which prevent code interleaving
std::mutex mux;

// Controls the "Every-Second" Print Thread 
bool continueSecondUpdate = true;

// Threaded function declaration.
void ThreadPrint();
// Ctrl-C handler declaration.
BOOL WINAPI CtrlHandler(DWORD fdwCtrlType);

// Holds taget IP
std::string targetIP="";

// temp choice target
std::string choice;




void JoinThreads() {

	// Wait for all threads to finish before proceeding.
	for (int i = 0; i < threadCount; i++)
	{
		// Threads may have been detached when CTRL+C was triggered.
		// Only join joinable threads.
		if (programThreads[i].joinable())
		{
			programThreads[i].join();
		}
	}

}


int main(int argc, char **argv)
{
	// Configures the program to handle CTRL+C and other events when focused on the console.
	SetConsoleCtrlHandler(CtrlHandler, true);

	// Displays the Interfaces available to capture packets.
	// Records the user choice
	captureEngine.SelectInterface();

	// Enter IP filter
	std::cout << "Do you want to enter an IP filter (Y/N)?\n";
	std::cin >> choice;
	if (choice == "Y" || choice == "y")
	{
		std::cout << "Target IP: \n";
		std::cin >> targetIP;
		//captureEngine.SetTargetIP(targetIP);
	}

	// Set the capture mode
	captureEngine.SetCaptureMode(0);

	// Set the Connection Timeout in Seconds
	captureEngine.SetTimeout(5);

	// Set the Console output mode
	captureEngine.SetConsoleMode(ConnectionsMade);

	// Set the Live Stream display
	// RawData = Show Packet Data
	// HeaderOnly = Show only the Packet Header
	captureEngine.SetLiveStreamDisplay(HeaderOnly);

	// Using &captureEngine as the object reference, start the CaptureEngine::Capture method.
	// The &CaptureEngine::Capture is a reference to the class method.
	// This threading example does not pass arguments.
	programThreads[threadCount++] = std::thread(&CaptureEngine::Capture, &captureEngine);

	// Testing threading with another local method.
	// programThreads[threadCount++] = std::thread(ThreadPrint);

	JoinThreads();

}
	
// Example of how to use the Packet data to generate messages
void ThreadPrint() 
{
	int secondsPassed = 1;
	int packetsCaptured = captureEngine.GetPacketList().size();
	int packetsPerSecond = 0;
	while(continueSecondUpdate)
	{
		// Lock the Mutex, meaning that other threads will give this thread exclusive execution while locked.
		mux.lock();
		packetsCaptured = captureEngine.GetPacketList().size(); 
		packetsPerSecond = ((packetsCaptured / secondsPassed) > 0) ? (packetsCaptured / secondsPassed) : 0;
		printf("\n\r %i Seconds have passed since we started capturing, and %i packets were captured at %d packets/sec. \n\n", secondsPassed, packetsCaptured, packetsPerSecond);
		// Unlock mutex, now all threads can operate besides each other.
		mux.unlock();
		Sleep(1000);
		secondsPassed++;
	}

}

/*
	Sourced from: https://docs.microsoft.com/en-us/windows/console/registering-a-control-handler-function
	Handles when CTRL+C and other events are pressed during execution.
*/
BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
		// Handle the CTRL-C signal. 
	case CTRL_C_EVENT:
		// Lock this thread
		mux.lock();	
		// Stop the Capturing Output
		captureEngine.SetContinueCapturing(false);
		// Stop the Update message
		continueSecondUpdate = false;
		// Detach all threads so they can safely be deleted.
		for (int i = 0; i < threadCount; i++)
		{
			// Kill the other threads
			programThreads[i].detach();
		}
		std::cout << " \n\n CTRL+C pressed, exiting... \n\n\n";
		Sleep(1500);
		// Unlock and exit
		mux.unlock();		
		exit(0);

	case CTRL_CLOSE_EVENT:
		Beep(600, 200);
		printf("Ctrl-Close event\n\n");
		return TRUE;

		// Pass other signals to the next handler. 
	case CTRL_BREAK_EVENT:
		Beep(900, 200);
		printf("Ctrl-Break event\n\n");
		return TRUE;

	case CTRL_LOGOFF_EVENT:
		Beep(1000, 200);
		printf("Ctrl-Logoff event\n\n");
		return FALSE;

	case CTRL_SHUTDOWN_EVENT:
		Beep(750, 500);
		printf("Ctrl-Shutdown event\n\n");
		return FALSE;

	default:
		return FALSE;
	}
}
