#ifndef ERRORS_HPP
#define ERRORS_HPP

#include "globals.hpp"

class Error : public std::enable_shared_from_this<Error>
{
protected:
    int pos_start = -1;
    int pos_end = -1;
    std::string error_name, details;

public:
    Error() = default;
    Error(int ps, int pe, std::string en, std::string dt)
        : pos_start(ps), pos_end(pe), error_name(en), details(dt) {}
    virtual void printErr() const;
    virtual std::shared_ptr<Error> getErr()
    {
        if (pos_start == -1 && pos_end == -1)
            return nullptr;
        return shared_from_this();
    }
};

class IlglCharErr : public Error
{
public:
    IlglCharErr(int ps, int pe, std::string en, std::string dt)
        : Error(ps, pe, en, dt) {}
    std::shared_ptr<Error> getErr() override
    {
        if (pos_start == -1 && pos_end == -1)
            return nullptr;
        return shared_from_this();
    }
    void printErr() const override {
        std::cout<<"ILLEGAL CHAR ERROR"<<std::endl;
        Error::printErr();
    }
};

class SyntaxErr : public Error
{
public:
    SyntaxErr(int ps, int pe, std::string en, std::string dt)
        : Error(ps, pe, en, dt) {}
    std::shared_ptr<Error> getErr() override
    {
        if (pos_start == -1 && pos_end == -1)
            return nullptr;
        return shared_from_this();
    }
    void printErr() const override {
        std::cout<<"SYNTAX ERROR"<<std::endl;
        Error::printErr();
    }
};

class IlglCompare : public Error 
{
public:
    IlglCompare(int ps, int pe, std::string en, std::string dt)
        : Error(ps, pe, en, dt) {}    
    std::shared_ptr<Error> getErr() override
    {
        if (pos_start == -1 && pos_end == -1)
            return nullptr;
        return shared_from_this();
    }
    void printErr() const override {
        std::cout<<"CANNOTE COMPARE VALUES OF DIFFERENT TYPES"<<std::endl;
        Error::printErr();
    }
};

#endif // ERRORS_HPP