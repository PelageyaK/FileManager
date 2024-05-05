#include "File.h"

void File::openFile()
{
	std::fstream fin(path_);

	if (fin.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "Файл пуст" << std::endl;
		return;
	}

	std::string str;
	
	while (!fin.eof())
	{
		str = "";
		getline(fin, str);
		std::cout << str << std::endl;
	}
	fin.close();
}
void File::writeFile(const std::string& content)
{
	std::fstream fout(path_);
	fout << content;
	fout.close();
}
void File::getSizeFile()
{
	std::cout << std::filesystem::file_size(path_) << " байт" << std::endl;
}

void File::renameFile(const std::string& newName, File& file)
{
	std::cout << "Файл " << file.getNameFile();
	file.setNameFile(newName);

	fs::path oldFilePath = file.getPathFile();
	fs::path newFilePath = oldFilePath;
	newFilePath.replace_filename(newName);

	fs::rename(oldFilePath, newFilePath);
	std::cout << " переименован в " << newName << std::endl;
}