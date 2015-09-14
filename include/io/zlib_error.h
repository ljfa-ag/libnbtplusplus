#ifndef ZLIB_ERROR_H_INCLUDED
#define ZLIB_ERROR_H_INCLUDED

#include <stdexcept>

///Exception thrown in case zlib encounters a problem
class zlib_error : public std::runtime_error
{
public:
    const int errcode;

    explicit zlib_error(const char* what_arg, int errcode = -1):
        std::runtime_error(what_arg), errcode(errcode)
    {}
};

#endif // ZLIB_ERROR_H_INCLUDED
