#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>

class ConfigReader {
public:
    // Constructor that takes the filename
    ConfigReader(const std::string& filename) {
        loadConfig(filename);
    }

    // Function to get the value for a given key
    std::string getValue(const std::string& key) const {
        auto it = configMap.find(key);
        if (it != configMap.end()) {
            return it->second;
        }
        return ""; // Return empty string if key not found
    }

    bool keyExists(const std::string& key) const {
        return configMap.find(key) != configMap.end();
    }

    // Function to print all configurations
    void printConfig() const {
        for (const auto& pair : configMap) {
            std::cout << pair.first << " : " << pair.second << std::endl;
        }
    }

private:
    std::map<std::string, std::string> configMap; // To store configurations

    // Function to load the configuration from the file
    void loadConfig(const std::string& filename) {
        std::ifstream configFile(filename);
        if (!configFile.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(configFile, line)) {
            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos) {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
                configMap[key] = value;
            }
        }

        configFile.close();
    }
};

#endif // CONFIGREADER_H
