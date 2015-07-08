/* Exceptions for Graph class */

#pragma once

#include <exception>
#include <string>

class OpenFileFailureException : public std::exception {
  public:
    OpenFileFailureException(std::string file);
    const char* what() const throw();
  private:
    std::string m_fileFailed;
};

class FullGraphException : public std::exception {
  public:
    FullGraphException(int max_size);
    const char* what() const throw();
  private:
    int m_max_size;
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