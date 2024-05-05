#pragma once
#include "File.h"

namespace fs = std::filesystem;

class Folder : public FileSysObject
{
private:
    std::string name_;
    std::string path_;
public:
    std::vector<Folder> folders_;
    std::vector<File> files_;

    Folder() {}

    Folder(const std::string& name) : name_{ name } {}

    Folder(const std::string& name, const std::string& path) : name_{ name }, path_{ path } {}

    ~Folder() {}

    void setNameFolder(const std::string& name)
    {
        name_ = name;
    }

    std::string getNameFolder() const
    {
        return name_;
    }

    std::filesystem::path getPathFolder() const
    {
        return path_;
    }

    void renameFolder(const std::string& newName, Folder& folder)
    {
        std::cout << "Папка " << folder.getNameFolder();
        folder.setNameFolder(newName);

        fs::path oldFolderPath = folder.getPathFolder();
        fs::path newFolderPath = oldFolderPath;
        newFolderPath.replace_filename(newName);

        fs::rename(oldFolderPath, newFolderPath);
        std::cout << " переименована в " << newName << std::endl;
    }
};

