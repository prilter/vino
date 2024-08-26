#define save(filename, lines)								\
	std::ofstream file(filename);							\
	if (file.is_open()) {								\
		for (const auto &line : lines)						\
			file << line << '\n';						\
		file.close();								\
	}										\

void getfiletext(const char *filename, std::vector<std::string> &lines) {
	std::ifstream infile(filename);							
	if (!infile.is_open()) {						
		system(((std::string)"touch " + (std::string)filename).c_str());					
		getfiletext(filename, lines);					
	}

	getline(infile, lines[0]); /* ESCAPING NEW LINE AFTER EVERY START */

	std::string line;
	for (;getline(infile, line);)
		lines.push_back(line);

	infile.close();
}	
