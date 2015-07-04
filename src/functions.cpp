#include <functions.hpp>

std::vector<std::string> 
decouperString(std::string const& str)
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

std::vector<int> 
stringToVectorInt(std::string const& str)
{
    std::vector<int> out;
    for(std::string::const_iterator it = str.begin(); it != str.end(); ++it)
        out.push_back(*it);
    return out;
}

std::string 
vectorToString(std::vector<int> const& vect)
{
    std::string out = "";
    for(unsigned int i(0); i < vect.size(); ++i)
        out += vect[i];
    return out;
}

std::vector<int> 
arrayEgalsCycle(int a[][2], int b[][2], int sizeArrays)
{
    std::vector<int> out;
    for(int i(0); i < sizeArrays; ++i){
        bool sontIddentiques = true;
        for(int j(0); j < sizeArrays; ++j){
            if(a[j][1] != b[(j + i) % sizeArrays][1]){
                sontIddentiques = false;
                break;
            }
        }
        if(sontIddentiques){
            out.push_back(i);
        }
    }
    return out;
}

std::vector<int>
vectorEgalsCycle(std::vector<int> a, std::vector<int> b)
{
    std::vector<int> out;
    if(a.size() != b.size())
        return out;
    for(unsigned int i(0); i < a.size(); ++i){
        bool sontIddentiques = true;
        for(unsigned int j(0); j < a.size(); ++j){
            if(a[j] != b[(j+i) % b.size()]){
                sontIddentiques = false;
                break;
            }
        }
        if(sontIddentiques){
            out.push_back(i);
        }
    }
    return out;
}
