#include <iostream>
#include "boost\program_options.hpp"
#include "Headers/ExecuteScript.h"

namespace po = boost::program_options;

int argparse(int ac, char** av)
{
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("script", "pass script to execute");

	po::variables_map vm;
	po::store(po::parse_command_line(ac, av, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		std::cout << desc << "\n";
		return 1;
	}
	else if (!(vm.count("script")) || (ac-1 != 2))
	{
		std::cerr << "invalid arguments passed, maybe you are forgetting to use -- \n";
		return 0;
	}

	std::string script_name = av[ac - 1];
	std::cout << "Executing script " << script_name << std::endl;
	return execute(script_name);
}	