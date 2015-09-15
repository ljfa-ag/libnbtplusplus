#ifndef ZLIB_ERROR_H_INCLUDED
#define ZLIB_ERROR_H_INCLUDED

#include <stdexcept>
#include <zlib.h>

///Exception thrown in case zlib encounters a problem
class zlib_error : public std::runtime_error
{
public:
    const int errcode;

    explicit zlib_error(const char* msg, int errcode):
        std::runtime_error(std::string(zError(errcode)) + ": " + msg),
        errcode(errcode)
    {}
};

#endif // ZLIB_ERROR_H_INCLUDED
