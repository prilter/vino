#include <string>
#include <cstdlib>
#include <cstdio>

#include "../macros.h"

/* TODO */
int f_term_getting_line(str &com)
{
	system("notify-send TODO");
	return 1;
	/*	size_t pos;
	str num_str;
	
	pos = com.find('f');	
	num_str = com.substr(pos + 1);
  num_str.erase(0, num_str.find_first_not_of(" \t")); * REMOVE SPACES AND TABS *

  if (num_str.empty())
		return 1; 

	* REMOVING AFTER DIGITS *
	for (int i = 0; i < num_str.length(); i++) {
		if (!std::isdigit(num_str[i])) {
			num_str[i] = '\0';
			break;
		}
	}

	fputs(num_str.c_str(), fopen("a.txt", "w"));
	return stoi(num_str);*/
}
