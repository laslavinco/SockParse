#include <experimental/filesystem>
#include <iostream>
#include <list>


bool PathExists(std::string path)
{
	bool res = std::experimental::filesystem::exists(path);
	return std::experimental::filesystem::exists(path);
}

std::string GetPythonPath()
{
	std::list<const char*> paths = 
	{ "C:/Python27/python.exe", "C:/Program Files/Autodesk/Maya2016/bin/mayapy.exe" };

	std::list<const char*>::iterator it = paths.begin();

	for (int i = 0; i < sizeof(paths); i++)
	{
		std::advance(it, i);
		std::string path = *it;
		if (PathExists(path))
			return path;
	}
	
}

void execute(const char* script_path)
{
	std::string python_path = GetPythonPath();
	std::string string_script_path = std::string(script_path);
	if (!(PathExists(script_path)))
	{
		printf("given path %s does not exists", script_path);
		throw std::invalid_argument("Give path does not exists");
	}
	
	const int total = sizeof(python_path) + sizeof(script_path);
	char* command = _strdup(python_path.c_str());

	for (int i = 0; i < sizeof(string_script_path); i++)
	{
		
		if (string_script_path[i] == '\\')
		{
			string_script_path[i] = '/';
		}
	}
	script_path = string_script_path.c_str();
	strcat(command, " ");
	strcat(command, script_path);

	std::string string_command = std::string(command);
	system(string_command.c_str());
	
}