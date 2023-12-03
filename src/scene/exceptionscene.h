#pragma once

#include <utils/baseexception/baseexception.h>

class NoFigureOnDesk: public BaseException
{
private:
    std::string _special_error_message = " (error type: no such figure with co-ords on desk)\n";
public:
    NoFigureOnDesk(std::string file, size_t line, std::string message = ""):
        BaseException(file, line)
    {
        std::strncat(_error_message, message.data(), sizeof(_error_message) - strlen(_error_message));
        std::strncat(_error_message, _special_error_message.data(), sizeof(_error_message) - strlen(_error_message));
    }
};

class FigureOnDesk: public BaseException
{
private:
    std::string _special_error_message = " (error type: figure with same co-ords on desk)\n";
public:
    FigureOnDesk(std::string file, size_t line, std::string message = ""):
        BaseException(file, line)
    {
        std::strncat(_error_message, message.data(), sizeof(_error_message) - strlen(_error_message));
        std::strncat(_error_message, _special_error_message.data(), sizeof(_error_message) - strlen(_error_message));
    }
};
