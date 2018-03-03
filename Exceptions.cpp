//-------------------------------------------------------
// Created on: Mar 18, 2017
//
// Author: Mikhail A. Volkov
// E-mail: Volkovmikhl@gmail.com
//-------------------------------------------------------

#include "SymbolicConstants.hpp"
#include <iostream>

#include "Exceptions.hpp"

OrpheusException::Exception::Exception(Symbol::ExceptionType type,
                                       std::string message       )
    : _type(type), _message(message)
{
}

const char*
OrpheusException::Exception::what() const noexcept
{
    return _message.c_str();
}

void
OrpheusException::Exception::print() const noexcept
{
    std::cout << _message << std::endl;
}

Symbol::ExceptionType
OrpheusException::Exception::getType() const
{
    return _type;
}
