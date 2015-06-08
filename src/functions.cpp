#include <functions.hpp>

std::vector<std::string> decouperString(std::string const&str)
{
	std::vector<std::string> out;
	std::string buffer("");
	bool negligerEspace(true); //pour gerer les suites d'espace par exemple
	for(std::string::const_iterator iter = str.begin(); iter != str.end(); ++iter){
		if(*iter == ' ' && ! negligerEspace){
			out.push_back(buffer);
			buffer.erase();
			negligerEspace = true;
		}else{
			buffer += *iter;
			negligerEspace = false;
		}
	}
	out.push_back(buffer);
	return out;
}