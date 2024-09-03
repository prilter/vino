#include <fstream>
#include <vector>
#include <string>

#define vec_str std::vector<std::string>
#define str	std::string

/* SAVE INFO( slow :( ) */
int save(const char *filename, vec_str *lines)
{
	std::ofstream file(filename);
	for (const std::string line : *lines)
		file << line << '\n';

	file.close();
	return 1;	
}

/* GET START INFO */
#include <sys/stat.h>
int read_info(const char *filename, vec_str &lines)
{
	std::ifstream file(filename);
	if (!file) {
		//touch(filename);
		file.open(filename);
	}

	std::getline(file, lines[0]); /* ESCAPING NEW LINE AFTER EVERY START */
	
	str line;
	for (;std::getline(file, line);)
		lines.push_back(line);

	file.close();
	return 1;
}
