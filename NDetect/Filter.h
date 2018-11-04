#pragma once
#include <map>
#include <fstream>
#include <iostream>
#include "pch.h"
#include "DTOs.h"
#include <string>




class Filter 
{
	// Target IP from the user
	std::string targetLocalIP = "";
	std::string targetDestIP = "";
	std::string targetLocalPort = "";
	std::string targetDestPort = "";


public:
	Filter();
	Filter(std::string targetLocalIP, std::string targetDestIP, std::string targetLocalPort, std::string targetDestPort);
	~Filter();

	// Set ters 
	void SetLocalTargetIP(std::string);
	void SetDestTargetIP(std::string);
	void SetLocalTargetPort(std::string);
	void SetDestTargetPort(std::string);

	// initialize map with port aliases
	void setMapPort();

	// Getters 
	std::string GetLocalTargetIP();
	std::string GetDestTargetIP();
	std::string GetLocalTargetPort();
	std::string GetDestTargetPort();

	// Method to show Target IP
	void ShowTargetIP();
};

