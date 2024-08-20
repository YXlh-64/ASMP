#ifndef EXCEPTIONHEADER_H
#define EXCEPTIONHEADER_H
#include <exception>
#include <stdexcept>
using namespace std;

class InavalidArgumentsException : public exception
{
public:
    InavalidArgumentsException(const char *message) : message(message){};

    const char *what() const noexcept override
    {
        return message;
    }

private:
    const char *message;
};

//----------------------------------------------------------------------------------------------------------------------------


class OutOfRangeIDException : public InavalidArgumentsException
{
public:
    OutOfRangeIDException() : InavalidArgumentsException("Invalid farmer value. Valid values are between 0 and 1000000 ") {}
};

class NegativeValueException : public InavalidArgumentsException
{
public:
    NegativeValueException() : InavalidArgumentsException("Negative values not allowed.") {}
};

class InvalidPenaltyException : public InavalidArgumentsException
{
public:
    InvalidPenaltyException() : InavalidArgumentsException("Invalid penalty value. Valid values are 1, 2, or 3") {}
};

class OutOfRangeMonthException : public InavalidArgumentsException
{
public:
    OutOfRangeMonthException() : InavalidArgumentsException("Invalid month value. Valid values are between  1 and 12") {}
};



class OutOfRangeYearException : public InavalidArgumentsException
{
    public:
     OutOfRangeYearException() : InavalidArgumentsException("Invalid year value. Valid values are between  1990 and 2022"){};

};


#endif
