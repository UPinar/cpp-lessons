#include "../headers/file.h"
#include <fstream>    
// std::ofstream, std::ifstream, std::ios::binary
#include <string>
#include <stdexcept>  // std::runtime_error

// -----------------------------------------------------
// -----------------------------------------------------

std::ofstream create_text_file(const std::string filename)
{
	std::ofstream ofs{ filename };

	if (!ofs) {
		throw std::runtime_error{ filename + " can not be created." };
	}
	return ofs;
}
// stream classes are move only types. 
// because of "ofs" is a automatic duration object 
// move semantics or copy ellision(NRVO) will be happen.


// -----------------------------------------------------
// -----------------------------------------------------

std::ifstream open_text_file(const std::string filename)
{
	std::ifstream ifs{ filename };

	if (!ifs) {
		throw std::runtime_error{ filename + " can not be opened." };
	}
	return ifs;
}

// -----------------------------------------------------
// -----------------------------------------------------

std::ofstream create_binary_file(const std::string filename)
{
	std::ofstream ofs{ filename, std::ios::binary };

	if (!ofs) {
		throw std::runtime_error{ filename + " can not be created." };
	}
	return ofs;
}

// -----------------------------------------------------
// -----------------------------------------------------

std::ifstream open_binary_file(const std::string filename)
{
	std::ifstream ifs{ filename, std::ios::binary };

	if (!ifs) {
		throw std::runtime_error{ filename + " can not be opened." };
	}
	return ifs;
}

// -----------------------------------------------------
// -----------------------------------------------------