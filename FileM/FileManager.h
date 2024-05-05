#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <regex>
#include "Windows.h"
#include "File.h"
#include "Folder.h"

namespace fs = std::filesystem;

class FileManager
{
public:

    FileManager()
    {
        fs::create_directories("Root");
    }

    ~FileManager() {}

    void Menu(Folder& folder);
    void exploreFolders(const fs::path& folderPath, Folder& folder);
    FileSysObject* searchF(const std::string& name, Folder& folder);
   
    void openFolder(const Folder& folder);
    void addFolder(const std::string& folderName, Folder& folder);
    void deleteFolder(Folder& folderToDelete, Folder& folder);

    void addFile(const std::string& fileName, Folder& folder);
    void deleteFile(File& fileToDelete, Folder& folder);
    bool checkName(std::string name);
};
