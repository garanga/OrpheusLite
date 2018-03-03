//-------------------------------------------------------
// Created on: Mar 18, 2017
//
// Author: Mikhail A. Volkov
// E-mail: Volkovmikhl@gmail.com
//-------------------------------------------------------

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

#include <string>
#include <exception>

namespace Symbol
{
    enum class ExceptionType;
}

namespace OrpheusException
{
    class Exception;
};

class OrpheusException::Exception : public std::exception
{
public:

    explicit
    Exception(Symbol::ExceptionType, std::string);

    const char*
    what() const noexcept final;

    void
    print() const noexcept;

    Symbol::ExceptionType
    getType() const;

private:

    Symbol::ExceptionType _type;
    std::string _message;
};


#endif /* EXCEPTIONS_HPP_ */
