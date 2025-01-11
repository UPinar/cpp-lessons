#ifndef FILE_H
#define FILE_H

#include <fstream>  // std::ofstream, std::ifstream
#include <string>

std::ofstream create_text_file(const std::string filename);
std::ifstream open_text_file(const std::string filename);
std::ofstream create_binary_file(const std::string filename);
std::ifstream open_binary_file(const std::string filename);

#endif // !FILE_H
