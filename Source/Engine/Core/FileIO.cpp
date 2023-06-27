#include "FileIO.h"
//#include <filesystem>
//#include <string>


namespace neu {
	std::string getFilePath()
	{
		//return "Yo";
		return std::filesystem::current_path().string();
	}
}
