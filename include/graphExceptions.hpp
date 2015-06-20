/* Exceptions for Graph class */

#ifndef INCLUDED_GRAPH_EXCEPTIONS_HPP
#define INCLUDED_GRAPH_EXCEPTIONS_HPP

#include <exception>

class OpenFileFailureException : public std::exception {
  public:
    OpenFileFailureException(std::string file);
    const char* what() const throw();
  private:
    std::string m_fileFailed;
};

class FullGraphException : public std::exception {
  public:
    const char* what() const throw();
};

class NonExistentVerticeException : public std::exception {
  public:
    NonExistentVerticeException(int place);
    const char* what() const throw();
  private:
    int m_place;
};

class NoMoreMarksException : public std::exception {
  public:
    const char* what() const throw();
};

#endif /* INCLUDED_GRAPH_EXCEPTIONS_HPP */