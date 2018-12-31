#include <experimental/filesystem>
#include <iostream>
#include <array>
#include <cstdlib>
#include <cstdio>

namespace fs = std::experimental::filesystem;

std::string GetPythonPath()
{

	std::array<std::string, 2> paths = 
	{ "C:/Python27/python.exe", "C:/Program Files/Autodesk/Maya2016/bin/mayapy.exe" };
	// \\bglrstxtx001\storage\projects\commres\Library\Scripts\Python27\Python.exe
	return paths[0];
}

int execute(std::string script_path)
{
	std::string python_path = GetPythonPath();

	if (!(fs::exists(script_path)))
	{
		printf("given path %s does not exists\n", script_path.c_str());
		return 0;
	}
	
	std::string command = python_path + " " + script_path;
	
	for (char& char_ref : command) {
		if (char_ref == '\\')
			char_ref = '/';
	}

	std::cout << command.c_str() << std::endl;
	std::cin.get();
	//system(command.c_str());
	std::array<char, 128> buffer;
	std::string result;
	FILE* pipe = _popen(command.c_str(), "r");
	if (!pipe)
	{
		std::cerr << "Error occured while reading pipe" << std::endl;
		return 0;
	}
	while (fgets(buffer.data(), 128, pipe) != NULL)
	{
		std::cout << "Reading data " << std::endl;
		result += buffer.data();
	}
	auto returnCode = _pclose(pipe);
	std::cout << result << std::endl;
	std::cout << returnCode << std::endl;
	return 1;
}