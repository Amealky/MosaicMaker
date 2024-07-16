#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Configuration {
	string outputImageName;
	int tileWidth;
	int tileHeight;
	int outputImageWidth;
	int outputImageHeight;
};

Configuration loadConfigurationFromTxt(string configFilePath);

#endif