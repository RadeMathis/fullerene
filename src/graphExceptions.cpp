/*** EXCEPTIONS ***/

#include <graphExceptions.hpp>

OpenFileFailureException::OpenFileFailureException(std::string file) 
        : exception() , m_fileFailed(file) {}

const char* OpenFileFailureException::what() const throw(){
    return ("Don't know why, but we were unable to open file : " 
            + m_fileFailed).c_str();
}

FullGraphException::FullGraphException(int max_size)
        : exception() , m_max_size(max_size) {}

const char* FullGraphException::what() const throw(){
    std::string buff;
    buff.append("Sorry but this graph is only able to contain ");
    buff.append(std::to_string(m_max_size));
    buff.append(" vertices.");
    return buff.c_str();
}

// TODO : gerer le bordel des string en c++

NonExistentVerticeException::NonExistentVerticeException(int place)
        : exception() , m_place(place) {}

const char* NonExistentVerticeException::what() const throw(){
    return "There isn't any vertice in place number " + m_place;
}


const char* NoMoreMarksException::what() const throw(){
    return "All the marks have been reserved, you can't get more, sorry.";
}