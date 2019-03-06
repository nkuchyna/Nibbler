//
// Created by Vyachealav MARTYNUIK on 2019-01-28.
//

#ifndef NIBLER_ERROREXCEPTION_H
#define NIBLER_ERROREXCEPTION_H

#include <exception>
#include <string>

class ErrorException : public std::exception{
public:
    ErrorException();
    ~ErrorException();
    ErrorException(std::string);
    const std::string &getError() const;
    ErrorException & operator=(ErrorException const &rhs);
    ErrorException(ErrorException const &rhs);

private:
    std::string error;
};

#endif //NIBLER_ERROREXCEPTION_H
