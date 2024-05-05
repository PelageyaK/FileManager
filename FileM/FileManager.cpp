#include "FileManager.h"

void FileManager::Menu(Folder& folder)
{
    Folder* nowFolder = &folder;
    int chAct2, chAct3, chAct4;
    std::string selF;
    std::string nameFold;
    std::string nameFile;
    std::string newName;
    std::string text;
    Folder* sFolder = nullptr;
    File* sFile = nullptr;
    bool loop1 = true, loop2 = true, loop3 = true;

    while (loop1 == true)
    {
        system("cls");
        std::cout << "++++++++++++++++++++�������� ��������++++++++++++++++++++" << std::endl;
        openFolder(*nowFolder);
        std::cout << "�������� ����� ��� ���� (������� � ���) ��� ������� +, ����� �������� ����� ��� ����" << std::endl;

        std::cin >> selF;

        if (selF == "+")
        {
            std::cout << "��������:\n 1. �������� �����\n 2. �������� ����" << std::endl;

            std::cin >> chAct2;

            if (chAct2 == 1)
            {
                std::cout << "������� ��� ����� �����:" << std::endl;
                std::cin >> nameFold;
                
                if (checkName(nameFold) == false)
                {
                    Sleep(1000);
                    continue;
                }

                addFolder(nameFold, *nowFolder);
                continue;
            }
            else if (chAct2 == 2)
            {
                std::cout << "������� ��� ������ ����� (c .txt):" << std::endl;
                std::cin >> nameFile;

                if (checkName(nameFile) == false)
                {
                    Sleep(1000);
                    continue;
                }

                addFile(nameFile, *nowFolder);
                continue;
            }
            else
            {
                std::cout << "������! ������� ���������� �����" << std::endl;
                Sleep(1000);
                continue;
            }
        }
        else
        {
            FileSysObject* tempF = searchF(selF, *nowFolder);

            if (dynamic_cast<File*>(tempF))
            {
                sFile = dynamic_cast<File*>(tempF);
                std::cout << "������ ����: " << sFile->getNameFile() << std::endl;
            }
            else if (dynamic_cast<Folder*>(tempF))
            {
                sFolder = dynamic_cast<Folder*>(tempF);
                std::cout << "������� �����: " << sFolder->getNameFolder() << std::endl;
            }

            if (tempF == nullptr)
            {
                Sleep(1000);
                continue;
            }
        }
   
        if (sFolder != nullptr)
        {
            std::cout << "�������� ��������:" << std::endl;
            std::cout << "1. ������� �����\n" << "2. ������� �����\n" << "3. ������������� �����\n" << "4. �����\n" << "0. ��������� � ������ �����" << std::endl;
            std::cin >> chAct3;

            if (chAct3 < 0 || chAct3 > 4)
            {
                std::cout << "������! ������� ���������� �����" << std::endl;
                Sleep(1000);
                continue;
            }

            switch (chAct3)
            {
            case 1:
                openFolder(*sFolder);
                nowFolder = sFolder;
                Sleep(1000);
                continue;
            case 2:
                deleteFolder(*sFolder, *nowFolder);
                break;
            case 3:
                std::cout << "������� ����� ���:" << std::endl;
                std::cin >> newName;
                sFolder->renameFolder(newName, *sFolder);
                break;
            case 5:
                exit(1);
                break;
            case 0:
                continue;
            default:
                std::cout << "�������� �����!" << std::endl;
            }
        }
        else if ((sFile) != nullptr)
        {
            std::cout << "�������� ��������:" << std::endl;
            std::cout << "1. ������� ���� (������� ����������)\n" << "2. �������� � ����\n" << "3. ������� ����\n" << "4. ������������� ����\n" << "5. ������ ������ �����\n" << "6. �����\n" << "0. ��������� � ������ �����" << std::endl;
            std::cin >> chAct4;

            if (chAct4 < 0 || chAct4 > 6)
            {
                std::cout << "������! ������� ���������� �����" << std::endl;
                Sleep(1000);
                continue;
            }

            switch (chAct4)
            {
            case 1:
                sFile->openFile();
                Sleep(1000);
                break;
            case 2:
                std::cout << "������� �����, ������� ������ �������� � ����: " << std::endl;
                std::cin >> text;

                sFile->writeFile(text);
                std::cout << std::endl;
                break;
            case 3:
                deleteFile(*sFile, *nowFolder);
                break;
            case 4:
                std::cout << "������� ����� ���:" << std::endl;
                std::cin >> newName;
                sFile->renameFile(newName, *sFile);
                break;
            case 5:
                sFile->getSizeFile();
                Sleep(1000);
                break;
            case 6:
                exit(1);
            case 0:
                loop2 = false;
                continue;
            default:
                std::cout << "�������� �����!" << std::endl;
            }
            sFolder = nullptr;
            sFile = nullptr;
        }
    }
}

void FileManager::exploreFolders(const fs::path& folderPath, Folder& folder)
{
    for (const auto& entry : fs::directory_iterator(folderPath))
    {
        if (entry.is_regular_file())
        {
            folder.files_.push_back(File(entry.path().filename().string(), entry.path().string()));
        }
        else if (entry.is_directory())
        {
            Folder newFolder(entry.path().filename().string(), entry.path().string());
            folder.folders_.push_back(newFolder);
            exploreFolders(entry, folder.folders_.back());
        }
    }
}

FileSysObject* FileManager::searchF(const std::string& name, Folder& folder)
{
    auto folderResult = std::find_if(folder.folders_.begin(), folder.folders_.end(), [&](const Folder& folder)
    {
        return folder.getNameFolder() == name;
    });

    if (folderResult != folder.folders_.end())
        return &(*folderResult);

    auto fileResult = std::find_if(folder.files_.begin(), folder.files_.end(), [&](const File& file)
    {
        return file.getNameFile() == name;
    });

    if (fileResult != folder.files_.end())
        return &(*fileResult);

    std::cout << "����� ��� ����� � ������ " << name << " �� �������" << std::endl;
    return nullptr;
}

void FileManager::openFolder(const Folder& folder)
{
    std::cout << "���������� ����� " << folder.getNameFolder() << ":" << std::endl;

    for (const auto& file : folder.files_)
        std::cout << file.getNameFile() << " (����)" << std::endl;

    for (const auto& subfolder : folder.folders_)
        std::cout << subfolder.getNameFolder() << " (�����)" << std::endl;
}

void FileManager::addFolder(const std::string& folderName, Folder& folder)
{
    auto it = std::find_if(folder.folders_.begin(), folder.folders_.end(), [&](const Folder& folder)
    {
        return folder.getNameFolder() == folderName;
    });

    if (it != folder.folders_.end())
    {
        std::cout << "����� � ������ " << folderName << " ��� ���������� � ����� " << folder.getNameFolder() << std::endl;
        return;
    }

    Folder newFolder = folderName;
    fs::path parentFolderPath = folder.getPathFolder();
    fs::path newFolderPath = parentFolderPath / folderName;
    fs::create_directory(newFolderPath);
    folder.folders_.push_back(newFolder);
}

void FileManager::deleteFolder(Folder& folderToDelete, Folder& folder)
{
    auto it = std::find_if(folder.folders_.begin(), folder.folders_.end(), [&](const Folder& folder)
    {
        return &folder == &folderToDelete;
    });

    fs::path folderPath = it->getPathFolder();
    fs::remove_all(folderPath);
    folder.folders_.erase(it);
}

void FileManager::addFile(const std::string& fileName, Folder& folder)
{
    auto it = std::find_if(folder.files_.begin(), folder.files_.end(), [&](const File& file)
    {
        return file.getNameFile() == fileName;
    });

    if (it != folder.files_.end())
    {
        std::cout << "����� � ������ " << fileName << " ��� ���������� � ����� " << folder.getNameFolder() << std::endl;
        return;
    }

    File newFile(fileName);
    fs::path parentFolderPath = folder.getPathFolder();
    fs::path filePath = parentFolderPath / fileName;
    std::fstream newFileStream(filePath, std::ios::out);

    if (newFileStream.is_open())
    {
        newFileStream << "������� �����, ������� ������ �������� � ���� : " << std::endl;
        newFileStream.close();
    }

    folder.files_.push_back(newFile);
}

void FileManager::deleteFile(File& fileToDelete, Folder& folder)
{
    auto it = std::find_if(folder.files_.begin(), folder.files_.end(), [&](const File& file)
        {
            return &file == &fileToDelete;
        });
    fs::path filePath = it->getPathFile();
    fs::remove_all(filePath);
    folder.files_.erase(it);
}

bool FileManager::checkName(std::string name)
{
    std::regex regex("[<>:\"\\\\/+%!@|?*]");

    if (std::regex_search(name, regex))
    {
        std::cout << "������ �������� ����������� �������." << std::endl;
        return false;
    }
    else
        return true;
}