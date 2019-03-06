//
// Created by Vyachealav MARTYNUIK on 2019-01-28.
//

#include <iostream>
#include "ErrorException.h"

ErrorException::ErrorException() {
    error = "hello";
}
ErrorException::ErrorException(ErrorException const &rhs) {
    *this = rhs;
}
ErrorException::~ErrorException() {}
ErrorException::ErrorException(std::string error) : error(error) {}
ErrorException & ErrorException::operator=(ErrorException const &rhs)
{
    this->error = rhs.getError();
    return *this;
}
const std::string &ErrorException::getError() const {
    return error;
}
