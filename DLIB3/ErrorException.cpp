//
// Created by Vyachealav MARTYNUIK on 2019-01-28.
//

#include <iostream>
#include "../inc/ErrorException.h"

ErrorException::ErrorException() {}
ErrorException::ErrorException(ErrorException const &rhs) {
    *this = rhs;
}
ErrorException::~ErrorException() {}
ErrorException::ErrorException(std::string error) : _error(error) {}
ErrorException & ErrorException::operator=(ErrorException const &rhs)
{
    this->_error = rhs.getError();
    return *this;
}
const std::string &ErrorException::getError() const {
    return _error;
}
