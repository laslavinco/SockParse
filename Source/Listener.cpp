#include <iostream>
#include <string>
#include "Headers/Argparse.h"


int main(int argc, char* args[])
{	
	if (argc >= 2)
		return argparse(argc, args);
	else 
	{
		std::cout << "At least One Argument should be passed";
		return 0;
	}

}