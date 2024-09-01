#include <fstream>
#include <vector>
#include <string>

#define vec_str std::vector<std::string>
#define str	std::string

/* GET START INFO */
int read_info(const char *filename, vec_str &lines)
{
	std::ifstream file(filename);
	if (!file) {
		system(((str)"touch " + (str)filename).c_str());
		file.open(filename);
	}

	std::getline(file, lines[0]); /* ESCAPING NEW LINE AFTER EVERY START */
	
	str line;
	for (;std::getline(file, line);)
		lines.push_back(line);

	return 1;
}

/* SAVE INFO */
int save(const char *filename, vec_str lines)
{
	std::ofstream file(filename);
	for (const auto &line : lines)
		file << line << '\n';

	return 1;
}
