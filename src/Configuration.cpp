#include "Configuration.h"

Configuration loadConfigurationFromTxt(string configFilePath) {
    Configuration config;

    ifstream file(configFilePath);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file: " + configFilePath);
    }

    string key, value;
    while (file >> key >> value) {
        if (key == "outputImageName") {
            config.outputImageName = value + ".JPG";
        }
        else if (key == "tileWidth") {
            config.tileWidth = stoi(value);
        }
        else if (key == "tileHeight") {
            config.tileHeight = stoi(value);
        }
        else if (key == "outputImageWidth") {
            config.outputImageWidth = std::stoi(value);
        }
        else if (key == "outputImageHeight") {
            config.outputImageHeight = std::stoi(value);
        }
       

    }

    file.close();

    return config;
}