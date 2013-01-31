/*
  endian_str.cpp - Stream input and output of binary numbers with different
  byte orders.

  Copyright (C) 2013 ljfa-ag

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "endian_str.h"

#include <iostream>

namespace endian
{

void read_native(std::istream& str, uint8_t& x)
{ x = str.get(); }

void read_native(std::istream& str, uint16_t& x)
{ str.read(reinterpret_cast<char*>(&x), 2); }

void read_native(std::istream& str, uint32_t& x)
{ str.read(reinterpret_cast<char*>(&x), 4); }

void read_native(std::istream& str, uint64_t& x)
{ str.read(reinterpret_cast<char*>(&x), 8); }

void read_native(std::istream& str, int8_t& x)
{ x = str.get(); }

void read_native(std::istream& str, int16_t& x)
{ str.read(reinterpret_cast<char*>(&x), 2); }

void read_native(std::istream& str, int32_t& x)
{ str.read(reinterpret_cast<char*>(&x), 4); }

void read_native(std::istream& str, int64_t& x)
{ str.read(reinterpret_cast<char*>(&x), 8); }

void read_native(std::istream& str, float& x)
{ str.read(reinterpret_cast<char*>(&x), 4); }

void read_native(std::istream& str, double& x)
{ str.read(reinterpret_cast<char*>(&x), 8); }

//-----

void write_native(std::ostream& str, uint8_t x)
{ str.put(x); }

void write_native(std::ostream& str, uint16_t x)
{ str.write(reinterpret_cast<const char*>(&x), 2); }

void write_native(std::ostream& str, uint32_t x)
{ str.write(reinterpret_cast<const char*>(&x), 4); }

void write_native(std::ostream& str, uint64_t x)
{ str.write(reinterpret_cast<const char*>(&x), 8); }

void write_native(std::ostream& str, int8_t x)
{ str.put(x); }

void write_native(std::ostream& str, int16_t x)
{ str.write(reinterpret_cast<const char*>(&x), 2); }

void write_native(std::ostream& str, int32_t x)
{ str.write(reinterpret_cast<const char*>(&x), 4); }

void write_native(std::ostream& str, int64_t x)
{ str.write(reinterpret_cast<const char*>(&x), 8); }

void write_native(std::ostream& str, float x)
{ str.write(reinterpret_cast<const char*>(&x), 4); }

void write_native(std::ostream& str, double x)
{ str.write(reinterpret_cast<const char*>(&x), 8); }

//-----

//anonymous
namespace
{

unsigned int getb(std::istream& str)
{ return static_cast<unsigned int>(str.get()) & 0xffU; }

}

void read_reorder(std::istream& str, uint8_t& x)
{ x = getb(str); }

void read_reorder(std::istream& str, uint16_t& x)
{
    x  = getb(str) << 8;
    x |= getb(str);
}

void read_reorder(std::istream& str, uint32_t& x)
{
    x  = getb(str) << 24;
    x |= getb(str) << 16;
    x |= getb(str) << 8;
    x |= getb(str);
}

void read_reorder(std::istream& str, uint64_t& x)
{
    x  = uint64_t(getb(str)) << 56;
    x |= uint64_t(getb(str)) << 48;
    x |= uint64_t(getb(str)) << 40;
    x |= uint64_t(getb(str)) << 32;
    x |= uint64_t(getb(str)) << 24;
    x |= uint64_t(getb(str)) << 16;
    x |= uint64_t(getb(str)) << 8;
    x |= uint64_t(getb(str));
}

void read_reorder(std::istream& str, int8_t& x)
{ x = str.get(); }

void read_reorder(std::istream& str, int16_t& x)
{ read_reorder(str, reinterpret_cast<uint16_t&>(x)); }

void read_reorder(std::istream& str, int32_t& x)
{ read_reorder(str, reinterpret_cast<uint32_t&>(x)); }

void read_reorder(std::istream& str, int64_t& x)
{ read_reorder(str, reinterpret_cast<uint64_t&>(x)); }

void read_reorder(std::istream& str, float& x)
{ read_reorder(str, reinterpret_cast<uint32_t&>(x)); }

void read_reorder(std::istream& str, double& x)
{ read_reorder(str, reinterpret_cast<uint64_t&>(x)); }

//-----

void write_reorder(std::ostream& str, uint8_t x)
{ str.put(x); }

void write_reorder(std::ostream& str, uint16_t x)
{
    str.put((x & 0xff00U) >> 8);
    str.put( x & 0x00ffU);
}

void write_reorder(std::ostream& str, uint32_t x)
{
    str.put((x & 0xff000000UL) >> 24);
    str.put((x & 0x00ff0000UL) >> 16);
    str.put((x & 0x0000ff00UL) >> 8);
    str.put( x & 0x000000ffUL);
}

void write_reorder(std::ostream& str, uint64_t x)
{
    str.put((x & 0xff00000000000000ULL) >> 56);
    str.put((x & 0x00ff000000000000ULL) >> 48);
    str.put((x & 0x0000ff0000000000ULL) >> 40);
    str.put((x & 0x000000ff00000000ULL) >> 32);
    str.put((x & 0x00000000ff000000ULL) >> 24);
    str.put((x & 0x0000000000ff0000ULL) >> 16);
    str.put((x & 0x000000000000ff00ULL) >> 8);
    str.put( x & 0x00000000000000ffULL);
}

void write_reorder(std::ostream& str, int8_t x)
{ str.put(x); }

void write_reorder(std::ostream& str, int16_t x)
{ write_reorder(str, uint16_t(x)); }

void write_reorder(std::ostream& str, int32_t x)
{ write_reorder(str, uint32_t(x)); }

void write_reorder(std::ostream& str, int64_t x)
{ write_reorder(str, uint64_t(x)); }

void write_reorder(std::ostream& str, float x)
{
    union
    {
        float f;
        uint32_t i;
    } un { .f = x };
    write_reorder(str, un.i);
}

void write_reorder(std::ostream& str, double x)
{
    union
    {
        double d;
        uint64_t i;
    } un { .d = x };
    write_reorder(str, un.i);
}

}
