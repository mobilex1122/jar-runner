#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <iostream>
#include <string>
#include <filesystem>
#include <string>

#include "Popup.h"
#include "Confirm.h"
#include "ConfigReader.h"

std::string getFileName(int argc, char* argv[])  {
    if (argc > 0) {
        // Get the full path of the executable
        std::string fullPath = argv[0];

        // Use std::filesystem to get the filename without extension
        std::filesystem::path path(fullPath);
        std::string executableName = path.stem().string(); // Get the name without extension

        return executableName;
    } else {
        return "";
    }

}

bool isJavaInstalled() {
    // Try to execute the command "java -version"
    // The output will be redirected to a temporary file
    std::cout << "$ java -version" << std::endl;

    int result = system("java -version");
    
    // Check the result of the command
    return (result == 0);
}

int ShowAndWaitPopoup(const std::string text, const std::string title) {
    Popup* p = new Popup(300, 100, text.c_str() , title.c_str());
    return Fl::run();
}

bool is_valid_filename(const std::string& filename) {
    // Check if the filename is empty
    if (filename.empty()) {
        return false;
    }

    // Check for path separators
    if (filename.find('/') != std::string::npos || 
        filename.find('\\') != std::string::npos) {
        return false; // Contains path separators
    }

    // Check for invalid characters (optional)
    for (char c : filename) {
        if (c == ':' || c == '*' || c == '?' || c == '"' || c == '<' || 
            c == '>' || c == '|' || c == ' ') {
            return false; // Contains invalid characters
        }
    }

    return true; // Valid filename
}

int main(int argc, char* argv[]) {


    std::cout << "Checking Java..." << std::endl;
    if (!isJavaInstalled()) {
        std::string text = "Missing Java!";
        #ifdef PLATFORM_WINDOWS
            text = "Missing Java.\nPlease download java from\n\"https://www.java.com/\"";
        #elif defined(PLATFORM_LINUX)
            text = "Missing Java.\nPlease download using your package manager.";
        #endif
        ShowAndWaitPopoup(text, "Missing Java");
        return 3;
    } else {
        std::cout << "Java Found!" << std::endl;
    }

    std::cout << "Loading Config..." << std::endl;

    if (!std::filesystem::exists("jr.cfg")) {
        ShowAndWaitPopoup("Missing Config File!!", "Critical Error");
        return 3;
    }


    ConfigReader* conf = new ConfigReader("jr.cfg");

    std::cout << "Config Values: " << std::endl;
    conf->printConfig();
    std::cout << std::endl;
    


    if (!conf->keyExists("file")) {
        ShowAndWaitPopoup("Missing Required Keys", "Critical Error");
        return 3;
    }

    if (conf->keyExists("java_args")) {
        Confirm* confr = new Confirm(300,130,"Java arguments set in config!\nRunning with config arguments might be dangerous.\nRun program?", "Warning");
        if (!confr->showAndWait()) {
            return 0;
        }
    }

    std::cout << "Config Loaded!" << std::endl;


    std::string jarFile = conf->getValue("file");
    std::string javaArgs = conf->getValue("java_args");


    if (!is_valid_filename(jarFile)) {
        ShowAndWaitPopoup("Invalid Filaname (Value: "+ jarFile +")", "Invallid Config");
        return 3;
    }


    if (jarFile.empty()) {
        ShowAndWaitPopoup("Error Getting Main Jar!","Error");
        return 1;
    }

    // Check if the JAR file exists
    if (!std::filesystem::exists(jarFile)) {
        ShowAndWaitPopoup("JAR file ("+ jarFile +") does not exist!", "Error");
        return 2;
    }

    

    
    std::string command = "java "+ javaArgs +" -jar " + jarFile;

    std::cout << "Running Command: " << command << std::endl << std::endl;


    int result = system(command.c_str());
    if (result != 0) {
        ShowAndWaitPopoup("Program exited with: " + std::to_string(result), "Java Error");
        return result;
    }
    return 0;
}


