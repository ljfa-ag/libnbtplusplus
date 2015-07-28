/*
 * libnbt++ - A library for the Minecraft Named Binary Tag format.
 * Copyright (C) 2013, 2015  ljfa-ag
 *
 * This file is part of libnbt++.
 *
 * libnbt++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libnbt++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libnbt++.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "endian_str.h"
#include <climits>
#include <iostream>

static_assert(CHAR_BIT == 8, "Assuming that a byte has 8 bits");

namespace endian
{

void read_little(std::istream& is, uint8_t& x)
{
    is.get(reinterpret_cast<char&>(x));
}

void read_little(std::istream& is, uint16_t& x)
{
    uint8_t tmp[2];
    is.read(reinterpret_cast<char*>(tmp), 2);
    x =  uint16_t(tmp[0])
      | (uint16_t(tmp[1]) << 8);
}

void read_little(std::istream& is, uint32_t& x)
{
    uint8_t tmp[4];
    is.read(reinterpret_cast<char*>(tmp), 4);
    x =  uint32_t(tmp[0])
      | (uint32_t(tmp[1]) << 8)
      | (uint32_t(tmp[2]) << 16)
      | (uint32_t(tmp[3]) << 24);
}

void read_little(std::istream& is, uint64_t& x)
{
    uint8_t tmp[8];
    is.read(reinterpret_cast<char*>(tmp), 8);
    x =  uint64_t(tmp[0])
      | (uint64_t(tmp[1]) << 8)
      | (uint64_t(tmp[2]) << 16)
      | (uint64_t(tmp[3]) << 24)
      | (uint64_t(tmp[4]) << 32)
      | (uint64_t(tmp[5]) << 40)
      | (uint64_t(tmp[6]) << 48)
      | (uint64_t(tmp[7]) << 56);
}

void read_little(std::istream& is, int8_t & x) { read_little(is, reinterpret_cast<uint8_t &>(x)); }
void read_little(std::istream& is, int16_t& x) { read_little(is, reinterpret_cast<uint16_t&>(x)); }
void read_little(std::istream& is, int32_t& x) { read_little(is, reinterpret_cast<uint32_t&>(x)); }
void read_little(std::istream& is, int64_t& x) { read_little(is, reinterpret_cast<uint64_t&>(x)); }

//------------------------------------------------------------------------------

void read_big(std::istream& is, uint8_t& x)
{
    is.read(reinterpret_cast<char*>(&x), 1);
}

void read_big(std::istream& is, uint16_t& x)
{
    uint8_t tmp[2];
    is.read(reinterpret_cast<char*>(tmp), 2);
    x =  uint16_t(tmp[1])
      | (uint16_t(tmp[0]) << 8);
}

void read_big(std::istream& is, uint32_t& x)
{
    uint8_t tmp[4];
    is.read(reinterpret_cast<char*>(tmp), 4);
    x =  uint32_t(tmp[3])
      | (uint32_t(tmp[2]) << 8)
      | (uint32_t(tmp[1]) << 16)
      | (uint32_t(tmp[0]) << 24);
}

void read_big(std::istream& is, uint64_t& x)
{
    uint8_t tmp[8];
    is.read(reinterpret_cast<char*>(tmp), 8);
    x =  uint64_t(tmp[7])
      | (uint64_t(tmp[6]) << 8)
      | (uint64_t(tmp[5]) << 16)
      | (uint64_t(tmp[4]) << 24)
      | (uint64_t(tmp[3]) << 32)
      | (uint64_t(tmp[2]) << 40)
      | (uint64_t(tmp[1]) << 48)
      | (uint64_t(tmp[0]) << 56);
}

void read_big(std::istream& is, int8_t & x) { read_big(is, reinterpret_cast<uint8_t &>(x)); }
void read_big(std::istream& is, int16_t& x) { read_big(is, reinterpret_cast<uint16_t&>(x)); }
void read_big(std::istream& is, int32_t& x) { read_big(is, reinterpret_cast<uint32_t&>(x)); }
void read_big(std::istream& is, int64_t& x) { read_big(is, reinterpret_cast<uint64_t&>(x)); }

//------------------------------------------------------------------------------

void write_little(std::ostream& os, uint8_t x)
{
    os.put(x);
}

void write_little(std::ostream& os, uint16_t x)
{
    uint8_t tmp[2] {
         x & 0x00FF,
        (x & 0xFF00) >> 8};
    os.write(reinterpret_cast<const char*>(tmp), 2);
}

void write_little(std::ostream& os, uint32_t x)
{
    uint8_t tmp[4] {
         x & 0x000000FFUL,
        (x & 0x0000FF00UL) >> 8,
        (x & 0x00FF0000UL) >> 16,
        (x & 0xFF000000UL) >> 24};
    os.write(reinterpret_cast<const char*>(tmp), 4);
}

void write_little(std::ostream& os, uint64_t x)
{
    uint8_t tmp[8] {
         x & 0x00000000000000FFULL,
        (x & 0x000000000000FF00ULL) >> 8,
        (x & 0x0000000000FF0000ULL) >> 16,
        (x & 0x00000000FF000000ULL) >> 24,
        (x & 0x000000FF00000000ULL) >> 32,
        (x & 0x0000FF0000000000ULL) >> 40,
        (x & 0x00FF000000000000ULL) >> 48,
        (x & 0xFF00000000000000ULL) >> 56};
    os.write(reinterpret_cast<const char*>(tmp), 8);
}

void write_little(std::ostream& os, int8_t  x) { write_little(os, static_cast<uint8_t >(x)); }
void write_little(std::ostream& os, int16_t x) { write_little(os, static_cast<uint16_t>(x)); }
void write_little(std::ostream& os, int32_t x) { write_little(os, static_cast<uint32_t>(x)); }
void write_little(std::ostream& os, int64_t x) { write_little(os, static_cast<uint64_t>(x)); }

//------------------------------------------------------------------------------

void write_big(std::ostream& os, uint8_t x)
{
    os.put(x);
}

void write_big(std::ostream& os, uint16_t x)
{
    uint8_t tmp[2] {
        (x & 0xFF00) >> 8,
         x & 0x00FF};
    os.write(reinterpret_cast<const char*>(tmp), 2);
}

void write_big(std::ostream& os, uint32_t x)
{
    uint8_t tmp[4] {
        (x & 0xFF000000UL) >> 24,
        (x & 0x00FF0000UL) >> 16,
        (x & 0x0000FF00UL) >> 8,
         x & 0x000000FFUL};
    os.write(reinterpret_cast<const char*>(tmp), 4);
}

void write_big(std::ostream& os, uint64_t x)
{
    uint8_t tmp[8] {
        (x & 0xFF00000000000000ULL) >> 56,
        (x & 0x00FF000000000000ULL) >> 48,
        (x & 0x0000FF0000000000ULL) >> 40,
        (x & 0x000000FF00000000ULL) >> 32,
        (x & 0x00000000FF000000ULL) >> 24,
        (x & 0x0000000000FF0000ULL) >> 16,
        (x & 0x000000000000FF00ULL) >> 8,
         x & 0x00000000000000FFULL};
    os.write(reinterpret_cast<const char*>(tmp), 8);
}

void write_big(std::ostream& os, int8_t  x) { write_big(os, static_cast<uint8_t >(x)); }
void write_big(std::ostream& os, int16_t x) { write_big(os, static_cast<uint16_t>(x)); }
void write_big(std::ostream& os, int32_t x) { write_big(os, static_cast<uint32_t>(x)); }
void write_big(std::ostream& os, int64_t x) { write_big(os, static_cast<uint64_t>(x)); }

}
