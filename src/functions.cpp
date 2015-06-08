#include <functions.hpp>

std::vector<std::string> decouperString(std::string const& str)
{
	std::vector<std::string> out;
	std::string buffer("");
	bool negligerEspace(true); //pour gerer les suites d'espace par exemple
	for(std::string::const_iterator it = str.begin(); it != str.end(); ++it){
		if(*it == ' ' && ! negligerEspace){
			out.push_back(buffer);
			buffer.erase();
			negligerEspace = true;
		}else{
			buffer += *it;
			negligerEspace = false;
		}
	}
	out.push_back(buffer);
	return out;
}

std::std::vector<int> stringToVectorInt(std::string const& str)
{
	std::std::vector<int> out;
	for(std::string::const_iterator it = str.begin(); it != str.end(); ++it)
		out.push_back(*it);
	return out;
}

std::string vectorToString(std::vector<int> const& vect){
	std::string out = "";
	for(int i(0); i < vect.size(); ++i)
		out += vect[i];
	return out;
}