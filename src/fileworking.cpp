#include <fstream>
#include <vector>
#include <string>

#include "macros.h"


/* SAVE INFO( slow :( ) */
int save(const char *filename, vec_str &lines)
{
	std::ofstream file(filename);
	for (const str line : lines)
		file << line << '\n';

	file.close();
	return 1;	
}

/* GET START INFO */
#define touch(filename) system(((str)"touch " + filename).c_str())
vec_str read_info(const char *filename)
{
	std::ifstream file(filename);
	
	/* HAVE A FILE */
	if (file) { 
		vec_str lines(0);
		for (str line; std::getline(file, line);)
			lines.push_back(line);

		file.close();
		return lines;
	}
	
	/* MAKE FILE */
	touch((str)filename);
	vec_str lines(1);
	return lines;
}
