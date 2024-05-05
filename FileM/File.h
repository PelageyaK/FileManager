#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include "Windows.h"
#include "FileSysObject.h"

namespace fs = std::filesystem;

class File : public FileSysObject
{
private:
    std::string name_;
    std::filesystem::path path_;
    std::string content_;
public:
    File() {}

    File(const std::string& name) : name_{ name } {}

    File(const std::string& name, std::filesystem::path path) : name_{ name }, path_{ path }
    {
        path = std::filesystem::current_path() / name;
    }

    File(const std::string& name, std::filesystem::path path, const std::string& content) : name_{ name }, path_{ path }, content_{ content }
    {
        path = std::filesystem::current_path() / name;
    }

    ~File() {}

    void setNameFile(const std::string& name)
    {
        name_ = name;
    }

    std::string getNameFile() const
    {
        return name_;
    }

    std::filesystem::path getPathFile() const
    {
        return path_;
    }

    void openFile();
    void writeFile(const std::string& content);
    void renameFile(const std::string& newName, File& file);
    void getSizeFile();
};

