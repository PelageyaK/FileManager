#include "FileManager.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    FileManager fileManager;
    Folder rootFolder("Root", "Root");
    fileManager.exploreFolders(fs::path("Root"), rootFolder);
    fileManager.Menu(rootFolder);

    return 0;
}