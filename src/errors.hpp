#ifndef ERRORS_HPP
#define ERRORS_HPP

#include "globals.hpp"

class Error
{
private:
    int pos_start, pos_end;
    std::string error_name, details;

public:
    Error(int ps, int pe, std::string en, std::string dt)
        : pos_start(ps), pos_end(pe), error_name(en), details(dt) {}
    void printErr();
};

class IlglCharErr : public Error
{
public:
    IlglCharErr(int ps, int pe, std::string en, std::string dt)
        : Error(ps, pe, en, dt) {}
};

class SyntaxErr : public Error
{
public:
    SyntaxErr(int ps, int pe, std::string en, std::string dt)
        : Error(ps, pe, en, dt) {}
};

#endif // ERRORS_HPP